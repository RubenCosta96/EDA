#ifndef MENU
#define MENU

typedef struct listManagers Manager;
typedef struct listClients Client;
typedef struct graph1 Adjacent;
typedef struct graph2 Graph;
typedef struct history History;

// Initialize menu
void loginOrReg(Client **client, Manager **manager, Vehicle **vehicle, Graph **g, History **hist);

// Enter to continue
void enterToContinue();

// Clears Console
void clearConsole();

// Menu to decide if you want to login as a user or manager;
void clientOrManagerLogin(Client **client, Manager **manager, Vehicle **vehicle, Graph **g, History **hist);

// Menu to decide if you want to register as a user or manager;
void clientOrManagerRegistration(Client **client, Manager **manager, Vehicle **vehicle, Graph **g, History **hist);

// Client Login
void clientLogin(Client **client, Vehicle **vehicle, Manager **manager, Graph **g, History **hist);

// Manager Login
void managerLogin(Manager **manager, Vehicle **vehicle, Client **client, Graph **g, History **hist);

// Manager Menu
void managerMenu(Manager **head, Vehicle **vehicle, Client **client, Manager *m, Graph **g, History **hist);

#endif