#ifndef H_SIGNALS
#define H_SIGNALS
#if defined(__linux__) || defined(__linux) || defined(__gnu_linux__)
  #define _GNU_SOURCE 1
#endif
#include <signal.h>
#include <stdlib.h>

int catch_signal(int, void(*)(int));

#endif
