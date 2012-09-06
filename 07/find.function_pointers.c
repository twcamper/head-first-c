#include <stdio.h>
#include <string.h>

const int NUM_ADS = 7;
const char *ADS[] = {
  "William: SBM GSOH likes sports, TV, dining",
  "Matt: SWM NS likes arts, movies, theater",
  "Luis: SLM ND likes books, theater, art",
  "Mike: DWM DS likes trucks, sports, and bieber",
  "Peter: SAM likes chess, working out and art",
  "Josh: SJM likes sports, movies and theater",
  "Jed: DBM likes theater, books and dining"
};

void find(int (*match)(const char *s))
{

  puts("Search Results:\n");
  for (int i = 0; i < NUM_ADS; i++) {
    if (match(ADS[i])) {
      printf("%s\n", ADS[i]);
    }
  }
  puts("-----------------------------------------------------");
}

int sports_no_bieber(const char *s)
{
  return strstr(s, "sports") && !strstr(s, "bieber");
}

int sports_or_workout(const char *s)
{
  return strstr(s, "sports") || strstr(s, "working out");
}

int ns_theater(const char *s)
{
  return strstr(s, "NS") && strstr(s, "theater");
}

int arts_theater_or_dining(const char *s)
{
  return strstr(s, "arts") || strstr(s, "theater") || strstr(s, "dining");
}

int main()
{

  find(sports_no_bieber);
  find(sports_or_workout);
  find(ns_theater);
  find(arts_theater_or_dining);
  return 0;
}
