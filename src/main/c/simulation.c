#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<stdbool.h>

#include "../header_files/structure.h"
#include "../header_files/random.h"
#include "../header_files/loadInitial.h"

#define BMAX_ANGLE 45

/**
 * Find the range according to the velocity
*/
float range(int angle, float velocity)
{
	return (velocity * velocity) * sin(2* angle * 3.14 / 180) / 10;
}

/**
 * Checking the 
*/
bool check(Coordinates attacker, Coordinates victim, float min_range, float max_range)
{
	int x = abs(attacker.x - victim.x);
	int y = abs(attacker.y - victim.y);
	float distance = sqrt((x*x) + (y*y));
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

bool escortSimulation(int escort_count, InitialConditionsEscort escort[escort_count], Coordinates battalian)
{
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
     
        if (check(escort[i].position, battalian, ship_min_range, ship_max_range))
        {
            printf("Battalian Ship is going to sink\n");
            printf("Attacked by the %d escort ship\n", i);
            return true;

        }else{
            // printf("BattalianShip is not going to sink\n");
        }
    }
    printf("BattalianShip is not hit by the Escort ship\n");
    return false;
}

void battalianSimulation(InitialConditionsBattalian battalian, int escort_count, InitialConditionsEscort escort[escort_count])
{
    float ship_max_range = range(BMAX_ANGLE, battalian.maxV);
    // printf("Battalian Ship Range: %f", battalian.maxV);

    int attacked_count = 0;

    for (int i = 0; i < escort_count; i++)
    {
        if(check(battalian.position, escort[i].position, 0, ship_max_range))
        {
            printf("Escort Ship %d is attacked by the battalian\n", escort[i].index);
            attacked_count ++;
        }
    }
    printf("%d Escort Ships are attacked by the Battalian Ship\n ", attacked_count);
    
}

void simulation1()
{
    int escort_ship_count;
    InitialConditionsEscort * escort_ships = loadEscortShip( & escort_ship_count);
    InitialConditionsBattalian battalian = loadBattalianShip();

    if (!escortSimulation(escort_ship_count, escort_ships, battalian.position))
    {
        battalianSimulation(battalian, escort_ship_count, escort_ships);
    }
    free(escort_ships);
}
