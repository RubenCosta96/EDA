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

  // Menu
  // clientReg(&clients);

  loginOrReg(&clients, &managers);

  printf("totClients = %d\n", totClients);
  printf("totManagers = %d\n", totManagers);
  printf("totVehicles = %d\n", totClients);

  printf("Clients:\n");
  listClients(clients);
  printf("Managers:\n");
  listManagers(managers);
  printf("Vehicles:\n");

  listVehicles(vehicles);

  // Save before exiting to data set
  saveClients(clients);
  saveManagers(managers);
  saveVehicles(vehicles);

  return 0;
}
