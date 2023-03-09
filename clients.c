#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clients.h"

<<<<<<< HEAD
Client* insertClient(Client* head, int id, char name[],int age,char NIF[],float balance,char address[], char email[], char pw[])
=======
// Verifies if the ID of the client exists on the list
int clientIdExists(Client *head, int id)
>>>>>>> d68f201f96ee2992408f5938338425943f7c8b55
{
 Client *current = head;
 while (current != NULL)
 {
		if (current->id == id)
		{
			return 1;
		}
		current = current->next;
 }
 return 0;
}

// Insert a new client
Client *insertClient(Client *head, int id, char name[], int age, char NIF[], float balance, char address[], int totalVehiclesRented)
{
 Client *new = malloc(sizeof(struct listClients));
 if (new != NULL)
 {
		new->id = id;
		strcpy(new->name, name);
		new->age = age;
		strcpy(new->NIF, NIF);
		new->balance = balance;
		strcpy(new->address, address);
		strcpy(new->email,email);
        strcpy(new->password,pw);
		new->next = head;
		return (new);
 }
 else
		return (head);
}

// Remove an existing client
Client *removeClient(Client *head, int id)
{
 Client *previous = head, *current = head, *aux;

 if (current == NULL)
		return NULL;
 else if (current->id == id)
 {
		aux = current->next;
		free(current);
		return (aux);
 }
 else
 {
		while ((current != NULL) && (current->id != id))
		{
			previous = current;
			current = current->next;
		}
		if (current == NULL)
			return (head);
		else
		{
			previous->next = current->next;
			free(current);
			return (head);
		}
 }
}