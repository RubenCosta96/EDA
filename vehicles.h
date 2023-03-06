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

#endif