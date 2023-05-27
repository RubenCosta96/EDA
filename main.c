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
  vehicles = readVehiclesBinary();
  clients = readClientsBinary();
  managers = readManagersBinary();
  // history = readHistory();

  initializeGraph(&graph);

  // Criação de valores simulação para os vértices
  createVertex(&graph, 1, "1", "1");
  createVertex(&graph, 2, "2", "2");
  createVertex(&graph, 3, "3", "3");
  createVertex(&graph, 4, "4", "4");
  createVertex(&graph, 5, "5", "5");
  createVertex(&graph, 6, "6", "6");
  createVertex(&graph, 7, "7", "7");
  createVertex(&graph, 8, "8", "8");
  createVertex(&graph, 9, "9", "9");

  // Criação de valores simulação para arestas
  createEdge(graph, "1", "2", 30);
  createEdge(graph, "1", "3", 21);
  createEdge(graph, "2", "4", 12);
  createEdge(graph, "3", "5", 15);
  createEdge(graph, "2", "3", 3);
  createEdge(graph, "3", "4", 17);
  createEdge(graph, "4", "7", 20);
  createEdge(graph, "4", "6", 4);
  createEdge(graph, "5", "6", 10);
  createEdge(graph, "5", "7", 8);
  createEdge(graph, "6", "8", 15);
  createEdge(graph, "7", "8", 26);

  printf("\n\n");
  printf("25/05/2023:\n");

  dijkstra(graph, "1", "8");

  /* Tirar de comentar
   // Menu
   loginOrReg(&clients, &managers, &vehicles, &graph, &history);

   // Save data
   saveVehiclesBinary(vehicles);
   saveClientsBinary(clients);
   saveManagersBinary(managers);

   // Test values for history function test
   // history->init.tm_year = 11; // Year since 1900 (2021 - 1900)
   // history->init.tm_mon = 4;   // Month (May)
   // history->init.tm_mday = 5;  // Day of the month
   // history->init.tm_hour = 10; // Hour
   // history->init.tm_min = 30;  // Minute
   // history->init.tm_sec = 0;   // Second

   listHistory(&history);
   Até aqui*/

  return 0;
}
