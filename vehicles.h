#ifndef VEHICLE
#define VEHICLE
#define MAX_LENGTH_LOCATION 60
#define MAX_LENGTH 50

typedef struct listManagers Manager;
typedef struct listClients Client;
typedef struct graph2 Graph;
typedef struct history History;

typedef struct listVehicles
{
     int id;
     char type[20];
     int autonomy, maxAutonomy;
     float cost, battery;
     char location[MAX_LENGTH_LOCATION];
     int rentedBy;
     struct listVehicles *next;
} Vehicle;

// Compares autonomies, used in sortByAutonomy function
int compare(int aut1, int aut2);

// Get clients max ID
int getMaxVehicleId(Vehicle *head);

// Verifies if the ID of the vehicles exists on the list (CHECK AGAIN)
int vehicleIdExists(Vehicle *head, int id);

// Registers a vehicle
void vehicleReg(Vehicle **head, Graph **g);

// Change data of vehicles (Only accessible by managers)
void changeVehicleData(Vehicle **head,Graph **g, int id);

// Lists vehicles not rented
int listVehiclesNotRented(Vehicle **head);

// Lists vehicles rented by a certain client
int listVehiclesRentedByClient(Vehicle **head, int vehicleID);

// Lists vehicles (DONE)
void listVehicles(Vehicle **head);

// Cancel Rental
void cancelRental(Vehicle **head, int vehicleID);

// Adds a new vehicle (CHECK AGAIN)
Vehicle *insertVehicle(Vehicle *head, int id, char type[], int autonomy, int maxAutonomy, float battery, float cost, int rentedBy, char location[]);

// Remove an existing vehicle (DONE)
void removeVehicle(Vehicle **head, int id);

// Sort vehicles by descending order of autonomy (CHECK AGAIN)
void sortVehiclesByAutonomy(Vehicle **head);

// Rent vehicle function
int rentVehicle(Vehicle **head, int vehicleID, Client *c, History **hist);

// Save vehicles in a txt (DONE)
int saveVehicles(Vehicle *head);

// Read vehicles from txt file (DONE)
Vehicle *readVehicles();

// Save managers in a binary file (DONE)
int saveVehiclesBinary(Vehicle *head);

// Read vehicles from a binary file (DONE)
Vehicle *readVehiclesBinary();

#endif