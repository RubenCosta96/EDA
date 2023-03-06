#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clients.h"

Client* insertClient(Client* head, int id, char name[],int age,char NIF[],float balance,char address[], int totalVehiclesRented)
{
	Client* new = malloc(sizeof(struct listClients));
	if (new != NULL)
	{
		new->id = id;
		strcpy(new->name, name);
		new->age = age;
		strcpy(new->NIF, NIF);
		new->balance = balance;
		strcpy(new->address, address);
		new->totalVehiclesRented = totalVehiclesRented;
		new->next = head;
		return (new);
	}
	else
		return (head);
}