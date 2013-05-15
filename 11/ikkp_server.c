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
int open_listener_socket();
void bind_to_port(int socket, int port);
int say(int socket, char *s);
void handle_shutdown(int sig);

void error(char *msg)
{
  fprintf(stderr, "%s: %s\n", msg, strerror(errno));
  exit(1);
}

int listener_d;

void handle_shutdown(int sig)
{
  if (listener_d)
    close(listener_d);

  fprintf(stderr, "Bye!\n");
  exit(0);
}

int open_listener_socket()
{
  int s = socket(PF_INET, SOCK_STREAM, 0);
  if (s == -1)
    error("Can't open socket");

  return 0;
}
void bind_to_port(int socket, int port)
{
  struct sockaddr_in name;
  name.sin_family = PF_INET;
  name.sin_port = (in_port_t)htons(30000);
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

int main()
{

  return 0;
}
