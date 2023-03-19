#ifndef MANAGERS
#define MANAGERS

typedef struct listVehicles Vehicle;

typedef struct listManagers
{
     int id;
     char name[50];
     char email[30];
     char password[16];
     struct listManagers *next;
} Manager;

// Gets managers max ID
int getMaxManagerId(Manager *head);

// Inserts a new manager
Manager *insertManager(Manager *head, int id, char name[], char email[], char pw[]);

// Manager Registration
void managerReg(Manager **head);

// Lists all the managers
void listManagers(Manager **head);

// Change data from a manager
void *changeManagerData(Manager *m);

// Remove a manager from the list
void removeManager(Manager **head, int id);

// Sort managers by variable selected from user input;
Manager *orderManagers(Manager *head);

// Save managers in a txt
int saveManagers(Manager *head);

// Read managers data saved in txt file
Manager *readManagers();

// Save managers in a bin file
int saveManagersBinary(Manager *head);

// Read managers data saved in bin file
Manager *readManagersBinary();

#endif
