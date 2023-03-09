#include <stdlib.h>
#include <string.h>

#include "managers.h"

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

<<<<<<< HEAD
// Login for manager
Manager *loginManager(Manager *head, char email[], char pw[]){
	Manager *login = head;

	if(strcmp(login->email,email) && strcmp(login->password,pw) == 0){
		Printf("Login successfull!");
	} else if(strcmp(login->email,email) || strcmp(login->password,pw) != 0){
		printf("Email ou password incorretos.");
	}


}

//Insert a new manager
Manager* insertManager(Manager *head, int id, char name[], char email[], char pw[])
=======
// Insert a new manager
Manager *insertManager(Manager *head, int id, char name[], int numVehicles)
>>>>>>> d68f201f96ee2992408f5938338425943f7c8b55
{

 Manager *new = malloc(sizeof(struct listManagers));
 if (new != NULL)
 {
<<<<<<< HEAD
  new->id = id;
  strcpy(new->name,name);
  strcpy(new->email,email);
  strcpy(new->password,pw);
  new->next = head;
  return(new);
=======
		new->id = id;
		strcpy(new->name, name);
		new->numVehicles = numVehicles;
		new->next = head;
		return (new);
>>>>>>> d68f201f96ee2992408f5938338425943f7c8b55
 }
 else
		return (head);
}

<<<<<<< HEAD
//Show list of managers
void listManagers(Manager *head){
	while(head !=NULL){
		printf("%d %s %s\n", head->id, head->name,head->email);
=======
// Show list of managers
void listManagers(Manager *head)
{
 while (head != NULL)
 {
		printf("%d %s %d\n", head->id, head->name, head->numVehicles);
>>>>>>> d68f201f96ee2992408f5938338425943f7c8b55
		head = head->next;
 }
}

// Change data from a manager
int changeManagerData(Manager *head, int id)
{
 if (!existeMeio(head, id))
 {
		Manager *new = malloc(sizeof(struct listManagers));
		if (new != NULL)
		{
		}
 }
}

<<<<<<< HEAD

//Sort managers by variable selected from user input;
/*Manager* orderManagers(Manager* head, ...) {
	Manager* order = malloc(sizeof(struct listManagers));
=======
// Sort managers by variable selected from user input;
/*Manager* orderManagers(Manager* head) {
 Manager* order = malloc(sizeof(struct listManagers));

>>>>>>> d68f201f96ee2992408f5938338425943f7c8b55


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
