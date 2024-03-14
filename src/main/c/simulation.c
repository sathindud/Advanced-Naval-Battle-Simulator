#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<stdbool.h>

#include "../header_files/structure.h"
#include "../header_files/random.h"

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
	float r = sqrt((x*x) + (y*y));
	// printf("Distance between b and e %f\n", r);

	if (r < min_range)
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



void escortSimulation(int escort_count, InitialConditionsEscort escort[escort_count], Coordinates battalian)
{
    for (int i = 0; i < escort_count; i++)
    {
        float exact_velocity = floatRandomNumber(escort[i].minV, escort[i].maxV);
        float ship_max_range = range(escort[i].minA, exact_velocity);
        float ship_min_range = range(escort[i].maxA,  exact_velocity);      

        // if (check(escort[i].position, battalian, ship_max_range))
        // {
        //     /* code */
        // }
        
    }


}

int main()
{
    float min = 10;
    float max = 45;
    findMaxMinAngle(&min, &max);
    printf("Min: %f Max: %f\n", min, max);
    return 0;
}