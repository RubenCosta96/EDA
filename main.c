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
  // history = readHistory();

  initializeGraph(&graph);

  // Criação de valores simulação para os vértices
  createVertex(&graph, 1, "Vertex1", "geo1");
  createVertex(&graph, 2, "Vertex2", "geo2");
  createVertex(&graph, 3, "Vertex3", "geo3");
  createVertex(&graph, 4, "Vertex4", "geo4");
  createVertex(&graph, 5, "Vertex5", "geo5");
  createVertex(&graph, 6, "Vertex6", "geo6");
  createVertex(&graph, 7, "Vertex7", "geo7");
  createVertex(&graph, 8, "Vertex8", "geo8");
  createVertex(&graph, 9, "Vertex9", "geo9");

  // Criação de valores simulação para arestas
  createEdge(graph, "geo1", "geo2", 17);
  createEdge(graph, "geo1", "geo3", 21);
  createEdge(graph, "geo2", "geo4", 12);
  createEdge(graph, "geo3", "geo5", 15);
  createEdge(graph, "geo2", "geo3", 3);
  createEdge(graph, "geo3", "geo4", 17);
  createEdge(graph, "geo4", "geo7", 20);
  createEdge(graph, "geo4", "geo6", 4);
  createEdge(graph, "geo5", "geo6", 10);
  createEdge(graph, "geo5", "geo7", 8);
  createEdge(graph, "geo6", "geo8", 15);
  createEdge(graph, "geo7", "geo8", 26);

  printf("\n\n");
  printf("27/05/2023:\n");
  float distances[SIZE] = {0};
  dijkstra(graph, "Vertex1", "Vertex8", distances);
  printf("\n\n");

  locationsBelowDistance(graph, vehicles, "Vertex1", 18.0);

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
