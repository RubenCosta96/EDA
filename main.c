#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clients.h"
#include "managers.h"
#include "vehicles.h"
#include "menuFuncs.h"
#include "graph.h"
#include "history.h"
#include "clients.c"
#include "managers.c"
#include "vehicles.c"
#include "menuFuncs.c"
#include "graph.c"
#include "history.c"

int main()
{
  // Initialization of variables
  Vehicle *vehicles = NULL;
  Client *clients = NULL;
  Manager *managers = NULL;
  History *history = NULL;
  Graph *graph = NULL;

  history = (History *)malloc(sizeof(History));
  if (history == NULL)
  {
    printf("Error: Could not allocate memory for history.\n");
    exit(1);
  }

  // Read data from data sets
  vehicles = readVehiclesBinary();
  clients = readClientsBinary();
  managers = readManagersBinary();
  // history = readHistory();

  /*
    // Menu
    loginOrReg(&clients, &managers, &vehicles);

    // Save data
    saveVehiclesBinary(vehicles);
    saveClientsBinary(clients);
    saveManagersBinary(managers);
    */

  history->init.tm_year = 11; // Year since 1900 (2021 - 1900)
  history->init.tm_mon = 4;   // Month (May)
  history->init.tm_mday = 5;  // Day of the month
  history->init.tm_hour = 10; // Hour
  history->init.tm_min = 30;  // Minute
  history->init.tm_sec = 0;   // Second

  history->end.tm_year = 11; // Year since 1900 (2021 - 1900)
  history->end.tm_mon = 4;   // Month (May)
  history->end.tm_mday = 6;  // Day of the month
  history->end.tm_hour = 11; // Hour
  history->end.tm_min = 45;  // Minute
  history->end.tm_sec = 0;   // Second

  history = insertHistory(history, 50, "Joao", 30, "Trotinete", 13, history->init, history->end);
  // listHistory(history);

  return 0;
}
