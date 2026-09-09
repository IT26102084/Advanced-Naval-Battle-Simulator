#include "../include/file.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


/* =================================================
   Internal Helper Functions
   ================================================= */

/*
 * Remove newline characters from a string.
 */
static void removeNewline(char *text)
{
    if (text == NULL)
        return;

    text[strcspn(text, "\r\n")] = '\0';
}


/*
 * Get current date and time.
 */
static void getDateTime(
    char *buffer,
    size_t bufferSize
)
{
    time_t currentTime;
    struct tm *timeInfo;

    if (buffer == NULL || bufferSize == 0)
        return;

    currentTime = time(NULL);
    timeInfo = localtime(&currentTime);

    if (timeInfo == NULL)
    {
        snprintf(
            buffer,
            bufferSize,
            "Unknown time"
        );

        return;
    }

    strftime(
        buffer,
        bufferSize,
        "%Y-%m-%d %H:%M:%S",
        timeInfo
    );
}


/* =================================================
   File Exists
   ================================================= */

int fileExists(
    const char *filename
)
{
    FILE *file;

    if (filename == NULL)
        return 0;

    file = fopen(filename, "r");

    if (file == NULL)
        return 0;

    fclose(file);

    return 1;
}


/* =================================================
   Ensure Data Directory
   ================================================= */

int ensureDataDirectory(void)
{
#ifdef _WIN32

    int result = system("if not exist data mkdir data");

#else

    int result = system("mkdir -p data");

#endif

    return (result == 0);
}


/* =================================================
   Save Battlefield
   ================================================= */

int saveBattlefield(
    const char *filename,
    const Battlefield *battlefield
)
{
    FILE *file;
    int i;

    if (filename == NULL || battlefield == NULL)
        return 0;

    file = fopen(filename, "w");

    if (file == NULL)
        return 0;


    fprintf(
        file,
        "# Advanced Naval Battle Simulator\n"
    );

    fprintf(
        file,
        "# Battlefield Configuration\n\n"
    );


    /* =========================
       Battlefield Information
       ========================= */

    fprintf(file, "[BATTLEFIELD]\n");

    fprintf(
        file,
        "size=%.6f\n",
        battlefield->size
    );

    fprintf(
        file,
        "battleship_x=%.6f\n",
        battlefield->battleshipPosition.x
    );

    fprintf(
        file,
        "battleship_y=%.6f\n",
        battlefield->battleshipPosition.y
    );

    fprintf(
        file,
        "escort_count=%d\n\n",
        battlefield->escortCount
    );


    /* =========================
       Battleship Information
       ========================= */

    fprintf(file, "[BATTLESHIP]\n");

    fprintf(
        file,
        "type=%c\n",
        battlefield->battleship.type
    );

    fprintf(
        file,
        "name=%s\n",
        battlefield->battleship.name
    );

    fprintf(
        file,
        "category=%d\n",
        battlefield->battleship.category
    );

    fprintf(
        file,
        "x=%.6f\n",
        battlefield->battleship.position.x
    );

    fprintf(
        file,
        "y=%.6f\n",
        battlefield->battleship.position.y
    );

    fprintf(
        file,
        "vMin=%.6f\n",
        battlefield->battleship.vMin
    );

    fprintf(
        file,
        "vMax=%.6f\n",
        battlefield->battleship.vMax
    );

    fprintf(
        file,
        "angleMin=%.6f\n",
        battlefield->battleship.angleMin
    );

    fprintf(
        file,
        "angleMax=%.6f\n",
        battlefield->battleship.angleMax
    );

    fprintf(
        file,
        "impactPower=%.6f\n",
        battlefield->battleship.impactPower
    );

    fprintf(
        file,
        "gamma=%.6f\n",
        battlefield->battleship.gamma
    );

    fprintf(
        file,
        "damage=%.6f\n",
        battlefield->battleship.damage
    );

    fprintf(
        file,
        "alive=%d\n\n",
        battlefield->battleship.alive
    );


    /* =========================
       Escort Ships
       ========================= */

    fprintf(file, "[ESCORT_SHIPS]\n");

    for (i = 0; i < battlefield->escortCount; i++)
    {
        Ship *ship =
            &battlefield->escortShips[i];

        fprintf(
            file,
            "SHIP %d\n",
            i
        );

        fprintf(
            file,
            "type=%c\n",
            ship->type
        );

        fprintf(
            file,
            "name=%s\n",
            ship->name
        );

        fprintf(
            file,
            "category=%d\n",
            ship->category
        );

        fprintf(
            file,
            "x=%.6f\n",
            ship->position.x
        );

        fprintf(
            file,
            "y=%.6f\n",
            ship->position.y
        );

        fprintf(
            file,
            "vMin=%.6f\n",
            ship->vMin
        );

        fprintf(
            file,
            "vMax=%.6f\n",
            ship->vMax
        );

        fprintf(
            file,
            "angleMin=%.6f\n",
            ship->angleMin
        );

        fprintf(
            file,
            "angleMax=%.6f\n",
            ship->angleMax
        );

        fprintf(
            file,
            "impactPower=%.6f\n",
            ship->impactPower
        );

        fprintf(
            file,
            "gamma=%.6f\n",
            ship->gamma
        );

        fprintf(
            file,
            "damage=%.6f\n",
            ship->damage
        );

        fprintf(
            file,
            "alive=%d\n\n",
            ship->alive
        );
    }


    fclose(file);

    return 1;
}


/* =================================================
   Load Battlefield
   ================================================= */

int loadBattlefield(
    const char *filename,
    Battlefield *battlefield
)
{
    FILE *file;

    char line[256];
    char key[100];
    char value[150];

    int currentShip = -1;

    if (filename == NULL ||
        battlefield == NULL)
    {
        return 0;
    }


    file = fopen(filename, "r");

    if (file == NULL)
        return 0;


    while (fgets(
        line,
        sizeof(line),
        file
    ) != NULL)
    {
        removeNewline(line);


        /* =========================
           Ignore Empty Lines
           ========================= */

        if (line[0] == '\0')
            continue;


        /* =========================
           Ignore Comments
           ========================= */

        if (line[0] == '#')
            continue;


        /* =========================
           Section Headers
           ========================= */

        if (line[0] == '[')
        {
            currentShip = -1;
            continue;
        }


        /* =========================
           Ship Header
           ========================= */

        if (strncmp(
            line,
            "SHIP ",
            5
        ) == 0)
        {
            currentShip = atoi(
                line + 5
            );

            if (currentShip < 0 ||
                currentShip >= MAX_ESCORT_SHIPS)
            {
                currentShip = -1;
            }

            continue;
        }


        /* =========================
           Key = Value
           ========================= */

        if (sscanf(
            line,
            "%99[^=]=%149[^\n]",
            key,
            value
        ) != 2)
        {
            continue;
        }


        /* =========================
           Escort Ship
           ========================= */

        if (currentShip >= 0)
        {
            Ship *ship =
                &battlefield->escortShips[currentShip];


            if (strcmp(key, "type") == 0)
            {
                ship->type = value[0];
            }

            else if (strcmp(key, "name") == 0)
            {
                strncpy(
                    ship->name,
                    value,
                    MAX_SHIP_NAME - 1
                );

                ship->name[
                    MAX_SHIP_NAME - 1
                ] = '\0';
            }

            else if (strcmp(key, "category") == 0)
            {
                ship->category =
                    (ShipCategory)atoi(value);
            }

            else if (strcmp(key, "x") == 0)
            {
                ship->position.x =
                    atof(value);
            }

            else if (strcmp(key, "y") == 0)
            {
                ship->position.y =
                    atof(value);
            }

            else if (strcmp(key, "vMin") == 0)
            {
                ship->vMin =
                    atof(value);
            }

            else if (strcmp(key, "vMax") == 0)
            {
                ship->vMax =
                    atof(value);
            }

            else if (strcmp(key, "angleMin") == 0)
            {
                ship->angleMin =
                    atof(value);
            }

            else if (strcmp(key, "angleMax") == 0)
            {
                ship->angleMax =
                    atof(value);
            }

            else if (strcmp(key, "impactPower") == 0)
            {
                ship->impactPower =
                    atof(value);
            }

            else if (strcmp(key, "gamma") == 0)
            {
                ship->gamma =
                    atof(value);
            }

            else if (strcmp(key, "damage") == 0)
            {
                ship->damage =
                    atof(value);
            }

            else if (strcmp(key, "alive") == 0)
            {
                ship->alive =
                    atoi(value);
            }
        }


        /* =========================
           Battlefield / Battleship
           ========================= */

        else
        {
            if (strcmp(key, "size") == 0)
            {
                battlefield->size =
                    atof(value);
            }

            else if (strcmp(
                key,
                "battleship_x"
            ) == 0)
            {
                battlefield->battleshipPosition.x =
                    atof(value);
            }

            else if (strcmp(
                key,
                "battleship_y"
            ) == 0)
            {
                battlefield->battleshipPosition.y =
                    atof(value);
            }

            else if (strcmp(
                key,
                "escort_count"
            ) == 0)
            {
                battlefield->escortCount =
                    atoi(value);
            }
        }
    }


    fclose(file);

    return 1;
}


/* =================================================
   Save Complete Simulation
   ================================================= */

int saveSimulation(
    const char *filename,
    const Battlefield *battlefield
)
{
    /*
     * The battlefield structure contains the
     * complete current simulation state.
     *
     * Therefore, saveBattlefield() can be used
     * to save the complete simulation.
     */

    return saveBattlefield(
        filename,
        battlefield
    );
}


/* =================================================
   Load Complete Simulation
   ================================================= */

int loadSimulation(
    const char *filename,
    Battlefield *battlefield
)
{
    /*
     * The saved battlefield contains the
     * complete simulation state.
     */

    return loadBattlefield(
        filename,
        battlefield
    );
}


/* =================================================
   Write Log
   ================================================= */

int writeLog(
    const char *filename,
    const char *message
)
{
    FILE *file;

    char dateTime[64];


    if (filename == NULL ||
        message == NULL)
    {
        return 0;
    }


    file = fopen(
        filename,
        "a"
    );

    if (file == NULL)
        return 0;


    getDateTime(
        dateTime,
        sizeof(dateTime)
    );


    fprintf(
        file,
        "[%s] %s\n",
        dateTime,
        message
    );


    fclose(file);

    return 1;
}


/* =================================================
   Log Battlefield
   ================================================= */

int logBattlefield(
    const char *filename,
    const Battlefield *battlefield
)
{
    FILE *file;

    char dateTime[64];

    int i;


    if (filename == NULL ||
        battlefield == NULL)
    {
        return 0;
    }


    file = fopen(
        filename,
        "a"
    );

    if (file == NULL)
        return 0;


    getDateTime(
        dateTime,
        sizeof(dateTime)
    );


    fprintf(
        file,
        "\n========================================\n"
    );

    fprintf(
        file,
        "NAVAL BATTLE SIMULATION LOG\n"
    );

    fprintf(
        file,
        "Date & Time: %s\n",
        dateTime
    );

    fprintf(
        file,
        "========================================\n"
    );


    /* =========================
       Battlefield
       ========================= */

    fprintf(
        file,
        "Battlefield Size : %.2f\n",
        battlefield->size
    );

    fprintf(
        file,
        "Battleship Position : (%.2f, %.2f)\n",
        battlefield->battleshipPosition.x,
        battlefield->battleshipPosition.y
    );

    fprintf(
        file,
        "Escort Ships : %d\n",
        battlefield->escortCount
    );


    /* =========================
       Battleship
       ========================= */

    fprintf(
        file,
        "\nBattleship\n"
    );

    fprintf(
        file,
        "Name      : %s\n",
        battlefield->battleship.name
    );

    fprintf(
        file,
        "Type      : %c\n",
        battlefield->battleship.type
    );

    fprintf(
        file,
        "Position  : (%.2f, %.2f)\n",
        battlefield->battleship.position.x,
        battlefield->battleship.position.y
    );

    fprintf(
        file,
        "Damage    : %.2f\n",
        battlefield->battleship.damage
    );

    fprintf(
        file,
        "Alive     : %s\n",
        battlefield->battleship.alive
            ? "Yes"
            : "No"
    );


    /* =========================
       Escort Ships
       ========================= */

    fprintf(
        file,
        "\nEscort Ships\n"
    );


    for (i = 0;
         i < battlefield->escortCount;
         i++)
    {
        Ship *ship =
            &battlefield->escortShips[i];


        fprintf(
            file,
            "\nShip %d\n",
            i + 1
        );

        fprintf(
            file,
            "Name      : %s\n",
            ship->name
        );

        fprintf(
            file,
            "Type      : %c\n",
            ship->type
        );

        fprintf(
            file,
            "Position  : (%.2f, %.2f)\n",
            ship->position.x,
            ship->position.y
        );

        fprintf(
            file,
            "Damage    : %.2f\n",
            ship->damage
        );

        fprintf(
            file,
            "Alive     : %s\n",
            ship->alive
                ? "Yes"
                : "No"
        );
    }


    fprintf(
        file,
        "\n========================================\n\n"
    );


    fclose(file);

    return 1;
}
