#include "../include/sim.h"
#include "../include/file.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>


/* =========================================================
   Ship Health
   ========================================================= */

#define BATTLESHIP_HEALTH 500.0
#define ESCORT_HEALTH     150.0


/* =========================================================
   Internal Simulation Statistics
   ========================================================= */

static int g_totalAttacks = 0;
static int g_successfulHits = 0;


/* =========================================================
   Internal Helper Functions
   ========================================================= */

static double randomDouble(double min, double max)
{
    double r;

    r = (double)rand() / (double)RAND_MAX;

    return min + r * (max - min);
}


static double clampDouble(double value, double min, double max)
{
    if (value < min)
        return min;

    if (value > max)
        return max;

    return value;
}


static double getShipHealth(const Ship *ship)
{
    if (ship == NULL)
        return 0.0;

    if (ship->category == SHIP_BATTLESHIP)
        return BATTLESHIP_HEALTH;

    return ESCORT_HEALTH;
}


static double getRemainingHealth(const Ship *ship)
{
    double health;

    if (ship == NULL)
        return 0.0;

    health = getShipHealth(ship);

    health -= ship->damage;

    if (health < 0.0)
        health = 0.0;

    return health;
}


/* =========================================================
   Battleship Information
   ========================================================= */

static const char *getBattleshipGun(char type)
{
    switch (type)
    {
        case 'U':
            return "50-caliber Mark 7 gun";

        case 'M':
            return "(356 mm) Mark VII gun";

        case 'R':
            return "(15 inch) Mle 1935 gun";

        case 'S':
            return "(16 inch) B-37 gun";

        default:
            return "Unknown gun";
    }
}


static const char *getBattleshipName(char type)
{
    switch (type)
    {
        case 'U':
            return "USS Iowa (BB-61)";

        case 'M':
            return "MS King George V";

        case 'R':
            return "Richelieu";

        case 'S':
            return "Sovetsky Soyuz-class";

        default:
            return "Unknown Battleship";
    }
}


/* =========================================================
   Battlefield Functions
   ========================================================= */

void initializeBattlefield(Battlefield *battlefield)
{
    if (battlefield == NULL)
        return;

    battlefield->size = 100.0;

    battlefield->battleshipPosition.x = 50.0;
    battlefield->battleshipPosition.y = 50.0;

    battlefield->escortCount = 0;

    initializeShip(&battlefield->battleship);

    battlefield->battleship.category = SHIP_BATTLESHIP;
    battlefield->battleship.alive = 1;

    memset(
        battlefield->escortShips,
        0,
        sizeof(battlefield->escortShips)
    );

    g_totalAttacks = 0;
    g_successfulHits = 0;
}


void setBattlefieldSize(
    Battlefield *battlefield,
    double size
)
{
    if (battlefield == NULL)
        return;

    if (size <= 0.0)
        return;

    battlefield->size = size;

    battlefield->battleshipPosition.x = size / 2.0;
    battlefield->battleshipPosition.y = size / 2.0;
}


void generateShipPositions(Battlefield *battlefield)
{
    int i;

    if (battlefield == NULL)
        return;

    /*
     * Battleship remains at centre.
     */

    battlefield->battleshipPosition.x =
        battlefield->size / 2.0;

    battlefield->battleshipPosition.y =
        battlefield->size / 2.0;

    battlefield->battleship.position =
        battlefield->battleshipPosition;


    /*
     * Generate escort positions.
     * Minimum distance from battleship = 10 units.
     */

    for (i = 0; i < battlefield->escortCount; i++)
    {
        double x;
        double y;
        int attempts = 0;

        do
        {
            x = randomDouble(
                0.0,
                battlefield->size
            );

            y = randomDouble(
                0.0,
                battlefield->size
            );

            attempts++;

            if (attempts > 10000)
                break;

        } while (
            calculateDistance(
                &battlefield->battleship.position,
                &(Position){x, y}
            ) < 10.0
        );

        battlefield->escortShips[i].position.x = x;
        battlefield->escortShips[i].position.y = y;
    }
}


/* =========================================================
   CREATE BATTLESHIP
   ========================================================= */

void createBattleship(Battlefield *battlefield)
{
    if (battlefield == NULL)
        return;


    /*
     * Initialize Battleship.
     */

    initializeShip(
        &battlefield->battleship
    );

    battlefield->battleship.category =
        SHIP_BATTLESHIP;


    /*
     * IMPORTANT:
     *
     * Battleship type selection is kept HERE.
     *
     * It is NOT performed before the Main Menu.
     */

    selectBattleshipType(
        &battlefield->battleship
    );


    /*
     * Keep Battleship at battlefield centre.
     */

    battlefield->battleship.position =
        battlefield->battleshipPosition;

    battlefield->battleship.alive = 1;
    battlefield->battleship.damage = 0.0;
}


void createEscortShips(
    Battlefield *battlefield,
    int numberOfShips
)
{
    int i;

    if (battlefield == NULL)
        return;

    if (numberOfShips < 0)
        numberOfShips = 0;

    if (numberOfShips > MAX_ESCORT_SHIPS)
        numberOfShips = MAX_ESCORT_SHIPS;

    battlefield->escortCount = numberOfShips;


    for (i = 0; i < numberOfShips; i++)
    {
        Ship *ship =
            &battlefield->escortShips[i];

        initializeShip(ship);

        ship->category = SHIP_ESCORT;

        selectEscortType(ship);

        ship->alive = 1;
        ship->damage = 0.0;

        snprintf(
            ship->name,
            MAX_SHIP_NAME,
            "Escort-%d",
            i + 1
        );
    }
}


/* =========================================================
   Ship Functions
   ========================================================= */

void initializeShip(Ship *ship)
{
    if (ship == NULL)
        return;

    ship->type = 'U';

    strcpy(
        ship->name,
        "Unknown Ship"
    );

    ship->category = SHIP_ESCORT;

    ship->position.x = 0.0;
    ship->position.y = 0.0;

    ship->vMin = 10.0;
    ship->vMax = 50.0;

    ship->angleMin = 10.0;
    ship->angleMax = 80.0;

    ship->impactPower = 100.0;

    ship->gamma = 1.0;

    ship->damage = 0.0;

    ship->alive = 1;
}


/* =========================================================
   SELECT BATTLESHIP TYPE
   ========================================================= */

void selectBattleshipType(Ship *ship)
{
    int choice;
    int validChoice = 0;

    if (ship == NULL)
        return;

    ship->category = SHIP_BATTLESHIP;


    printf("\n");
    printf("============================================\n");
    printf("          SELECT BATTLESHIP TYPE\n");
    printf("============================================\n");

    printf("\n");
    printf("1. USS Iowa (BB-61)\n");
    printf("   Notation : U\n");
    printf("   Gun      : 50-caliber Mark 7 gun\n");

    printf("\n");
    printf("2. MS King George V\n");
    printf("   Notation : M\n");
    printf("   Gun      : (356 mm) Mark VII gun\n");

    printf("\n");
    printf("3. Richelieu\n");
    printf("   Notation : R\n");
    printf("   Gun      : (15 inch) Mle 1935 gun\n");

    printf("\n");
    printf("4. Sovetsky Soyuz-class\n");
    printf("   Notation : S\n");
    printf("   Gun      : (16 inch) B-37 gun\n");

    printf("\n");
    printf("============================================\n");


    /*
     * Keep asking until valid choice.
     */

    while (!validChoice)
    {
        printf(
            "Enter Battleship Type (1-4): "
        );

        if (scanf("%d", &choice) != 1)
        {
            printf(
                "Invalid input! Please enter "
                "a number from 1 to 4.\n"
            );

            while (getchar() != '\n')
                ;

            continue;
        }

        if (choice < 1 || choice > 4)
        {
            printf(
                "Invalid choice! Please select "
                "1, 2, 3 or 4.\n"
            );

            continue;
        }

        validChoice = 1;
    }


    /*
     * Assign Battleship information.
     */

    switch (choice)
    {
        case 1:

            ship->type = 'U';

            strcpy(
                ship->name,
                "USS Iowa (BB-61)"
            );

            ship->vMin = 30.0;
            ship->vMax = 100.0;

            ship->angleMin = 15.0;
            ship->angleMax = 75.0;

            ship->impactPower = 150.0;

            ship->gamma = 1.20;

            break;


        case 2:

            ship->type = 'M';

            strcpy(
                ship->name,
                "MS King George V"
            );

            ship->vMin = 30.0;
            ship->vMax = 95.0;

            ship->angleMin = 15.0;
            ship->angleMax = 75.0;

            ship->impactPower = 145.0;

            ship->gamma = 1.18;

            break;


        case 3:

            ship->type = 'R';

            strcpy(
                ship->name,
                "Richelieu"
            );

            ship->vMin = 30.0;
            ship->vMax = 95.0;

            ship->angleMin = 15.0;
            ship->angleMax = 75.0;

            ship->impactPower = 148.0;

            ship->gamma = 1.19;

            break;


        case 4:

            ship->type = 'S';

            strcpy(
                ship->name,
                "Sovetsky Soyuz-class"
            );

            ship->vMin = 30.0;
            ship->vMax = 98.0;

            ship->angleMin = 15.0;
            ship->angleMax = 75.0;

            ship->impactPower = 152.0;

            ship->gamma = 1.21;

            break;
    }


    ship->damage = 0.0;
    ship->alive = 1;


    /*
     * Display selected Battleship.
     */

    printf("\n");
    printf("============================================\n");
    printf("       BATTLESHIP CREATED SUCCESSFULLY\n");
    printf("============================================\n");

    printf(
        "Battleship Name : %s\n",
        ship->name
    );

    printf(
        "Notation        : %c\n",
        ship->type
    );

    printf(
        "Gun             : %s\n",
        getBattleshipGun(ship->type)
    );

    printf(
        "Velocity Range  : %.2f - %.2f\n",
        ship->vMin,
        ship->vMax
    );

    printf(
        "Angle Range     : %.2f - %.2f degrees\n",
        ship->angleMin,
        ship->angleMax
    );

    printf(
        "Impact Power    : %.2f\n",
        ship->impactPower
    );

    printf(
        "Gamma           : %.2f\n",
        ship->gamma
    );

    printf("============================================\n");
}


/* =========================================================
   SELECT ESCORT TYPE
   ========================================================= */

void selectEscortType(Ship *ship)
{
    if (ship == NULL)
        return;

    ship->category = SHIP_ESCORT;

    ship->type = 'E';

    strcpy(
        ship->name,
        "Escort"
    );

    ship->vMin = 20.0;
    ship->vMax = 80.0;

    ship->angleMin = 10.0;
    ship->angleMax = 70.0;

    ship->impactPower = 75.0;

    ship->gamma = 1.00;

    ship->damage = 0.0;

    ship->alive = 1;
}


int isShipAlive(const Ship *ship)
{
    if (ship == NULL)
        return 0;

    return ship->alive != 0;
}


double calculateDistance(
    const Position *a,
    const Position *b
)
{
    double dx;
    double dy;

    if (a == NULL || b == NULL)
        return 0.0;

    dx = b->x - a->x;
    dy = b->y - a->y;

    return sqrt(
        dx * dx + dy * dy
    );
}


/* =========================================================
   Projectile Functions
   ========================================================= */

double degreesToRadians(double degrees)
{
    return degrees * PI / 180.0;
}


double calculateFlightTime(
    double distance,
    double velocity,
    double angle
)
{
    double radians;
    double verticalVelocity;

    if (distance < 0.0)
        return -1.0;

    if (velocity <= 0.0)
        return -1.0;

    if (angle <= 0.0 || angle >= 90.0)
        return -1.0;

    radians = degreesToRadians(angle);

    verticalVelocity =
        velocity * sin(radians);

    if (verticalVelocity <= 0.0)
        return -1.0;

    return (
        2.0 *
        verticalVelocity /
        GRAVITY
    );
}


double calculateProjectileRange(
    double velocity,
    double angle
)
{
    double radians;

    if (velocity <= 0.0)
        return 0.0;

    if (angle <= 0.0 || angle >= 90.0)
        return 0.0;

    radians = degreesToRadians(angle);

    return (
        velocity * velocity *
        sin(2.0 * radians) /
        GRAVITY
    );
}


double calculateHorizontalVelocity(
    double velocity,
    double angle
)
{
    double radians;

    if (velocity <= 0.0)
        return 0.0;

    radians = degreesToRadians(angle);

    return (
        velocity *
        cos(radians)
    );
}


double calculateVerticalVelocity(
    double velocity,
    double angle
)
{
    double radians;

    if (velocity <= 0.0)
        return 0.0;

    radians = degreesToRadians(angle);

    return (
        velocity *
        sin(radians)
    );
}


int canProjectileReachTarget(
    double distance,
    double velocity,
    double angle
)
{
    double range;

    if (distance < 0.0)
        return 0;

    range =
        calculateProjectileRange(
            velocity,
            angle
        );

    return (
        range + 0.000001 >= distance
    );
}


/* =========================================================
   Attack Functions
   ========================================================= */

int canAttack(
    const Ship *attacker,
    const Ship *target
)
{
    double distance;
    double maximumRange;

    if (attacker == NULL ||
        target == NULL)
    {
        return 0;
    }

    if (!attacker->alive ||
        !target->alive)
    {
        return 0;
    }

    if (attacker == target)
        return 0;

    distance =
        calculateDistance(
            &attacker->position,
            &target->position
        );

    maximumRange =
        calculateProjectileRange(
            attacker->vMax,
            45.0
        );

    return (
        distance <= maximumRange
    );
}


double calculateImpactPower(
    const Ship *attacker,
    const Ship *target
)
{
    double distance;
    double velocity;
    double angle;
    double range;
    double rangeFactor;
    double power;
    double maximumPower;

    if (attacker == NULL ||
        target == NULL)
    {
        return 0.0;
    }

    if (!attacker->alive ||
        !target->alive)
    {
        return 0.0;
    }

    distance =
        calculateDistance(
            &attacker->position,
            &target->position
        );

    velocity =
        (
            attacker->vMin +
            attacker->vMax
        ) / 2.0;

    angle = 45.0;

    if (angle < attacker->angleMin)
        angle = attacker->angleMin;

    if (angle > attacker->angleMax)
        angle = attacker->angleMax;

    if (!canProjectileReachTarget(
        distance,
        velocity,
        angle
    ))
    {
        velocity = attacker->vMax;
    }

    if (!canProjectileReachTarget(
        distance,
        velocity,
        angle
    ))
    {
        return 0.0;
    }

    range =
        calculateProjectileRange(
            velocity,
            angle
        );

    if (range <= 0.0)
        return 0.0;

    rangeFactor =
        1.0 -
        fabs(range - distance) /
        range;

    rangeFactor =
        clampDouble(
            rangeFactor,
            0.0,
            1.0
        );

    power =
        attacker->impactPower *
        attacker->gamma *
        (
            0.50 +
            0.50 * rangeFactor
        );

    maximumPower =
        attacker->impactPower *
        attacker->gamma;

    power =
        clampDouble(
            power,
            0.0,
            maximumPower
        );

    return power;
}


AttackResult performAttack(
    const Ship *attacker,
    const Ship *target
)
{
    AttackResult result;

    double distance;
    double angle;
    double velocity;
    double range;


    result.attackerIndex = -1;
    result.targetIndex = -1;

    result.distance = 0.0;

    result.velocity = 0.0;
    result.angle = 0.0;

    result.impactPower = 0.0;

    result.hit = 0;


    if (attacker == NULL ||
        target == NULL)
    {
        return result;
    }

    if (!attacker->alive ||
        !target->alive)
    {
        return result;
    }

    distance =
        calculateDistance(
            &attacker->position,
            &target->position
        );

    result.distance = distance;


    if (!canAttack(
        attacker,
        target
    ))
    {
        return result;
    }


    velocity = attacker->vMax;
    angle = 45.0;


    if (angle < attacker->angleMin)
        angle = attacker->angleMin;

    if (angle > attacker->angleMax)
        angle = attacker->angleMax;


    if (!canProjectileReachTarget(
        distance,
        velocity,
        angle
    ))
    {
        double a;

        for (
            a = attacker->angleMin;
            a <= attacker->angleMax;
            a += 1.0
        )
        {
            if (canProjectileReachTarget(
                distance,
                velocity,
                a
            ))
            {
                angle = a;
                break;
            }
        }
    }


    range =
        calculateProjectileRange(
            velocity,
            angle
        );


    if (range < distance)
        return result;


    result.velocity = velocity;
    result.angle = angle;


    result.impactPower =
        calculateImpactPower(
            attacker,
            target
        );


    if (result.impactPower <= 0.0)
        return result;


    {
        double accuracy;
        double randomValue;

        accuracy =
            1.0 -
            fabs(range - distance) /
            (range + 0.000001);

        accuracy =
            clampDouble(
                accuracy,
                0.0,
                1.0
            );

        accuracy =
            0.50 +
            0.50 * accuracy;

        randomValue =
            (double)rand() /
            (double)RAND_MAX;

        if (randomValue <= accuracy)
        {
            result.hit = 1;
        }
    }


    return result;
}


/* =========================================================
   Damage Functions
   ========================================================= */

void applyDamage(
    Ship *target,
    double damage
)
{
    double maxHealth;

    if (target == NULL)
        return;

    if (!target->alive)
        return;

    if (damage <= 0.0)
        return;

    maxHealth =
        getShipHealth(target);

    target->damage += damage;

    if (target->damage >= maxHealth)
    {
        target->damage = maxHealth;
        target->alive = 0;
    }
}


/* =========================================================
   Assignment Parts
   ========================================================= */

void runPart1A(void)
{
    Battlefield battlefield;

    printf("\n");
    printf("============================================\n");
    printf("           PART 1A - BATTLEFIELD\n");
    printf("============================================\n");

    initializeBattlefield(&battlefield);

    setBattlefieldSize(
        &battlefield,
        100.0
    );

    /*
     * Type selection happens here,
     * through createBattleship().
     */
    createBattleship(&battlefield);

    printf(
        "Battlefield size : %.2f x %.2f\n",
        battlefield.size,
        battlefield.size
    );

    printf(
        "Battleship       : %s\n",
        battlefield.battleship.name
    );

    printf(
        "Battleship type  : %c\n",
        battlefield.battleship.type
    );

    printf(
        "Battleship gun   : %s\n",
        getBattleshipGun(
            battlefield.battleship.type
        )
    );

    printf(
        "Battleship HP    : %.2f\n",
        getShipHealth(
            &battlefield.battleship
        )
    );

    printf(
        "Status            : %s\n",
        battlefield.battleship.alive
            ? "Alive"
            : "Destroyed"
    );

    printf("============================================\n");
}


void runPart1B(void)
{
    Battlefield battlefield;
    int numberOfShips;

    printf("\n");
    printf("============================================\n");
    printf("           PART 1B - ESCORT SHIPS\n");
    printf("============================================\n");

    initializeBattlefield(&battlefield);

    setBattlefieldSize(
        &battlefield,
        100.0
    );

    createBattleship(&battlefield);

    printf(
        "Enter number of escort ships (1-%d): ",
        MAX_ESCORT_SHIPS
    );

    if (scanf("%d", &numberOfShips) != 1)
    {
        numberOfShips = 5;

        while (getchar() != '\n')
            ;
    }

    if (numberOfShips < 1)
        numberOfShips = 1;

    if (numberOfShips > MAX_ESCORT_SHIPS)
        numberOfShips = MAX_ESCORT_SHIPS;

    createEscortShips(
        &battlefield,
        numberOfShips
    );

    generateShipPositions(
        &battlefield
    );

    displayAllShips(
        &battlefield
    );

    printf("============================================\n");
}


void runPart1C(void)
{
    Battlefield battlefield;

    initializeBattlefield(&battlefield);

    setBattlefieldSize(
        &battlefield,
        100.0
    );

    createBattleship(&battlefield);

    createEscortShips(
        &battlefield,
        5
    );

    generateShipPositions(
        &battlefield
    );

    printf("\n");
    printf("============================================\n");
    printf("           PART 1C - POSITIONS\n");
    printf("============================================\n");

    displayBattlefield(
        &battlefield
    );

    displayAllShips(
        &battlefield
    );

    printf("============================================\n");
}


void runPart2A(void)
{
    Battlefield battlefield;

    initializeBattlefield(&battlefield);

    setBattlefieldSize(
        &battlefield,
        100.0
    );

    createBattleship(&battlefield);

    createEscortShips(
        &battlefield,
        5
    );

    generateShipPositions(
        &battlefield
    );

    printf("\n");
    printf("============================================\n");
    printf("           PART 2A - PROJECTILE\n");
    printf("============================================\n");


    if (battlefield.escortCount > 0)
    {
        Ship *target =
            &battlefield.escortShips[0];

        double distance;
        double velocity;
        double angle;
        double range;
        double time;


        distance =
            calculateDistance(
                &battlefield.battleship.position,
                &target->position
            );

        velocity =
            battlefield.battleship.vMax;

        angle = 45.0;


        if (angle <
            battlefield.battleship.angleMin)
        {
            angle =
                battlefield.battleship.angleMin;
        }

        if (angle >
            battlefield.battleship.angleMax)
        {
            angle =
                battlefield.battleship.angleMax;
        }


        range =
            calculateProjectileRange(
                velocity,
                angle
            );

        time =
            calculateFlightTime(
                distance,
                velocity,
                angle
            );


        printf(
            "Target distance       : %.2f\n",
            distance
        );

        printf(
            "Projectile velocity   : %.2f\n",
            velocity
        );

        printf(
            "Projectile angle      : %.2f degrees\n",
            angle
        );

        printf(
            "Projectile range      : %.2f\n",
            range
        );

        printf(
            "Flight time           : %.2f seconds\n",
            time
        );

        printf(
            "Can reach target      : %s\n",
            canProjectileReachTarget(
                distance,
                velocity,
                angle
            )
                ? "YES"
                : "NO"
        );
    }


    printf("============================================\n");
}


void runPart2B(void)
{
    Battlefield battlefield;
    AttackResult result;


    initializeBattlefield(&battlefield);

    setBattlefieldSize(
        &battlefield,
        100.0
    );

    createBattleship(&battlefield);

    createEscortShips(
        &battlefield,
        5
    );

    generateShipPositions(
        &battlefield
    );


    printf("\n");
    printf("============================================\n");
    printf("           PART 2B - ATTACK\n");
    printf("============================================\n");


    if (battlefield.escortCount > 0)
    {
        Ship *target =
            &battlefield.escortShips[0];


        result =
            performAttack(
                &battlefield.battleship,
                target
            );


        printf(
            "Attacker       : %s\n",
            battlefield.battleship.name
        );

        printf(
            "Gun            : %s\n",
            getBattleshipGun(
                battlefield.battleship.type
            )
        );

        printf(
            "Target         : %s\n",
            target->name
        );

        printf(
            "Distance       : %.2f\n",
            result.distance
        );

        printf(
            "Velocity       : %.2f\n",
            result.velocity
        );

        printf(
            "Angle          : %.2f degrees\n",
            result.angle
        );

        printf(
            "Impact power   : %.2f\n",
            result.impactPower
        );

        printf(
            "Result         : %s\n",
            result.hit
                ? "HIT"
                : "MISS"
        );


        if (result.hit)
        {
            applyDamage(
                target,
                result.impactPower
            );

            printf(
                "Target damage  : %.2f\n",
                target->damage
            );

            printf(
                "Target health  : %.2f / %.2f\n",
                getRemainingHealth(target),
                getShipHealth(target)
            );

            printf(
                "Target status  : %s\n",
                target->alive
                    ? "Alive"
                    : "Destroyed"
            );
        }
    }


    printf("============================================\n");
}


void runPart2C(void)
{
    Battlefield battlefield;


    initializeBattlefield(&battlefield);

    setBattlefieldSize(
        &battlefield,
        100.0
    );

    createBattleship(&battlefield);

    createEscortShips(
        &battlefield,
        5
    );

    generateShipPositions(
        &battlefield
    );


    printf("\n");
    printf("============================================\n");
    printf("           PART 2C - SIMULATION\n");
    printf("============================================\n");


    runSimulation(
        &battlefield
    );


    {
        SimulationStatistics statistics;

        statistics =
            calculateStatistics(
                &battlefield
            );

        displayStatistics(
            &statistics
        );
    }


    printf("============================================\n");
}


/* =========================================================
   Simulation
   ========================================================= */

void runSimulation(Battlefield *battlefield)
{
    int round;
    int i;


    if (battlefield == NULL)
        return;


    g_totalAttacks = 0;
    g_successfulHits = 0;


    for (round = 1; round <= 20; round++)
    {
        int aliveEscorts = 0;


        printf(
            "\n--- Simulation Round %d ---\n",
            round
        );


        /* =========================================
           Battleship attacks Escort Ships
           ========================================= */

        if (battlefield->battleship.alive)
        {
            for (
                i = 0;
                i < battlefield->escortCount;
                i++
            )
            {
                AttackResult result;

                Ship *target =
                    &battlefield->escortShips[i];


                if (!target->alive)
                    continue;


                result =
                    performAttack(
                        &battlefield->battleship,
                        target
                    );


                if (result.velocity > 0.0)
                    g_totalAttacks++;


                if (result.hit)
                {
                    g_successfulHits++;


                    applyDamage(
                        target,
                        result.impactPower
                    );


                    printf(
                        "Battleship [%c] -> %s : HIT "
                        "(Damage %.2f | "
                        "Total Damage %.2f | "
                        "Health %.2f/%.2f)\n",

                        battlefield->battleship.type,

                        target->name,

                        result.impactPower,

                        target->damage,

                        getRemainingHealth(target),

                        getShipHealth(target)
                    );


                    if (!target->alive)
                    {
                        printf(
                            "%s has been destroyed.\n",
                            target->name
                        );
                    }
                }
                else
                {
                    printf(
                        "Battleship [%c] -> %s : MISS\n",

                        battlefield->battleship.type,

                        target->name
                    );
                }
            }
        }


        /* =========================================
           Escort Ships attack Battleship
           ========================================= */

        for (
            i = 0;
            i < battlefield->escortCount;
            i++
        )
        {
            AttackResult result;

            Ship *attacker =
                &battlefield->escortShips[i];


            if (!attacker->alive)
                continue;


            if (!battlefield->battleship.alive)
                break;


            result =
                performAttack(
                    attacker,
                    &battlefield->battleship
                );


            if (result.velocity > 0.0)
                g_totalAttacks++;


            if (result.hit)
            {
                g_successfulHits++;


                applyDamage(
                    &battlefield->battleship,
                    result.impactPower
                );


                printf(
                    "%s -> Battleship [%c] : HIT "
                    "(Damage %.2f | "
                    "Total Damage %.2f | "
                    "Health %.2f/%.2f)\n",

                    attacker->name,

                    battlefield->battleship.type,

                    result.impactPower,

                    battlefield->battleship.damage,

                    getRemainingHealth(
                        &battlefield->battleship
                    ),

                    getShipHealth(
                        &battlefield->battleship
                    )
                );


                if (!battlefield->battleship.alive)
                {
                    printf(
                        "Battleship has been destroyed.\n"
                    );

                    break;
                }
            }
            else
            {
                printf(
                    "%s -> Battleship [%c] : MISS\n",

                    attacker->name,

                    battlefield->battleship.type
                );
            }
        }


        /* =========================================
           Count Alive Escorts
           ========================================= */

        aliveEscorts = 0;


        for (
            i = 0;
            i < battlefield->escortCount;
            i++
        )
        {
            if (battlefield->escortShips[i].alive)
                aliveEscorts++;
        }


        /* =========================================
           Round Status
           ========================================= */

        printf(
            "\nRound %d Status:\n",
            round
        );


        printf(
            "Battleship [%c] %s\n",

            battlefield->battleship.type,

            battlefield->battleship.name
        );


        printf(
            "Battleship Health : %.2f / %.2f\n",

            getRemainingHealth(
                &battlefield->battleship
            ),

            getShipHealth(
                &battlefield->battleship
            )
        );


        printf(
            "Alive Escort Ships: %d / %d\n",
            aliveEscorts,
            battlefield->escortCount
        );


        /* =========================================
           End Conditions
           ========================================= */

        if (!battlefield->battleship.alive)
        {
            printf(
                "\nSimulation finished: "
                "Battleship destroyed.\n"
            );

            break;
        }


        if (aliveEscorts == 0)
        {
            printf(
                "\nSimulation finished: "
                "All escort ships destroyed.\n"
            );

            break;
        }


        if (round == 20)
        {
            printf(
                "\nSimulation finished: "
                "Maximum 20 rounds reached.\n"
            );
        }
    }
}


/* =========================================================
   Reset Simulation
   ========================================================= */

void resetSimulation(Battlefield *battlefield)
{
    int i;


    if (battlefield == NULL)
        return;


    battlefield->battleship.damage = 0.0;
    battlefield->battleship.alive = 1;


    for (
        i = 0;
        i < battlefield->escortCount;
        i++
    )
    {
        battlefield->escortShips[i].damage = 0.0;
        battlefield->escortShips[i].alive = 1;
    }


    g_totalAttacks = 0;
    g_successfulHits = 0;


    generateShipPositions(
        battlefield
    );
}


/* =========================================================
   Calculate Statistics
   ========================================================= */

SimulationStatistics calculateStatistics(
    const Battlefield *battlefield
)
{
    SimulationStatistics statistics;

    int i;


    statistics.totalAttacks =
        g_totalAttacks;

    statistics.successfulHits =
        g_successfulHits;

    statistics.destroyedShips =
        0;

    statistics.battleshipDamage =
        0.0;

    statistics.totalDamage =
        0.0;


    if (battlefield == NULL)
        return statistics;


    statistics.battleshipDamage =
        battlefield->battleship.damage;


    statistics.totalDamage +=
        battlefield->battleship.damage;


    if (!battlefield->battleship.alive)
        statistics.destroyedShips++;


    for (
        i = 0;
        i < battlefield->escortCount;
        i++
    )
    {
        const Ship *ship =
            &battlefield->escortShips[i];


        statistics.totalDamage +=
            ship->damage;


        if (!ship->alive)
            statistics.destroyedShips++;
    }


    return statistics;
}


/* =========================================================
   Display Battlefield
   ========================================================= */

void displayBattlefield(
    const Battlefield *battlefield
)
{
    if (battlefield == NULL)
        return;


    printf("\n");
    printf("============================================\n");
    printf("             BATTLEFIELD\n");
    printf("============================================\n");


    printf(
        "Size              : %.2f x %.2f\n",
        battlefield->size,
        battlefield->size
    );


    printf(
        "Battleship        : %s\n",
        battlefield->battleship.name
    );


    printf(
        "Notation          : %c\n",
        battlefield->battleship.type
    );


    printf(
        "Gun               : %s\n",
        getBattleshipGun(
            battlefield->battleship.type
        )
    );


    printf(
        "Battleship X      : %.2f\n",
        battlefield->battleshipPosition.x
    );


    printf(
        "Battleship Y      : %.2f\n",
        battlefield->battleshipPosition.y
    );


    printf(
        "Battleship Health : %.2f / %.2f\n",

        getRemainingHealth(
            &battlefield->battleship
        ),

        getShipHealth(
            &battlefield->battleship
        )
    );


    printf(
        "Escort Ship Count : %d\n",
        battlefield->escortCount
    );


    printf("============================================\n");
}


/* =========================================================
   Display Single Ship
   ========================================================= */

void displayShip(const Ship *ship)
{
    double maxHealth;
    double remainingHealth;


    if (ship == NULL)
        return;


    maxHealth =
        getShipHealth(ship);


    remainingHealth =
        getRemainingHealth(ship);


    printf("\n");
    printf("--------------------------------------------\n");


    printf(
        "Name          : %s\n",
        ship->name
    );


    printf(
        "Type          : %c\n",
        ship->type
    );


    printf(
        "Category      : %s\n",

        ship->category == SHIP_BATTLESHIP
            ? "Battleship"
            : "Escort"
    );


    if (ship->category == SHIP_BATTLESHIP)
    {
        printf(
            "Notation      : %c\n",
            ship->type
        );

        printf(
            "Gun           : %s\n",
            getBattleshipGun(ship->type)
        );
    }


    printf(
        "Position      : (%.2f, %.2f)\n",
        ship->position.x,
        ship->position.y
    );


    printf(
        "Velocity Min  : %.2f\n",
        ship->vMin
    );


    printf(
        "Velocity Max  : %.2f\n",
        ship->vMax
    );


    printf(
        "Angle Min     : %.2f\n",
        ship->angleMin
    );


    printf(
        "Angle Max     : %.2f\n",
        ship->angleMax
    );


    printf(
        "Impact Power  : %.2f\n",
        ship->impactPower
    );


    printf(
        "Gamma         : %.2f\n",
        ship->gamma
    );


    printf(
        "Max Health    : %.2f\n",
        maxHealth
    );


    printf(
        "Health        : %.2f / %.2f\n",
        remainingHealth,
        maxHealth
    );


    printf(
        "Damage        : %.2f\n",
        ship->damage
    );


    printf(
        "Status        : %s\n",
        ship->alive
            ? "Alive"
            : "Destroyed"
    );


    printf("--------------------------------------------\n");
}


/* =========================================================
   Display All Ships
   ========================================================= */

void displayAllShips(
    const Battlefield *battlefield
)
{
    int i;


    if (battlefield == NULL)
        return;


    printf("\n");
    printf("============================================\n");
    printf("                 ALL SHIPS\n");
    printf("============================================\n");


    printf("\n[BATTLESHIP]\n");


    displayShip(
        &battlefield->battleship
    );


    printf("\n[ESCORT SHIPS]\n");


    for (
        i = 0;
        i < battlefield->escortCount;
        i++
    )
    {
        displayShip(
            &battlefield->escortShips[i]
        );
    }
}


/* =========================================================
   Display Statistics
   ========================================================= */

void displayStatistics(
    const SimulationStatistics *statistics
)
{
    double accuracy;


    if (statistics == NULL)
        return;


    if (statistics->totalAttacks > 0)
    {
        accuracy =
            (
                (double)statistics->successfulHits /
                (double)statistics->totalAttacks
            ) * 100.0;
    }
    else
    {
        accuracy = 0.0;
    }


    printf("\n");
    printf("============================================\n");
    printf("          SIMULATION STATISTICS\n");
    printf("============================================\n");


    printf(
        "Total Attacks       : %d\n",
        statistics->totalAttacks
    );


    printf(
        "Successful Hits     : %d\n",
        statistics->successfulHits
    );


    printf(
        "Destroyed Ships     : %d\n",
        statistics->destroyedShips
    );


    printf(
        "Battleship Damage   : %.2f\n",
        statistics->battleshipDamage
    );


    printf(
        "Total Damage        : %.2f\n",
        statistics->totalDamage
    );


    printf(
        "Hit Accuracy        : %.2f%%\n",
        accuracy
    );


    printf("============================================\n");
}
