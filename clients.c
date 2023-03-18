#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clients.h"
#include "managers.h"
#include "vehicles.h"
#include "menuFuncs.h"
#define MAX_LINE 250
#define MAX_LENGTH_NAME 50
#define MAX_LENGTH_ADDRESS 50
#define MAX_LENGTH_EMAIL 50

int totClients = 0;

// Verifies if the ID of the client exists on the list
int clientIdExists(Client *head, int id)
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

// Get clients max ID
int getMaxClientId(Client *head)
{
	int maxId = 0;
	Client *current = head;
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

// Show list of clients
void listClients(Client **client)
{
	Client *head = *client;
	printf("ID\tName\tAge\tNIF\t\tBalance\t\tAddress\t\t\tEmail\t\tPassword\n");
	for (; head != NULL; head = head->next)
	{
		printf("%d\t%s\t%d\t%s\t%.2f\t\t%s\t%s\t\t%s\n", head->id, head->name, head->age,
			  head->NIF, head->balance, head->address, head->email, head->password);
	}
}

// Insert a new client
Client *insertClient(Client *head, int id, char name[], int age, char NIF[], float balance, char address[], char email[], char pw[])
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
		strcpy(new->email, email);
		strcpy(new->password, pw);
		new->next = head;
		totClients++;
		return (new);
	}
	else
		return (head);
}

// Registers a client
void clientReg(Client **head)
{
	int age;
	char name[MAX_LENGTH_NAME], NIF[9], address[MAX_LENGTH_ADDRESS], email[MAX_LENGTH_EMAIL], password[16];
	float balance;
	int maxID = getMaxClientId(*head) + 1;

	printf("Your ID is: %d\n", maxID);
	printf("Name: ");
	fflush(stdout); // Use on windows
	scanf("%s", name);
	printf("Age: ");
	fflush(stdout); // Use on windows
	scanf("%d", &age);
	printf("NIF: ");
	fflush(stdout); // Use on windows
	scanf("%s", NIF);
	balance = 0;
	printf("Address: ");
	fflush(stdout); // Use on windows
	scanf("%s", address);
	printf("Email: ");
	fflush(stdout); // Use on windows
	scanf("%s", email);
	printf("Password: ");
	fflush(stdout); // Use on windows
	scanf("%s", password);
	*head = insertClient(*head, maxID, name, age, NIF, balance, address, email, password);
}

// Remove an existing client
void removeClient(Client **head, int id)
{
	Client *previous = *head, *current = *head;

	if (current == NULL)
		return;
	if (current->id == id)
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

void addFundsClient(Client *c, float balance)
{

	if (balance <= 0)
	{
		printf("Invalid amount.\n");
		getchar();
		return;
	}
	c->balance += balance;
	printf("%.2f added to your balance.\nYou currently have %.2f€.\n", balance, c->balance);
	getchar();
	return;
}

void clientMenu(Client **head, Vehicle **vehicle, Client *c, Manager **manager)
{
	int opt;
	float balance = 0;
	Client *current = *head;

	clearConsole();
	printf("Welcome, %s!\n", c->name);
	system("cat ./Menus/clients/clientsMenu.txt");
	fflush(stdout);
	scanf("%d", &opt);

	switch (opt)
	{
	case 1:
		fflush(stdout);
		// Rent vehicle function;
		clearConsole();
		int freeVehicles;
		printf("Rental options:\n");
		freeVehicles = listVehiclesNotRented(vehicle);
		if (freeVehicles > 0)
		{
			printf("Which vehicle do you wish to rent?\nID: ");
			int vehicleID;
			scanf("%d", &vehicleID);
			float newBalance = rentVehicle(vehicle, vehicleID, c);
			if (newBalance >= 0)
				c->balance = newBalance;
		}
		else
		{
			printf("No available vehicles to rent.\n");
		}
		break;
	case 2:
		fflush(stdout);
		printf("What is the value of funds you want to add?\n");
		printf("Value: ");
		scanf("%f", &balance);
		addFundsClient(c, balance);
		break;
	case 3:
		fflush(stdout);
		int rentedVehicles = listVehiclesRentedByClient(vehicle, c->id);
		if (rentedVehicles == 0)
		{
			printf("You don't have any vehicles rented.\n");
		}
		else
		{
			printf("Which vehicle do you want to cancel your rent?\nID: ");
			int vehicleID;
			scanf("%d", &vehicleID);
			cancelRental(vehicle, vehicleID);
		}
		break;
	case 4:
		fflush(stdout);
		current = changeClientData(current);
		break;
	case 5:
		fflush(stdout);
		removeClient(head, c->id);
		printf("Account removed with success.\n");
		enterToContinue();
		loginOrReg(head, manager, vehicle);
		return;
		break;
	case 0:
		loginOrReg(head, manager, vehicle);
		return;
		break;
	default:
		printf("Invalid Option!\n");
		break;
	}
	enterToContinue();
	clientMenu(head, vehicle, c, manager);
}

void *changeClientData(Client *c)
{
	int opt;
	char newName[MAX_LENGTH_NAME], newEmail[MAX_LENGTH_EMAIL], newPassword[16], newAddress[MAX_LENGTH_ADDRESS];
	char newNIF[10];
	int newAge;

	clearConsole();
	system("cat ./Menus/clients/clientsMenu2.txt");

	do
	{
		printf("Enter option: ");
		fflush(stdout);
		scanf("%d", &opt);
		printf("\n");

		switch (opt)
		{
		case 1:
			while ((getchar()) != '\n')
				;
			printf("Enter new name: ");
			fgets(newName, MAX_LENGTH_NAME, stdin);
			newName[strcspn(newName, "\n")] = '\0';
			strcpy(c->name, newName);
			break;
		case 2:
			while ((getchar()) != '\n')
				;
			printf("Enter new age: ");
			scanf("%d", &newAge);
			c->age = newAge;
			break;
		case 3:
			while ((getchar()) != '\n')
				;
			printf("Enter new NIF: ");
			fgets(newNIF, 10, stdin);
			newNIF[strlen(newNIF) - 1] = '\0';
			strcpy(c->NIF, newNIF);
			break;
		case 4:
			while ((getchar()) != '\n')
				;
			printf("Enter new address: ");
			fgets(newAddress, strlen(newAddress), stdin);
			newAddress[strlen(newAddress) - 1] = '\0';
			strcpy(c->address, newAddress);
			break;
		case 5:
			while ((getchar()) != '\n')
				;
			printf("Enter new email: ");
			fgets(newEmail, MAX_LENGTH_EMAIL, stdin);
			newEmail[strcspn(newEmail, "\n")] = '\0';
			strcpy(c->email, newEmail);
			break;
		case 6:
			while ((getchar()) != '\n')
				;
			printf("Enter new password: ");
			fgets(newPassword, 16, stdin);
			newPassword[strcspn(newPassword, "\n")] = '\0';
			strcpy(c->password, newPassword);
			break;
		case 0:
			break;
		default:
			printf("Invalid option. Please select again.\n");
			fflush(stdout);
			break;
		}

	} while (opt < 0 || opt > 6);
}

// Save managers in a txt
int saveClients(Client *head)
{
	FILE *fp;
	fp = fopen("clients1.txt", "w");
	if (fp != NULL)
	{
		Client *aux = head;

		while (aux != NULL)
		{
			fprintf(fp, "%d,%s,%d,%s,%.2f,%s,%s,%s\n", aux->id, aux->name,
				   aux->age, aux->NIF, aux->balance, aux->address, aux->email, aux->password);

			aux = aux->next;
		}
		fclose(fp);
		return (1);
	}
	else
		return (0);
}

// Read vehicles from txt file
Client *readClients()
{
	FILE *fp;
	int id, age;
	float balance;
	char name[MAX_LENGTH_NAME], NIF[10], address[MAX_LENGTH_ADDRESS], email[MAX_LENGTH_ADDRESS], password[16];
	Client *aux = NULL;

	fp = fopen("clients.txt", "r");
	if (fp != NULL)
	{
		char line[MAX_LINE];
		while (fgets(line, sizeof(line), fp))
		{

			sscanf(line, "%d,%[^,],%d,%[^,],%f,%[^,],%[^,],%[^,\r\n]", &id, name, &age, NIF, &balance, address, email, password);

			aux = insertClient(aux, id, name, age, NIF, balance, address, email, password);
		}
		fclose(fp);
	}
	return (aux);
}