#include <stdio.h>
#include <calories.h>

void display_calories(float weight, float distance, float coefficient)
{
  printf("Weight: %3.2f lbs\n", weight);
  printf("Distance: %3.2f miles\n", distance);
  printf("Calories burned: %4.2f\n", coefficient * weight * distance);
}
