#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

void error(char *msg)
{
  fprintf(stderr, "%s: %s\n", msg, strerror(errno));
  exit(1);
}

int main(int argc, char *argv[])
{
  const char *PYTHON = "/usr/bin/python";
  const char *SCRIPT = "09/rssgossip.py";
  char *feeds[] = {
    "http://www.nytimes.com/services/xml/rss/nyt/Africa.xml",
    "http://www.nytimes.com/services/xml/rss/nyt/Americas.xml",
    "http://www.nytimes.com/services/xml/rss/nyt/MiddleEast.xml",
    "http://www.nytimes.com/services/xml/rss/nyt/Europe.xml",
    "http://www.nytimes.com/services/xml/rss/nyt/AsiaPacific.xml"
  };
  int   feed_count = 5;
  char *search_phrase = argv[1];
  FILE *f = fopen("stories.txt", "w");
  if (!f)
    error("Can't open stories.txt");

  /*will save off pids to wait on them in parallel later*/
  pid_t pids[feed_count];
  int i;
  for (i = 0; i < feed_count; i++) {
    char var[255];
    sprintf(var, "RSS_FEED=%s", feeds[i]);
    char *vars[] = {var, NULL};

    pids[i] = fork();
    if (pids[i] == -1)
      error("Can't fork process");

    if (pids[i] == 0) {
      if (dup2(fileno(f),1) == -1) {
        error("Can't redirect Standard Output");
      }
      if (execle(PYTHON, PYTHON, SCRIPT, search_phrase, NULL, vars) == -1) {
        error("Can't run script");
      }
    }
  }
  for (i = 0; i < feed_count; i++) {
    /*pid has non-zero value if we are in the parent process*/
    /*i.e., it's the value of the child's pid*/
    if (pids[i])  {
      int pid_status;
      if (waitpid(pids[i], &pid_status, 0) == -1)  {
        error("Error waiting for child process");
      }
    }
  }
  return 0;
}
