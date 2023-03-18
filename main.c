#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TEST
#include <time.h>

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
  vehicles = readVehiclesBinary();
  clients = readClientsBinary();
  managers = readManagersBinary();

  // Menu
  loginOrReg(&clients, &managers, &vehicles);

  saveVehiclesBinary(vehicles);
  saveClientsBinary(clients);
  saveManagersBinary(managers);

  return 0;
}
