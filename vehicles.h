#ifndef VEHICLE
#define VEHICLE

typedef struct listManagers Manager;
typedef struct listClients Client;

typedef struct listVehicles
{
 int id;
 char type[10];
 int autonomy;
 float cost;
 char location[20];
 Client *c;
 struct listVehicles *next;
} Vehicle;

// Verifies if the ID of the vehicles exists on the list
int vehicleIdExists(Vehicle *head, int id);

// Adds a new vehicle
Vehicle *insertVehicle(Vehicle *head, int id, char name[], char type[], int autonomy, float cost, char location[]);

// Remove an existing vehicle
Vehicle *removeVehicle(Vehicle *head, int id);

// Sort vehicles by descending order of autonomy
Vehicle *sortVehiclesDescending(Vehicle *head, int autonomy, int (*compare)(int aut1, int aut2));

#endif