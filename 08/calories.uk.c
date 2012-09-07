#include <stdio.h>
#include <calories.h>

void display_calories(float weight, float distance, float coefficient)
{
  printf("Weight: %3.2f kg\n", weight / 2.2046);
  printf("Distance: %3.2f km\n", distance / 1.609344);
  printf("Calories burned: %4.2f\n", coefficient * weight * distance);
}
