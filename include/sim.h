#ifndef SIM_H
#define SIM_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>


/* =========================================================
   CONSTANTS
   ========================================================= */

#define MAX_ESCORT_SHIPS 100
#define MAX_SHIP_NAME 50

#define GRAVITY 9.81
#define PI 3.14159265358979323846


/* =========================================================
   POSITION STRUCTURE
   ========================================================= */

typedef struct
{
    double x;
    double y;

} Position;


/* =========================================================
   SHIP CATEGORY
   ========================================================= */

typedef enum
{
    SHIP_BATTLESHIP,
    SHIP_ESCORT

} ShipCategory;


/* =========================================================
   SHIP STRUCTURE
   ========================================================= */

typedef struct
{
    /* Ship identification */

    char type;

    char name[MAX_SHIP_NAME];


    /* Ship category */

    ShipCategory category;


    /* Ship position */

    Position position;


    /* Projectile velocity range */

    double vMin;
    double vMax;


    /* Firing angle range */

    double angleMin;
    double angleMax;


    /* Weapon properties */

    double impactPower;

    double gamma;


    /* Current damage */

    double damage;


    /* Ship status */

    int alive;

} Ship;


/* =========================================================
   BATTLEFIELD STRUCTURE
   ========================================================= */

typedef struct
{
    /* Battlefield dimension */

    double size;


    /* Battleship position */

    Position battleshipPosition;


    /* Battleship */

    Ship battleship;


    /* Escort Ships */

    Ship escortShips[MAX_ESCORT_SHIPS];


    /* Number of Escort Ships */

    int escortCount;

} Battlefield;


/* =========================================================
   PROJECTILE STRUCTURE
   ========================================================= */

typedef struct
{
    /* Projectile velocity */

    double velocity;


    /* Projectile firing angle */

    double angle;


    /* Time of flight */

    double flightTime;


    /* Projectile range */

    double range;


    /* Horizontal velocity */

    double horizontalVelocity;


    /* Vertical velocity */

    double verticalVelocity;

} Projectile;


/* =========================================================
   ATTACK RESULT STRUCTURE
   ========================================================= */

typedef struct
{
    /* Attacker index */

    int attackerIndex;


    /* Target index */

    int targetIndex;


    /* Distance between ships */

    double distance;


    /* Attack velocity */

    double velocity;


    /* Attack angle */

    double angle;


    /* Impact power */

    double impactPower;


    /* Hit result */

    int hit;

} AttackResult;


/* =========================================================
   SIMULATION STATISTICS
   ========================================================= */

typedef struct
{
    /* Total number of attacks */

    int totalAttacks;


    /* Number of successful hits */

    int successfulHits;


    /* Number of destroyed ships */

    int destroyedShips;


    /* Damage received by Battleship */

    double battleshipDamage;


    /* Total damage caused */

    double totalDamage;

} SimulationStatistics;


/* =========================================================
   BATTLEFIELD FUNCTIONS
   ========================================================= */

void initializeBattlefield(
    Battlefield *battlefield
);


void setBattlefieldSize(
    Battlefield *battlefield,
    double size
);


void generateShipPositions(
    Battlefield *battlefield
);


void createBattleship(
    Battlefield *battlefield
);


void createEscortShips(
    Battlefield *battlefield,
    int numberOfShips
);


/* =========================================================
   SHIP FUNCTIONS
   ========================================================= */

void initializeShip(
    Ship *ship
);


void selectBattleshipType(
    Ship *ship
);


void selectEscortType(
    Ship *ship
);


int isShipAlive(
    const Ship *ship
);


double calculateDistance(
    const Position *a,
    const Position *b
);


/* =========================================================
   PROJECTILE FUNCTIONS
   ========================================================= */

double degreesToRadians(
    double degrees
);


double calculateFlightTime(
    double distance,
    double velocity,
    double angle
);


double calculateProjectileRange(
    double velocity,
    double angle
);


double calculateHorizontalVelocity(
    double velocity,
    double angle
);


double calculateVerticalVelocity(
    double velocity,
    double angle
);


int canProjectileReachTarget(
    double distance,
    double velocity,
    double angle
);


/* =========================================================
   ATTACK FUNCTIONS
   ========================================================= */

AttackResult performAttack(
    const Ship *attacker,
    const Ship *target
);


int canAttack(
    const Ship *attacker,
    const Ship *target
);


double calculateImpactPower(
    const Ship *attacker,
    const Ship *target
);


void applyDamage(
    Ship *target,
    double damage
);


/* =========================================================
   ASSIGNMENT PARTS
   ========================================================= */

/*
 * Part 1-A
 */

void runPart1A(void);


/*
 * Part 1-B
 */

void runPart1B(void);


/*
 * Part 1-C
 */

void runPart1C(void);


/*
 * Part 2-A
 */

void runPart2A(void);


/*
 * Part 2-B
 */

void runPart2B(void);


/*
 * Part 2-C
 */

void runPart2C(void);


/* =========================================================
   SIMULATION FUNCTIONS
   ========================================================= */

void runSimulation(
    Battlefield *battlefield
);


void resetSimulation(
    Battlefield *battlefield
);


/*
 * IMPORTANT:
 *
 * calculateStatistics() returns a
 * SimulationStatistics structure.
 *
 * Correct usage:
 *
 * SimulationStatistics statistics;
 *
 * statistics = calculateStatistics(&battlefield);
 */

SimulationStatistics calculateStatistics(
    const Battlefield *battlefield
);


/* =========================================================
   DISPLAY FUNCTIONS
   ========================================================= */

void displayBattlefield(
    const Battlefield *battlefield
);


void displayShip(
    const Ship *ship
);


void displayAllShips(
    const Battlefield *battlefield
);


void displayStatistics(
    const SimulationStatistics *statistics
);


/* =========================================================
   END OF SIM_H
   ========================================================= */

#endif /* SIM_H */
