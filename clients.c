#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clients.h"
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

// Show list of clients
void listClients(Client *head)
{
 while (head != NULL)
 {
		printf("%d %s %d %s %f %s %s %s\n", head->id, head->name, head->age,
									head->NIF, head->balance, head->address, head->email, head->password);
		head = head->next;
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

 printf("Your ID is: %d\n", totClients + 1);
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
 *head = insertClient(*head, totClients + 1, name, age, NIF, balance, address, email, password);
}

// Remove an existing client
void removeClient(Client **head, int id)
{
 Client *previous = *head, *current = *head;

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

// Save managers in a txt
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

			sscanf(line, "%d,%[^,],%d,%[^,],%f,%[^,],%[^,],%[^,\n]", &id, name, &age, NIF, &balance, address, email, password);
			// sscanf(line, "%d,%[^,],%d,%[^,],", &id, name, &age, nif);
			// printf("Name: %s\n", name);
			// printf("ID: %d\n", id);
			// printf("Age: %d\n", age);
			// printf("%s\n %f\n %s\n", nif, balance, address);

			aux = insertClient(aux, id, name, age, NIF, balance, address, email, password);
		}
		fclose(fp);
 }
 return (aux);
}