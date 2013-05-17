#if defined(__linux__) || defined(__linux) || defined(__gnu_linux__)
  #define _GNU_SOURCE 1
#endif
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "error.h"
#include "signals.h"
#include "knock-knock-database.h"

/* Macro Definitions */
#define RESPONSE_MAX  MAX_WHO

/* Global Variables */
static int listener_d = 0;

/* Type Definitions */
typedef enum {JOKE_COMPLETE, JOKE_REPROMPT, JOKE_ERROR} JokeStatus;

/* Function Prototypes */
int read_in(int socket, char *buf, int len);
int open_listener_socket(void);
int open_client_socket(void);
void bind_to_port(int socket, int port);
int say(int socket, char *s);
void handle_shutdown(int sig);
JokeStatus tell_joke(int, Joke);

/* Function Defintions */
void log_error(char *s, unsigned int line)
{
  fprintf(stderr, "IKKP error: %s: %d\n", s, line);
}
JokeStatus tell_joke(int client_d, Joke joke)
{
  int len;
  char name[strlen(joke.who) + 2];
  char response[RESPONSE_MAX + 2] = {'\0'};
  char expected_response[RESPONSE_MAX + 2] = {'\0'};
  char nudge[strlen(joke.who) + 25];

  if (say(client_d, "\r\nKnock! Knock!\r\n") == -1) {
    log_error("say", __LINE__);
    return JOKE_ERROR;
  }

  len = read_in(client_d, response, RESPONSE_MAX + 2);
  if (strncasecmp(response, "Who's there?", len) != 0) {
    if (say(client_d, "You should say 'Who's there?'\r\n") == -1) {
      log_error("say", __LINE__);
      return JOKE_ERROR;
    }
    return JOKE_REPROMPT;
  }

  strcpy(name, joke.who);
  strcat(name, "\r\n");
  if (say(client_d, name) == -1)
    return JOKE_ERROR;

  strcpy(expected_response, joke.who);
  strcat(expected_response, " Who?");
  len = read_in(client_d, response, RESPONSE_MAX + 2);
  if (strncasecmp(response, expected_response, len) != 0) {
    sprintf(nudge, "You should say '%s who?'\r\n", joke.who);
    if (say(client_d, nudge) == -1) {
      log_error("say", __LINE__);
      return JOKE_ERROR;
    }
    return JOKE_REPROMPT;
  }
  strcat(joke.punchline, "\r\n");
  if (say(client_d, joke.punchline) == -1) {
    log_error("say", __LINE__);
    return JOKE_ERROR;
  }

  return JOKE_COMPLETE;
}

void handle_shutdown(int sig)
{
  if (listener_d)
    close(listener_d);

  fprintf(stderr, "\n%d: That's All Folks!\n", sig);
  exit(EXIT_SUCCESS);
}

int open_listener_socket(void)
{
  int s = socket(PF_INET, SOCK_STREAM, 0);
  if (s == -1)
    exit_error("Can't open listener socket");

  return s;
}
int open_client_socket(void)
{
  static struct sockaddr_storage client_address;
  static unsigned int address_size = sizeof(client_address);
  int s;
  if ((s = accept(listener_d, (struct sockaddr *)&client_address, &address_size)) == -1)
    exit_error("Can't open client socket");

  return s;
}
void bind_to_port(int socket, int port)
{
  struct sockaddr_in name;
  name.sin_family = PF_INET;
  name.sin_port = (in_port_t)htons(port);
  name.sin_addr.s_addr = htonl(INADDR_ANY);
  int reuse = 1;
  if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int)) == -1)
    exit_error("Can't set the 'reuse' option on the socket");
  if (bind(socket, (struct sockaddr *)&name, sizeof(name)) == -1)
    exit_error("Can't bind to socket");
}
int say(int socket, char *s)
{
  int result = send(socket, s, strlen(s), 0);
  if (result == -1)
    fprintf(stderr, "%s: %s\n", "Error talking to the client", strerror(errno));
  return result;
}

int read_in(int socket, char *buf, int len)
{
  /* treat the socket stream as a regular IO stream, so we can do character IO */
  FILE *fp = fdopen(socket, "r");
  int i = 0, ch;

  /* eat any leading whitespace */
  while (isspace(ch = fgetc(fp)) && ch != EOF)
    ;
  if (ferror(fp))
    exit_error("fgetc");

  while (ch != '\n' && ch != EOF) {
    if (i < len)
      buf[i++] = ch;
    ch = fgetc(fp);
  }
  if (ferror(fp))
    exit_error("fgetc");

  /* terminate the string, eating any trailing whitespace */
  while (isspace(buf[--i])) {
    buf[i] = '\0';
  }

  return strlen(buf);
}

int main(int argc, char *argv[])
{
  int connect_d = 0, rc = 0;

  if (argc < 3)
    invocation_error(argv[0], "port data-file");

  int port = atoi(argv[1]);
  Joke j;
  KnockKnockDB db;

  if ((db= load(argv[2])) == NULL)
    exit_error("Database Who?");

  if (catch_signal(SIGINT, handle_shutdown) == -1)
    exit_error("Setting interrupt handler");

  listener_d = open_listener_socket();
  bind_to_port(listener_d, port);

  if (listen(listener_d, 10) == -1)
    exit_error("Can't listen");

  printf("Waiting for connection on port %d\n", port);

  for (;;) {
    connect_d = open_client_socket();
    if (say(connect_d, "Internet Knock-Knock Protocol Server\r\nVersion 1.0\r\n") == -1) {
      log_error("say", __LINE__);
      close(connect_d);
      continue;
    }
    do {
      if (rc == JOKE_COMPLETE)
        j = next_joke(db);
      rc = tell_joke(connect_d, j);
    } while (rc != JOKE_ERROR && has_got_a_million_of_them(db));

    close(connect_d);
  }

  destroy(db);

  return 0;
}
