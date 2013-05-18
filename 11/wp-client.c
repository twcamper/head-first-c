#include "error.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

/* open socket by domain name rather than IP address */
int open_socket(char *host, char *port)
{
  struct addrinfo *res;
  struct addrinfo hints;
  int d_sock, c;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = PF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  if (getaddrinfo(host, port, &hints, &res) == -1)
    exit_error("Can't resolve the address");
  if (( d_sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1)
    exit_error("Can't open socket");

  c = connect(d_sock, res->ai_addr, res->ai_addrlen);
  freeaddrinfo(res);
  if (c == -1)
    exit_error("Can't connect to the socket");

  return d_sock;
}
int say(int socket, char *s)
{
  int result = send(socket, s, strlen(s), 0);
  if (result == -1)
    perror("Can't talk to the server");

  return result;
}

int main(int argc, char *argv[])
{
  int d_sock, bytes_received;
  char buf[255], rec[256];

  if (argc < 2)
    invocation_error(argv[0], "[page name]");

  /* connect to server */
  d_sock = open_socket("en.wikipedia.org", "80");

  /* request the resource */
  sprintf(buf, "GET /wiki/%s http/1.1\r\n", argv[1]);
  say(d_sock, buf);

  /* send host name and required blank line */
  say(d_sock, "Host: en.wikipedia.org\r\n\r\n");

  /* display page on stdout in 255 byte chunks */
  bytes_received = recv(d_sock, rec, 255, 0);
  while (bytes_received) {
    if (bytes_received == EOF)
      exit_error("can't read from server");

    rec[bytes_received] = '\0';
    printf("%s", rec);
    bytes_received = recv(d_sock, rec, 255, 0);
  }
  close(d_sock);

  return 0;
}
