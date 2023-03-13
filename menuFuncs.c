#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clients.h"
#include "managers.h"
#include "menuFuncs.h"
#define MAX_LENGTH_NAME 50
#define MAX_LENGTH_ADDRESS 50
#define MAX_LENGTH_EMAIL 50

// Menu to choose option login/registration
void loginOrReg(Client **client, Manager **manager)
{
 int opt;

 system("type menu1.txt || cat menu1.txt");
 fflush(stdout);
 scanf("%d", &opt);

 switch (opt)
 {
 case 1:
  printf("Login:\n");
  fflush(stdout);
  // clientOrManagerLogin(client, manager);
  break;
 case 2:
  printf("Registration\n");
  fflush(stdout);
  clientOrManagerRegistration(client, manager);
  break;
 case 0:
  break;
 default:
  printf("Invalid option.\n");
  break;
 }
}

void enterToContinue()
{ /*
  printf("Press enter to continue...");
  fflush(stdout); // flush the output buffer to ensure the message is displayed

  while (getchar() != '\n')
  {
   // read characters from stdin until a newline character is encountered
  }*/
}

void clearConsole()
{
 // system("@cls || clear");
}

void clientOrManagerLogin(Client **client, Manager **manager)
{
 int opt;

 printf("Are you a manager or a client?\n");
 scanf("%d", &opt);

 switch (opt)
 {
 case 1:
  clientLogin(client);
  break;
 case 2:
  managerLogin(manager);
  break;
 default:
  break;
 }
}

void clientOrManagerRegistration(Client **client, Manager **manager)
{
 int opt;

 printf("Are you a manager or a client?\n 1-Client / 2- Manager\n");
 fflush(stdout);
 scanf("%d", &opt);

 switch (opt)
 {
 case 1:
  clientReg(client);

  break;
 case 2:
  // managerReg(manager);
  break;
 default:
  break;
 }
}

// Tenho de dar return a algo para verificar que o login foi feito com succeso?
void clientLogin(Client **client)
{
 if ((*client) == NULL)
 {
  printf("Invalid client\n");
  return;
 }

 char email[50], pw[16];

 printf("Client Login\n");
 printf("Email: ");
 scanf("%s", email);
 printf("Password: ");
 scanf("%s", pw);
 if (strcmp((*client)->email, email) == 0 && strcmp((*client)->password, pw) == 0)
 {
  printf("Welcome %s", (*client)->name);
 }
 else
 {
  printf("Invalid username or password.");
  return;
 }
}

void managerLogin(Manager **manager)
{
 if (*manager == NULL)
 {
  printf("Invalid client.\n");
  return;
 }

 char email[50], pw[16];

 printf("Manager Login\n");
 printf("Email: ");
 scanf("%s", email);
 printf("Password: ");
 scanf("%s", pw);
 if (strcmp((*manager)->email, email) == 0 && strcmp((*manager)->password, pw) == 0)
 {
  printf("Welcome %s", (*manager)->name);
 }
 else
 {
  printf("Invalid username or password.");
 }
}

void managerReg(Manager *manager)
{
}