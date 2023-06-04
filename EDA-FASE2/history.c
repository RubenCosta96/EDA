#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "history.h"
#include "graph.h"

#define MAX_LENGTH_NAME 50
#define MAX_LENGTH_ADDRESS 50
#define MAX_LENGTH_EMAIL 50
#define MAX_LINE 250

History *insertHistory(History *head, int clientID, char clientName[], int vehicleID, char vehicleType[],
                       float cost, char initLocation[], struct tm init)
{
     History *new = malloc(sizeof(struct history));
     if (new != NULL)
     {
          new->clientID = clientID;
          strcpy(new->clientName, clientName);
          new->vehicleID = vehicleID;
          strcpy(new->vehicleType, vehicleType);
          strcpy(new->initLocation, initLocation);
          strcpy(new->finalLocation, "Vehicle in use.");
          new->cost = cost;
          new->init = init;
          new->init.tm_year += 1900;
          new->next = head;
          return (new);
     }
     else
          return (head);
}

void listHistory(History **history)
{
     History *head = *history;
     printf("Client ID\tClient Name\tVehicle ID\tVehicle Type\tTotal Cost\tStarting Location\tFinal Location\tStart of rental\t\tEnd of rental\t\n");
     for (; head != NULL; head = head->next)
     {
          printf("%d\t\t%s\t%d\t\t%s\t%.2f\t%s\t%s\t\t%d/%d/%d %.2d:%.2d:%.2d\t%d/%d/%d %.2d:%.2d:%.2d\n",
                 head->clientID, head->clientName,
                 head->vehicleID, head->vehicleType, head->cost, head->initLocation, head->finalLocation,
                 head->init.tm_mday, head->init.tm_mon,
                 head->init.tm_year, head->init.tm_hour, head->init.tm_min, head->init.tm_sec,
                 head->end.tm_mday, head->end.tm_mon, head->end.tm_year, head->end.tm_hour,
                 head->end.tm_min, head->end.tm_sec);
     }
}

void cancelRentHist(History **history, Graph **g, int vehicleID, int clientID, int locationID)
{
     History *aux = *history;
     Graph *auxgraph = *g;

     while (aux != NULL)
     {
          if ((clientID == aux->clientID) && (vehicleID == aux->vehicleID))
          {
               time_t rawtime;
               time(&rawtime);
               aux->end = *localtime(&rawtime);
               aux->end.tm_year += 1900;
               while (auxgraph != NULL)
               {
                    if (locationID == auxgraph->id)
                    {
                         strcpy(aux->finalLocation, auxgraph->vertex);
                         return;
                    }
                    auxgraph = auxgraph->next;
               }
               aux = aux->next;
          }
     }
}

int saveHistory(History *head)
{
     FILE *fp;
     fp = fopen("history.txt", "w");
     if (fp != NULL)
     {
          History *aux = head;
          while (aux != NULL)
          {

               fprintf(fp, "%d,%s,%d,%s,%f,%d/%d/%d,%d:%d:%d\n", aux->clientID, aux->clientName,
                       aux->vehicleID, aux->vehicleType, aux->cost,
                       aux->init.tm_mday, aux->init.tm_mon, aux->init.tm_year,
                       aux->init.tm_hour, aux->init.tm_min, aux->init.tm_sec);
               aux = aux->next;
          }
          fclose(fp);
          return (1);
     }
     else
          return (0);
}

History *readHistory()
{
     FILE *fp;
     int clientID, vehicleID;
     float cost;
     char clientName[MAX_LENGTH_NAME], vehicleType[MAX_LENGTH_NAME];
     char initLoc[SIZE], finalLoc[SIZE];
     struct tm init = {0};
     struct tm end = {0};
     History *aux = NULL;

     fp = fopen("history.txt", "r");
     if (fp != NULL)
     {
          char line[MAX_LINE];
          while (fgets(line, sizeof(line), fp))
          {
               sscanf(line, "%d,%[^,],%d,%[^,],%f,%[^,],%[^,],%d/%d/%d %d:%d:%d,%d/%d/%d %d:%d:%d\n",
                      &clientID, clientName, &vehicleID, vehicleType, &cost, initLoc, finalLoc, &init.tm_mday, &init.tm_mon,
                      &init.tm_year, &init.tm_hour, &init.tm_min, &init.tm_sec,
                      &end.tm_mday, &end.tm_mon, &end.tm_year, &end.tm_hour,
                      &end.tm_min, &end.tm_sec);

               aux = insertHistory(aux, clientID, clientName, vehicleID,
                                   vehicleType, cost, initLoc, init);
          }
          fclose(fp);
     }
     return (aux);
}

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
               aux = insertHistory(aux, history.clientID, history.clientName,
                                   history.vehicleID, history.vehicleType, history.cost,
                                   history.initLocation, history.init);
          }
     }
     fclose(fp);
     return (aux);
}