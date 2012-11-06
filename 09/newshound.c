#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>

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

  pid_t pid;
  int i;
  for (i = 0; i < feed_count; i++) {
    char var[255];
    sprintf(var, "RSS_FEED=%s", feeds[i]);
    char *vars[] = {var, NULL};

    pid = fork();
    if (pid == -1)
      error("Can't fork process");

    if (pid == 0) {
      if (execle(PYTHON, PYTHON, SCRIPT, search_phrase, NULL, vars) == -1) {
        error("Can't run script");
      }
    } else
      printf("forked process %i: %s\n", pid, feeds[i]);
  }
  return 0;
}
