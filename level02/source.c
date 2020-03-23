#include <stdio.h>
#include <string.h>

int main(void)
{
  int iVar1;
  size_t sVar2;
  long lVar3;
  char *puVar4;
  char local_118 [14];
  char local_a8 [6];
  char local_78 [12];
  int local_14;
  FILE *local_10;
  
  lVar3 = 0xc;
  puVar4 = local_78;
  while (lVar3 != 0) {
    lVar3 = lVar3 + -1;
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  puVar4 = 0;
  lVar3 = 5;
  puVar4 = local_a8;
  while (lVar3 != 0) {
    lVar3 = lVar3 + -1;
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  puVar4 = 0;
  lVar3 = 0xc;
  puVar4 = local_118;
  while (lVar3 != 0) {
    lVar3 = lVar3 + -1;
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  puVar4 = 0;
  local_10 = (FILE *)0x0;
  local_14 = 0;
  local_10 = fopen("/home/users/level03/.pass","r");
  if (local_10 == (FILE *)0x0) {
    fwrite("ERROR: failed to open password file\n",1,0x24,stderr);
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  sVar2 = fread(local_a8,1,0x29,local_10);
  local_14 = (int)sVar2;
  sVar2 = strcspn((char *)local_a8,"\n");
  if (local_14 != 0x29) {
    fwrite("ERROR: failed to read password file\n",1,0x24,stderr);
    fwrite("ERROR: failed to read password file\n",1,0x24,stderr);
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  fclose(local_10);
  puts("===== [ Secure Access System v1.0 ] =====");
  puts("/***************************************\\");
  puts("| You must login to access this system. |");
  puts("\\**************************************/");
  printf("--[ Username: ");
  fgets((char *)local_78,100,stdin);
  sVar2 = strcspn((char *)local_78,"\n");
  printf("--[ Password: ");
  fgets((char *)local_118,100,stdin);
  sVar2 = strcspn((char *)local_118,"\n");
  puts("*****************************************");
  iVar1 = strncmp((char *)local_a8,(char *)local_118,0x29);
  if (iVar1 == 0) {
    printf("Greetings, %s!\n",local_78,local_78);
    system("/bin/sh");
    return 0;
  }
  printf((char *)local_78);
  puts(" does not have access!");
                    /* WARNING: Subroutine does not return */
  exit(1);
}
