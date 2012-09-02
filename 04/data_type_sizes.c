#include <stdio.h>
#include <limits.h>
#include <float.h>


int main()
{
  printf("INT_MAX: %i\n", INT_MAX);
  printf("INT_MIN: %i\n", INT_MIN);
  printf("size: %i bytes\n", sizeof(int));

  printf("SHRT_MAX: %hi\n", SHRT_MAX);
  printf("SHRT_MIN: %hi\n", SHRT_MIN);
  printf("size: %i bytes\n", sizeof(short));

  printf("LONG_MAX: %li\n", LONG_MAX);
  printf("LONG_MIN: %li\n", LONG_MIN);
  printf("size: %i bytes\n", sizeof(long));

  printf("FLT_MAX: %f\n", FLT_MAX);
  printf("FLT_MIN: %f\n", FLT_MIN);
  printf("size: %i bytes\n", sizeof(float));

  printf("DBL_MAX: %f\n", DBL_MAX);
  printf("DBL_MIN: %f\n", DBL_MIN);
  printf("size: %i bytes\n", sizeof(double));

  printf("CHAR_MAX: %i\n", (short)CHAR_MAX);
  printf("CHAR_MIN: %i\n", (short)CHAR_MIN);
  printf("size: %i bytes\n", sizeof(char));

  return 0;
}
