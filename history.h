#ifndef HISTORY
#define HISTORY

#define MAX_LENGTH_NAME 50
#define MAX_LENGTH_VEHICLE 50

typedef struct history{
    int clientID,vehicleID;
    float cost;
    char clientName[MAX_LENGTH_NAME];
    char vehicleName[MAX_LENGTH_VEHICLE];
    struct tm init;
    struct tm end;
    struct history *next;
}History;

#endif