#ifndef TUI_H
#define TUI_H

#include "sim.h"

/* =========================================================
   Main Menu
   ========================================================= */

void displayMainMenu(void);
int getMainMenuChoice(void);

void displayInstructions(void);


/* =========================================================
   Battlefield Menu
   ========================================================= */

void displayBattlefieldMenu(void);
int getBattlefieldMenuChoice(void);


/* =========================================================
   Ship Menu
   ========================================================= */

void displayShipMenu(void);
int getShipMenuChoice(void);


/* =========================================================
   Simulation Menu
   ========================================================= */

void displaySimulationMenu(void);
int getSimulationMenuChoice(void);


/* =========================================================
   Display Functions
   ========================================================= */

void displayBattlefieldTUI(const Battlefield *battlefield);
void displayShipsTUI(const Battlefield *battlefield);
void displayShipTUI(const Ship *ship);
void displayStatisticsTUI(const SimulationStatistics *statistics);


/* =========================================================
   Input Functions
   ========================================================= */

int getIntegerInput(const char *prompt);
double getDoubleInput(const char *prompt);
char getCharacterInput(const char *prompt);

void getStringInput(
    const char *prompt,
    char *buffer,
    int bufferSize
);


/* =========================================================
   General UI Functions
   ========================================================= */

void displayTitle(void);
void displaySeparator(void);

void displaySuccess(const char *message);
void displayError(const char *message);
void displayWarning(const char *message);

void pauseScreen(void);
void clearScreen(void);


/* =========================================================
   Main TUI
   ========================================================= */

void runTUI(void);

#endif
