#include <stdio.h>

int main(void)
{
  int local_14[4];

  puts("***********************************");
  puts("* \t     -Level00 -\t\t  *");
  puts("***********************************");
  printf("Password:");
  __isoc99_scanf(&DAT_08048636, local_14);
  if (local_14[0] != 0x149c)
  {
    puts("\nInvalid Password!");
  }
  else
  {
    puts("\nAuthenticated!");
    system("/bin/sh");
  }
  return (int)(local_14[0] != 0x149c);
}
