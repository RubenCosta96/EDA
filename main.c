#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clients.h"
#include "managers.h"
#include "vehicles.h"
#include "menuFuncs.h"

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

  managers = changeManagerData(managers, "teste");

  // managers = insertManager(managers, 8, "Nando", "nando@gmail.com", "nando123");
  // listManagers(managers);
  //  Menu
  // loginOrReg(&clients, &managers);
  // listManagers(managers);

  // saveManagers(managers);

  /*printf("totClients = %d\n", totClients);
  printf("totManagers = %d\n", totManagers);
  printf("totVehicles = %d\n", totClients);*/

  return 0;
}
