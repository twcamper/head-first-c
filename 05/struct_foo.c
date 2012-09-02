#include <stdio.h>

struct name {
  char *first;
  char *middle;
  char *last;
};
struct person {
  struct name name;
  int age;
  char gender;
};

typedef struct person author;

struct business {
  char *name;
  struct person CEO;
  char *corporate_overlord;
  int year_founded;
  int employees;
};

typedef struct business publisher;

typedef struct book {
  char *title;
  author author;
  char *isbn;
  int  pages;
  int year;
  publisher publisher;
} book;

int main()
{
  publisher Harcourt =
  {
    "Harcourt, Brace, Javonovich, Inc.",
    {"Tom", "T.", "Madoff"},
    "Malfeasigy, LLC",
    1921,
    48
  };
  book Schneurmanns =
  {
    "10,000 Flea Circus",
    {{"Edward", "G.", "Schneurmanns"}, 43, 'M'},
    "973-0123456789",
    373,
    2011,
    Harcourt
  };

  printf("Please read %s,\n by %s %s %s, published by %s (a %s company)\n",
      Schneurmanns.title, Schneurmanns.author.name.first, Schneurmanns.author.name.middle, Schneurmanns.author.name.last, Schneurmanns.publisher.name, Schneurmanns.publisher.corporate_overlord);
  return 0;
}
