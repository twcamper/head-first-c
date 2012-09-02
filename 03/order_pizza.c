#include <stdio.h>
/*#include <unistd.h>*/
// unistd.h does not declare optarg or optind as external, so we
// fail under -std=c99
#include <getopt.h>

int main(int argc, char *argv[])
{

  char *delivery = "";
  int thick      = 0;
  int ingredient_count = 0;
  char ch;

  while ((ch = getopt(argc, argv, "d:t")) != EOF)
  switch (ch) {
    case 'd':
      delivery = optarg;
      break;
    case 't':
      thick = 1;
      break;
    default:
      fprintf(stderr, "Unknown option: '%s'\n", optarg);
      return 1;
  }

  argc -= optind;
  argv += optind;

  if (thick)
    puts("Thick Crust");

  if (delivery[0])
    printf("To be delivered %s\n", delivery);

  puts("Ingredients:");

  for (ingredient_count = 0; ingredient_count < argc; ingredient_count++)
    puts(argv[ingredient_count]);
  return 0;
}
