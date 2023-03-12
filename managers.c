#include <stdlib.h>
#include <string.h>

#include "managers.h"
#define MAX_LINE 100

// Verifies if the ID of the manager exists on the list
int managerIdExists(Manager *head, int id)
{
 Manager *current = head;
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

// Login for manager
Manager *loginManager(Manager *head, char email[], char pw[])
{
 Manager *login = head;

 if (strcmp(login->email, email) && strcmp(login->password, pw) == 0)
 {
		printf("Login successfull!\n Welcome %s\n", login->name);
 }
 else if (strcmp(login->email, email) || strcmp(login->password, pw) != 0)
 {
		printf("Email or password invalid.\n");
 }
}

// Insert a new manager
Manager *insertManager(Manager *head, int id, char name[], char email[], char pw[])
{

 Manager *new = malloc(sizeof(struct listManagers));
 if (new != NULL)
 {
		new->id = id;
		strcpy(new->name, name);
		strcpy(new->email, email);
		strcpy(new->password, pw);
		new->next = head;
		return (new);
 }
 else
		return (head);
}

// Show list of managers
void listManagers(Manager *head)
{
 while (head != NULL)
 {
		printf("%d %s %s\n", head->id, head->name, head->email);
		head = head->next;
 }
}

// Change data from a manager
/*int changeManagerData(Manager *head, int id)
{
 Manager *aux = head;
 while (aux->id != NULL)
 {
		if (aux->id == id)
		{
		}
		aux = aux->next;
 }
 return 0;
}*/
// Sort managers by variable selected from user input;
/*Manager* orderManagers(Manager* head, ...) {
 Manager* order = malloc(sizeof(struct listManagers));


}
*/

// Remove a manager from the list
Manager *removeManager(Manager *head, int id)
{
 Manager *previous = head, *current = head, *aux;

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
int saveManagers(Manager *head)
{
 FILE *fp;
 fp = fopen("managers.txt", "w");
 if (fp != NULL)
 {
		Manager *aux = head;
		while (aux != NULL)
		{
			fprintf(fp, "%d,%s,%s,%s;\n", aux->id, aux->name,
											aux->email, aux->password);
			aux = aux->next;
		}
		fclose(fp);
		return (1);
 }
 else
		return (0);
}

// Read managers data saved in txt file
Manager *readManagers()
{
 FILE *fp;
 int id;
 char name[40], email[50], password[16];
 Manager *aux = NULL;
 fp = fopen("managers.txt", "r");
 if (fp != NULL)
 {
		char line[MAX_LINE];
		while (fgets(line, sizeof(line), fp))
		{
			sscanf(line, "%d,%39[^,\n],%49[^,\n],%15[^,\n]", &id, name, email, password);
			aux = insertManager(aux, id, name, email, password);
		}
		fclose(fp);
 }
 return (aux);
}
