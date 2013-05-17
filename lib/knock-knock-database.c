#include "knock-knock-database.h"

struct jokes_type {
  size_t size;
  size_t next;
  Joke jokes[];  /* C99 flexible array member: must be last in struct */
};

KnockKnockDB load(char *filename)
{
  struct stat fs;
  if (stat(filename, &fs)) {
    exit_error(filename);
  }
  if (fs.st_size == 0) {
    fprintf(stderr, "Empty file: %s\n", filename);
    exit(EXIT_FAILURE);
  }
  FILE *relentless_stream_of_jokes;
  if (!(relentless_stream_of_jokes = fopen(filename, "r")))
    exit_error(filename);

  KnockKnockDB db = NULL; /* NULL so first realloc is like a malloc */
  char line[sizeof(Joke)], *l;
  bool read_error = false;
  Joke j;
  int field_index;
  size_t line_count;
  for (line_count = 0; (l = fgets(line, sizeof(Joke), relentless_stream_of_jokes)); line_count++) {
    if ((db = realloc(db, sizeof(db) + (sizeof(Joke) * (line_count + 1)))) == NULL)  {
      memory_error(__FILE__, __LINE__, __func__);
    }
    memset(&j, 0, sizeof(j));

    /* move past any initial whitespace */
    while (*l && isspace(*l)) l++;

    /* populate the name field 'who' */
    for (field_index = 0; field_index < MAX_WHO && *l && *l != '|';l++, field_index++) {
      j.who[field_index] = *l;
    }

    /* terminate 'who' field, at first non-word char */
    while (isspace(j.who[--field_index]))
      j.who[field_index] = '\0';

    /* step past delimiter */
    l++;

    /* move past any initial whitespace before the punchline */
    while (*l && isspace(*l)) l++;

    /* populate punchline field */
    for ( field_index = 0; (field_index < MAX_PUNCHLINE) && *l && *l != '\n'; field_index++, l++) {
      j.punchline[field_index] = *l;
    }
    /* terminate 'punchline' field, at first non-word char */
    while (isspace(j.punchline[--field_index]))
      j.punchline[field_index] = '\0';

    db->jokes[line_count] = j;
  }
  if (ferror(relentless_stream_of_jokes)) {
    perror(filename);
    read_error = true;
  }

  if (fclose(relentless_stream_of_jokes) == EOF || read_error) {
    destroy(db);
    exit_error(filename);
  }

  db->size = line_count;
  db->next = 0;
  return db;
}
bool has_got_a_million_of_them(KnockKnockDB db)
{
  return db->next < db->size;
}
void destroy(KnockKnockDB db)
{
  free(db);
}
Joke next_joke(KnockKnockDB db)
{
  return db->jokes[db->next++];
}
