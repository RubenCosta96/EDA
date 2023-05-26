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

typedef struct
{
     float distance;
     int previous;
} PathData;

// Creates a new vertex
int createVertex(Graph **g, int id, char *newVertex, char *newGeocode);

int vertexExists(Graph *g, char geocode[]);

int createEdge(Graph *g, char vOrigin[], char vDestination[], float weight);

void listAdjacents(Graph *g, char *geocode);

// NEW--
void initializeGraph(Graph **graph);

int getIdByVertex(Graph *graph, char *vertex);

int getIdByGeocode(Graph *graph, char *geocode);

Graph *findMinWeightVertex(Graph *graph);

float dijkstra(Graph *graph, char *initial, char *final);

void printRoute(int *route, int finalIndex);
// --

void listVertexes(Graph **graph);

int convertVertexToID(Graph **g, char *vertex);

int convertIdToLocation(Graph **g, int locationID);

int convertCodeToVertex(Graph **g, char *geocode, char *respVertex);

int addVehicleLoc(Graph *g, char geocode[], int vehicleID);

int getMaxVertexId(Graph *head);

Graph *insertGraph(Graph *head, int id, char vertex[SIZE], char geocode[SIZE], float minCost);

Graph *findMinWeightVertex(Graph *graph);

Graph *readGraphBinary();

int saveGraphBinary(Graph *head);

int saveGraph(Graph *head);

Graph *readGraph();

#endif