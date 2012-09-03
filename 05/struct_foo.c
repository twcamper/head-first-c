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

typedef struct business {
  char *name;
  struct person CEO;
  struct business *parent;
  int year_founded;
  int employees;
} business;

typedef struct business publisher;

typedef struct book {
  char *title;
  author author;
  char *isbn;
  int  pages;
  int year;
  publisher publisher;
} book;

 /*we should pass a pointer, instead we are updating a copy*/
void bad_update(struct person p)
{
  p.age++;
  printf("bad_update: %i - %p\n", p.age, &p.age);
}

void update(struct person *p)
{
  printf("p %p\n", p);
  (*p).age++;
  printf("update: *p.age %i\n", (*p).age);
  p->age++;
  printf("update: p->age %i\n", p->age);
}
int main()
{
  struct person dude = {};
  dude.age = 21;
  dude.gender = 'M';
  struct name d_name = {"Ronnie", "Wayne", "Sykes"};
  dude.name = d_name;
  /*dude.name.first = "Ronnie";*/
  /*dude.name.last  = "Sykes";*/

  update(&dude);
   /*all the same address*/
  printf("main(): &dude.age(%p) (&dude.age)(%p)\n",  &dude.age, (&dude.age));
  printf("BEFORE: %i\n", dude.age);
  bad_update(dude);
  printf("AFTER: %i\n", dude.age);

  printf("The dude's name is %s %s, and he's %i years old.\n", dude.name.first, dude.name.last, dude.age);
  business malfeasigy = {"Malfeasigy, LLC", {{"Lucretia", "B", "DeVil"}, 38, 'F'}, NULL, 1381, 201020304};
  publisher Harcourt =
  {
    .CEO = {{"Tom", "T.", "Madoff"}, 12, 'M'},
    .year_founded = 1921,
    .name = "Harcourt, Brace, Javonovich, Inc.",
    .parent = &malfeasigy,
    .employees = 48
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

  printf("Please read \"%s,\" by %s %s %s,\n (published by %s a %s company. CEO %s %s %s who is a %i year old %c)\n",
      Schneurmanns.title, Schneurmanns.author.name.first, Schneurmanns.author.name.middle, Schneurmanns.author.name.last,
      Schneurmanns.publisher.name, Schneurmanns.publisher.parent->name,
      Schneurmanns.publisher.CEO.name.first, Schneurmanns.publisher.CEO.name.middle, Schneurmanns.publisher.CEO.name.last,
      Schneurmanns.publisher.CEO.age, Schneurmanns.publisher.CEO.gender);
  return 0;
}
