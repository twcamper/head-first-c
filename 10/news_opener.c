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

  const char *PYTHON = "/usr/bin/python";
  const char *SCRIPT = "09/rssgossip.py";
  char *phrase = argv[1];
  char *vars[] = {"RSS_FEED=http://www.nytimes.com/services/xml/rss/nyt/Americas.xml", NULL};

  /*Create a pipe */
  int fd[2];
  if (pipe(fd) == -1)
    error("Can't create the pipe");

  /*Fork a child process*/
  pid_t pid = fork();
  if (pid == -1)
    error("Can't fork process");

  /*Child will be write-end of the pipe: will generate output by running python*/
  if (!pid) {
    /*stdout becomes write-end of pipe*/
    dup2(fd[1],1);
    /*closing read-end because we don't read over here*/
    close(fd[0]);

    if (execle(PYTHON, PYTHON, SCRIPT, "-u", phrase, NULL, vars) == -1)
      error("Can't run script");
  }

  /* Parent process will be read-end */

  /*stdin becomes read-end of pipe */
  dup2(fd[0], 0);
  /*closing write-end because all we do is read over here */
  close(fd[1]);

  /*will collect the urls from the python script at the other end of the pipe*/
  char *urls[255];
  char line[255];
  int url_count = 0;

  while (fgets(line,255,stdin)) {
    if (line[0] == '\t')  {
      urls[url_count] = &line[1];
      url_count++;
    }
  }

  if (url_count > 0)
    open_urls(url_count, urls);

  return 0;
}
