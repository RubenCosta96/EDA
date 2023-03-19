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

/**
 * @brief Menu that allows the user either to choose if he wants to "Login" or "Register".
 *
 * @param client
 * @param manager
 * @param vehicle
 */
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

/**
 * @brief Function to display a message that only goes to the next screen after the key "ENTER" is pressed.
 *
 */
void enterToContinue()
{
  getchar();
  printf("\nPress enter to continue...");
  fflush(stdout);

  while (getchar() != '\n')
    ;
}

/**
 * @brief Function to clear the terminal
 *
 */
void clearConsole()
{
  system("clear || cls");
}

/**
 * @brief Function that allows the user to decide if he's logging in as a "Client" or a "Manager".
 *
 * @param client
 * @param manager
 * @param vehicle
 */
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

/**
 * @brief Function that allows the user to decide if he's registering as a "Client" or a "Manager".
 *
 * @param client
 * @param manager
 * @param vehicle
 */
void clientOrManagerRegistration(Client **client, Manager **manager, Vehicle **vehicle)
{
  int opt;

  clearConsole();
  system("cat ./Menus/general/menuReg.txt");
  scanf("%d", &opt);
  switch (opt)
  {
  case 1:
    clientReg(client);
    loginOrReg(client, manager, vehicle);
    break;
  case 2:
    managerReg(manager);
    loginOrReg(client, manager, vehicle);
    break;
  case 0:
    loginOrReg(client, manager, vehicle);
    return;
  default:
    printf("Invalid Option!\n");
    enterToContinue();
    clientOrManagerRegistration(client, manager, vehicle);
    break;
  }
}

/**
 * @brief Function that allows a client to login.
 *
 * @param client
 * @param vehicle
 * @param manager
 */
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

/**
 * @brief Function that allows the manager to login.
 *
 * @param manager
 * @param vehicle
 * @param client
 */
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

/**
 * @brief Function that prints the menu of the manager and recieves the option he wishes to execute.
 *
 * @param head
 * @param vehicle
 * @param client
 * @param m
 */
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
