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

#endif