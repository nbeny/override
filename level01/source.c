#include <stdio.h>

int verify_user_name(void)
{
  int iVar1;
  byte *pbVar2;
  byte *pbVar3;
  bool bVar4;
  bool bVar5;
  byte bVar6;
  
  bVar6 = 0;
  bVar4 = (int)0x10;
  bVar5 = (int)0x1c;
  puts("verifying username....\n");
  iVar1 = 7;
  pbVar2 = a_user_name;
  pbVar3 = "dat_wil";
  do {
    if (iVar1 == 0) break;
    iVar1 = iVar1 + -1;
    pbVar2 = pbVar2 + (int)bVar6 * -2 + 1;
    pbVar3 = pbVar3 + (int)bVar6 * -2 + 1;
  } while (bVar5);
  return (int)((!bVar4 && !bVar5) - bVar4);
}

int verify_user_pass(byte *param_1)
{
  int iVar1;
  byte *pbVar2;
  bool in_CF;
  bool in_ZF;
  
  iVar1 = 5;
  pbVar2 = (byte *)"admin";
  do {
    if (iVar1 == 0) break;
    iVar1 = iVar1 + -1;
    param_1 = param_1 + 1;
    pbVar2 = pbVar2 + 1;
  } while (in_ZF);
  return (int)((!in_CF && !in_ZF) - in_CF);
}

int main(void)
{
  int uVar1;
  int iVar2;
  char *puVar3;
  char *local_54[16];
  int local_14;
  
  iVar2 = 0x10;
  puVar3 = local_54;
  while (iVar2 != 0) {
    iVar2 = iVar2 + -1;
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  local_14 = 0;
  puts("********* ADMIN LOGIN PROMPT *********");
  printf("Enter Username: ");
  fgets(a_user_name,0x100,stdin);
  local_14 = verify_user_name();
  if (local_14 == 0) {
    puts("Enter Password: ");
    fgets((char *)local_54,100,stdin);
    local_14 = verify_user_pass(local_54);
    if ((local_14 == 0) || (local_14 != 0)) {
      puts("nope, incorrect password...\n");
      uVar1 = 1;
    }
    else {
      uVar1 = 0;
    }
  }
  else {
    puts("nope, incorrect username...\n");
    uVar1 = 1;
  }
  return uVar1;
}
