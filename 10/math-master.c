#if defined(__linux__) || defined(__linux) || defined(__gnu_linux__)
  #define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

int score = 0;

void end_game(int sig)
{
  printf("\nFinal score: %i\n", score);
  exit(EXIT_SUCCESS);
}

int catch_signal(int sig, void (*handler) (int))
{
  struct sigaction action;
  action.sa_handler = handler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;
  return sigaction(sig, &action, NULL);
}

void times_up(int sig)
{
  puts("\nTIME'S UP!");
  raise(SIGINT);
}

int main(void)
{
  int a, b, answer;
  char txt[4];
  catch_signal(SIGALRM, times_up);
  catch_signal(SIGINT, end_game);
  srandom((unsigned int) time(NULL));
  while(1)
  {
    a = rand() % 11;
    b = rand() % 11;
    alarm(5);
    printf("\nWhat is %d times %d? ", a, b);
    fgets(txt, 4, stdin);
    answer = atoi(txt);
    if (answer == a * b)
      score++;
    else
      printf("\nWrong! Score: %i\n", score);
  }
  return 0;
}
