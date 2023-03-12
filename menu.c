#include <stdio.h>
#include "menuFuncs.h"

// Menu to choose option login/registration
void loginOrReg(int opt)
{
 int opt;

 system("type menu.txt" || "cat menu.txt");
 scanf("%d", &opt);

 switch (opt)
 {
 case 1:
  printf("Login:\n");
  void clientOrManagerLogin();
  break;
 case 2:
  printf("Registration\n");
  void clientOrManagerRegistration();
  break;
 case 0:
  void enterToContinue();
  break;
 default:
  printf("Invalid option.\n");
  break;
 }

 return 0;
}
