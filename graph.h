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
     int id;
     char geocode[SIZE];
     char vertex[SIZE];
     float minCost;
     Adjacent *adjacents;
     Vehicle *vehicles;
     struct graph2 *next;
} Graph;

typedef struct route{
     char vertex[MAX_LENGTH];
     float weight;
}Route;

// Creates a new vertex
int createVertex(Graph **g, int id, char *newVertex);

int vertexExists(Graph *g, char vertex[]);

int createEdge(Graph *g, char vOrigin[], char vDestination[], float weight);

void listAdjacents(Graph *g, char *vertex);

void listVertexes(Graph **graph);

int convertLocationID(Graph **g,int locationID);

int addVehicleLoc(Graph *g, char geocode[], int vehicleID);

int getBestRoute(Graph **g, int startLocID, int endLocID);

int getMaxVertexId(Graph *head);

Graph *insertGraph(Graph *head, int id,char vertex[SIZE],char geocode[SIZE],float minCost);

Graph* findMinWeightVertex(Graph* graph);

Graph *readGraphBinary();

int saveGraphBinary(Graph *head);

int saveGraph(Graph *head);

Graph *readGraph();

#endif