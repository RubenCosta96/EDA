#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clients.h"
#include "managers.h"
#include "vehicles.h"
#include "menuFuncs.h"
#include "graph.h"

#define INFINITY 99999
#define MAX_LINE 250

int createVertex(Graph **g, int id, char *newVertex)
{
     Graph *new = malloc(sizeof(struct graph2));

     if (new != NULL)
     {
          strcpy(new->vertex, newVertex);
          new->id = id;
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
          printf("Connection: %s", vertex);
          while (strcmp(g->vertex, vertex) != 0)
               g = g->next;
          aux = g->adjacents;

          while (aux != NULL)
          {
               // printf("%s %.2f\n", aux->vertex, aux->weight);

               printf(" -> %s", aux->vertex);
               aux = aux->next;
          }
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

int getBestRoute(Graph **g, int startLocID, int endLocID)
{
     Graph *route = g;
     int routeCost = 0;

     while (g != NULL)
     {
          if (startLocID == route->id)
          {
               routeCost += route->adjacents->weight;
               route->adjacents = route->adjacents->next;
          }
          route = route->next;
     }

     return routeCost;
}


//Alterar?
void initializeGraph(Graph* graph, char* sourceVertex) {
    while (graph != NULL) {
        if (strcmp(graph->vertex, sourceVertex) == 0) {
            graph->adjacents->weight = 0.0;
            graph->minCost = 0.0;
        } else {
            graph->adjacents->weight = INFINITY;
            graph->minCost = INFINITY;
        }
        graph = graph->next;
    }
}

//Alterar?
void dijkstra(Graph* graph, char* sourceVertex) {
    initializeGraph(graph, sourceVertex);

    while (graph != NULL) {
        Graph* currentVertex = findMinWeightVertex(graph);
        Adjacent* adj = currentVertex->adjacents;

        while (adj != NULL) {
            Graph* adjacentVertex = adj->next;
            float weight = adj->weight;

            if (currentVertex->adjacents->weight + weight < adjacentVertex->adjacents->weight) {
                adjacentVertex->adjacents->weight = currentVertex->adjacents->weight + weight;
                adjacentVertex->minCost = currentVertex->minCost + weight;  // Update minimum cost
            }

            adj = adj->next;
        }

        graph = graph->next;
    }
}

Graph* findMinWeightVertex(Graph* graph) {
    Graph* minVertex = NULL;
    float minWeight = INFINITY;

    while (graph != NULL) {
        if (graph->adjacents->weight < minWeight) {
            minVertex = graph;
            minWeight = graph->adjacents->weight;
        }
        graph = graph->next;
    }
    return minVertex;
}


int convertLocationID(Graph **g,int locationID){
     Graph *aux = g;
     char locationFound[MAX_LENGTH_LOCATION];

     while(aux != NULL){
          if(aux->id == locationID){
               strcpy(locationFound,aux->vertex);
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

Graph *insertGraph(Graph *head, int id,char vertex[SIZE],char geocode[SIZE],float minCost)
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
               //change to insertGraph
			//aux = insertVehicle(aux, graph.id, vehicle.type, vehicle.autonomy, vehicle.maxAutonomy, vehicle.battery, vehicle.cost, vehicle.rentedBy, vehicle.location);
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
               //Change to graph info
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
               //Change to graph info
			fprintf(fp, "%d:%d\n", aux->id,aux->adjacents->weight);
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
               //Change to insertGraph
			sscanf(line, "%d,%[^,],%d,%f,%f,%d,%[^\r\n]", &id, type, &autonomy, &battery, &cost, &rentedBy, location);

			//aux = insertVehicle(aux, id, type, autonomy, maxAutonomy, battery, cost, rentedBy, location);
		}
		fclose(fp);
	}
	return (aux);
}