#include <stdio.h>

int main() 
{
  char cards[] = "JQK";
  char *fernt = "fernt";

  char a_card = cards[2];

  fernt = cards + 1;

  cards[2] = cards[1];
  cards[1] = cards[0];
  cards[0] = cards[2];
  cards[2] = cards[1];
  cards[1] = a_card;

  puts(fernt);
  puts(cards);
  return 0;
}
