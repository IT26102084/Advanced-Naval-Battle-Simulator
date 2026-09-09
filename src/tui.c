#include "../include/tui.h"
#include "../include/file.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


/* =========================================================
   ANSI COLOUR CODES
   ========================================================= */

#define RESET       "\033[0m"
#define BOLD        "\033[1m"

#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"
#define GRAY        "\033[90m"

#define BRIGHT_RED      "\033[91m"
#define BRIGHT_GREEN    "\033[92m"
#define BRIGHT_YELLOW   "\033[93m"
#define BRIGHT_BLUE     "\033[94m"
#define BRIGHT_MAGENTA  "\033[95m"
#define BRIGHT_CYAN     "\033[96m"


/* =========================================================
   INTERNAL HELPER FUNCTIONS
   ========================================================= */

static void clearInputBuffer(void)
{
    int ch;

    while ((ch = getchar()) != '\n' &&
           ch != EOF)
    {
        /* Clear remaining input */
    }
}


static void printHeader(const char *title)
{
    printf("\n");

    printf(BRIGHT_CYAN BOLD);
    printf("============================================================\n");
    printf("  %s\n", title);
    printf("============================================================\n");
    printf(RESET);
}


/* =========================================================
   TITLE
   ========================================================= */

void displayTitle(void)
{
    clearScreen();

    printf("\n");

    printf(BRIGHT_CYAN BOLD);
    printf("************************************************************\n");
    printf("*                                                          *\n");
    printf("*          ADVANCED NAVAL BATTLE SIMULATOR                 *\n");
    printf("*                                                          *\n");
    printf(RESET);

    printf(BRIGHT_YELLOW BOLD);
    printf("*                 SLIIT - SE1012                           *\n");
    printf("*              Programming Methodology                    *\n");
    printf(RESET);

    printf(BRIGHT_CYAN BOLD);
    printf("*                                                          *\n");
    printf("*                                                          *\n");
    printf("************************************************************\n");
    printf(RESET);

    printf("\n");
}


/* =========================================================
   SEPARATOR
   ========================================================= */

void displaySeparator(void)
{
    printf(BLUE);
    printf(
        "------------------------------------------------------------\n"
    );
    printf(RESET);
}


/* =========================================================
   MAIN MENU
   ========================================================= */

void displayMainMenu(void)
{
    printHeader("MAIN MENU");

    printf(BRIGHT_GREEN "  1. " RESET
           "Battlefield Management\n");

    printf(BRIGHT_GREEN "  2. " RESET
           "Ship Information\n");

    printf(BRIGHT_GREEN "  3. " RESET
           "Simulation\n");

    printf(BRIGHT_GREEN "  4. " RESET
           "Save Simulation\n");

    printf(BRIGHT_GREEN "  5. " RESET
           "Load Simulation\n");

    printf(BRIGHT_GREEN "  6. " RESET
           "Display Statistics\n");

    printf(BRIGHT_YELLOW "  7. View Instructions\n" RESET);

    printf(BRIGHT_RED "  0. Exit\n" RESET);

    displaySeparator();
}


/* =========================================================
   MAIN MENU INPUT
   ========================================================= */

int getMainMenuChoice(void)
{
    return getIntegerInput(
        CYAN "Enter your choice: " RESET
    );
}


/* =========================================================
   INSTRUCTIONS
   ========================================================= */

void displayInstructions(void)
{
    clearScreen();

    printHeader("SIMULATOR INSTRUCTIONS");

    printf(BRIGHT_YELLOW BOLD);
    printf("\n1. OBJECTIVE\n");
    printf(RESET);

    printf(
        "The simulator models a naval battle between a stationary\n"
        "Battleship (B) and several Escort Ships (E).\n"
    );

    printf(
        "The Battleship attempts to attack and destroy Escort Ships\n"
        "using projectile motion calculations.\n"
    );

    printf("\n");


    printf(BRIGHT_YELLOW BOLD);
    printf("2. BATTLEFIELD\n");
    printf(RESET);

    printf(
        "The battlefield is a square 2D area.\n"
    );

    printf(
        "Lower-left corner : (0, 0)\n"
        "Upper-right corner: (D, D)\n"
    );

    printf(
        "The value of D can be configured by the user.\n"
    );

    printf("\n");


    printf(BRIGHT_YELLOW BOLD);
    printf("3. BATTLESHIP\n");
    printf(RESET);

    printf(
        "The Battleship is stationary during the simulation.\n"
    );

    printf(
        "Its properties include:\n"
    );

    printf(
        "  - Ship type\n"
        "  - Position\n"
        "  - Minimum velocity\n"
        "  - Maximum velocity\n"
        "  - Minimum firing angle\n"
        "  - Maximum firing angle\n"
        "  - Impact power\n"
        "  - Gamma value\n"
    );

    printf("\n");


    printf(BRIGHT_YELLOW BOLD);
    printf("4. ESCORT SHIPS\n");
    printf(RESET);

    printf(
        "Escort Ships are positioned inside the battlefield.\n"
    );

    printf(
        "The number of Escort Ships can be configured by the user.\n"
    );

    printf(
        "Each Escort Ship has its own position, velocity range,\n"
        "angle range, impact power, gamma value and damage.\n"
    );

    printf("\n");


    printf(BRIGHT_YELLOW BOLD);
    printf("5. PROJECTILE MOTION\n");
    printf(RESET);

    printf(
        "Projectile motion is calculated using velocity,\n"
        "firing angle and gravitational acceleration.\n"
    );

    printf(
        "Gravitational acceleration:\n"
    );

    printf(
        "  g = 9.81 m/s^2\n"
    );

    printf("\n");


    printf(BRIGHT_YELLOW BOLD);
    printf("6. ATTACK SYSTEM\n");
    printf(RESET);

    printf(
        "During an attack, the simulator calculates the distance\n"
        "between the attacker and target.\n"
    );

    printf(
        "The projectile calculations determine whether the target\n"
        "can be reached successfully.\n"
    );

    printf("\n");


    printf(BRIGHT_YELLOW BOLD);
    printf("7. POWER DEGRADATION - PART 2-C\n");
    printf(RESET);

    printf(
        "Repeated firing causes impact power degradation.\n"
    );

    printf(
        "The degradation is modelled using a power-law relationship.\n"
    );

    printf(
        "As firing continues, the effective impact power can decrease.\n"
    );

    printf("\n");


    printf(BRIGHT_YELLOW BOLD);
    printf("8. SIMULATION SETUP\n");
    printf(RESET);

    printf(
        "Before running a simulation, configure the required\n"
        "battlefield and ship parameters.\n"
    );

    printf(
        "The Simulation Setup option provides an overview of\n"
        "the parameters that should be configured.\n"
    );

    printf("\n");


    printf(BRIGHT_YELLOW BOLD);
    printf("9. BATTLEFIELD DISPLAY\n");
    printf(RESET);

    printf(
        "The battlefield is represented using a 10 x 10 text map.\n"
    );

    printf("\n");

    printf("Legend:\n");

    printf(
        "  " BRIGHT_RED "[B]" RESET
        " = Battleship\n"
    );

    printf(
        "  " BRIGHT_YELLOW "[E]" RESET
        " = Escort Ship\n"
    );

    printf(
        "  " GRAY "[.]" RESET
        " = Empty area\n"
    );

    printf("\n");


    printf(BRIGHT_YELLOW BOLD);
    printf("10. SHIP INFORMATION\n");
    printf(RESET);

    printf(
        "The Ship Information menu can be used to view:\n"
    );

    printf(
        "  - Battleship information\n"
        "  - Escort Ship information\n"
        "  - All ship information\n"
    );

    printf("\n");


    printf(BRIGHT_YELLOW BOLD);
    printf("11. SIMULATION STATISTICS\n");
    printf(RESET);

    printf(
        "Statistics include:\n"
    );

    printf(
        "  - Total attacks\n"
        "  - Successful hits\n"
        "  - Destroyed ships\n"
        "  - Battleship damage\n"
        "  - Total damage\n"
        "  - Hit accuracy\n"
    );

    printf("\n");


    printf(BRIGHT_YELLOW BOLD);
    printf("12. SAVE AND LOAD\n");
    printf(RESET);

    printf(
        "Save Simulation stores the current simulation data.\n"
    );

    printf(
        "Load Simulation restores previously saved data.\n"
    );

    printf("\n");


    printf(BRIGHT_GREEN BOLD);
    printf("IMPORTANT NOTES\n");
    printf(RESET);

    printf(
        "1. Configure the battlefield before starting the simulation.\n"
        "2. Make sure Escort Ship positions are inside the battlefield.\n"
        "3. Check ship properties before running the simulation.\n"
        "4. Use Display Statistics after running the simulation.\n"
        "5. Save the simulation if you want to restore it later.\n"
    );

    printf("\n");

    displaySeparator();

    pauseScreen();
}


/* =========================================================
   BATTLEFIELD MENU
   ========================================================= */

void displayBattlefieldMenu(void)
{
    printHeader("BATTLEFIELD MANAGEMENT");

    printf(BRIGHT_GREEN "  1. " RESET
           "Display Battlefield\n");

    printf(BRIGHT_GREEN "  2. " RESET
           "Set Battlefield Size\n");

    printf(BRIGHT_GREEN "  3. " RESET
           "Create Battleship\n");

    printf(BRIGHT_GREEN "  4. " RESET
           "Create Escort Ships\n");

    printf(BRIGHT_GREEN "  5. " RESET
           "Generate Ship Positions\n");

    printf(BRIGHT_GREEN "  6. " RESET
           "Display All Ships\n");

    printf(BRIGHT_RED "  0. " RESET
           "Back\n");

    displaySeparator();
}


/* =========================================================
   BATTLEFIELD MENU INPUT
   ========================================================= */

int getBattlefieldMenuChoice(void)
{
    return getIntegerInput(
        CYAN "Enter your choice: " RESET
    );
}


/* =========================================================
   SHIP MENU
   ========================================================= */

void displayShipMenu(void)
{
    printHeader("SHIP INFORMATION");

    printf(BRIGHT_GREEN "  1. " RESET
           "Display Battleship\n");

    printf(BRIGHT_GREEN "  2. " RESET
           "Display Escort Ships\n");

    printf(BRIGHT_GREEN "  3. " RESET
           "Display All Ships\n");

    printf(BRIGHT_RED "  0. " RESET
           "Back\n");

    displaySeparator();
}


/* =========================================================
   SHIP MENU INPUT
   ========================================================= */

int getShipMenuChoice(void)
{
    return getIntegerInput(
        CYAN "Enter your choice: " RESET
    );
}


/* =========================================================
   SIMULATION MENU
   ========================================================= */

void displaySimulationMenu(void)
{
    printHeader("SIMULATION");

    printf(BRIGHT_GREEN "  1. " RESET
           "Run Simulation\n");

    printf(BRIGHT_GREEN "  2. " RESET
           "Reset Simulation\n");

    printf(BRIGHT_YELLOW "  3. " RESET
           "Simulation Setup\n");

    printf(BRIGHT_GREEN "  4. " RESET
           "Display Statistics\n");

    printf(BRIGHT_RED "  0. " RESET
           "Back\n");

    displaySeparator();
}


/* =========================================================
   SIMULATION MENU INPUT
   ========================================================= */

int getSimulationMenuChoice(void)
{
    return getIntegerInput(
        CYAN "Enter your choice: " RESET
    );
}


/* =========================================================
   INTEGER INPUT
   ========================================================= */

int getIntegerInput(
    const char *prompt
)
{
    int value;
    int result;

    while (1)
    {
        if (prompt != NULL)
        {
            printf("%s", prompt);
        }

        result = scanf(
            "%d",
            &value
        );

        if (result == 1)
        {
            clearInputBuffer();

            return value;
        }

        printf(
            BRIGHT_RED
            "Invalid input. Please enter an integer.\n"
            RESET
        );

        clearInputBuffer();
    }
}


/* =========================================================
   DOUBLE INPUT
   ========================================================= */

double getDoubleInput(
    const char *prompt
)
{
    double value;
    int result;

    while (1)
    {
        if (prompt != NULL)
        {
            printf("%s", prompt);
        }

        result = scanf(
            "%lf",
            &value
        );

        if (result == 1)
        {
            clearInputBuffer();

            return value;
        }

        printf(
            BRIGHT_RED
            "Invalid input. Please enter a number.\n"
            RESET
        );

        clearInputBuffer();
    }
}


/* =========================================================
   CHARACTER INPUT
   ========================================================= */

char getCharacterInput(
    const char *prompt
)
{
    char value;

    while (1)
    {
        if (prompt != NULL)
        {
            printf("%s", prompt);
        }

        if (scanf(
            " %c",
            &value
        ) == 1)
        {
            clearInputBuffer();

            return value;
        }

        clearInputBuffer();

        printf(
            BRIGHT_RED
            "Invalid input.\n"
            RESET
        );
    }
}


/* =========================================================
   STRING INPUT
   ========================================================= */

void getStringInput(
    const char *prompt,
    char *buffer,
    int bufferSize
)
{
    if (
        buffer == NULL ||
        bufferSize <= 0
    )
    {
        return;
    }

    if (prompt != NULL)
    {
        printf("%s", prompt);
    }

    if (fgets(
        buffer,
        bufferSize,
        stdin
    ) == NULL)
    {
        buffer[0] = '\0';

        return;
    }

    buffer[
        strcspn(buffer, "\r\n")
    ] = '\0';
}


/* =========================================================
   DISPLAY BATTLEFIELD
   ========================================================= */

void displayBattlefieldTUI(
    const Battlefield *battlefield
)
{
    int rows;
    int cols;

    int i;

    if (battlefield == NULL)
    {
        displayError(
            "Invalid battlefield."
        );

        return;
    }


    printHeader(
        "BATTLEFIELD MAP"
    );


    printf(
        CYAN
        "Battlefield Size: %.2f x %.2f\n"
        RESET,
        battlefield->size,
        battlefield->size
    );

    printf("\n");


    /*
     * 10 x 10 text map.
     */

    rows = 10;
    cols = 10;


    printf("       ");

    for (i = 0; i < cols; i++)
    {
        printf("----");
    }

    printf("-\n");


    for (
        int row = 0;
        row < rows;
        row++
    )
    {
        printf(
            GRAY
            "  %2d | "
            RESET,
            row
        );


        for (
            int col = 0;
            col < cols;
            col++
        )
        {
            char symbol = '.';

            double cellWidth =
                battlefield->size /
                (double)cols;

            double cellHeight =
                battlefield->size /
                (double)rows;


            double x =
                (col + 0.5) *
                cellWidth;

            double y =
                (row + 0.5) *
                cellHeight;


            /*
             * Check Battleship.
             */

            if (
                fabs(
                    battlefield->battleship.position.x
                    - x
                ) < cellWidth / 2.0
                &&
                fabs(
                    battlefield->battleship.position.y
                    - y
                ) < cellHeight / 2.0
                &&
                battlefield->battleship.alive
            )
            {
                symbol = 'B';
            }


            /*
             * Check Escort Ships.
             */

            for (
                i = 0;
                i < battlefield->escortCount;
                i++
            )
            {
                if (
                    battlefield->escortShips[i].alive
                    &&
                    fabs(
                        battlefield->escortShips[i]
                            .position.x - x
                    ) < cellWidth / 2.0
                    &&
                    fabs(
                        battlefield->escortShips[i]
                            .position.y - y
                    ) < cellHeight / 2.0
                )
                {
                    symbol = 'E';

                    break;
                }
            }


            /*
             * Coloured symbols.
             */

            if (symbol == 'B')
            {
                printf(
                    "["
                    BRIGHT_RED
                    "B"
                    RESET
                    "]"
                );
            }
            else if (symbol == 'E')
            {
                printf(
                    "["
                    BRIGHT_YELLOW
                    "E"
                    RESET
                    "]"
                );
            }
            else
            {
                printf(
                    "["
                    GRAY
                    "."
                    RESET
                    "]"
                );
            }
        }

        printf("\n");
    }


    printf("\n");

    printf(
        "Legend: "
        BRIGHT_RED "[B] Battleship" RESET
        "   "
        BRIGHT_YELLOW "[E] Escort Ship" RESET
        "   "
        GRAY "[.] Empty" RESET
        "\n"
    );
}


/* =========================================================
   DISPLAY ALL SHIPS
   ========================================================= */

void displayShipsTUI(
    const Battlefield *battlefield
)
{
    int i;

    if (battlefield == NULL)
    {
        displayError(
            "Invalid battlefield."
        );

        return;
    }


    printHeader(
        "SHIP INFORMATION"
    );


    printf(
        BRIGHT_CYAN
        "%-5s %-20s %-8s %-12s %-12s %-12s\n"
        RESET,
        "No.",
        "Name",
        "Type",
        "X",
        "Y",
        "Status"
    );

    displaySeparator();


    /*
     * Battleship.
     */

    printf(
        "%-5d %-20s %-8c %-12.2f %-12.2f ",
        1,
        battlefield->battleship.name,
        battlefield->battleship.type,
        battlefield->battleship.position.x,
        battlefield->battleship.position.y
    );


    if (battlefield->battleship.alive)
    {
        printf(
            BRIGHT_GREEN
            "%-12s"
            RESET
            "\n",
            "Alive"
        );
    }
    else
    {
        printf(
            BRIGHT_RED
            "%-12s"
            RESET
            "\n",
            "Destroyed"
        );
    }


    /*
     * Escort Ships.
     */

    for (
        i = 0;
        i < battlefield->escortCount;
        i++
    )
    {
        Ship *ship =
            &battlefield->escortShips[i];


        printf(
            "%-5d %-20s %-8c %-12.2f %-12.2f ",
            i + 2,
            ship->name,
            ship->type,
            ship->position.x,
            ship->position.y
        );


        if (ship->alive)
        {
            printf(
                BRIGHT_GREEN
                "%-12s"
                RESET
                "\n",
                "Alive"
            );
        }
        else
        {
            printf(
                BRIGHT_RED
                "%-12s"
                RESET
                "\n",
                "Destroyed"
            );
        }
    }


    printf("\n");
}


/* =========================================================
   DISPLAY SINGLE SHIP
   ========================================================= */

void displayShipTUI(
    const Ship *ship
)
{
    if (ship == NULL)
    {
        displayError(
            "Invalid ship."
        );

        return;
    }


    printHeader(
        "SHIP DETAILS"
    );


    printf(
        CYAN
        "Name             : "
        RESET
        "%s\n",
        ship->name
    );


    printf(
        CYAN
        "Type             : "
        RESET
        "%c\n",
        ship->type
    );


    printf(
        CYAN
        "Category         : "
        RESET
        "%s\n",
        ship->category ==
            SHIP_BATTLESHIP
            ? "Battleship"
            : "Escort"
    );


    printf(
        CYAN
        "Position X       : "
        RESET
        "%.2f\n",
        ship->position.x
    );


    printf(
        CYAN
        "Position Y       : "
        RESET
        "%.2f\n",
        ship->position.y
    );


    /*
     * IMPORTANT:
     * Correct fields from sim.h:
     *
     * vMin
     * vMax
     */

    printf(
        CYAN
        "Minimum Velocity : "
        RESET
        "%.2f\n",
        ship->vMin
    );


    printf(
        CYAN
        "Maximum Velocity : "
        RESET
        "%.2f\n",
        ship->vMax
    );


    printf(
        CYAN
        "Minimum Angle    : "
        RESET
        "%.2f\n",
        ship->angleMin
    );


    printf(
        CYAN
        "Maximum Angle    : "
        RESET
        "%.2f\n",
        ship->angleMax
    );


    printf(
        CYAN
        "Impact Power     : "
        RESET
        "%.2f\n",
        ship->impactPower
    );


    printf(
        CYAN
        "Gamma            : "
        RESET
        "%.2f\n",
        ship->gamma
    );


    printf(
        CYAN
        "Damage           : "
        RESET
        "%.2f\n",
        ship->damage
    );


    printf(
        CYAN
        "Status           : "
        RESET
    );


    if (ship->alive)
    {
        printf(
            BRIGHT_GREEN
            "ALIVE"
            RESET
            "\n"
        );
    }
    else
    {
        printf(
            BRIGHT_RED
            "DESTROYED"
            RESET
            "\n"
        );
    }
}


/* =========================================================
   DISPLAY STATISTICS
   ========================================================= */

void displayStatisticsTUI(
    const SimulationStatistics *statistics
)
{
    if (statistics == NULL)
    {
        displayError(
            "Invalid statistics."
        );

        return;
    }


    printHeader(
        "SIMULATION STATISTICS"
    );


    printf(
        CYAN
        "Total Attacks       : "
        RESET
        BRIGHT_YELLOW
        "%d"
        RESET
        "\n",
        statistics->totalAttacks
    );


    printf(
        CYAN
        "Successful Hits     : "
        RESET
        BRIGHT_GREEN
        "%d"
        RESET
        "\n",
        statistics->successfulHits
    );


    printf(
        CYAN
        "Destroyed Ships     : "
        RESET
        BRIGHT_RED
        "%d"
        RESET
        "\n",
        statistics->destroyedShips
    );


    printf(
        CYAN
        "Battleship Damage   : "
        RESET
        "%.2f\n",
        statistics->battleshipDamage
    );


    printf(
        CYAN
        "Total Damage        : "
        RESET
        "%.2f\n",
        statistics->totalDamage
    );


    /*
     * Calculate accuracy.
     */

    if (statistics->totalAttacks > 0)
    {
        double accuracy =
            (
                (double)statistics->successfulHits
                /
                (double)statistics->totalAttacks
            ) * 100.0;


        printf(
            CYAN
            "Hit Accuracy        : "
            RESET
        );


        if (accuracy >= 50.0)
        {
            printf(
                BRIGHT_GREEN
                "%.2f%%"
                RESET
                "\n",
                accuracy
            );
        }
        else
        {
            printf(
                BRIGHT_YELLOW
                "%.2f%%"
                RESET
                "\n",
                accuracy
            );
        }
    }
    else
    {
        printf(
            CYAN
            "Hit Accuracy        : "
            RESET
            GRAY
            "0.00%%"
            RESET
            "\n"
        );
    }
}


/* =========================================================
   SUCCESS MESSAGE
   ========================================================= */

void displaySuccess(
    const char *message
)
{
    printf(
        "\n"
        BRIGHT_GREEN
        BOLD
        "[ SUCCESS ] "
        RESET
        "%s\n",
        message != NULL
            ? message
            : ""
    );
}


/* =========================================================
   ERROR MESSAGE
   ========================================================= */

void displayError(
    const char *message
)
{
    printf(
        "\n"
        BRIGHT_RED
        BOLD
        "[ ERROR ] "
        RESET
        "%s\n",
        message != NULL
            ? message
            : ""
    );
}


/* =========================================================
   WARNING MESSAGE
   ========================================================= */

void displayWarning(
    const char *message
)
{
    printf(
        "\n"
        BRIGHT_YELLOW
        BOLD
        "[ WARNING ] "
        RESET
        "%s\n",
        message != NULL
            ? message
            : ""
    );
}


/* =========================================================
   PAUSE SCREEN
   ========================================================= */

void pauseScreen(void)
{
    char buffer[8];

    printf(
        "\n"
        GRAY
        "Press ENTER to continue..."
        RESET
    );

    fgets(
        buffer,
        sizeof(buffer),
        stdin
    );
}


/* =========================================================
   CLEAR SCREEN
   ========================================================= */

void clearScreen(void)
{
    /*
     * Reset colours before clearing terminal.
     */

    printf(RESET);

    fflush(stdout);

#ifdef _WIN32

    system("cls");

#else

    system("clear");

#endif
}


/* =========================================================
   RUN TUI
   ========================================================= */

void runTUI(void)
{
    Battlefield battlefield;

    int running = 1;


    /* =====================================================
       INITIALIZE BATTLEFIELD
       ===================================================== */

    initializeBattlefield(
        &battlefield
    );


    /*
     * Default battlefield size.
     */

    setBattlefieldSize(
        &battlefield,
        100.0
    );


    /*
     * Create default Battleship.
     */

    createBattleship(
        &battlefield
    );


    /*
     * Create default Escort Ships.
     */

    createEscortShips(
        &battlefield,
        5
    );


    /*
     * Generate initial positions.
     */

    generateShipPositions(
        &battlefield
    );


    /* =====================================================
       MAIN LOOP
       ===================================================== */

    while (running)
    {
        int choice;


        displayTitle();

        displayMainMenu();

        choice =
            getMainMenuChoice();


        switch (choice)
        {
            /* =================================================
               1. BATTLEFIELD MANAGEMENT
               ================================================= */

            case 1:
            {
                int back = 0;

                while (!back)
                {
                    int option;

                    clearScreen();

                    displayBattlefieldMenu();

                    option =
                        getBattlefieldMenuChoice();


                    switch (option)
                    {
                        /* -------------------------------------
                           DISPLAY BATTLEFIELD
                           ------------------------------------- */

                        case 1:

                            clearScreen();

                            displayBattlefieldTUI(
                                &battlefield
                            );

                            pauseScreen();

                            break;


                        /* -------------------------------------
                           SET BATTLEFIELD SIZE
                           ------------------------------------- */

                        case 2:
                        {
                            double size;


                            size =
                                getDoubleInput(
                                    CYAN
                                    "Enter battlefield size D: "
                                    RESET
                                );


                            if (size > 0.0)
                            {
                                setBattlefieldSize(
                                    &battlefield,
                                    size
                                );

                                displaySuccess(
                                    "Battlefield size updated successfully."
                                );
                            }
                            else
                            {
                                displayError(
                                    "Battlefield size must be greater than zero."
                                );
                            }


                            pauseScreen();

                            break;
                        }


                        /* -------------------------------------
                           CREATE BATTLESHIP
                           ------------------------------------- */

                        case 3:

                            createBattleship(
                                &battlefield
                            );

                            displaySuccess(
                                "Battleship created successfully."
                            );

                            pauseScreen();

                            break;


                        /* -------------------------------------
                           CREATE ESCORT SHIPS
                           ------------------------------------- */

                        case 4:
                        {
                            int count;


                            count =
                                getIntegerInput(
                                    CYAN
                                    "Enter number of Escort Ships: "
                                    RESET
                                );


                            if (
                                count >= 0 &&
                                count <= MAX_ESCORT_SHIPS
                            )
                            {
                                createEscortShips(
                                    &battlefield,
                                    count
                                );

                                displaySuccess(
                                    "Escort Ships created successfully."
                                );
                            }
                            else
                            {
                                displayError(
                                    "Invalid number of Escort Ships."
                                );
                            }


                            pauseScreen();

                            break;
                        }


                        /* -------------------------------------
                           GENERATE POSITIONS
                           ------------------------------------- */

                        case 5:

                            generateShipPositions(
                                &battlefield
                            );

                            displaySuccess(
                                "Ship positions generated successfully."
                            );

                            pauseScreen();

                            break;


                        /* -------------------------------------
                           DISPLAY ALL SHIPS
                           ------------------------------------- */

                        case 6:

                            clearScreen();

                            displayShipsTUI(
                                &battlefield
                            );

                            pauseScreen();

                            break;


                        /* -------------------------------------
                           BACK
                           ------------------------------------- */

                        case 0:

                            back = 1;

                            break;


                        default:

                            displayError(
                                "Invalid battlefield menu choice."
                            );

                            pauseScreen();

                            break;
                    }
                }

                break;
            }


            /* =================================================
               2. SHIP INFORMATION
               ================================================= */

            case 2:
            {
                int back = 0;

                while (!back)
                {
                    int option;

                    clearScreen();

                    displayShipMenu();

                    option =
                        getShipMenuChoice();


                    switch (option)
                    {
                        /* -------------------------------------
                           DISPLAY BATTLESHIP
                           ------------------------------------- */

                        case 1:

                            clearScreen();

                            displayShipTUI(
                                &battlefield.battleship
                            );

                            pauseScreen();

                            break;


                        /* -------------------------------------
                           DISPLAY ESCORT SHIPS
                           ------------------------------------- */

                        case 2:

                            clearScreen();

                            if (
                                battlefield.escortCount
                                == 0
                            )
                            {
                                displayWarning(
                                    "No Escort Ships are available."
                                );
                            }
                            else
                            {
                                int i;

                                for (
                                    i = 0;
                                    i < battlefield.escortCount;
                                    i++
                                )
                                {
                                    displayShipTUI(
                                        &battlefield
                                            .escortShips[i]
                                    );
                                }
                            }

                            pauseScreen();

                            break;


                        /* -------------------------------------
                           DISPLAY ALL SHIPS
                           ------------------------------------- */

                        case 3:

                            clearScreen();

                            displayShipsTUI(
                                &battlefield
                            );

                            pauseScreen();

                            break;


                        /* -------------------------------------
                           BACK
                           ------------------------------------- */

                        case 0:

                            back = 1;

                            break;


                        default:

                            displayError(
                                "Invalid ship menu choice."
                            );

                            pauseScreen();

                            break;
                    }
                }

                break;
            }


            /* =================================================
               3. SIMULATION
               ================================================= */

            case 3:
            {
                int back = 0;

                while (!back)
                {
                    int option;

                    clearScreen();

                    displaySimulationMenu();

                    option =
                        getSimulationMenuChoice();


                    switch (option)
                    {
                        /* -------------------------------------
                           RUN SIMULATION
                           ------------------------------------- */

                        case 1:

                            clearScreen();

                            printf(
                                BRIGHT_CYAN
                                BOLD
                                "\nStarting Naval Battle Simulation...\n"
                                RESET
                            );

                            printf("\n");

                            runSimulation(
                                &battlefield
                            );

                            displaySuccess(
                                "Simulation completed."
                            );

                            pauseScreen();

                            break;


                        /* -------------------------------------
                           RESET SIMULATION
                           ------------------------------------- */

                        case 2:

                            resetSimulation(
                                &battlefield
                            );

                            displaySuccess(
                                "Simulation reset successfully."
                            );

                            pauseScreen();

                            break;


                        /* -------------------------------------
                           SIMULATION SETUP
                           ------------------------------------- */

                        case 3:

                            clearScreen();

                            printHeader(
                                "SIMULATION SETUP"
                            );

                            printf("\n");


                            printf(
                                BRIGHT_YELLOW
                                BOLD
                                "1. Battleship Properties\n"
                                RESET
                            );

                            printf(
                                "   Configure the Battleship type,\n"
                                "   velocity range, firing angle range,\n"
                                "   impact power and gamma value.\n"
                            );

                            printf("\n");


                            printf(
                                BRIGHT_YELLOW
                                BOLD
                                "2. Escort Ships Settings\n"
                                RESET
                            );

                            printf(
                                "   Configure the number of Escort Ships\n"
                                "   and their related parameters.\n"
                            );

                            printf("\n");


                            printf(
                                BRIGHT_YELLOW
                                BOLD
                                "3. Battlefield Settings\n"
                                RESET
                            );

                            printf(
                                "   Configure the battlefield size and\n"
                                "   generate valid ship positions.\n"
                            );

                            printf("\n");


                            printf(
                                BRIGHT_GREEN
                                BOLD
                                "Current Battlefield\n"
                                RESET
                            );

                            printf(
                                "   Size         : %.2f x %.2f\n",
                                battlefield.size,
                                battlefield.size
                            );

                            printf(
                                "   Escort Ships : %d\n",
                                battlefield.escortCount
                            );


                            printf("\n");

                            displaySeparator();

                            printf(
                                CYAN
                                "Use Battlefield Management to configure\n"
                                "the battlefield and create ships.\n"
                                RESET
                            );

                            pauseScreen();

                            break;


                        /* -------------------------------------
                           DISPLAY STATISTICS
                           ------------------------------------- */

                        case 4:
                        {
                            SimulationStatistics stats;


                            clearScreen();


                            /*
                             * IMPORTANT:
                             *
                             * calculateStatistics() returns
                             * SimulationStatistics.
                             *
                             * It accepts only one argument.
                             */

                            stats =
                                calculateStatistics(
                                    &battlefield
                                );


                            displayStatisticsTUI(
                                &stats
                            );


                            pauseScreen();

                            break;
                        }


                        /* -------------------------------------
                           BACK
                           ------------------------------------- */

                        case 0:

                            back = 1;

                            break;


                        default:

                            displayError(
                                "Invalid simulation menu choice."
                            );

                            pauseScreen();

                            break;
                    }
                }

                break;
            }


            /* =================================================
               4. SAVE SIMULATION
               ================================================= */

            case 4:

                clearScreen();

                printHeader(
                    "SAVE SIMULATION"
                );

                ensureDataDirectory();


                if (
                    saveSimulation(
                        SAVE_FILE,
                        &battlefield
                    )
                )
                {
                    displaySuccess(
                        "Simulation saved successfully."
                    );
                }
                else
                {
                    displayError(
                        "Unable to save simulation."
                    );
                }


                pauseScreen();

                break;


            /* =================================================
               5. LOAD SIMULATION
               ================================================= */

            case 5:

                clearScreen();

                printHeader(
                    "LOAD SIMULATION"
                );


                if (!fileExists(SAVE_FILE))
                {
                    displayWarning(
                        "No saved simulation file was found."
                    );

                    pauseScreen();

                    break;
                }


                if (
                    loadSimulation(
                        SAVE_FILE,
                        &battlefield
                    )
                )
                {
                    displaySuccess(
                        "Simulation loaded successfully."
                    );
                }
                else
                {
                    displayError(
                        "Unable to load simulation."
                    );
                }


                pauseScreen();

                break;


            /* =================================================
               6. DISPLAY STATISTICS
               ================================================= */

            case 6:
            {
                SimulationStatistics stats;


                clearScreen();


                /*
                 * Correct calculateStatistics()
                 * function usage.
                 */

                stats =
                    calculateStatistics(
                        &battlefield
                    );


                displayStatisticsTUI(
                    &stats
                );


                pauseScreen();

                break;
            }


            /* =================================================
               7. VIEW INSTRUCTIONS
               ================================================= */

            case 7:

                displayInstructions();

                break;


            /* =================================================
               0. EXIT
               ================================================= */

            case 0:

                running = 0;

                break;


            /* =================================================
               INVALID OPTION
               ================================================= */

            default:

                displayError(
                    "Invalid main menu choice."
                );

                pauseScreen();

                break;
        }
    }


    /* =====================================================
       EXIT MESSAGE
       ===================================================== */

    clearScreen();

    printf("\n");

    printf(
        BRIGHT_CYAN
        BOLD
        "============================================================\n"
        "       Thank you for using Naval Battle Simulator!\n"
        "============================================================\n"
        RESET
    );

    printf("\n");
}
