#ifndef KNOCK_KNOCK_DATABASE_H
#define KNOCK_KNOCK_DATABASE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <ctype.h>
#include "error.h"

#define MAX_WHO       128
#define MAX_PUNCHLINE 1024
typedef struct {
  char who[MAX_WHO];
  char punchline[MAX_PUNCHLINE + 2];
} Joke;

typedef struct jokes_type *KnockKnockDB;

KnockKnockDB load(char *);
bool has_got_a_million_of_them(KnockKnockDB);
Joke next_joke(KnockKnockDB);
void destroy(KnockKnockDB);

#endif
