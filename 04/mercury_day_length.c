#include <stdio.h>

float mercury_day_in_earth_days();
int hours_in_an_earth_day();

int main()
{
  float length_of_day = mercury_day_in_earth_days();
  /*int length_of_day = mercury_day_in_earth_days();
    returns incorrect value 1392.0 hours
   * */ 
  int hours = hours_in_an_earth_day();
  float day = length_of_day * hours;

  printf("A day on Mercury is %f hours\n", day);
  // A day on Mercury is 1407.600098 hours
  return 0;
}

float mercury_day_in_earth_days() { return 58.65; }
int hours_in_an_earth_day()       { return 24; }
