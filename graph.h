#ifndef GRAPH
#define GRAPH

typedef struct listVehicles Vehicle;
typedef struct listManagers Manager;

#define SIZE 50

typedef struct graph1
{
     char vertex[SIZE];
     float weight;
     struct graph1 *next;
} Adjacent;

typedef struct graph2
{
     char vertex[SIZE];
     Adjacent *adjacents;
     Vehicle *vehicles;
     struct graph2 *next;
} Graph;

// Creates a new vertex
int createVertex(Graph **g, char *newVertex);

int vertexExists(Graph *g, char vertex[]);

int createEdge(Graph *g, char vOrigin[], char vDestination[], float weight);

void listAdjacents(Graph *g, char *vertex);

#endif