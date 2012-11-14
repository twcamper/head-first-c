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

void open_urls(int url_count, char *urls[])
{
  char *COMMAND = "www-browser";
  int pid_status;

  /*command plus url list as arguments*/
  char *cmd_line[url_count + 2];

  cmd_line[0] = COMMAND;
  int i;
  for (i = 1; i <= url_count; i++) {
    cmd_line[i] = urls[i - 1];
  }
  cmd_line[i] = NULL;

  pid_t pid = fork();

  if (pid == -1)
    error("Can't fork process: open_url()");

  if (!pid) /* child process */  {
    if (execvp(COMMAND, cmd_line) == -1) {
      error(COMMAND);
    }
  }

  if (waitpid(pid, &pid_status, 0) == -1)
    error("Error waiting for child process");
}

int main(int argc, char *argv[])
{

  open_urls(argc - 1, argv + 1);
  return 0;
}
