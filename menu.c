#include <stdio.h>

// Menu to choose option login/registration
void loginOrReg(int opt);
{
 int opt;

 printf("Choose an option:\n");
 printf("1 - Register\n");
 printf("2 - Login\n");
 scanf("%d", &opt);

 switch (opt)
 {
 case 1:
  printf("Registration:\n");
  // Registration code
  break;
 case 2:
  printf("Login:\n");
  // Login code
  break;
 default:
  printf("Invalid option.\n");
  break;
 }

 return 0;
}
