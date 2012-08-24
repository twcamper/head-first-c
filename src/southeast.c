#include <stdio.h>

void go_southeast(int *lat, int *lon) {
  *lat = *lat - 1;
  *lon = *lon + 1;
}

int main()
{
  int latitude = 32;
  int longitude = -64;

  printf("Addresses:\vlatitude: %p\tlongitude: %p\n", &latitude, &longitude);
  go_southeast(&latitude, &longitude);
  printf("Avast! Now at: [%i, %i]\n", latitude, longitude);

  return 0;
}
