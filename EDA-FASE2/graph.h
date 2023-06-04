#ifndef GRAPH
#define GRAPH

typedef struct listVehicles Vehicle;
typedef struct listManagers Manager;
typedef struct history History;
typedef struct graph1 Adjacent;
typedef struct graph2 Graph;

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
     Adjacent *adjacents;
     Vehicle *vehicles;
     struct graph2 *next;
} Graph;

// Creates a new vertex
int createVertex(Graph **g, char *newVertex, char *newGeocode);

int vertexExists(Graph *g, char geocode[]);

int createEdge(Graph *g, char vOrigin[], char vDestination[], float weight);

void listAdjacents(Graph *g, char *geocode);

void initializeGraph(Graph **graph);

int getIdByVertex(Graph *graph, char *vertex);

int getIdByGeocode(Graph *graph, char *geocode);

int getGeocodeByVertex(Graph **graph, char *vertex, char *geocode);

Graph *findMinWeightVertex(Graph *graph);

float dijkstra(Graph *graph, char *initial, char *final, float *dist, int id);

void locationsBelowDistance(Graph *graph, Vehicle *v, char *initial, float distance);

float printRoute(int *route, float *weight, int finalIndex, int id);

float getLowestDistance(float *distances, int numVertices);

void listVertexes(Graph **graph);

int convertVertexToID(Graph **g, char *vertex);

int convertIdToLocation(Graph **g, int locationID, char *location);

int convertCodeToVertex(Graph **g, char *geocode, char *respVertex);

int getMaxVertexId(Graph *head);

Graph *insertGraph(Graph *head, int id, char vertex[SIZE], char geocode[SIZE]);

int saveAdjacents(Adjacent *head);

Graph *readGraphBinary();

void saveGraphBinary(Graph *head);

int saveGraph(Graph *head);

Graph *readGraph();

Graph *readAdjacents(Graph *g);

#endif