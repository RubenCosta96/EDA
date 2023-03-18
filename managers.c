#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "managers.h"
#include "menuFuncs.h"
#define MAX_LINE 250
#define MAX_LENGTH_NAME 50
#define MAX_LENGTH_ADDRESS 50
#define MAX_LENGTH_EMAIL 50

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

/**
 * @brief Functions that allows the manager to login.
 *
 * @param head
 * @param email
 * @param pw
 * @return Manager*
 */
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

/**
 * @brief Function to insert a new manager into the already existing linked list of manager.
 *
 * @param head
 * @param id
 * @param name
 * @param email
 * @param pw
 * @return Manager*
 */
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

/**
 * @brief Function that will recieve the inputs of the user to register a new manager
 *
 * @param head
 */
void managerReg(Manager **head)
{
	int id;
	char name[MAX_LENGTH_NAME], email[MAX_LENGTH_EMAIL], password[16];
	int maxID = getMaxManagerId(*head) + 1;

	printf("Your ID is: %d\n", maxID);
	printf("Name: ");
	getchar();
	scanf("%[^\n]", name);
	printf("Email: ");
	getchar();
	scanf("%[^\n]", email);
	printf("Password: ");
	getchar();
	scanf("%[^\n]", password);

	*head = insertManager(*head, maxID, name, email, password);
	clearConsole();
}

/**
 * @brief Prints on the terminal the list of managers registered
 *
 * @param manager
 */
void listManagers(Manager **manager)
{
	Manager *head = *manager;
	while (head != NULL)
	{
		printf("%d %s %s\n", head->id, head->name, head->email);
		head = head->next;
	}
}

/**
 * @brief Function that allows the manager to change any of the fields of his data
 *
 * @param m
 * @return void*
 */
void *changeManagerData(Manager *m)
{
	int opt;
	char newName[MAX_LENGTH_NAME];
	char newEmail[MAX_LENGTH_EMAIL];
	char newPassword[16];

	clearConsole();
	system("cat Menus/managers/managersMenu2.txt");

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
			strcpy(m->name, newName);
			break;
		case 2:
			while ((getchar()) != '\n')
				;
			printf("Enter new email: ");
			fgets(newEmail, MAX_LENGTH_EMAIL, stdin);
			newEmail[strcspn(newEmail, "\n")] = '\0';
			strcpy(m->email, newEmail);
			break;
		case 3:
			while ((getchar()) != '\n')
				;
			printf("Enter new password: ");
			fgets(newPassword, 16, stdin);
			newPassword[strcspn(newPassword, "\n")] = '\0';
			strcpy(m->password, newPassword);
			break;
		case 0:
			break;
		default:
			printf("Invalid option. Please select again.\n");
			fflush(stdout);
			break;
		}
	} while (opt != 0);
}

/**
 * @brief Removes an existing manager from the linked list
 *
 * @param head
 * @param id
 */
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

/**
 * @brief Saves all the data of the managers in a .txt file
 *
 * @param head
 * @return int
 */
int saveManagers(Manager *head)
{
	FILE *fp;
	fp = fopen("managers1.txt", "w");
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

/**
 * @brief Reads the data present on the .txt file that has all the managers data saved.
 *
 * @return Manager*
 */
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
			sscanf(line, "%d,%[^,],%[^,],%[^,\r\n]", &id, name, email, password);
			aux = insertManager(aux, id, name, email, password);
		}
		fclose(fp);
	}
	return (aux);
}

/**
 * @brief Gets the highest value of the IDs of the managers registered.
 *
 * @param head
 * @return int
 */
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

/**
 * @brief Saves all the data of the managers in a binary file
 *
 * @param head
 * @return int
 */
int saveManagersBinary(Manager *head)
{
	FILE *fp;
	fp = fopen("managerBinary.bin", "wb");
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro.\n");
	}
	else if (fp != NULL)
	{
		Manager *aux = head;
		while (aux != NULL)
		{
			fwrite(aux, sizeof(Manager), 1, fp);
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
 * @return Vehicle*
 */
Manager *readManagersBinary()
{
	FILE *fp;

	Manager *aux = NULL;

	fp = fopen("managerBinary.bin", "rb");
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro.");
		return NULL;
	}
	while (!feof(fp))
	{
		Manager manager;
		size_t bytes_read = fread(&manager, sizeof(Manager), 1, fp);
		if (bytes_read == 1)
		{
			aux = insertManager(aux, manager.id, manager.name, manager.email, manager.password);
		}
	}
	fclose(fp);
	return (aux);
}