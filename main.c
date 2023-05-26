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
  createVertex(&graph, 1, "Rua do Bombeiro", "as.tres.palavras");
  createVertex(&graph, 2, "Avenida de Barcelos", "next.outras.palavras");
  createVertex(&graph, 3, "Estádio de Barcelos", "mais.tres.palavras");
  createVertex(&graph, 4, "Rotunda do Galo", "outras.tres.palavras");
  createVertex(&graph, 5, "Campo da Feira", "plus.tres.palavras");
  createVertex(&graph, 6, "IPCA", "extra.tres.palavras");
  createVertex(&graph, 7, "Alcaides Faria", "max.outras.palavras");

  // Criação de valores simulação para arestas
  createEdge(graph, "next.outras.palavras", "as.tres.palavras", 2);
  createEdge(graph, "as.tres.palavras", "mais.tres.palavras", 8);
  createEdge(graph, "next.outras.palavras", "plus.tres.palavras", 3);
  createEdge(graph, "next.outras.palavras", "extra.tres.palavras", 1);
  createEdge(graph, "extra.tres.palavras", "max.outras.palavras", 5);
  createEdge(graph, "extra.tres.palavras", "outras.tres.palavras", 8);
  createEdge(graph, "max.outras.palavras", "outras.tres.palavras", 11);
  createEdge(graph, "mais.tres.palavras", "outras.tres.palavras", 14);
  createEdge(graph, "plus.tres.palavras", "outras.tres.palavras", 20);

  listVertexes(&graph);
  listAdjacents(graph, "next.outras.palavras");

  printf("\n\n");
  printf("25/05/2023:\n");

  dijkstra(graph, "Avenida de Barcelos", "Rotunda do Galo");

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
