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
void destroy(island *i);

int main()
{
  char name[80];

  fgets(name, 80, stdin);
  island *p_island_0 = create(name);
  fgets(name, 80, stdin);
  island *p_island_1 = create(name);
  p_island_0->next = p_island_1;

  display(p_island_0);

  destroy(p_island_0);
  destroy(p_island_1);
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

void destroy(island *i)
{
  free(i->name);
  free(i);
}
void display(island *start)
{
  island *i = start;
  for (;i != NULL; i = i->next) {
    printf("Name: %s open: %s-%s\n", i->name, i->opens, i->closes);
  }
}
