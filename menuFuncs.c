#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clients.h"
#include "managers.h"

void enterToContinue()
{
 printf("Press enter to continue...");
 fflush(stdout);

 while (getchar() != '\n')
 {
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
  void managerLogin(Manager * manager);
  break;
 case 0:
  printf("Exiting...");
  enterToContinue();
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
  void clientReg(Client * head);
  break;
 case 2:
  void clientReg(Client * head);
  break;
 case 0:
  printf("Exiting");
  void enterToContinue();
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
 Client *newClient = NULL;
 int id, age;
 char name[50], NIF[9], address[50], email[30], pw[16];
 float balance;

 id = aux->id + 1;

 printf("Your ID is: %d\n", &id);
 printf("Name: ");
 scanf("%49[^/n]", name);
 printf("Age: ");
 scanf("%d", &age);
 printf("NIF: ");
 scanf("%8[^/n]", NIF);
 balance = 0;
 printf("Address: ");
 scanf("%49[^/n]", address);
 printf("Email: ");
 scanf("%29[^/n]", email);
 printf("Password: ");
 scanf("%16[^/n]", pw);
 newClient = insertClient(aux, id, name, age, NIF, balance, address, email, pw);
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

void managerReg(Manager *head)
{
 Manager *aux = head;
 Manager *newManager = NULL;
 int id, age;
 char name[50], address[50], email[30], pw[16];
 float balance;

 id = aux->id + 1;

 printf("Your ID is: %d\n", &id);
 printf("Name: ");
 scanf("%49[^/n]", name);
 printf("Email: ");
 scanf("%29[^/n]", email);
 printf("Password: ");
 scanf("%16[^/n]", pw);
 newManager = insertManager(aux, id, name, email, pw);
}