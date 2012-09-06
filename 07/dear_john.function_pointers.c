#include <stdio.h>

enum response_type {DUMP, SECOND_CHANCE, MARRIAGE};
typedef struct {
  char *name;
  enum response_type type;
} response;

void salutation(char *name)
{
  printf("Dear %s,\n", name);
}
void dump(response r)
{
  salutation(r.name);
  puts("Unfortunately your last date contacted us to\nsay that they will not be seeing you again.");
}
void second_chance(response r)
{
  salutation(r.name);
  puts("Good news: your last date has asked us to\narrange another meeting.  Please call ASAP.");
}
void marriage(response r)
{
  salutation(r.name);
  puts("Congratulations! Your last date has contacted\nus with a proposal of marriage.");
}

int main()
{
  response r[] = {
    {"Mike", DUMP}, {"Luis", SECOND_CHANCE}, {"Matt", SECOND_CHANCE}, {"William", MARRIAGE}
  };
  void (*replies[])(response) = {dump, second_chance, marriage};

  for (int i = 0; i < 4; i++)  {
    (replies[r[i].type])(r[i]);
  }
  return 0;
}
