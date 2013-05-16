#ifndef H_SIGNALS
#define H_SIGNALS
#include <signal.h>
#include <stdlib.h>

int catch_signal(int, void(*)(int));

#endif
