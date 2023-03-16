#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clients.h"
#include "clients.c"
#include "managers.h"
#include "managers.c"
#include "vehicles.h"
#include "vehicles.c"
#include "menuFuncs.h"
#include "menuFuncs.c"

int main()
{
  // Initialization of variables
  Vehicle *vehicles = NULL;
  Client *clients = NULL;
  Manager *managers = NULL;

  // Read data from data sets
  vehicles = readVehicles();
  clients = readClients();
  managers = readManagers();

  //managers = changeManagerData(managers, "teste");

  // managers = insertManager(managers, 8, "Nando", "nando@gmail.com", "nando123");
  // listManagers(managers);
  //  Menu
  //loginOrReg(&clients, &managers);
  // listManagers(managers);

  addFundsClient(&clients,1,50);
  listClients(clients);
  saveClients(clients);

  // saveManagers(managers);

  /*printf("totClients = %d\n", totClients);
  printf("totManagers = %d\n", totManagers);
  printf("totVehicles = %d\n", totClients);*/

  return 0;
}
