#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<stdbool.h>

#include "../header_files/structure.h"
#include "../header_files/random.h"
#include "../header_files/loadInitial.h"
#include "../header_files/saveSimulation.h"
#include "../header_files/simulationStat.h"
#include "../header_files/simulationHelper.h"


/**
 * Simulation 01
*/
void simulation1()
{
    //Loading the escort ships and battaleships 
    int escort_ship_count;
    InitialConditionsEscort * escort_ships = loadEscortShip( & escort_ship_count);
    InitialConditionsBattalian battalian = loadBattalianShip();

    resetLog(battalian);

    float health = 0;

    //Running the simulation
    printf("Simulation is in Progress ...\n ");
    if (!escortSimulation(escort_ship_count, escort_ships, battalian.position, &health))
    {
        battalianSimulation(battalian, escort_ship_count, escort_ships);
    }

    free(escort_ships);
    simulationStat();

}


/**
 * Simulation 2
*/

void simulation2()
{
   resetBattalianLog();
    resetEscortLog();

    int escort_ship_count;
    InitialConditionsEscort * escort_ships = loadEscortShip( & escort_ship_count);
    InitialConditionsBattalian battalian = loadBattalianShip();

    resetLog(battalian);


    float health = 0;

    // printf("Escort count: %d\n", escort_ship_count);

    Coordinates canvas_size = loadUserInput().canvas_size;
    
    Coordinates destination;
    destination.x = intRandomNumber(0, canvas_size.x);
    destination.y = intRandomNumber(0, canvas_size.y);

    // printf("random position %d %d\n", destination.x, destination.y);
    // printf("current position %d %d\n", current.x, current.y);

    //  Running the simulation
    printf("Simulation is in Progress ...\n ");

    if (!escortSimulation(escort_ship_count, escort_ships, battalian.position, &health))
    {
        battalianSimulation(battalian, escort_ship_count, escort_ships);
        while (battalian.position.x != destination.x || battalian.position.y != destination.y)
        {
            //Changing the Position            
            battalian.position = changeCoordinate(battalian.position, destination);

            //  Running the simulation
            removeAttackedEscots(&escort_ship_count, escort_ships);
            // printf("Escort count: %d\n", escort_ship_count);
            if (!escortSimulation(escort_ship_count, escort_ships, battalian.position, &health))
            {
                battalianSimulation(battalian, escort_ship_count, escort_ships);
            }else{
                break;
            }
        }
    }
    free(escort_ships);
    simulationStat();

    
}

/**
 * Simulation 3
*/
void simulation3()
{
    resetBattalianLog();
    resetEscortLog();

    int escort_ship_count;
    InitialConditionsEscort * escort_ships = loadEscortShip( & escort_ship_count);
    InitialConditionsBattalian battalian = loadBattalianShip();

    resetLog(battalian);


    float health = 0;

    // printf("Escort count: %d\n", escort_ship_count);

    Coordinates canvas_size = loadUserInput().canvas_size;
    
    Coordinates destination;
    destination.x = intRandomNumber(0, canvas_size.x);
    destination.y = intRandomNumber(0, canvas_size.y);

    // printf("random position %d %d\n", destination.x, destination.y);
    // printf("current position %d %d\n", current.x, current.y);

    //Get a random k value 
    int k = intRandomNumber(0, findItterationCount(battalian.position, destination));

    //  Running the simulation
    printf("Simulation is in Progress ...\n ");

    if (!escortSimulation(escort_ship_count, escort_ships, battalian.position, &health))
    {
        battalianSimulation(battalian, escort_ship_count, escort_ships);
        while (battalian.position.x != destination.x || battalian.position.y != destination.y)
        {
            //changing the position
            battalian.position = changeCoordinate(battalian.position, destination);

            //Find the kth itteration
            k -- ;
            if(k < 0)
            {
                battalian.max_angle = 30;

            }

            //  Running the simulation
            removeAttackedEscots(&escort_ship_count, escort_ships);
            // printf("Escort count: %d\n", escort_ship_count);
            if (!escortSimulation(escort_ship_count, escort_ships, battalian.position, &health))
            {
                battalianSimulation(battalian, escort_ship_count, escort_ships);
            }else{
                break;
            }
        }
    }
    free(escort_ships);
    simulationStat();

    
}
/**
 * Simulation 04
*/

void simulation4()
{
    resetBattalianLog();
    resetEscortLog();

    int escort_ship_count;
    InitialConditionsEscort * escort_ships = loadEscortShip( & escort_ship_count);
    InitialConditionsBattalian battalian = loadBattalianShip();

    resetLog(battalian);


    // printf("Escort count: %d", escort_ship_count);

    Coordinates canvas_size = loadUserInput().canvas_size;
    
    Coordinates destination;
    destination.x = intRandomNumber(0, canvas_size.x);
    destination.y = intRandomNumber(0, canvas_size.y);

    // printf("random position %d %d\n", destination.x, destination.y);
    // printf("current position %d %d\n", current.x, current.y);

    //Cumulative Impact
    float health = HEALTH;

    //  Running the simulation
    printf("Simulation is in Progress ... \n");

    if (!escortSimulation(escort_ship_count, escort_ships, battalian.position, &health))
    {
        battalianSimulation(battalian, escort_ship_count, escort_ships);
        while (battalian.position.x != destination.x || battalian.position.y != destination.y)
        {
            //Change Position
            battalian.position = changeCoordinate(battalian.position, destination);

            //  Running the simulation
            removeAttackedEscots(&escort_ship_count, escort_ships);
            // printf("Escort count: %d\n", escort_ship_count);
            if (!escortSimulation(escort_ship_count, escort_ships, battalian.position, &health))
            {
                battalianSimulation(battalian, escort_ship_count, escort_ships);
            }else{
                break;
            }
        }
    }else{

    }
    free(escort_ships);
    simulationStat();
}

// int main()
// {
//     int escort_ship_count;

//     InitialConditionsEscort * escort_ships = loadEscortShip( & escort_ship_count);
//     // InitialConditionsBattalian battalian = loadBattalianShip();

//     for (int i = 0; i < escort_ship_count; i++)
//     {
//         printf("%d\n", escort_ships[i].index);
//     }
//     printf("Escort count: %d", escort_ship_count);
//     removeAttackedEscots(&escort_ship_count, escort_ships);
//     printf("--\n");

//     for (int i = 0; i < escort_ship_count; i++)
//     {
//         printf("%d\n", escort_ships[i].index);
//     }
//     printf("Escort count: %d\n", escort_ship_count);
    

// }
