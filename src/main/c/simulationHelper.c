#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<stdbool.h>

#include "../header_files/structure.h"
#include "../header_files/random.h"
#include "../header_files/saveSimulation.h"
#include "../header_files/loadInitial.h"

/**
 * Change Position
*/

Coordinates changeCoordinate(Coordinates current, Coordinates destination)
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

    return current;
}

/**
 * Find Position count to the destination
*/

int findItterationCount(Coordinates current, Coordinates destination)
{
    int count = 0;

    while(current.x != destination.x || current.y != destination.y)
    {
        count ++;
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
    }
    return count;

}

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
 * Checking the victim ship is on attackers range
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
            if ((* maxA - 45) <= (45 - * minA))
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
/**
 * Base simulation forEscort ships 
*/

bool escortSimulation(int escort_count, InitialConditionsEscort * escort , Coordinates battalian, float * health)
{

    BattalianShipLog Blog;

    Blog.position.x = battalian.x;
    Blog.position.y = battalian.y;

    Blog.escort_index = -1;


    for (int i = 0; i < escort_count; i++)
    {
        // printf("%d\n", escort[i].index);
        // printf("------------------------------\n");

        // printf("Escort Ship index %d\n", escort[i].index);
        
        //sathindu
        float exact_velocity = floatRandomNumber(escort[i].minV, escort[i].maxV);
        // float exact_velocity = escort[i].maxV;
        // printf("Velocity of the shell %f \n", exact_velocity);

        //Rearranging the angles
        findMaxMinAngle(&escort[i].minA, &escort[i].maxA);
        // printf("Max Angle %f \n", escort[i].maxA);
        // printf("Min Angle %f \n", escort[i].minA);


        float ship_max_range = range(escort[i].maxA, exact_velocity);
        float ship_min_range = range(escort[i].minA,  exact_velocity); 

        float distance = getDistance(escort[i].position, battalian);

        if (check(distance, ship_min_range, ship_max_range))
        {
            // printf("BattalianShip Hitted * \n");
            // printf("Battalianship Health: %f\n", * health);

            if(* health > 0)
            {
                // printf("%d\n", escort[i].index);

                * health -= HEALTH * escort[i].impact_power;
                Blog.escort_index = escort[i].index;

                // printf("Max Attacking Range %f \n", ship_max_range);
                // printf("Min Attacking Range %f \n", ship_min_range);
                // printf("Distance between the ships %f \n", distance);
                // printf("Battalian ship hit by : %d\n", i);

            }else{
                // printf("BattalianShip Sinked :( \n");
                Blog.escort_index = i;

                // printf("Attacked Escort Ship index: %d\n", i);
                Blog.battaleship_status = 0;
                Blog.cumulative_impact = * health;
                saveBattalianLog(Blog);
                return true;
            }
        }else{
            // printf("BattalianShip is not going to sink\n");
        }
    }
    // printf("BattalianShip Suvived :) \n");
    Blog.battaleship_status = 1;
    Blog.cumulative_impact = * health;

    saveBattalianLog(Blog);
    return false;
}

/**
 * Calculating the shell travel time
*/

float calculateTime(float velocity, float distance)
{
    // printf("%f %f", velocity, distance);
    float theta = asin(distance * GRAVITY / (velocity * velocity)) / 2;
    return distance / (velocity * cos( theta)) ;
}

/**
 * Base simulation for BattalianShips
*/

void battalianSimulation(InitialConditionsBattalian battalian, int escort_count, InitialConditionsEscort escort[escort_count])
{
    // printf("---------------------------\n");
    EscortShipsLog Elog;
    float ship_max_range = range(battalian.max_angle, battalian.maxV);
    // printf("Battalian Ship Range: %f", battalian.maxV);



    for (int i = 0; i < escort_count; i++)
    {
        float distance = getDistance(battalian.position, escort[i].position);

        if(check(distance, 0, ship_max_range))
        {
            // printf("Escort Ship %d is attacked by the battalian\n", escort[i].index);
            float time = calculateTime(battalian.maxV, distance);

            Elog.index = escort[i].index;
            Elog.time = time;
            saveEscortLog(Elog);
        }
    }
    // printf("Attacked Escort Ships Count: %d \n ", attacked_count);

}
/**
 * Remove a row in a escort  array
*/

void removeRowEscort(int * escort_count, InitialConditionsEscort * escort, int index)
{
    for(int i = index; i < *escort_count -1; i++)
    {
        escort[i] = escort[i+1];
    }
    * escort_count -= 1;
}
/**
 * Remove a row in time array
*/
void removeRowTime(int * escort_count, Time * escort, int index)
{
    for(int i = index; i < *escort_count -1; i++)
    {
        escort[i] = escort[i+1];
    }
    * escort_count -= 1;
}

/**
 * Eleminate Already sinked escorts from the array
*/
void removeAttackedEscots(int * escort_count, InitialConditionsEscort * escorts)
{
    //need to change the size
    // InitialConditionsEscort * new_escorts = (InitialConditionsEscort *)calloc (10, sizeof(InitialConditionsEscort));

    int attack_count = 0;

    int * attacked_escorts = loadSinkedEscorts(&attack_count);

    if(attacked_escorts != NULL)
    {
        int x = 0;
        for(int i = 0; i < *escort_count; i++)
        {
            for(int j = 0; j < attack_count; j++)
            {
                if (escorts[i].index == attacked_escorts[j])
                {
                    removeRowEscort(escort_count, escorts, i);
                    i --;
                    break;
                }
            }
        }

    }

}




// int main()
// {
//     Coordinates x;
//     x.x = 6;
//     x.y = 3;
//     Coordinates y;
//     y.x = 5;
//     y.y = 5;

//     printf("%d", changeCoordinate(x, y).x );
//     return 0;
// }