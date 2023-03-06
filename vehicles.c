#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vehicles.h"

Vehicle* insertVehicle(Vehicle* head, int id, char name[], char type[], int autonomy, float cost, char location[])
{
	Vehicle* new = malloc(sizeof(struct listVehicles));
	if (new != NULL)
	{
		new->id = id;
		strcpy(new->type, type);
		new->autonomy =  autonomy;
		new->cost = cost;
		strcpy(new->location, location);
		new->next = head;
		return (new);
	}
	else
		return (head);
}
