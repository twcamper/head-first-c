#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void error(char *msg)
{
  fprintf(stderr, "%s: %s\n", msg, strerror(errno));
  exit(1);
}

void open_url(char *url)
{
  const char *BROWSER = "www-browser";
  int pid_status;

  pid_t pid = fork();

  if (pid == -1)
    error("Can't fork process: open_url()");

  if (!pid) /* child process */  {
    if (execlp(BROWSER, BROWSER, url, NULL) == -1) {
      error(strdup(BROWSER));
    }
  }

  if (waitpid(pid, &pid_status, 0) == -1)
    error("Error waiting for child process");
}

int main(int argc, char *argv[])
{

  open_url(argv[1]);
  return 0;
}
