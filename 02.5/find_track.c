#include <stdio.h>
#include <string.h>

char *tracks[] = {
    "I left my heart at Harvard Med School",
    "Newark, Newark, a wonderful town",
    "Dancing with a Dork",
    "From here to maternity",
    "The girl from Iwo Jima"
};

void find_track(char search_for[])
{
  int i;
  for (i = 0; i < 5; i++)  {  // c99 allows inline int declaration
    if (strstr(tracks[i], search_for))
      printf("Track %i: '%s'\n", i, tracks[i]);
  }
}

int main()
{
  char search_for[80];
  printf("Search for: ");
  /*fgets(search_for, 80, stdin); // returns \n so the strstr() search fails*/
  scanf("%79s", search_for);
  find_track(search_for);
  return 0;
}
