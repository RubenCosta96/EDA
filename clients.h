#ifndef CLIENTS
#define CLIENTS

typedef struct listVehicles Vehicle;
typedef struct listManagers Manager;

typedef struct listClients
{
     int id;
     char name[50];
     int age;
     char NIF[10];
     float balance;
     char address[50];
     char email[30];
     char password[16];
     struct listClients *next;
} Client;

// Verifies if the ID of the client exists on the list(CHECK AGAIN)
int clientIdExists(Client *head, int id);

// Get clients max ID
int getMaxClientId(Client *head);

// Registers a new client (CHECK AGAIN)
void clientReg(Client **head);

// Show list of clients (DONE)
void listClients(Client **head);

// Insert a new client (CHECK AGAIN)
Client *insertClient(Client *head, int id, char name[], int age, char NIF[], float balance, char address[], char email[], char pw[]);

// Remove an existing client (DONE)
void removeClient(Client **head, int id);

// Adds a certain balance to the client (HALF DONE) #Change ID to email maybe?
void addFundsClient(Client *c, float balance);

// Presents client principal menu
void clientMenu(Client **head, Vehicle **vehicle, Client *c, Manager **manager);

// Presents list of options for the client to change the data that he wishes to update
void *changeClientData(Client *c);

// Save managers in a txt (DONE)
int saveClients(Client *head);

// Read vehicles from txt file (DONE)
Client *readClients();

#endif