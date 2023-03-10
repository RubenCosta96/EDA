#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clients.h"
#define MAX_LINE 100

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
 for (; head != NULL; head = head->next)
 {
		printf("%d %s %d %s %f %s %s %s\n", head->id, head->name, head->age,
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
			fprintf(fp, "%d,%s,%d,%s,%f,%s,%s,%s\n", aux->id, aux->name,
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
 char name[50], NIF[9], address[50], email[30], password[16];

 Client *aux = NULL;
 fp = fopen("clients.txt", "r");
 if (fp != NULL)
 {
		char line[MAX_LINE];
		while (fgets(line, sizeof(line), fp))
		{
			sscanf(line, "%d,%49[^,\n],%d,%8[^,\n],%f,%49[^,\n],%29[^,\n],%15[^,\n]", &id, name, &age, NIF, &balance, address, email, password);
			aux = insertClient(aux, id, name, age, NIF, balance, address, email, password);
		}
		fclose(fp);
 }
 return (aux);
}