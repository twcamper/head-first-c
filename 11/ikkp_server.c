#include <arpa/inet.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void error(char *msg);
int read_in(int socket, char *buf, int len);
int open_listener_socket(void);
int open_client_socket(void);
void bind_to_port(int socket, int port);
int say(int socket, char *s);
void handle_shutdown(int sig);

void error(char *msg)
{
  fprintf(stderr, "%s: %s\n", msg, strerror(errno));
  exit(EXIT_FAILURE);
}

static int listener_d = 0, connect_d = 0;

void handle_shutdown(int sig)
{
  if (listener_d)
    close(listener_d);

  if (connect_d)
    close(connect_d);

  fprintf(stderr, "Signal %d: Bye!\n", sig);
  exit(EXIT_SUCCESS);
}

int open_listener_socket(void)
{
  int s = socket(PF_INET, SOCK_STREAM, 0);
  if (s == -1)
    error("Can't open listener socket");

  return s;
}
int open_client_socket(void)
{
  static struct sockaddr_storage client_address;
  static unsigned int address_size = sizeof(client_address);
  int s;
  if ((s = accept(listener_d, (struct sockaddr *)&client_address, &address_size)) == -1)
    error("Can't open client socket");

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
    error("Can't set the 'reuse' option on the socket");
  if (bind(socket, (struct sockaddr *)&name, sizeof(name)) == -1)
    error("Can't bind to socket");
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
  int slen = len;
  int c = 0;
  buf[0] = '\0';

  while ((c = recv(socket, buf, slen, 0) > 0) && (buf[c-1] != '\n')) {
    buf += c; slen -= c;
  }
  if (c < 0)
    return c;

  /*replace the '\r'*/
  if (c > 0)
    buf[c-1] = '\0';

  return len - slen;
}

#define RESPONSE_MAX 128
int main(void)
{
  char response[RESPONSE_MAX + 2] = {'\0'};
  int rc = 0;
  listener_d = open_listener_socket();
  bind_to_port(listener_d, 30001);

  listen(listener_d, 10);
  puts("Waiting for connection");

  for (;;) {
    connect_d = open_client_socket();
    rc = say(connect_d, "Internet Knock-Knock Protocal Server\r\nVersion 1.0\r\nKnock! Knock!\r\n");
    if (rc == -1) {
      close(connect_d);
      continue;
    }
    rc = read_in(connect_d, response, RESPONSE_MAX + 2);
    if (strcmp(response, "Who's there?") != 0 || rc == 0) {
      close(connect_d);
      continue;
    }
    if (rc < 0)
      continue;
    rc = say(connect_d, "Oscar\r\n");
    if (rc == -1) {
      close(connect_d);
      continue;
    }
    rc = read_in(connect_d, response, RESPONSE_MAX + 2);
    if (strcmp(response, "Oscar who?") != 0 || rc == 0) {
      close(connect_d);
      continue;
    }
    say(connect_d, "Oscar silly question, you get a silly answer\r\n");
    close(connect_d);
  }

  return 0;
}
