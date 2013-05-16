#ifndef H_ERROR
#define H_ERROR
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void invocation_error(char *program, char *usage);
void memory_error(char *file, unsigned int line, const char *func);
void exit_error(char *);
#endif
