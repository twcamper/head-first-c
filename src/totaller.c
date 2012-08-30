#include <stdio.h>

float total = 0.0;
short count =  0;

float add_with_tax(float f)
{
  short tax_percent = 6;
  float tax_rate = 1 + tax_percent / 100.0;
  total += f * tax_rate;
  count++;

  return total;
}

int main()
{
  float val;
  printf("Price of item: ");
  while (scanf("%f", &val) == 1) {
    printf("subtotal: %.2f\n", add_with_tax(val));
    printf("Price of item: ");
  }

  printf("\nFinal total: %.2f\n", total);
  printf("Number of items: %hi\n", count);
  return 0;
}
