#ifndef HISTORY
#define HISTORY

#include <time.h>

#define MAX_LENGTH_NAME 50

typedef struct listVehicles Vehicle;
typedef struct listManagers Manager;

typedef struct history
{
     int clientID, vehicleID;
     float cost;
     char clientName[MAX_LENGTH_NAME], vehicleType[MAX_LENGTH_NAME];
     struct tm init;
     struct tm end;
     struct history *next;
} History;

History *insertHistory(History *head, int clientID, char clientName[], int vehicleID, char vehicleType[],
                       float cost, struct tm init, struct tm end);

void listHistory(History **history);

int saveHistory(History *head);

History *readHistory();

int saveHistoryBinary(History *head);

History *readHistoryBinary();

#endif