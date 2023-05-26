#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "vehicles.h"
#include "menuFuncs.h"
#include "clients.h"
#include "history.h"
#include "graph.h"
#define MAX_LINE 250

/**
 * @brief Function that recieves values of the autonomy from 2 vehicles and compares them.
 *
 * @param aut1
 * @param aut2
 * @return int
 */
int compare(int aut1, int aut2)
{
	if (aut1 < aut2)
		return -1;
	else if (aut1 > aut2)
		return 1;
	else
		return 0;
}

/**
 * @brief Gets the highest value of the IDs of the vehicles registered
 *
 * @param head
 * @return int
 */
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

/**
 * @brief Prints on the terminal the list of vehicles registered
 *
 * @param v
 */
void listVehicles(Vehicle **v)
{
	Vehicle *head = *v;
	printf("ID\tType\t\tAutonomy\tCost\tRented By\tLocation\n");
	for (; head != NULL; head = head->next)
	{
		printf("%d\t%s\t%d\t\t%.2f\t%d\t\t%s\n", head->id, head->type, head->autonomy, head->cost, head->rentedBy, head->location);
	}
}

/**
 * @brief Prints on the terminal the list of vehicles that are rented by the client that's logged in.
 *
 * @param vehicle
 * @param clientID
 * @return int
 */
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

/**
 * @brief Prints on the terminal the list of vehicles that are available to be rented.
 *
 * @param vehicle
 * @return int
 */
int listVehiclesNotRented(Vehicle **vehicle)
{
	Vehicle *head = *vehicle;
	int freeVehicles = 0;
	printf("ID\tType\t\tAutonomy\tCost per minute\t\tLocation\n");
	for (; head != NULL; head = head->next)
	{
		if (head->rentedBy <= 0)
		{
			printf("%d\t%s\t%d\t\t%.2f\t\t%s\n", head->id, head->type, head->autonomy, head->cost, head->location);
			freeVehicles++;
		}
	}
	if (freeVehicles == 0)
	{
		clearConsole();
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

/**
 * @brief Function to insert a new vehicle into the already existing linked list of vehicles
 *
 * @param head
 * @param id
 * @param type
 * @param autonomy
 * @param cost
 * @param rentedBy
 * @param location
 * @return Vehicle*
 */
Vehicle *insertVehicle(Vehicle *head, int id, char type[], int autonomy, int maxAutonomy, float battery, float cost, int rentedBy, char location[])
{
	Vehicle *new = malloc(sizeof(struct listVehicles));
	if (new != NULL)
	{
		new->id = id;
		strcpy(new->type, type);
		new->autonomy = autonomy;
		new->maxAutonomy = maxAutonomy;
		new->cost = cost;
		strcpy(new->location, location);
		new->rentedBy = rentedBy;
		new->next = head;
		return (new);
	}
	else
		return (head);
}

/**
 * @brief Function that will recieve the inputs of the user to register a new vehicle
 *
 * @param head
 */
void vehicleReg(Vehicle **head, Graph **g)
{
	Graph *new = *g;
	char type[20], location[MAX_LENGTH_LOCATION], geocode[MAX_LENGTH];
	int autonomy, maxAutonomy, rentedBy, locationID;
	float cost, battery;
	int maxID = getMaxVehicleId(*head) + 1;

	printf("Vehicle ID: %d\n", maxID);
	while ((getchar()) != '\n')
		;

	printf("Type: ");
	fgets(type, sizeof(type), stdin);
	type[strcspn(type, "\n")] = 0;

	printf("Maximum autonomy: ");
	scanf("%d", &maxAutonomy);
	while ((getchar()) != '\n')
		;

	printf("Current Autonomy: ");
	scanf("%d", &autonomy);
	while ((getchar()) != '\n')
		;

	printf("In which location is your vehicle?\n");
	listVertexes(g);
	scanf("%d", &locationID);
	while (new != NULL)
	{
		if (new->id == locationID)
		{
			strcpy(location, new->vertex);
			strcpy(geocode, new->geocode);
		}
		new = new->next;
	}

	rentedBy = 0;

	printf("Cost: ");
	scanf("%f", &cost);

	*head = insertVehicle(*head, maxID, type, autonomy, maxAutonomy, battery, cost, rentedBy, location);
}

/**
 * @brief Function that allows the manager to change any of the fields of the selected vehicle's data.
 *
 * @param head
 * @param id
 */
void changeVehicleData(Vehicle **head, Graph **g, int id)
{
	Vehicle *aux = *head;
	int opt, newLocation;
	char newType[20];
	int newAutonomy, newRentedBy, newLocationID;
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
				listVertexes(g);
				scanf("%d", &newLocation);
				aux->id = convertIdToLocation(g, newLocation); // receber localização converter para ID
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
		} while (opt != 0);
	}
	else
	{
		printf("ID not found.\n");
	}
}

/**
 * @brief Removes a vehicle from the linked list.
 *
 * @param head
 * @param id
 */
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

/**
 * @brief Sorts all the vehicles in descending order of their respective autonomy, presenting a list.
 *
 * @param head
 */
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

/**
 * @brief Function that allows a vehicle to be rented by a client
 *
 * @param head
 * @param vehicleID
 * @param c
 * @return int
 */
int rentVehicle(Vehicle **head, int vehicleID, Client *c, History **hist)
{
	Vehicle *currentV = *head;
	History *newHist = *hist;
	time_t rawtime;
	time(&rawtime);

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
	else if (c->balance - currentV->cost < 0)
	{
		printf("Not enough balance.\n");
		return -1;
	}
	else if (currentV->rentedBy != 0)
	{
		printf("Vehicle is currently rented");
		return -1;
	}
	else
	{
		currentV->rentedBy = c->id;
		c->balance -= currentV->cost;
		*hist = insertHistory(*hist, c->id, c->name, vehicleID, currentV->type,
							  currentV->cost, currentV->location, *localtime(&rawtime));
		printf("Vehicle rented.\n");
	}

	return c->balance;
}

/**
 * @brief Function that allows a client to cancel a rental that was made.
 *
 * @param head
 * @param vehicleID
 */
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
		currentV->rentedBy = 0;
	}
}

/**
 * @brief Saves all the data of the vehicles in a .txt file
 *
 * @param head
 * @return int
 */
int saveVehicles(Vehicle *head)
{
	FILE *fp;
	fp = fopen("vehicles.txt", "w");
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

/**
 * @brief Reads the data present on the .txt file that has all the vehicles data saved.
 *
 * @return Vehicle*
 */
Vehicle *readVehicles()
{
	FILE *fp;
	int id, autonomy, maxAutonomy;
	float cost, battery;
	char type[15], location[20];
	int rentedBy;

	Vehicle *aux = NULL;
	fp = fopen("vehicles.txt", "r");
	if (fp != NULL)
	{
		char line[MAX_LINE];
		while (fgets(line, sizeof(line), fp))
		{
			sscanf(line, "%d,%[^,],%d,%f,%f,%d,%[^\r\n]", &id, type, &autonomy, &battery, &cost, &rentedBy, location);
			aux = insertVehicle(aux, id, type, autonomy, maxAutonomy, battery, cost, rentedBy, location);
		}
		fclose(fp);
	}
	return (aux);
}

/**
 * @brief Saves all the data of the vehicles in a binary file
 *
 * @param head
 * @return int
 */
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

/**
 * @brief Reads the data present on the binary file that has all the vehicles data saved.
 *
 * @return Vehicle*
 */
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
		Vehicle vehicle;
		size_t bytes_read = fread(&vehicle, sizeof(Vehicle), 1, fp);
		if (bytes_read == 1)
		{
			aux = insertVehicle(aux, vehicle.id, vehicle.type, vehicle.autonomy, vehicle.maxAutonomy, vehicle.battery, vehicle.cost, vehicle.rentedBy, vehicle.location);
		}
	}
	fclose(fp);
	return (aux);
}