#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clients.h"
#include "managers.h"
#include "vehicles.h"

Client *insertClient(Client *head, int id, char name[], int age, char NIF[], float balance, char address[], char email[], char pw[]);

int main()
{
  /*Manager* managers = NULL;

   /*
     // Asks for data to create a manager
     Manager *manager = malloc(sizeof(Manager));
     int n = 0;
     manager->id = n + 1;
     printf("Your manager ID is: %d\n", manager->id);

     printf("Enter Manager Name: ");
     scanf("%s", manager->name);

*/
  /*
    // Insert client test
    Client *clients = NULL;
    clients = insertClient(clients, 1, "Joao", 18, "12345678", 10, "rua", "joao@gmail.com", "teste123");

    if (clients != NULL)
    {
      printf("ID: %d\n Name: %s\n Age: %d\n NIF: %s\n Balance: %f\n Address: %s\n Email: %s\n Password: %s\n",
             clients->id, clients->name, clients->age, clients->NIF, clients->balance, clients->address, clients->email, clients->password);
    }
    else
    {
      printf("Erro ao inserir cliente\n");
    }
  */
  Vehicle *vehicles = NULL;

  vehicles = insertVehicle(vehicles, 1, "troti1", 50, 0, "u");
  vehicles = insertVehicle(vehicles, 1, "troti2", 10, 0, "u");
  vehicles = insertVehicle(vehicles, 1, "troti3", 25, 0, "u");
  vehicles = insertVehicle(vehicles, 1, "troti4", 5, 0, "u");
  vehicles = insertVehicle(vehicles, 1, "troti5", 60, 0, "u");
  vehicles = insertVehicle(vehicles, 1, "troti6", 100, 0, "u");

  sortVehiclesByAutonomy(vehicles);

  return 0;
}
