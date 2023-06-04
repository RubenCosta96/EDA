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

/**
 * @brief Creates a new vertex with the given name and geocode and adds it to the graph.
 *
 * @param g
 * @param newVertex
 * @param newGeocode
 * @return int
 */
int createVertex(Graph **g, char *newVertex, char *newGeocode)
{
     Graph *new = malloc(sizeof(struct graph2));
     int maxID = getMaxVertexId(*g) + 1;

     if (new != NULL)
     {
          new->id = maxID;
          strcpy(new->vertex, newVertex);
          strcpy(new->geocode, newGeocode);
          new->next = *g;
          new->adjacents = NULL;
          *g = new;
          return 1;
     }
     else
          return 0;
}

/**
 * @brief Checks if a vertex with the given geocode exists in the graph.
 *
 * @param g
 * @param geocode
 * @return int
 */
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

/**
 * @brief Creates a new edge between two vertices in the graph with the given weight.
 *
 * @param g
 * @param vOrigin
 * @param vDestination
 * @param weight
 * @return int
 */
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

/**
 * @brief Inserts a new adjacent vertex with the given weight to a vertex's adjacency list.
 *
 * @param head
 * @param vertex
 * @param weight
 * @return Adjacent*
 */
Adjacent *insertAdjacent(Adjacent *head, char vertex[], float weight)
{
     Adjacent *new = malloc(sizeof(struct graph1));
     if (new != NULL)
     {
          strcpy(new->vertex, vertex);
          new->weight = weight;
          new->next = head;
          return (new);
     }
     else
          return (head);
}

/**
 * @brief Lists all the adjacent vertices of a given vertex.
 *
 * @param g
 * @param geocode
 */
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

/**
 * @brief Lists all the vertices in the graph.
 *
 * @param graph
 */
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

/**
 * @brief Initializes the graph by setting the head to NULL.
 *
 * @param graph
 */
void initializeGraph(Graph **graph)
{
     *graph = NULL;
}

/**
 * @brief Returns the ID of a vertex given its name.
 *
 * @param graph
 * @param vertex
 * @return int
 */
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

/**
 * @brief Returns the ID of a vertex given its geocode.
 *
 * @param graph
 * @param geocode
 * @return int
 */
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

/**
 * @brief Returns the geocode of a vertex given its name.
 *
 * @param graph
 * @param vertex
 * @param geocode
 * @return int
 */
int getGeocodeByVertex(Graph **graph, char *vertex, char *geocode)
{
     Graph *aux = *graph;

     while (aux != NULL)
     {
          if (strcmp(aux->vertex, vertex) == 0)
          {
               strcpy(geocode, aux->geocode);
               return 1;
          }
          aux = aux->next;
     }
     return 0;
}

/**
 * @brief Finds the vertex with the minimum weight among unvisited vertices.
 *
 * @param graph
 * @return Graph*
 */
Graph *findMinWeightVertex(Graph *graph)
{
     float minWeight = FLT_MAX;
     Graph *minVertex = NULL;
     Graph *currentNode = graph;

     while (currentNode != NULL)
     {
          Adjacent *adjacent = currentNode->adjacents;

          if (adjacent != NULL)
          {

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

/**
 * @brief Finds the shortest path between two vertices using Dijkstra's algorithm.
 *
 * @param graph
 * @param initial
 * @param distances
 * @param id
 * @return float
 */
float dijkstra(Graph *graph, char *initial, char *final, float *distances, int id)
{
     Graph *aux = graph;
     Graph *aux1 = graph;
     int visited[SIZE];
     int route[SIZE];
     float weight[SIZE];

     for (int i = 0; i < SIZE; i++)
     {
          distances[i] = FLT_MAX;
          visited[i] = 0;
          route[i] = -1;
          weight[i] = 0;
     }

     int initialIndex = getIdByVertex(graph, initial);
     distances[initialIndex] = 0;

     float totalDistance = 0.0;
     while (1)
     {
          Graph *minVertex = NULL;
          float minDistance = INFINITY;

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

          if (minVertex == NULL || strcmp(minVertex->vertex, final) == 0)
          {
               break;
          }

          visited[minVertex->id] = 1;

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
     }
     aux = aux->next;
     int finalIndex = getIdByVertex(graph, final);
     return printRoute(route, weight, finalIndex, id);
}

/**
 * @brief Prints the shortest path and corresponding weights.
 *
 * @param route
 * @param weight
 * @param finalIndex
 * @param id
 * @return float
 */
float printRoute(int *route, float *weight, int finalIndex, int id)
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

     while (currentIndex != -1)
     {
          path[count] = currentIndex;
          pathWeights[count] = weight[currentIndex];
          count++;
          currentIndex = route[currentIndex];
     }

     printf("Shortest route:\n");
     for (int i = count - 1; i >= 0; i--)
     {
          printf("Vertex: %d, Weight: %.2f\n", path[i], pathWeights[i]);
          totalRoute += pathWeights[i];
     }
     if (id == 0)
     {
          printf("\n Lowest value route: %.2f", totalRoute);
     }
     return totalRoute;
}

/**
 * @brief Prints the locations and vehicles within a certain distance from a given location.
 *
 * @param graph
 * @param v
 * @param initial
 * @param distance used to calculate the max distance other vehicles can be
 */
void locationsBelowDistance(Graph *graph, Vehicle *v, char *initial, float distance)
{
     Graph *gAux = graph;
     Vehicle *vAux = v;
     float dist[SIZE];
     char type[SIZE];

     for (int i = 0; i < 10; i++)
     {
          dist[i] = 9999.0;
     }
     printf("Vehicles in the radius of %.2f km are:\n", distance);
     while (gAux != NULL)
     {
          dijkstra(graph, initial, gAux->vertex, dist, 1);

          if (dist[gAux->id] <= distance && dist[gAux->id] != 0)
          {
               printf("Location: %s, Distance: %.2f\n", gAux->vertex, dist[gAux->id]);
               findVehicleInVertex(&vAux, gAux->vertex, type);
          }

          gAux = gAux->next;
     }
}

/**
 * @brief Converts a vertex name to its corresponding ID.
 *
 * @param g
 * @param vertex
 * @return int
 */
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

/**
 * @brief Converts a location ID to its corresponding vertex name.
 *
 * @param g
 * @param locationID
 * @param location
 * @return int
 */
int convertIdToLocation(Graph **g, int locationID, char *location)
{
     Graph *aux = *g;

     while (aux != NULL)
     {
          if (aux->id == locationID)
          {
               strcpy(location, aux->vertex);
               return 1;
          }
          aux = aux->next;
     }
     return 0;
}

/**
 * @brief Converts a geocode to its corresponding vertex name.
 *
 * @param g
 * @param geocode
 * @param respVertex
 * @return int
 */
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

// Not working correctly, fix or change
void pickUpVehicles(Vehicle **vehicles, Graph **g, char *initial, char *final, int truckCapacity)
{
     Vehicle *vAux = *vehicles;
     Graph *gAux = *g;

     float distances[SIZE];
     dijkstra(gAux, initial, final, distances, 0);

     // Collects vehicles below 50% battery level
     int collectedCount = 0;
     Vehicle *currentVehicle = vAux;
     while (currentVehicle != NULL && collectedCount < truckCapacity)
     {
          if (currentVehicle->battery < 50.00)
          {
               printf("Collecting Vehicle %d at Location %s\n", currentVehicle->id, currentVehicle->location);
               collectedCount++;
          }
          currentVehicle = currentVehicle->next;
     }
}

/**
 * @brief Returns the maximum ID among the vertices in the graph.
 *
 * @param head
 * @return int
 */
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

/**
 * @brief Inserts a new graph node with the given ID, vertex name, and geocode.
 *
 * @param head
 * @param id
 * @param vertex
 * @param geocode
 * @return Graph*
 */
Graph *insertGraph(Graph *head, int id, char vertex[SIZE], char geocode[SIZE])
{
     Graph *new = malloc(sizeof(struct graph2));
     if (new != NULL)
     {
          new->id = id;
          strcpy(new->vertex, vertex);
          strcpy(new->geocode, geocode);
          return (new);
     }
     else
          return (head);
}

/**
 * @brief Returns the lowest distance from an array of distances.
 *
 * @param distances
 * @param numVertices
 * @return float
 */
float getLowestDistance(float *distances, int numVertices)
{
     float minDistance = FLT_MAX;

     for (int i = 0; i < numVertices; i++)
     {
          if (distances[i] < minDistance)
          {
               minDistance = distances[i];
          }
     }

     return minDistance;
}

/**
 * @brief Reads the graph data from a binary file.
 *
 * @return Graph*
 */
Graph *readGraphBinary()
{
     FILE *file = fopen("graphbinary.bin", "rb");
     if (file == NULL)
     {
          printf("Failed to open the file for reading.\n");
          return NULL;
     }

     // Read the graph nodes from the file
     Graph *head = NULL;
     Graph *current = NULL;

     while (1)
     {
          // Read the next graph node from the file
          Graph *node = (Graph *)malloc(sizeof(Graph));
          size_t itemsRead = fread(node, sizeof(Graph), 1, file);

          if (itemsRead != 1)
          {
               // No more nodes to read
               free(node);
               break;
          }

          // Add the node to the linked list
          if (head == NULL)
          {
               head = node;
               current = node;
          }
          else
          {
               current->next = node;
               current = node;
          }
     }

     // Close the file
     fclose(file);

     return head;
}

/**
 * @brief Saves the graph data to a binary file.
 *
 * @param head
 * @return int
 */
void saveGraphBinary(Graph *graph)
{
     // Open the binary file for writing
     FILE *file = fopen("graphbinary.bin", "wb");
     if (file == NULL)
     {
          printf("Failed to open the file for writing.\n");
          return;
     }

     // Write each graph node to the file
     Graph *current = graph;
     while (current != NULL)
     {
          // Write the entire graph node structure
          fwrite(current, sizeof(Graph), 1, file);

          // Move to the next node
          current = current->next;
     }

     // Close the file
     fclose(file);
}

/**
 * @brief Saves graph and adjacents data in a txt file.
 *
 * @param head
 * @return int
 */
int saveGraph(Graph *head)
{
     FILE *graphFile;
     FILE *adjacentFile;
     graphFile = fopen("graph.txt", "w");
     adjacentFile = fopen("adjacents.txt", "w");

     if (graphFile != NULL && adjacentFile != NULL)
     {
          Graph *graphAux = head;
          while (graphAux != NULL)
          {
               // Save graph information to graph.txt
               fprintf(graphFile, "%s,%s\n", graphAux->vertex, graphAux->geocode);

               Adjacent *adjacentAux = graphAux->adjacents;
               while (adjacentAux != NULL)
               {
                    // Save adjacent information to adjacents.txt
                    fprintf(adjacentFile, "%s,%s,%.2f\n", graphAux->geocode, adjacentAux->vertex, adjacentAux->weight);

                    adjacentAux = adjacentAux->next;
               }

               graphAux = graphAux->next;
          }

          fclose(graphFile);
          fclose(adjacentFile);
          return 1;
     }
     else
          return 0;
}

/**
 * @brief Read data from a txt file and stores it in the Graph linked list.
 *
 * @return Graph*
 */
Graph *readGraph()
{
     FILE *fp;
     char geocode[SIZE], vertex[SIZE];

     Graph *aux = NULL;
     fp = fopen("graph.txt", "r");
     if (fp != NULL)
     {
          char line[MAX_LINE];
          while (fgets(line, sizeof(line), fp))
          {
               sscanf(line, "%[^,],%[^,\r\n]", vertex, geocode);
               createVertex(&aux, vertex, geocode);
          }
          fclose(fp);
     }
     return (aux);
}

/**
 * @brief Read data from a txt file and stores it in the Adjacent part of the Graph linked list.
 *
 * @param g
 * @return Graph*
 */
Graph *readAdjacents(Graph *g)
{
     FILE *fp;
     char geocodeInit[SIZE], geocodeFin[SIZE];
     float weight;

     fp = fopen("adjacents.txt", "r");
     if (fp != NULL)
     {
          char line[MAX_LINE];
          while (fgets(line, sizeof(line), fp))
          {
               sscanf(line, "%[^,],%[^,],%f\n", geocodeInit, geocodeFin, &weight);
               createEdge(g, geocodeInit, geocodeFin, weight);
          }
          fclose(fp);
     }
     return (g);
}