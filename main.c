#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clients.h"
#include "managers.h"
#include "vehicles.h"

int main()
{

  Vehicle *vehicles = NULL;
  Client *clients = NULL;
  Manager *managers = NULL;
  vehicles = readVehicles();
  clients = readClients();
  managers = readManagers();
  printf("Clients:\n");
  listClients(clients);
  printf("\n");
  printf("Managers:\n");
  listManagers(managers);
  printf("\n");
  listVehicles(vehicles);

  /*vehicles = insertVehicle(vehicles, 1, "troti1", 50, 0, "u");
  vehicles = insertVehicle(vehicles, 1, "troti2", 10, 0, "u");
  vehicles = insertVehicle(vehicles, 1, "troti3", 25, 0, "u");
  vehicles = insertVehicle(vehicles, 1, "troti4", 5, 0, "u");
  vehicles = insertVehicle(vehicles, 1, "troti5", 60, 0, "u");
  vehicles = insertVehicle(vehicles, 1, "troti6", 100, 0, "u");

  saveVehicles(vehicles);
*/
  // sortVehiclesByAutonomy(vehicles);

  return 0;
}
