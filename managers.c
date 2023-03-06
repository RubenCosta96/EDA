#include <stdlib.h>
#include <string.h>

#include "managers.h"


//Insert a new manager
Manager* insertManager(Manager *head, int id, char name[], int numVehicles)
{

 Manager* new = malloc(sizeof(struct listManagers));
 if (new != NULL)
 {
  new->id = id;
  strcpy(new->name,name);
  new->numVehicles = numVehicles;
  new->next = head;
  return(new);
 }
 else return(head);
}


//Show list of managers
void listManagers(Manager *head){
	while(head !=NULL){
		printf("%d %s %d\n", head->id, head->name,head->numVehicles);
		head = head->next;
	}
}



//Sort managers by variable selected from user input;
/*Manager* orderManagers(Manager* head) {
	Manager* order = malloc(sizeof(struct listManagers));


	
}
*/

//Remove a manager from the list
Manager* removeManager(Manager* head, int id) {
	Manager* previous = head, * current = head, * aux;

	if (current == NULL) return NULL;
	else if (current->id == id) {
		aux = current->next;
		free(current);
		return(aux);
	}
	else {
		while ((current != NULL) && (current->id != id)) {
			previous = current;
			current = current->next;
		}
		if (current == NULL) return(head);
		else {
			previous->next = current->next;
			free(current);
			return(head);
		}
	}
}
