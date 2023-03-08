#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clients.h"
#include "managers.h"
#include "vehicles.h"

/*
1. Definicao de uma estrutura de dados dinamica (a validar previamente com o docente), para a representacao
dos meios de mobilidade eletrica, clientes e gestores;
2. Armazenamento/leitura dos dados em ficheiro de texto (valores de simulacao) e binarios (preservar dados);
3. Insercao de novos dados (cliente/gestor/meio de mobilidade eletrica); M -> DONE;
4. Remocao de determinados dados (cliente/gestor/meio de mobilidade eletrica);
5. Alteracao de determinados dados (cliente/gestor/meio de mobilidade eletrica);
6. Registo do aluguer de um determinado meio de mobilidade eletrica;
7. Listagem dos meios de mobilidade eletrica por ordem decrescente de autonomia;
*/

Manager *insertManager(Manager *head, int id, char name[], int numVehicles); // Creates a new manager

int main()
{
  Vehicle *vehicles = NULL;
  insertVehicle(vehicles, 1, "Joao", "Gunao", 50, 0, "u");
  insertVehicle(vehicles, 1, "Pedro", "Gunao", 10, 0, "u");
  insertVehicle(vehicles, 1, "Tata", "Gunao", 25, 0, "u");
  insertVehicle(vehicles, 1, "dasd", "Gunao", 5, 0, "u");
  insertVehicle(vehicles, 1, "titi", "Gunao", 60, 0, "u");
  insertVehicle(vehicles, 1, "ttto", "Gunao", 100, 0, "u");

  /*
    // Asks for data to create a manager
    Manager *manager = malloc(sizeof(Manager));
    int n = 0;
    manager->id = n + 1;
    printf("Your manager ID is: %d\n", manager->id);

    printf("Enter Manager Name: ");
    scanf("%s", manager->name);

    printf("Enter Number of Vehicles: ");
    scanf("%d", &manager->numVehicles);

    // Prints manager data
    printf("Manager ID: %d\n", manager->id);
    printf("Manager Name: %s\n", manager->name);
    printf("Number of Vehicles: %d\n", manager->numVehicles);

    free(manager);
  */
  /*
  // Call insertManager function
  head = insertManager(head, reg.id, reg.name, reg.numVehicles);

  // Print the linked list
  Manager *current = head;
  while (current != NULL)
  {
    printf("ID: %d, Name: %s, NumVehicles: %d\n", current->id, current->name, current->numVehicles);
    current = current->next;
  }
  */

  return 0;
}