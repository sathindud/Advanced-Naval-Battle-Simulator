#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<stdbool.h>

#include "../header_files/structure.h"
#include "../header_files/random.h"
#include "../header_files/loadInitial.h"
#include "../header_files/saveSimulation.h"

#define BMAX_ANGLE 45

/**
 * Find the range according to the velocity
*/
float range(int angle, float velocity)
{
	return (velocity * velocity) * sin(2* angle * 3.14 / 180) / GRAVITY;
}

float getDistance(Coordinates attacker, Coordinates victim)
{
    int x = abs(attacker.x - victim.x);
	int y = abs(attacker.y - victim.y);
	return sqrt((x*x) + (y*y));
}

/**
 * Checking the 
*/
bool check(float distance, float min_range, float max_range)
{
	
	// printf("Distance between b and e %f\n", distance);

	if (distance >= min_range && distance <= max_range )
	{
		return true;
	}else
	{
		return false;
	}

}
/**
 * Check the Maximum and Minimum Range Angle
*/
void findMaxMinAngle(float * minA, float * maxA)
{
    if (* maxA <= 45){}
    else {
        if (* minA < 45)
        {
            if ((* maxA - 45) < (45 - * minA))
            {
                * minA = *maxA;
            }
            * maxA = 45.0;
        }else{
            float temp = * maxA;
            * maxA = * minA;
            * minA = temp;
        }
    }

}

bool escortSimulation(int escort_count, InitialConditionsEscort * escort , Coordinates battalian)
{

    BattalianShipLog Blog;

    Blog.position.x = battalian.x;
    Blog.position.y = battalian.y;


    for (int i = 0; i < escort_count; i++)
    {
        // printf("------------------------------\n");

        // printf("Escort Ship index %d\n", escort[i].index);
        float exact_velocity = floatRandomNumber(escort[i].minV, escort[i].maxV);
        // printf("Velocity of the shell %f \n", exact_velocity);

        //Rearranging the angles
        findMaxMinAngle(&escort[i].minA, &escort[i].maxA);
        // printf("Max Angle %f \n", escort[i].maxA);
        // printf("Min Angle %f \n", escort[i].minA);


        float ship_max_range = range(escort[i].maxA, exact_velocity);
        // printf("Max Attacking Range %f \n", ship_max_range);

        float ship_min_range = range(escort[i].minA,  exact_velocity); 

        // printf("Min Attacking Range %f \n", ship_min_range);

        float distance = getDistance(escort[i].position, battalian);
     
        if (check(distance, ship_min_range, ship_max_range))
        {
            printf("BattalianShip Sinked :( \n");
            Blog.escort_index = i;

            printf("Attacked Escort Ship index: %d\n", i);
            Blog.battaleship_status = 0;
            saveBattalianLog(Blog);

            return true;

        }else{
            // printf("BattalianShip is not going to sink\n");
        }
    }
    printf("BattalianShip Suvived :) \n");
    Blog.battaleship_status = 1;
    return false;
}


float calculateTime(float velocity, float distance)
{
    return distance / cos(velocity * 3.14 / 180) ;
}

void battalianSimulation(InitialConditionsBattalian battalian, int escort_count, InitialConditionsEscort escort[escort_count])
{
    EscortShipsLog Elog;
    float ship_max_range = range(BMAX_ANGLE, battalian.maxV);
    // printf("Battalian Ship Range: %f", battalian.maxV);

    int attacked_count = 0;
    float total_time = 0;


    for (int i = 0; i < escort_count; i++)
    {
        float distance = getDistance(battalian.position, escort[i].position);

        if(check(distance, 0, ship_max_range))
        {
            // printf("Escort Ship %d is attacked by the battalian\n", escort[i].index);
            float time = calculateTime(battalian.maxV, distance);
            total_time += time;
            attacked_count ++;

            Elog.index = escort[i].index;
            Elog.time = time;
            saveEscortLog(Elog);
        }
    }
    printf("Attacked Escort Ships Count: %d \n ", attacked_count);
    printf("Total time it takes: %fs \n ", total_time);
    
}

/**
 * Simulation 01
*/

void simulation1()
{
    //Resetiing the log files before running the simulation
    resetBattalianLog();
    resetEscortLog();

    //Loading the escort ships and battaleships 
    int escort_ship_count;
    InitialConditionsEscort * escort_ships = loadEscortShip( & escort_ship_count);
    InitialConditionsBattalian battalian = loadBattalianShip();

    //Running the simulation
    if (!escortSimulation(escort_ship_count, escort_ships, battalian.position))
    {
        battalianSimulation(battalian, escort_ship_count, escort_ships);
    }

    free(escort_ships);
}

void removeRow(int * escort_count, InitialConditionsEscort * escort, int index)
{
    for(int i = index; i < *escort_count -1; i++)
    {
        escort[i] = escort[i+1];
    }
    * escort_count -= 1;
}

void removeAttackedEscots(int * escort_count, InitialConditionsEscort * escorts)
{
    //need to change the size
    // InitialConditionsEscort * new_escorts = (InitialConditionsEscort *)calloc (10, sizeof(InitialConditionsEscort));

    int attack_count = 0;

    int * attacked_escorts = loadAttackedEscorts(&attack_count);
    if(attacked_escorts != NULL)
    {
        int x = 0;
        for(int i = 0; i < *escort_count; i++)
        {
            for(int j = 0; j < attack_count; j++)
            {
                if (escorts[i].index == attacked_escorts[j])
                {
                    removeRow(escort_count, escorts, i);
                }
            }
        }
    }

}


Coordinates movePosition(Coordinates current, Coordinates destination)
{

        if (current.y > destination.y)
        {
            current.y --;
        }else{
            current.y ++;
        }

        if (current.x > destination.x)
        {
                current.x --;
        }else{
                current.x ++;
        }

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

    printf("Escort count: %d", escort_ship_count);

    Coordinates canvas_size = loadCanvasSize();
    Coordinates current = battalian.position;
    
    Coordinates destination;
    destination.x = intRandomNumber(0, canvas_size.x);
    destination.y = intRandomNumber(0, canvas_size.y);

    printf("random position %d %d\n", destination.x, destination.y);
    printf("current position %d %d\n", current.x, current.y);

    //  Running the simulation
    if (!escortSimulation(escort_ship_count, escort_ships, battalian.position))
    {
        battalianSimulation(battalian, escort_ship_count, escort_ships);
        while (current.x != destination.x || current.y != destination.y)
        {
            if (current.y > destination.y)
            {
                current.y --;
            }
            else if(current.y < destination.y)
            {
                current.y ++;
            }

            if (current.x > destination.x)
            {
                    current.x --;
            }
            else if(current.x < destination.x)
            {
                    current.x ++;
            }
            printf("current position %d %d\n", current.x, current.y);
            //  Running the simulation
            removeAttackedEscots(&escort_ship_count, escort_ships);
            printf("Escort count: %d\n", escort_ship_count);
            if (!escortSimulation(escort_ship_count, escort_ships, battalian.position))
            {
                battalianSimulation(battalian, escort_ship_count, escort_ships);
            }else{
                break;
            }
        }
    }
    free(escort_ships);
    
}

// int main()
// {
//     int escort_ship_count;

//     InitialConditionsEscort * escort_ships = loadEscortShip( & escort_ship_count);
//     InitialConditionsBattalian battalian = loadBattalianShip();

//     for (int i = 0; i < escort_ship_count; i++)
//     {
//         printf("%d\n", escort_ships[i].index);
//     }
//     printf("Escort count: %d", escort_ship_count);
//     removeAttackedEscots(&escort_ship_count, escort_ships);
//     printf("--");

//     for (int i = 0; i < escort_ship_count; i++)
//     {
//         printf("%d\n", escort_ships[i].index);
//     }
//     printf("Escort count: %d", escort_ship_count);
    

// }
