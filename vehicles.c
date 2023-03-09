#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vehicles.h"

// Sorts vehicles by autonomy
int compare(int aut1, int aut2)
{
 if (aut1 < aut2)
		return -1;
 else if (aut1 > aut2)
		return 1;
 else
		return 0;
}

// Verifies if the ID of the vehicles exists on the list
int vehicleIdExists(Vehicle *head, int id)
{
 Vehicle *current = head;
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

// Adds a new vehicle
Vehicle *insertVehicle(Vehicle *head, int id, char name[], char type[], int autonomy, float cost, char location[])
{
 Vehicle *new = malloc(sizeof(struct listVehicles));
 if (new != NULL)
 {
		new->id = id;
		strcpy(new->type, type);
		new->autonomy = autonomy;
		new->cost = cost;
		strcpy(new->location, location);
		new->next = head;
		return (new);
 }
 else
		return (head);
}

// Remove an existing vehicle
Vehicle *removeVehicle(Vehicle *head, int id)
{
 Vehicle *previous = head, *current = head, *aux;

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

// Sort vehicles by descending order of autonomy

Vehicle *sortVehiclesDescending(Vehicle *head, int (*compare)(int aut1, int aut2))
{
 Vehicle i, j;
 Vehicle *aux = head;

 if (head == NULL || compare(autonomy, head->autonomy) < 0)
 {
		n->next = head;
		return n;
 }
}
