#ifndef MENU
#define MENU

typedef struct listManagers Manager;
typedef struct listClients Client;

// Initialize menu
void loginOrReg(Client **client, Manager **manager, Vehicle **vehicle);

// Enter to continue
void enterToContinue();

// Clears Console
void clearConsole();

// Menu to decide if you want to login as a user or manager;
void clientOrManagerLogin(Client **client, Manager **manager, Vehicle **vehicle);

// Menu to decide if you want to register as a user or manager;
void clientOrManagerRegistration(Client **client, Manager **manager, Vehicle **vehicle);

// Client Login
void clientLogin(Client **client, Vehicle **vehicle, Manager **manager);

// Manager Login
void managerLogin(Manager **manager, Vehicle **vehicle, Client **client);

// Manager Menu
void managerMenu(Manager **head, Vehicle **vehicle, Client **client, Manager *m);

#endif