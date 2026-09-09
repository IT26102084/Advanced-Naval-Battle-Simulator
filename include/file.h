#ifndef FILE_H
#define FILE_H

#include "sim.h"

/* =========================
   File Names
   ========================= */

#define CONFIG_FILE "data/config.txt"
#define SAVE_FILE   "data/savegame.txt"
#define LOG_FILE    "data/simulation.log"


/* =================================================
   Battlefield File Functions
   ================================================= */

/*
 * Save battlefield configuration to a file.
 */
int saveBattlefield(
    const char *filename,
    const Battlefield *battlefield
);


/*
 * Load battlefield configuration from a file.
 */
int loadBattlefield(
    const char *filename,
    Battlefield *battlefield
);


/* =================================================
   Simulation Save / Load
   ================================================= */

/*
 * Save complete simulation state.
 */
int saveSimulation(
    const char *filename,
    const Battlefield *battlefield
);


/*
 * Load complete simulation state.
 */
int loadSimulation(
    const char *filename,
    Battlefield *battlefield
);


/* =================================================
   Log Functions
   ================================================= */

/*
 * Write a text message to the log file.
 */
int writeLog(
    const char *filename,
    const char *message
);


/*
 * Save current battlefield state to log.
 */
int logBattlefield(
    const char *filename,
    const Battlefield *battlefield
);


/* =================================================
   Utility Functions
   ================================================= */

/*
 * Check whether a file exists.
 */
int fileExists(
    const char *filename
);


/*
 * Create the data directory.
 */
int ensureDataDirectory(void);

#endif /* FILE_H */
