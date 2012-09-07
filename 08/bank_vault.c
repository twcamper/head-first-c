#include <stdio.h>
#include <checksum.h>
#include <encrypt.h>

int main()
{
  char s[] = "Speak, friend, and enter!";
  int original_checksum = checksum(s);
  int decrypted_checksum;
  encrypt(s);
  printf("Encrypted to '%s'\n", s);
  printf("Checksum is %i\n", checksum(s));

  encrypt(s);
  printf("Decrypted back to '%s'\n", s);

  decrypted_checksum = checksum(s);
  if (decrypted_checksum == original_checksum) {
    printf("Checksum is %i\n", checksum(s));
    return 0;
  }
  fprintf(stderr, "Checksum Failure! %i != %i\n", decrypted_checksum, original_checksum);
  return 1;
}
