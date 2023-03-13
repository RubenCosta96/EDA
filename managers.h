#ifndef MANAGERS
#define MANAGERS
extern int totManagers;

typedef struct listVehicles Vehicle;

typedef struct listManagers
{
 int id;
 char name[50];
 char email[30];
 char password[16];
 struct listManagers *next;
} Manager;

// Verifies if the ID of the manager exists on the list
int managerIdExists(Manager *head, int id);

// Inserts a new manager
Manager *insertManager(Manager *head, int id, char name[], char email[], char pw[]);

// Lists all the managers
void listManagers(Manager *head);

// Change data from a manager
int changeManagerData(Manager *head, int id);

// Remove a manager from the list
Manager *removeManager(Manager *head, int id);

// Sort managers by variable selected from user input;
Manager *orderManagers(Manager *head);

// Save managers in a txt
int saveManagers(Manager *head);

// Read managers data saved in txt file
Manager *readManagers();

#endif
