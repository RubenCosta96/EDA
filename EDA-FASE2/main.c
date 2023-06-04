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
  Adjacent *adj = NULL;
  Graph *graph = NULL;

  history = (History *)malloc(sizeof(History));
  if (history == NULL)
  {
    printf("Error: Could not allocate memory for history.\n");
    exit(1);
  }

  // Read data from data sets
  vehicles = readVehicles();
  clients = readClientsBinary();
  managers = readManagersBinary();
  initializeGraph(&graph);
  graph = readGraphBinary();
  graph = readAdjacents(graph);

  // Menu

  loginOrReg(&clients, &managers, &vehicles, &graph, &history);

  // Save data

  saveVehiclesBinary(vehicles);
  saveClientsBinary(clients);
  saveManagersBinary(managers);
  saveGraphBinary(graph);

  return 0;
}
