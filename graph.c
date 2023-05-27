#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#include "clients.h"
#include "managers.h"
#include "vehicles.h"
#include "menuFuncs.h"
#include "graph.h"

#define INFINITY 99999
#define MAX_LINE 250

int createVertex(Graph **g, int id, char *newVertex, char *newGeocode)
{
     Graph *new = malloc(sizeof(struct graph2));

     if (new != NULL)
     {
          strcpy(new->vertex, newVertex);
          strcpy(new->geocode, newGeocode);
          new->id = id;
          new->next = *g;
          new->adjacents = NULL;
          *g = new;
          return 1;
     }
     else
          return 0;
}

int vertexExists(Graph *g, char geocode[])
{
     while (g != NULL)
     {
          if (strcmp(g->geocode, geocode) == 0)
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
          while (strcmp(g->geocode, vOrigin) != 0)
               g = g->next;

          new = malloc(sizeof(struct graph1));
          if (new != NULL)
          {
               strcpy(new->vertex, vDestination);
               new->weight = weight;
               new->next = g->adjacents;
               g->adjacents = new;
               return 1;
          }
          else
               return 0;
     }
     else
          return 0;
}

void listAdjacents(Graph *g, char *geocode)
{
     Graph *aux1 = g;
     Adjacent *aux;
     if (vertexExists(g, geocode))
     {
          char respVertex[SIZE];
          convertCodeToVertex(&g, geocode, respVertex);
          printf("Connection: %s", respVertex);
          while (strcmp(g->geocode, geocode) != 0)
          {
               g = g->next;
          }
          aux = g->adjacents;

          while (aux != NULL)
          {
               char respLoc[SIZE];
               convertCodeToVertex(&aux1, aux->vertex, respLoc);
               printf(" -> %s", respLoc);

               aux = aux->next;
          }
          printf("\n");
     }
}

void listVertexes(Graph **graph)
{
     printf("ID\tGeocode\t\t\tLocation\n");
     Graph *head = *graph;
     for (; head != NULL; head = head->next)
     {
          printf("%d\t%s\t%s", head->id, head->geocode, head->vertex);
          printf("\n");
     }
}

int addVehicleLoc(Graph *g, char geocode[], int vehicleID)
{
     while ((g != NULL) && (strcmp(g->vertex, geocode) != 0))
     {
          g = g->next;
          if (g == NULL)
               return (0);
          else
          {
               Vehicle *new = malloc(sizeof(struct listVehicles));
               new->id = vehicleID;
               new->next = g->vehicles;
               g->vehicles = new;
               strcpy(new->location, g->vertex);
               printf("New Location: %s", new->location);
               return (1);
          }
     }
}

void initializeGraph(Graph **graph)
{
     *graph = NULL;
}

int getIdByVertex(Graph *graph, char *vertex)
{
     Graph *currentNode = graph;

     while (currentNode != NULL)
     {
          if (strcmp(currentNode->vertex, vertex) == 0)
          {
               return currentNode->id;
          }
          currentNode = currentNode->next;
     }
     return -1;
}

int getIdByGeocode(Graph *graph, char *geocode)
{
     Graph *currentNode = graph;

     while (currentNode != NULL)
     {
          if (strcmp(currentNode->geocode, geocode) == 0)
          {
               return currentNode->id;
          }
          currentNode = currentNode->next;
     }
     return -1;
}

Graph *findMinWeightVertex(Graph *graph)
{
     float minWeight = FLT_MAX;
     Graph *minVertex = NULL;
     Graph *currentNode = graph;

     // Traverse the graph vertices
     while (currentNode != NULL)
     {
          Adjacent *adjacent = currentNode->adjacents;

          // Check if the adjacent nodes exist
          if (adjacent != NULL)
          {
               // Iterate over the adjacent nodes
               while (adjacent != NULL)
               {
                    if (adjacent->weight < minWeight)
                    {
                         minWeight = adjacent->weight;
                         minVertex = currentNode;
                    }

                    adjacent = adjacent->next;
               }
          }

          currentNode = currentNode->next;
     }
     return minVertex;
}

float dijkstra(Graph *graph, char *initial, char *final)
{
     Graph *aux = graph;
     Graph *aux1 = graph;
     // Create distance and visited arrays
     float distances[SIZE];
     int visited[SIZE];
     int route[SIZE];
     float weight[SIZE];

     // Initialize distances and visited arrays
     for (int i = 0; i < SIZE; i++)
     {
          distances[i] = FLT_MAX;
          visited[i] = 0;
          route[i] = -1;
          weight[i] = 0;
     }

     // Set the distance of the initial location to 0
     int initialIndex = getIdByVertex(graph, initial);
     distances[initialIndex] = 0;

     // Dijkstra's algorithm
     float totalDistance = 0.0;
     while (1)
     {
          // Find the vertex with the minimum distance among unvisited vertices
          Graph *minVertex = NULL;
          float minDistance = INFINITY;

          // Iterate over all vertices
          Graph *current = aux;
          while (current != NULL)
          {
               if (!visited[current->id] && distances[current->id] < minDistance)
               {
                    minVertex = current;
                    minDistance = distances[current->id];
               }
               current = current->next;
          }

          // If all vertices have been visited or the final location is reached, break the loop
          if (minVertex == NULL || strcmp(minVertex->vertex, final) == 0)
          {
               break;
          }

          // Mark the current vertex as visited
          visited[minVertex->id] = 1;

          // Update distances of neighboring vertices
          Adjacent *adjacent = minVertex->adjacents;
          while (adjacent != NULL)
          {

               int adjacentIndex = getIdByGeocode(aux1, adjacent->vertex);
               if (!visited[adjacentIndex] && distances[minVertex->id] != FLT_MAX &&
                   distances[minVertex->id] + adjacent->weight < distances[adjacentIndex])
               {
                    distances[adjacentIndex] = distances[minVertex->id] + adjacent->weight;
                    route[adjacentIndex] = minVertex->id;
                    weight[adjacentIndex] = adjacent->weight;
               }
               adjacent = adjacent->next;
          }

          // Move to the next unvisited node
     }
     aux = aux->next;
     // Return the minimum cost from the initial to the final location
     int finalIndex = getIdByVertex(graph, final);
     printRoute(route, weight, finalIndex);
     return totalDistance;
}

int printRoute(int *route, float *weight, int finalIndex)
{
     float totalRoute = 0.0;

     if (route[finalIndex] == -1)
     {
          printf("No route found.\n");
          return -1;
     }

     int path[SIZE];
     float pathWeights[SIZE];
     int count = 0;
     int currentIndex = finalIndex;

     // Build the route path and path weights
     while (currentIndex != -1)
     {
          path[count] = currentIndex;
          pathWeights[count] = weight[currentIndex];
          count++;
          currentIndex = route[currentIndex];
     }

     // Print the route and corresponding weights in reverse order
     printf("Shortest route:\n");
     for (int i = count - 1; i >= 0; i--)
     {
          printf("Vertex: %d, Weight: %.2f\n", path[i], pathWeights[i]);
          totalRoute += pathWeights[i];
     }
     printf("\n VALOR: %.2f", totalRoute);
     return totalRoute;
}

int convertVertexToID(Graph **g, char *vertex)
{
     Graph *aux = *g;
     int locationFound;

     while (aux != NULL)
     {
          if (strcmp(aux->vertex, vertex) == 0)
          {
               locationFound = aux->id;
               printf("Location Found: %d", locationFound);
               return 1;
          }
          aux = aux->next;
     }
     return 0;
}

int convertIdToLocation(Graph **g, int locationID)
{
     Graph *aux = *g;
     char locationFound[MAX_LENGTH_LOCATION];

     while (aux != NULL)
     {
          if (aux->id == locationID)
          {
               strcpy(locationFound, aux->vertex);
               return 1;
          }
          aux = aux->next;
     }
     return 0;
}

int convertCodeToVertex(Graph **g, char *geocode, char *respVertex)
{
     Graph *aux = *g;
     char locationFound[MAX_LENGTH_LOCATION];

     while (aux != NULL)
     {
          if (strcmp(aux->geocode, geocode) == 0)
          {
               strcpy(locationFound, aux->vertex);
               strcpy(respVertex, locationFound);
               return 1;
          }
          aux = aux->next;
     }
     return 0;
}

int getMaxVertexId(Graph *head)
{
     int maxId = 0;
     Graph *current = head;
     while (current != NULL)
     {
          if (current->id > maxId)
          {
               maxId = current->id;
          }
          current = current->next;
     }
     return maxId;
}

Graph *insertGraph(Graph *head, int id, char vertex[SIZE], char geocode[SIZE], float minCost)
{
     Graph *new = malloc(sizeof(struct graph2));
     if (new != NULL)
     {
          new->id = id;
          strcpy(new->vertex, vertex);
          strcpy(new->geocode, geocode);
          new->minCost = minCost;
          return (new);
     }
     else
          return (head);
}

Graph *readGraphBinary()
{
     FILE *fp;

     Graph *aux = NULL;

     fp = fopen("graphBinary.bin", "rb");
     if (fp == NULL)
     {
          printf("Erro ao abrir o ficheiro.");
          return NULL;
     }
     while (!feof(fp))
     {
          Graph graph;
          size_t bytes_read = fread(&graph, sizeof(Graph), 1, fp);
          if (bytes_read == 1)
          {
               // change to insertGraph
               // aux = insertVehicle(aux, graph.id, vehicle.type, vehicle.autonomy, vehicle.maxAutonomy, vehicle.battery, vehicle.cost, vehicle.rentedBy, vehicle.location);
          }
     }
     fclose(fp);
     return (aux);
}

int saveGraphBinary(Graph *head)
{
     FILE *fp;
     fp = fopen("graphBinary.bin", "wb");
     if (fp == NULL)
     {
          printf("Erro ao abrir o ficheiro.\n");
     }
     else if (fp != NULL)
     {
          Graph *aux = head;
          while (aux != NULL)
          {
               // Change to graph info
               fwrite(aux, sizeof(Graph), 1, fp);
               aux = aux->next;
          }
          fclose(fp);
          return (1);
     }
     else
          return (0);
}

int saveGraph(Graph *head)
{
     FILE *fp;
     fp = fopen("graph.txt", "w");
     if (fp != NULL)
     {
          Graph *aux = head;
          while (aux != NULL)
          {
               // Change to graph info
               fprintf(fp, "%d:%f\n", aux->id, aux->adjacents->weight);
               aux = aux->next;
          }
          fclose(fp);
          return (1);
     }
     else
          return (0);
}

Graph *readGraph()
{
     FILE *fp;
     int id, autonomy, maxAutonomy;
     float cost, battery;
     char type[15], location[20];
     int rentedBy;

     Graph *aux = NULL;
     fp = fopen("graph.txt", "r");
     if (fp != NULL)
     {
          char line[MAX_LINE];
          while (fgets(line, sizeof(line), fp))
          {
               // Change to insertGraph
               sscanf(line, "%d,%[^,],%d,%f,%f,%d,%[^\r\n]", &id, type, &autonomy, &battery, &cost, &rentedBy, location);

               // aux = insertVehicle(aux, id, type, autonomy, maxAutonomy, battery, cost, rentedBy, location);
          }
          fclose(fp);
     }
     return (aux);
}