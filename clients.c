#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "clients.h"
#include "managers.h"
#include "vehicles.h"
#include "menuFuncs.h"
#include "history.h"
#include "graph.h"
#define MAX_LINE 250
#define MAX_LENGTH_NAME 50
#define MAX_LENGTH_ADDRESS 50
#define MAX_LENGTH_EMAIL 50

/**
 * @brief Gets the highest value of the IDs of the clients registered
 *
 * @param head
 * @return int
 */
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

/**
 * @brief Prints on the terminal the list of clients registered
 *
 * @param client
 */
void listClients(Client **client)
{
	Client *head = *client;
	printf("ID\tName\t\tAge\tNIF\t\tBalance\t\tAddress\t\t\tEmail\t\t\t\tPassword\n");
	for (; head != NULL; head = head->next)
	{
		printf("%d\t%s\t%d\t%s\t%.2f\t\t%s\t%s\t\t%s\n", head->id, head->name, head->age,
			   head->NIF, head->balance, head->address, head->email, head->password);
	}
}

/**
 * @brief Function to insert a new client into the already existing linked list of clients
 *
 * @param head
 * @param id
 * @param name
 * @param age
 * @param NIF
 * @param balance
 * @param address
 * @param email
 * @param pw
 * @return Client*
 */
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
		return (new);
	}
	else
		return (head);
}

/**
 * @brief Function that will recieve the inputs of the user to register a new client
 *
 * @param head
 */
void clientReg(Client **head)
{
	int age;
	char name[MAX_LENGTH_NAME], NIF[10], address[MAX_LENGTH_ADDRESS], email[MAX_LENGTH_EMAIL], password[16];
	float balance;
	int maxID = getMaxClientId(*head) + 1;

	printf("Your ID is: %d\n", maxID);
	printf("Name: ");
	getchar();
	scanf("%[^\n]", name);
	printf("Age: ");
	getchar();
	scanf("%d", &age);
	printf("NIF: ");
	getchar();
	scanf("%9[^\n]", NIF);
	balance = 0;
	printf("Address: ");
	getchar();
	scanf("%[^\n]", address);
	printf("Email: ");
	getchar();
	scanf("%[^\n]", email);
	printf("Password: ");
	getchar();
	fflush(stdout); // Use on windows
	scanf("%[^\n]", password);
	*head = insertClient(*head, maxID, name, age, NIF, balance, address, email, password);
}

/**
 * @brief Removes an existing client from the linked list
 *
 * @param head
 * @param id
 */
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

/**
 * @brief Function that recieves input from the user to add funds the respective user's balance.
 *
 * @param c
 * @param balance
 */
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
	return;
}

/**
 * @brief Function that presents to ther user the options that are available to the client after login
 *
 * @param head
 * @param vehicle
 * @param c
 * @param manager
 */
void clientMenu(Client **head, Vehicle **vehicle, Client *c, Manager **manager, Graph **g, History **hist)
{
	int opt;
	float balance = 0;

	clearConsole();
	printf("Welcome, %s!\n", c->name);
	printf("Current balance: %.2f €\n", c->balance);
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
		freeVehicles = listVehiclesNotRented(vehicle);
		if (freeVehicles > 0)
		{
			printf("Which vehicle do you wish to rent?\nID: ");
			int vehicleID;
			scanf("%d", &vehicleID);
			float newBalance = rentVehicle(vehicle, vehicleID, c, hist);
			if (newBalance >= 0)
			{
				c->balance = newBalance;
			}
		}
		else
		{
			printf("No available vehicles to rent.\n");
		}
		break;
	case 2:
		fflush(stdout);
		clearConsole();
		printf("What is the value of funds you want to add?\n");
		printf("Value: ");
		scanf("%f", &balance);
		addFundsClient(c, balance);
		break;
	case 3:
		fflush(stdout);
		clearConsole();
		int rentedVehicles = listVehiclesRentedByClient(vehicle, c->id);
		if (rentedVehicles == 0)
		{
			printf("You don't have any vehicles rented.\n");
		}
		else
		{
			printf("Which vehicle do you want to cancel your rental?\nID: ");
			int vehicleID, locationID;
			scanf("%d", &vehicleID);
			printf("What is the final location of your trip?\n");
			listVertexes(g);
			scanf("%d", &locationID);
			cancelRental(vehicle, g, vehicleID);
			cancelRentHist(hist, g, vehicleID, c->id, locationID);
		}
		break;
	case 4:
		fflush(stdout);
		c = changeClientData(c);
		break;
	case 5:
		fflush(stdout);
		removeClient(head, c->id);
		printf("Account removed with success.\n");
		enterToContinue();
		loginOrReg(head, manager, vehicle, g, hist);
		return;
		break;
	case 6:
		clearConsole();
		checkUserData(c);
		break;
	case 7:
		// List vehicles in x geocode;
		break;
	case 0:
		loginOrReg(head, manager, vehicle, g, hist);
		return;
		break;
	default:
		printf("Invalid Option!\n");
		break;
	}
	enterToContinue();
	clientMenu(head, vehicle, c, manager, g, hist);
}

/**
 * @brief Function that allows the client to change any of the fields of his data
 *
 * @param c
 * @return Client*
 */
Client *changeClientData(Client *c)
{
	int opt;
	char newName[MAX_LENGTH_NAME], newEmail[MAX_LENGTH_EMAIL], newPassword[16], newAddress[MAX_LENGTH_ADDRESS];
	char newNIF[10];
	int newAge;

	do
	{
		clearConsole();
		system("cat ./Menus/clients/clientsMenu2.txt");
		printf("Current data:\n");
		checkUserData(c);
		printf("\nEnter option: ");
		fflush(stdout);
		scanf("%d", &opt);

		switch (opt)
		{
		case 1:
			while ((getchar()) != '\n')
				;
			printf("Enter new name: ");
			scanf("%[^\n]", newName);

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
			scanf("%[^\n]", newNIF);

			strcpy(c->NIF, newNIF);
			break;
		case 4:
			while ((getchar()) != '\n')
				;
			printf("Enter new address: ");
			scanf("%[^\n]", newAddress);
			strcpy(c->address, newAddress);
			break;
		case 5:
			while ((getchar()) != '\n')
				;
			printf("Enter new email: ");
			scanf("%[^\n]", newEmail);
			strcpy(c->email, newEmail);
			break;
		case 6:
			while ((getchar()) != '\n')
				;
			printf("Enter new password: ");
			scanf("%[^\n]", newAddress);
			strcpy(c->password, newPassword);
			break;
		case 0:
			break;
		default:
			printf("Invalid option. Please select again.\n");
			fflush(stdout);
			break;
		}
	} while (opt != 0);
	return c;
}

/**
 * @brief Prints on the terminal the info of the user that's logged in.
 *
 * @param c
 */
void checkUserData(Client *c)
{
	printf("Name: %s\n", c->name);
	printf("Age: %d\n", c->age);
	printf("NIF: %s\n", c->NIF);
	printf("Address: %s\n", c->address);
	printf("Email: %s\n", c->email);
}

/**
 * @brief Saves all the data of the clients in a .txt file
 *
 * @param head
 * @return int
 */
int saveClients(Client *head)
{
	FILE *fp;
	fp = fopen("clients.txt", "w");
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

/**
 * @brief Reads the data present on the .txt file that has all the clients data saved.
 *
 * @return Client*
 */
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

/**
 * @brief Saves all the data of the cilents in a binary file
 *
 * @param head
 * @return int
 */
int saveClientsBinary(Client *head)
{
	FILE *fp;
	fp = fopen("clientBinary.bin", "wb");
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro.\n");
	}
	else if (fp != NULL)
	{
		Client *aux = head;
		while (aux != NULL)
		{
			fwrite(aux, sizeof(Client), 1, fp);
			aux = aux->next;
		}
		fclose(fp);
		return (1);
	}
	else
		return (0);
}

/**
 * @brief Reads the data present on the binary file that has all the clients data saved.
 *
 * @return Client*
 */
Client *readClientsBinary()
{
	FILE *fp;

	Client *aux = NULL;

	fp = fopen("clientBinary.bin", "rb");
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro.");
		return NULL;
	}
	while (!feof(fp))
	{
		Client client;
		size_t bytes_read = fread(&client, sizeof(Client), 1, fp);
		if (bytes_read == 1)
		{
			aux = insertClient(aux, client.id, client.name, client.age, client.NIF, client.balance, client.address, client.email, client.password);
		}
	}
	fclose(fp);
	return (aux);
}