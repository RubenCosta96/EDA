#ifndef CLIENTS
#define CLIENTS
extern int totClients;

typedef struct listVehicles Vehicle;

typedef struct listClients
{
 int id;
 char name[50];
 int age;
 char NIF[9];
 float balance;
 char address[50];
 char email[30];
 char password[16];
 struct listClients *next;
} Client;

// Verifies if the ID of the client exists on the list
int clientIdExists(Client *head, int id);

// Registers a new client
void clientReg(Client **head);

// Show list of clients
void listClients(Client *head);

// Insert a new client
Client *insertClient(Client *head, int id, char name[], int age, char NIF[], float balance, char address[], char email[], char pw[]);

// Remove an existing client
Client *removeClient(Client *head, int id);

// Save managers in a txt
int saveClients(Client *head);

// Read vehicles from txt file
Client *readClients();

#endif