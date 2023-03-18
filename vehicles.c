#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vehicles.h"
#define MAX_LINE 250

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

// Get clients max ID
int getMaxVehicleId(Vehicle *head)
{
	int maxId = 0;
	Vehicle *current = head;
	while (current != NULL)
	{
		if (current->id > maxId)
		{
			maxId = current->id;
		}
		current = current->next;
	}
	return maxId;
}

// Show list of vehicles
void listVehicles(Vehicle **v)
{
	Vehicle *head = *v;
	printf("ID\tType\tAutonomy\tCost\tRented By\tLocation\n");
	for (; head != NULL; head = head->next)
	{
		printf("%d\t%s\t%d\t\t%.2f\t%d\t\t%s\n", head->id, head->type, head->autonomy, head->cost, head->rentedBy, head->location);
	}
}

int listVehiclesRentedByClient(Vehicle **vehicle, int clientID)
{
	Vehicle *head = *vehicle;
	int rentedVehicles = 0;
	printf("ID\tType\tAutonomy\tCost\t\tLocation\n");
	for (; head != NULL; head = head->next)
	{
		if (head->rentedBy == clientID)
		{
			printf("%d\t%s\t%d\t\t%.2f\t\t%s\n", head->id, head->type, head->autonomy, head->cost, head->location);
			rentedVehicles++;
		}
	}
	return (rentedVehicles);
}

int listVehiclesNotRented(Vehicle **vehicle)
{
	Vehicle *head = *vehicle;
	int freeVehicles = 0;
	printf("ID\tType\tAutonomy\tCost\t\tLocation\n");
	for (; head != NULL; head = head->next)
	{
		if (head->rentedBy < 0)
		{
			printf("%d\t%s\t%d\t\t%.2f\t\t%s\n", head->id, head->type, head->autonomy, head->cost, head->location);
			freeVehicles++;
		}
	}
	return freeVehicles;
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
Vehicle *insertVehicle(Vehicle *head, int id, char type[], int autonomy, float cost, int rentedBy, char location[])
{
	Vehicle *new = malloc(sizeof(struct listVehicles));
	if (new != NULL)
	{
		new->id = id;
		strcpy(new->type, type);
		new->autonomy = autonomy;
		new->cost = cost;
		strcpy(new->location, location);
		new->rentedBy = rentedBy;
		new->next = head;
		return (new);
	}
	else
		return (head);
}

// Registers a vehicle
void vehicleReg(Vehicle **head)
{
	char type[20], location[MAX_LENGTH_LOCATION];
	int autonomy, rentedBy;
	float cost;
	int maxID = getMaxVehicleId(*head) + 1;

	printf("Vehicle ID: %d\n", maxID);
	while ((getchar()) != '\n')
		;

	printf("Type: ");
	fgets(type, sizeof(type), stdin);
	type[strcspn(type, "\n")] = 0;

	printf("Autonomy: ");
	scanf("%d", &autonomy);
	while ((getchar()) != '\n')
		;

	printf("Location: ");
	fgets(location, sizeof(location), stdin);
	location[strcspn(location, "\n")] = 0;

	rentedBy = 0;

	printf("Cost: ");
	fflush(stdout);
	scanf("%f", &cost);

	*head = insertVehicle(*head, maxID, type, autonomy, cost, rentedBy, location);
}

void changeVehicleData(Vehicle **head, int id)
{
	Vehicle *aux = *head;
	int opt;
	char newType[20], newLocation[MAX_LENGTH_LOCATION];
	int newAutonomy, newRentedBy;
	float newCost;

	while (aux != NULL && aux->id != id)
	{
		aux = aux->next;
	}
	if (aux->id == id)
	{
		do
		{
			clearConsole();
			system("cat Menus/managers/vehicleMenu.txt");
			printf("Enter option: ");
			fflush(stdout);
			scanf("%d", &opt);
			printf("\n");

			switch (opt)
			{
			case 1:
				while ((getchar()) != '\n')
					;
				printf("Enter new type: ");
				fgets(newType, 20, stdin);
				newType[strcspn(newType, "\n")] = '\0';
				strcpy(aux->type, newType);
				break;
			case 2:
				while ((getchar()) != '\n')
					;
				printf("Enter new autonomy: ");
				scanf("%d", &newAutonomy);
				aux->autonomy = newAutonomy;
				break;
			case 3:
				while ((getchar()) != '\n')
					;
				printf("Enter new cost: ");
				scanf("%f", &newCost);
				aux->cost = newCost;
				break;
			case 4:
				while ((getchar()) != '\n')
					;
				printf("Enter new location: ");
				fgets(newLocation, 20, stdin);
				newLocation[strcspn(newLocation, "\n")] = '\0';
				strcpy(aux->location, newLocation);
				break;
			case 5:
				while ((getchar()) != '\n')
					;
				printf("Who is this vehicle rented by?");
				scanf("%d", &newRentedBy);
				aux->rentedBy = newRentedBy;
				break;
			case 0:
				return;
				break;
			default:
				printf("Invalid option. Please select again.\n");
				fflush(stdout);
				break;
			}
		} while (opt > 0 || opt < 5);
	}
	else
	{
		printf("ID not found.\n");
	}
}

// Remove an existing vehicle
void removeVehicle(Vehicle **head, int id)
{
	Vehicle *previous = *head, *current = *head;

	if (current == NULL)
		return;
	else if (current->id == id)
	{
		*head = current->next;
		free(current);
	}
	else
	{
		while ((current != NULL) && (current->id != id))
		{
			previous = current;
			current = current->next;
		}
		if (current == NULL)
		{
			printf("Invalid ID!");
			return;
		}
		else
		{
			previous->next = current->next;
			free(current);
		}
	}
}

// Sort vehicles by descending order of autonomy

void sortVehiclesByAutonomy(Vehicle **head)
{
	Vehicle *aux = *head;
	if (aux == NULL)
		return;

	// create a temporary linked list to hold the sorted nodes
	Vehicle *sortedList = NULL;

	while (aux != NULL)
	{
		// remove the first node from the unsorted list
		Vehicle *current = aux;
		aux = current->next;

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
	*head = sortedList;
}

int rentVehicle(Vehicle **head, int vehicleID, Client *c)
{

	Vehicle *currentV = *head;

	while (currentV != NULL && currentV->id != vehicleID)
	{
		currentV = currentV->next;
	}
	// In case user inserts invalid ID
	if (currentV == NULL)
	{
		printf("Vehicle not found.\n");
		return -1;
	}
	// Verifies if there is enough balance
	if (c->balance - currentV->cost < 0)
	{
		printf("Not enough balance.\n");
		return -1;
	}
	else if (currentV->rentedBy != -1)
	{
		printf("Vehicle is currently rented");
		return -1;
	}
	else
	{
		currentV->rentedBy = c->id;
		c->balance -= currentV->cost;
		printf("Vehicle rented.\n");
	}

	return c->balance;
}

void cancelRental(Vehicle **head, int vehicleID)
{
	Vehicle *currentV = *head;

	while (currentV != NULL && currentV->id != vehicleID)
	{
		currentV = currentV->next;
	}
	// In case user inserts invalid ID
	if (currentV == NULL)
	{
		printf("Vehicle not found.\n");
		return;
	}
	else
	{
		printf("How many km did you drive?\n");
		int distance;
		scanf("%d", &distance);
		if (distance < 0)
		{
			printf("Invalid distance.\n");
			distance = 0;
		}
		if (distance > currentV->autonomy)
		{
			printf("Distance introduced is higher than autonomy.\n");
			return;
		}
		currentV->autonomy -= distance;
		currentV->rentedBy = -1;
	}
}

// Save vehicles in a txt file
int saveVehicles(Vehicle *head)
{
	FILE *fp;
	fp = fopen("vehicles1.txt", "w");
	if (fp != NULL)
	{
		Vehicle *aux = head;
		while (aux != NULL)
		{
			fprintf(fp, "%d,%s,%d,%.2f,%d,%s\n", aux->id, aux->type,
				   aux->autonomy, aux->cost, aux->rentedBy, aux->location);
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
	int rentedBy;

	Vehicle *aux = NULL;
	fp = fopen("vehicles.txt", "r");
	if (fp != NULL)
	{
		char line[MAX_LINE];
		while (fgets(line, sizeof(line), fp))
		{
			sscanf(line, "%d,%[^,],%d,%f,%d,%[^\r\n]", &id, type, &autonomy, &cost, &rentedBy, location);
			aux = insertVehicle(aux, id, type, autonomy, cost, rentedBy, location);
		}
		fclose(fp);
	}
	return (aux);
}

// Save vehicles in a binary file
int saveVehiclesBinary(Vehicle *head)
{
	FILE *fp;
	fp = fopen("vehiclesBinary.bin", "wb");
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro.\n");
	}
	else if (fp != NULL)
	{
		Vehicle *aux = head;
		while (aux != NULL)
		{
			fwrite(aux, sizeof(Vehicle), 1, fp);
			aux = aux->next;
		}
		fclose(fp);
		return (1);
	}
	else
		return (0);
}

// Read vehicles from binary file
Vehicle *readVehiclesBinary()
{
	FILE *fp;

	Vehicle *aux = NULL;

	fp = fopen("vehiclesBinary.bin", "rb");
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro.");
		return NULL;
	}
	while (!feof(fp))
	{
		Vehicle car;
		size_t bytes_read = fread(&car, sizeof(Vehicle), 1, fp);
		if (bytes_read == 1)
		{
			aux = insertVehicle(aux, car.id, car.type, car.autonomy, car.cost, car.rentedBy, car.location);
		}
	}
	fclose(fp);
	return (aux);
}