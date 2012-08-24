#include <stdio.h>
#include <stdlib.h>

int main()
{
  char card_name[3];
  int count = 0;

  while (card_name[0] != 'X') {
    puts("Enter the card name: ");
    scanf("%2s", card_name);

    int val = 0;
    switch (card_name[0]) {
      case 'A':
        val = 11;
        break;
      case 'J':
      case 'Q':
      case 'K':
        val = 10;
        break;
      case 'X':
        continue;
      default:
        val = atoi(card_name);
        if (val > 10) {
          printf("Error: I don't understand '%i'\n", val);
          continue;
        }
    }

    // check if the value is 3 to 6
    if (val > 2 && val < 7) count++;
    // Otherwise, check if the card was 10, J, Q, or K
    else if (val == 10) count--;
    printf("Current count: %i\n", count);
  }
  return 0;
}
