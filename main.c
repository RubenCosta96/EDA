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

int compare(int aut1, int aut2)
{
 Vehicle *v1 = aut1;
 Vehicle *v2 = aut2;
 if (v1->autonomy < v2->autonomy)
  return -1;
 else if (v1->autonomy > v2->autonomy)
  return 1;
 else
  return 0;
}

int main()
{

 Manager *managers = NULL;

 managers = insertManager(managers, 1, "Carlos", 0);
 managers = insertManager(managers, 2, "Pedro", 0);
 managers = insertManager(managers, 3, "Filipe", 0);

 // listManagers(managers);

 return 0;
}
