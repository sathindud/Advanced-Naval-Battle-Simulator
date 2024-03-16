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

bool escortSimulation(int escort_count, InitialConditionsEscort escort[escort_count], Coordinates battalian, BattalianShipLog * Blog)
{
    Blog->position.x = battalian.x;
    Blog->position.y = battalian.y;

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
            printf("Battalian Ship is going to sink\n");
            Blog->escort_index = i;

            printf("Attacked Escort Ship index: %d\n", i);
            Blog->battaleship_status = 0;

            return true;

        }else{
            // printf("BattalianShip is not going to sink\n");
        }
    }
    printf("BattalianShip is not hit by the Escort ship\n");
    Blog->battaleship_status = 1;
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


void simulation1()
{
    resetBattalianLog();
    resetEscortLog();

    int escort_ship_count;
    InitialConditionsEscort * escort_ships = loadEscortShip( & escort_ship_count);
    InitialConditionsBattalian battalian = loadBattalianShip();

    BattalianShipLog Blog;

    // EscortShipsLog * Elog = (EscortShipsLog *)calloc(escort_ship_count, sizeof(EscortShipsLog) )

    if (!escortSimulation(escort_ship_count, escort_ships, battalian.position, &Blog))
    {
        battalianSimulation(battalian, escort_ship_count, escort_ships);
    }else{
        saveBattalianLog(Blog);
    }


    free(escort_ships);
}


void simulation2()
{
    resetBattalianLog();
    resetEscortLog();

    Coordinates canvas_size = loadCanvasSize();
    InitialConditionsBattalian battalian = loadBattalianShip();
    Coordinates current_position = battalian.position;
    
    Coordinates position;
    position.x = intRandomNumber(0, canvas_size.x);
    position.y = intRandomNumber(0, canvas_size.y);

    printf("random position %d %d", position.x, position.y);
    printf("current position %d %d\n", current_position.x, current_position.y);

    while (current_position.x != position.x)
    {
        while(current_position.y != position.y)
        {
            printf("current position %d %d\n", current_position.x, current_position.y);

            if (current_position.y > position.y)
            {
                current_position.y --;
            }else{
                current_position.y ++;
            }
        }

        if (current_position.x > position.x)
        {
                current_position.x --;
        }else{
                current_position.x ++;
        }
        printf("current position %d %d\n", current_position.x, current_position.y);

    }
    
}
