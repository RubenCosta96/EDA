#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "clients.h"
#include "managers.h"
#include "vehicles.h"
#include "menuFuncs.h"
#include "history.h"

int saveHistoryBinary(History *head)
{
	FILE *fp;
	fp = fopen("historyBinary.bin", "wb");
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro.\n");
	}
	else if (fp != NULL)
	{
		History *aux = head;
		while (aux != NULL)
		{
			fwrite(aux, sizeof(History), 1, fp);
			aux = aux->next;
		}
		fclose(fp);
		return (1);
	}
	else
		return (0);
}

History *readHistoryBinary()
{
	FILE *fp;

	History *aux = NULL;

	fp = fopen("historyBinary.bin", "rb");
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro.");
		return NULL;
	}
	while (!feof(fp))
	{
		History history;
		size_t bytes_read = fread(&history, sizeof(History), 1, fp);
		if (bytes_read == 1)
		{
			aux = insertManager(aux, manager.id, manager.name, manager.email, manager.password); // Change to history
		}
	}
	fclose(fp);
	return (aux);
}