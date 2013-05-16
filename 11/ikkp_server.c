#include <arpa/inet.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "error.h"
#include "signals.h"

int read_in(int socket, char *buf, int len);
int open_listener_socket(void);
int open_client_socket(void);
void bind_to_port(int socket, int port);
int say(int socket, char *s);
void handle_shutdown(int sig);

static int listener_d = 0;

void handle_shutdown(int sig)
{
  if (listener_d)
    close(listener_d);

  fprintf(stderr, "\n%d: Bye!\n", sig);
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

#define RESPONSE_MAX 128
#define PORT         30001
int main(void)
{
  char response[RESPONSE_MAX + 2] = {'\0'};
  int connect_d = 0, rc = 0, len;

  if (catch_signal(SIGINT, handle_shutdown) == -1)
    exit_error("Setting interrupt handler");

  listener_d = open_listener_socket();
  bind_to_port(listener_d, PORT);

  if (listen(listener_d, 10) == -1)
    exit_error("Can't listen");

  printf("Waiting for connection on port %d\n", PORT);

  for (;;) {
    connect_d = open_client_socket();
    rc = say(connect_d, "Internet Knock-Knock Protocal Server\r\nVersion 1.0\r\nKnock! Knock!\r\n");
    if (rc == -1) {
      close(connect_d);
      continue;
    }
    len = read_in(connect_d, response, RESPONSE_MAX + 2);
    if (strncasecmp(response, "Who's there?", len) != 0) {
      close(connect_d);
      continue;
    }
    rc = say(connect_d, "Oscar\r\n");
    if (rc == -1) {
      close(connect_d);
      continue;
    }
    len = read_in(connect_d, response, RESPONSE_MAX + 2);
    if (strncasecmp(response, "Oscar Who?", len) != 0) {
      close(connect_d);
      continue;
    }
    say(connect_d, "Oscar silly question, you get a silly answer\r\n");
    close(connect_d);
  }

  return 0;
}
