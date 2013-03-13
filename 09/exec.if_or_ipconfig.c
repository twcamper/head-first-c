#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int print_sysinfo()
{
  char *cmd = "uname";
  if ( execlp(cmd, cmd, "-a", NULL) == -1) {
      fprintf(stderr, "Cannot run uname: %i - %s\n", errno, strerror(errno));
      return 2;
    }
  return 0;
}
int main()
{
  char *cmd = "/sbin/ifconfig";
  short r_code;
  if (execl(cmd, cmd, NULL) == -1) {
    if (execlp("ipconfig", "ipconfig", NULL) == -1) {
      fprintf(stderr, "Cannot run ipconfig: %i - %s\nSYSTEM INFO:\n", errno, strerror(errno));
      if ((r_code = print_sysinfo()))
        return r_code;
      else
        return 1;
    }
  }
  return 0;
}
