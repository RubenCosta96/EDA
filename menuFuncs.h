#ifndef MENU
#define MENU

typedef struct listManagers Manager;
typedef struct listClients Client;

// Initialize menu
void loginOrReg(Client **client, Manager **manager);

// Enter to continue
void enterToContinue();

// Clears Console
void clearConsole();

// Menu to decide if you want to login as a user or manager;
void clientOrManagerLogin(Client **client, Manager **manager);

// Menu to decide if you want to register as a user or manager;
void clientOrManagerRegistration(Client **client, Manager **manager);

// Client Login
void clientLogin(Client **client);

// Manager Login
void managerLogin(Manager **manager);

// Manager Registration
void managerReg(Manager *manager);

#endif