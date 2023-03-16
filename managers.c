#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "managers.h"
#define MAX_LINE 250
#define MAX_LENGTH_NAME 50
#define MAX_LENGTH_ADDRESS 50
#define MAX_LENGTH_EMAIL 50

int totManagers = 0;

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
		totManagers++;
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

Manager *changeManagerData(Manager *head, char email[])
{
 Manager *aux = head;
 int opt;
 char newName[MAX_LENGTH_NAME];
 char newEmail[MAX_LENGTH_EMAIL];
 char newPassword[16];
 int emailFound = 0;

 system("type managersMenu2.txt || cat managersMenu2.txt");

 while (aux != NULL)
 {
		if (strcmp(aux->email, email) == 0)
		{
			emailFound = 1;
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
					strcpy(aux->name, newName);
					saveManagers(head);
					break;
				case 2:
					while ((getchar()) != '\n')
						;
					printf("Enter new email: ");
					fgets(newEmail, MAX_LENGTH_EMAIL, stdin);
					newEmail[strcspn(newEmail, "\n")] = '\0';
					strcpy(aux->email, newEmail);
					break;
				case 3:
					while ((getchar()) != '\n')
						;
					printf("Enter new password: ");
					fgets(newPassword, 16, stdin);
					newPassword[strcspn(newPassword, "\n")] = '\0';
					strcpy(aux->password, newPassword);
					break;
				case 0:
					break;
				default:
					printf("Invalid option. Please select again.\n");
					fflush(stdout);
					break;
				}

			} while (opt != 0);
			break;													
		}

		else
		{
			aux = aux->next;
		}
 }
 if (!emailFound)
 {
		printf("Email not found.\n");
 }
 return head;
}

// Remove a manager from the list
void removeManager(Manager **head, int id)
{
 Manager *previous = *head, *current = *head;

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
int saveManagers(Manager *head)
{
 FILE *fp;
 fp = fopen("managers.txt", "w");
 if (fp != NULL)
 {
		Manager *aux = head;
		while (aux != NULL)
		{

			fprintf(fp, "%d,%s,%s,%s\n", aux->id, aux->name,
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
			sscanf(line, "%d,%[^,],%[^,],%[^,\n]", &id, name, email, password);
			aux = insertManager(aux, id, name, email, password);
		}
		fclose(fp);
 }
 return (aux);
}

int getMaxManagerId(Manager *head)
{
 int maxId = 0;
 Manager *current = head;
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
