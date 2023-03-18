#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TEST
#include <time.h>

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

  // Menu
  loginOrReg(&clients, &managers, &vehicles);

  saveManagers(managers);
  saveClients(clients);
  saveVehicles(vehicles);

  return 0;
}
