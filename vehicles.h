#ifndef VEHICLE
#define VEHICLE
extern int totVehicles;

typedef struct listManagers Manager;
typedef struct listClients Client;

typedef struct listVehicles
{
 int id;
 char type[20];
 int autonomy;
 float cost;
 char location[20];
 Client *c;
 struct listVehicles *next;
} Vehicle;

// Verifies if the ID of the vehicles exists on the list
int vehicleIdExists(Vehicle *head, int id);

// Lists vehicles
void listVehicles(Vehicle *head);

// Adds a new vehicle
Vehicle *insertVehicle(Vehicle *head, int id, char type[], int autonomy, float cost, char location[]);

// Remove an existing vehicle
Vehicle *removeVehicle(Vehicle *head, int id);

// Sort vehicles by descending order of autonomy
void sortVehiclesByAutonomy(Vehicle *head);

// Save managers in a txt
int saveVehicles(Vehicle *head);

// Read vehicles from txt file
Vehicle *readVehicles();

#endif