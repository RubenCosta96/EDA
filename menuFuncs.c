#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vehicles.h"
#include "clients.h"
#include "managers.h"
#include "menuFuncs.h"
#define MAX_LENGTH_NAME 50
#define MAX_LENGTH_ADDRESS 50
#define MAX_LENGTH_EMAIL 50

// Menu to choose option login/registration
void loginOrReg(Client **client, Manager **manager, Vehicle **vehicle)
{
  int opt;

  clearConsole();
  system("cat ./Menus/general/menu1.txt");
  scanf("%d", &opt);

  switch (opt)
  {
  case 1:
    fflush(stdout);
    clientOrManagerLogin(client, manager, vehicle);
    break;
  case 2:
    fflush(stdout);
    clientOrManagerRegistration(client, manager, vehicle);
    break;
  case 0:
    return;
    break;
  default:
    printf("Invalid option.\n");
    enterToContinue();
    loginOrReg(client, manager, vehicle);
    break;
  }
}

void enterToContinue()
{
  getchar();
  printf("Press enter to continue...");
  fflush(stdout);

  while (getchar() != '\n')
    ;
}

void clearConsole()
{
  system("clear || cls");
}

void clientOrManagerLogin(Client **client, Manager **manager, Vehicle **vehicle)
{
  int opt;

  clearConsole();
  system("cat ./Menus/general/menuLog.txt");
  fflush(stdout);
  scanf("%d", &opt);

  switch (opt)
  {
  case 1:
    fflush(stdout);
    clientLogin(client, vehicle, manager);
    break;
  case 2:
    fflush(stdout);
    managerLogin(manager, vehicle, client);
    break;
  case 0:
    loginOrReg(client, manager, vehicle);
    return;
  default:
    printf("Invalid Option!\n");
    enterToContinue();
    clientOrManagerLogin(client, manager, vehicle);
    break;
  }
}

void clientOrManagerRegistration(Client **client, Manager **manager, Vehicle **vehicle)
{
  int opt;

  do
  {
    clearConsole();
    system("cat ./Menus/general/menuReg.txt");
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
void clientLogin(Client **client, Vehicle **vehicle, Manager **manager)
{
  char email[MAX_LENGTH_EMAIL], password[16];

  printf("Email: ");
  scanf("%s", email);

  printf("Password: ");
  scanf("%s", password);

  Client *current = *client;
  while (current != NULL)
  {
    if (strcmp(current->email, email) == 0 && strcmp(current->password, password) == 0)
    {
      clientMenu(client, vehicle, current, manager);
      return;
    }
    current = current->next;
  }
  printf("Invalid email or password.\n");
  clientLogin(client, vehicle, manager);
}

void managerLogin(Manager **manager, Vehicle **vehicle, Client **client)
{
  char email[MAX_LENGTH_EMAIL], password[16];

  printf("Email: ");
  scanf("%s", email);

  printf("Password: ");
  scanf("%s", password);

  Manager *current = *manager;
  while (current != NULL)
  {
    if (strcmp(current->email, email) == 0 && strcmp(current->password, password) == 0)
    {
      managerMenu(manager, vehicle, client, current);
      return;
    }
    current = current->next;
  }
  printf("Invalid email or password.\n");
  managerLogin(manager, vehicle, client);
}

void managerMenu(Manager **head, Vehicle **vehicle, Client **client, Manager *m)
{
  int opt;
  Manager *current = *head;

  clearConsole();
  printf("Welcome %s\n", m->name);
  system("cat ./Menus/managers/managersMenu.txt");
  fflush(stdout);
  scanf("%d", &opt);

  switch (opt)
  {
  case 1:
    // Add vehicle
    clearConsole();
    printf("Vehicle to add:\n");
    vehicleReg(vehicle);
    getchar();
    enterToContinue();
    break;
  case 2:
    // Check history
    // TO DO
    break;
  case 3:
    // Change vehicle
    clearConsole();
    fflush(stdout);
    listVehicles(vehicle);
    printf("\n");
    printf("Which vehicle do u use wish to change data from?\nID: ");
    int vehicleID;
    scanf("%d", &vehicleID);
    clearConsole();
    changeVehicleData(vehicle, vehicleID);
    break;
  case 4:
    // Change data
    clearConsole();
    fflush(stdout);
    current = changeManagerData(current);
    break;
  case 5:
    // List vehicles
    clearConsole();
    fflush(stdout);
    listVehicles(vehicle);
    enterToContinue();
    break;
  case 6:
    // List clients
    clearConsole();
    fflush(stdout);
    listClients(client);
    enterToContinue();
    break;
  case 7:
    // Remove clients
    clearConsole();
    listClients(client);
    printf("What is the ID of the client you wish to remove?\n");
    int remClient;
    scanf("%d", &remClient);
    removeClient(client, remClient);
    enterToContinue();
    break;
  case 8:
    // Remove vehicle
    clearConsole();
    listVehicles(vehicle);
    printf("What is the ID of the client you wish to remove?\n");
    int remVehicle;
    scanf("%d", &remVehicle);
    removeVehicle(vehicle, remVehicle);
    enterToContinue();
    break;
  case 9:
    // Sort vehicles by autonomy
    clearConsole();
    fflush(stdout);
    sortVehiclesByAutonomy(vehicle);
    listVehicles(vehicle);
    enterToContinue();
    break;
  case 10:
    // Delete account
    fflush(stdout);
    removeManager(head, m->id);
    printf("Account removed with success.\n");
    enterToContinue();
    clearConsole();
    loginOrReg(client, head, vehicle);
    return;
    break;
  case 0:
    clearConsole();
    loginOrReg(client, head, vehicle);
    return;
    break;
  default:
    break;
  }
  managerMenu(head, vehicle, client, m);
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