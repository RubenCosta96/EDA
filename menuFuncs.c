#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clients.h"
#include "managers.h"

void enterToContinue()
{
 printf("Press enter to continue...");
 fflush(stdout); // flush the output buffer to ensure the message is displayed

 while (getchar() != '\n')
 {
  // read characters from stdin until a newline character is encountered
 }

 return 0;
}

void clearConsole()
{
 system("@cls || clear");
}

void clientOrManagerLogin()
{
 int opt;

 printf("Are you a manager or a client?\n");
 scanf("%d", &opt);

 switch (opt)
 {
 case 1:
  void clientLogin(Client * client);
  break;
 case 2:
  // Manager
  break;
 default:
  break;
 }
}

void clientOrManagerRegistration()
{
 int opt;

 printf("Are you a manager or a client?\n");
 scanf("%d", &opt);

 switch (opt)
 {
 case 1:
  // Client
  break;
 case 2:
  // Manager
  break;
 default:
  break;
 }
}

// Tenho de dar return a algo para verificar que o login foi feito com succeso?
void clientLogin(Client *client)
{
 if (client == NULL)
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
 if (strcmp(client->email, email) == 0 && strcmp(client->password, pw) == 0)
 {
  printf("Welcome %s", client->name);
 }
 else
 {
  printf("Invalid username or password.");
  return;
 }
}

void clientReg(Client *head)
{
 Client *aux = head;
 aux->id += 1;
 printf("Your ID is: %d\n", aux->id);
 printf("Name: ");
 scanf("%49[^/n]", aux->name);
 printf("Age: ");
 scanf("%d", aux->age);
 printf("NIF: ");
 scanf("%8[^/n]", aux->NIF);
 aux->balance = 0;
 printf("Address: ");
 scanf("%49[^/n]", aux->address);
 printf("Email: ");
 scanf("%29[^/n]", aux->email);
 printf("Password: ");
 scanf("%16[^/n]", aux->password);
}

void managerLogin(Manager *manager)
{
 if (manager == NULL)
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
 if (strcmp(manager->email, email) == 0 && strcmp(manager->password, pw) == 0)
 {
  printf("Welcome %s", manager->name);
 }
 else
 {
  printf("Invalid username or password.");
 }
}

void managerReg()
{
}