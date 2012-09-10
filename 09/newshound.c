#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
  const char *PYTHON = "/usr/bin/python";
  const char *SCRIPT = "09/rssgossip.py";
  char *feeds[] = {"http://www.nytimes.com/services/xml/rss/nyt/Africa.xml"};
  int   feed_count = 1;

  char *search_phrase = argv[1];

  for (int i = 0; i < feed_count; i++) {
    char var[255];
    sprintf(var, "RSS_FEED=%s", feeds[i]);
    char *vars[] = {var, NULL};
    if (execle(PYTHON, PYTHON, SCRIPT, search_phrase, NULL, vars) == -1) {
      fprintf(stderr, "Can't run script: %s\n", strerror(errno));
      return 1;
    }
  }
  return 0;
}
