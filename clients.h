#ifndef CLIENTS
#define CLIENTS

typedef struct listVehicles Vehicle;

typedef struct listClients
{
 int id;
 char name[30];
 int age;
 char NIF[9];
 float balance;
 char address[50];
 char email[30];
 char password[16];
 Vehicle *v;
 struct listClients *next;
} Client;

// Verifies if the ID of the client exists on the list
int clientIdExists(Client *head, int id);

// Insert a new client
Client *insertClient(Client *head, int id, char name[], int age, char NIF[], float balance, char address[], int totalVehiclesRented);

// Remove an existing client
Client *removeClient(Client *head, int id);

#endif