/* enable strdup() declaration in string.h */
#if defined(__linux__) || defined(__linux) || defined(__gnu_linux__)
  #define _BSD_SOURCE 1
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct island {
  char *name;
  char *opens;
  char *closes;
  struct island *next;
} island;

void display(island *start);
island* create(char *name);
void release(island *i);

int main()
{
  island *start   = NULL;
  island *current = NULL;
  island *next    = NULL;
  char name[80];

  for(; fgets(name, 80, stdin) != NULL; current = next) {
    next = create(name);
    if (start == NULL)
      start = next;
    if (current != NULL)
      current->next = next;
  }

  display(start);
  release(start);
  return 0;
}

island* create(char *name)
{
  island *i = malloc(sizeof(island));

  i->name   = strdup(name);
  i->opens  = "09:00";
  i->closes = "17:00";
  i->next   = NULL;

  return i;
}

void release(island *i)
{
  island *next = NULL;
  while (i != NULL) {
    next = i->next;
    free(i->name);
    free(i);
    i = next;
  }
}
void display(island *start)
{
  island *i = start;
  for (;i != NULL; i = i->next) {
    printf("Name: %s open: %s-%s\n", i->name, i->opens, i->closes);
  }
}
