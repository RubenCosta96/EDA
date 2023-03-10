#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vehicles.h"
#define MAX_LINE 100

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

// Show list of vehicles
void listVehicles(Vehicle *head)
{
 for (; head != NULL; head = head->next)
 {
		printf("%d %s %d %f %s\n", head->id, head->type, head->autonomy, head->cost, head->location);
 }
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
Vehicle *insertVehicle(Vehicle *head, int id, char type[], int autonomy, float cost, char location[])
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

void sortVehiclesByAutonomy(Vehicle *head)
{
 if (head == NULL)
		return;

 // create a temporary linked list to hold the sorted nodes
 Vehicle *sortedList = NULL;

 while (head != NULL)
 {
		// remove the first node from the unsorted list
		Vehicle *current = head;
		head = current->next;

		// find the appropriate position for the node in the sorted list
		Vehicle **insertionPoint = &sortedList;
		while (*insertionPoint != NULL && compare((*insertionPoint)->autonomy, current->autonomy) > 0)
		{
			insertionPoint = &((*insertionPoint)->next);
		}

		// insert the node into the sorted list
		current->next = *insertionPoint;
		*insertionPoint = current;
 }

 // set the head of the original list to the head of the sorted list
 head = sortedList;
 listVehicles(sortedList);
}

// Save vehicles in a txt file
int saveVehicles(Vehicle *head)
{
 FILE *fp;
 fp = fopen("vehicles.txt", "w");
 if (fp != NULL)
 {
		Vehicle *aux = head;
		while (aux != NULL)
		{
			fprintf(fp, "%d,%s,%d,%f,%s;", aux->id, aux->type,
											aux->autonomy, aux->cost, aux->location);
			aux = aux->next;
		}
		fclose(fp);
		return (1);
 }
 else
		return (0);
}

// Read vehicles from txt file
Vehicle *readVehicles()
{
 FILE *fp;
 int id, autonomy;
 float cost;
 char type[15], location[20];

 Vehicle *aux = NULL;
 fp = fopen("vehicles.txt", "r");
 if (fp != NULL)
 {
		char line[MAX_LINE];
		while (fgets(line, sizeof(line), fp))
		{
			sscanf(line, "%d,%14[^,\n],%d,%f,%19[^\n]", &id, type, &autonomy, &cost, location);
			aux = insertVehicle(aux, id, type, autonomy, cost, location);
		}
		fclose(fp);
 }
 return (aux);
}