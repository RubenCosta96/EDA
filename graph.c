#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clients.h"
#include "managers.h"
#include "vehicles.h"
#include "menuFuncs.h"
#include "graph.h"

int createVertex(Graph **g, char *newVertex)
{
     Graph *new = malloc(sizeof(struct listVehicles));
     if (new != NULL)
     {
          strcpy(new->vertex, newVertex);
          new->vehicles = NULL;
          new->next = *g;
          *g = new;
          return 1;
     }
     else
          return 0;
}

int vertexExists(Graph *g, char vertex[])
{
     while (g != NULL)
     {
          if (strcmp(g->vertex, vertex) == 0)
               return 1;
          else
               g = g->next;
     }
     return 0;
}

int createEdge(Graph *g, char vOrigin[], char vDestination[], float weight)
{
     Adjacent *new;
     if (vertexExists(g, vOrigin) && vertexExists(g, vDestination))
     {
          while (strcmp(g->vertex, vOrigin) != 0)
               g = g->next;

          new = malloc(sizeof(struct graph2));
          if (new != NULL)
          {
               strcpy(new->vertex, vDestination);
               new->weight = weight;
               new->next = g->adjacents;
               g->adjacents = new;
          }
     }
}

void listAdjacents(Graph *g, char *vertex)
{
     Adjacent *aux;
     if (vertexExists(g, vertex))
     {
          while (strcmp(g->vertex, vertex) != 0)
               g = g->next;
          aux = g->adjacents;
          while (aux != NULL)
          {
               printf("%s %.2f\n", aux->vertex, aux->weight);
               aux = aux->next;
          }
     }
}

int insertVehicle(Graph *g, char geocode[], int vehicleID)
{
     while ((g != NULL) && (strcmp(g->vertex, geocode) != 0))
          g = g->next;
     if (g == NULL)
          return (0);
     else
     {
          Vehicle *new = malloc(sizeof(struct listVehicles));
          new->id = vehicleID;
          new->next = g->vehicles;
          g->vehicles = new;
          return (1);
     }
}