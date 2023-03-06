#include <stdio.h>
#ifndef MANAGERS
#define MANAGERS

typedef struct listVehicles Vehicle;

typedef struct listManagers
{
 int id;
 char name[50];
 int numVehicles;
 Vehicle *vehicles[50];
 struct listManagers *next;
} Manager;

// Inserts a new manager
Manager* insertManager(Manager *head, int id, char name[], int numVehicles);

// Lists all the managers
void listManagers(Manager *head);

//Remove a manager from the list
Manager* removeManager(Manager* head, int id);

//Sort managers by variable selected from user input;
Manager* orderManagers(Manager* head);

#endif
