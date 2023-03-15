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

  do
  {
    system("type menu1.txt || cat menu1.txt");
    fflush(stdout);
    scanf("%d", &opt);

    switch (opt)
    {
    case 1:
      printf("Login:\n");
      fflush(stdout);
      clientOrManagerLogin(client, manager);
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
  } while (opt != 0);
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
  system("clear || cls"); // clears the console screen on Unix-based systems
}

void clientOrManagerLogin(Client **client, Manager **manager)
{
  int opt;

  do
  {
    system("type menu2.txt || cat menu2.txt");
    fflush(stdout);
    scanf("%d", &opt);

    switch (opt)
    {
    case 1:
      fflush(stdout);
      clientLogin(client);
      break;
    case 2:
      fflush(stdout);
      managerLogin(manager);
      break;
    case 0:
      break;
    default:
      printf("Invalid Option!\n");

      break;
    }
  } while (opt != 0);
}

void clientOrManagerRegistration(Client **client, Manager **manager)
{
  int opt;

  do
  {
    system("type menu3.txt || cat menu3.txt");
    fflush(stdout);
    scanf("%d", &opt);

    switch (opt)
    {
    case 1:
      clientReg(client);
      break;
    case 2:
      managerReg(manager);
      break;
    case 0:
      break;
    default:
      printf("Invalid Option!\n");
      break;
    }
  } while (opt != 1 && opt != 2 && opt != 0);
}

// Client login
void clientLogin(Client **client)
{
  char email[30], password[16];
  printf("Email: ");
  scanf("%29s", email);
  printf("Password: ");
  scanf("%15s", password);

  Client *current = *client;
  while (current != NULL)
  {
    if (strcmp(current->email, email) == 0 && strcmp(current->password, password) == 0)
    {
      printf("Welcome, %s!\n", current->name);
      return;
    }
    current = current->next;
  }
  printf("Invalid email or password.\n");
}

void managerLogin(Manager **manager)
{
  if (*manager == NULL)
  {
    printf("Invalid client.\n");
    return;
  }

  char email[50], pw[16];
  int opt;

  printf("Manager Login\n");
  printf("Email: ");
  scanf("%s", email);
  printf("Password: ");
  scanf("%s", pw);
  if (strcmp((*manager)->email, email) == 0 && strcmp((*manager)->password, pw) == 0)
  {
    printf("Welcome %s\n", (*manager)->name);
    do
    {
      system("type managersMenu.txt || cat managersMenu.txt");
      fflush(stdout);
      scanf("%d", &opt);
      switch (opt)
      {
      case 1:
        printf("Vehicle to add:\n");

        break;
      case 2:
        break;
      case 3:
        break;
      case 4:
        break;
      case 5:
        break;
      case 6:
        break;
      case 0:
        break;
      default:
        break;
      }
    } while (opt < 0 || opt > 6);
  }
  else
  {
    printf("Invalid username or password.");
  }
}

void managerReg(Manager **head)
{
  int id;
  char name[MAX_LENGTH_NAME], email[MAX_LENGTH_EMAIL], password[16];
  int maxID = getMaxManagerId(*head) + 1;

  printf("Your ID is: %d\n", maxID);
  printf("Name: ");
  fflush(stdout); // Use on windows
  scanf("%s", name);
  printf("Email: ");
  fflush(stdout); // Use on windows
  scanf("%s", email);
  printf("Password: ");
  fflush(stdout); // Use on windows
  scanf("%s", password);

  *head = insertManager(*head, maxID, name, email, password);
  saveManagers(*head);
  clearConsole();
}