#include <stdio.h>
#include<math.h>
#include<stdbool.h>
#include<stdlib.h>


#include "../header_files/structure.h"

#define GRAVITY 9.8

float range(int angle, float velocity)
{
	return (velocity * velocity) * sin(2* angle * 3.14 / 180) / 10;
}

float findMaxVelocity(Coordinates canvas_size)
{
	return sqrt((canvas_size.x / 2.0)* GRAVITY);
}

bool check(Coordinates b, Coordinates e, float range)
{
	int x = abs(b.x - e.x);
	int y = abs(b.y - e.y);
	float r = sqrt((x*x) + (y*y));
	printf("Distance between b and e %f\n", r);


	if ( r < range)
	{
		return true;
	}else
	{
		return false;
	}

}


int main()
{
	Coordinates battalian,canvas_size;

	Coordinates x[4];

	canvas_size.x = 10;
	canvas_size.y = 10;

	battalian.x = 5;
	battalian.y = 5;

	float r_max[4];
	float r_min[4];

	x[0].x = 5;
	x[0].y = 10;

	float battalian_velocity = findMaxVelocity(canvas_size);
	printf("Maximum velocity according to the canvas size: %f\n", battalian_velocity);

	float b_range = range(45, battalian_velocity);
	printf("Battalianship Range %f\n", b_range);


	// r_max[0] = range(30, 10);
	// r_min[0] = range(60, 10);

	x[1].x = 8;
	x[1].y = 5;
	// r_max[1] = range(10, 10);
	// r_min[1] = range(40, 10);
	
	x[2].x = 1;
	x[2].y = 3;
	// r_max[2] = range(10, 10);
	// r_min[2] = range(35, 10);
	
	x[3].x = 10;
	x[3].y = 10;
	// r_max[3] = range(10, 10);
	// r_min[3] = range(60, 10);

	for (int i = 0; i < 4; i++)
	{
		printf("Escort SHip Number: %d\n", i+1);

		if (check(battalian, x[i], b_range))
		{
			printf("Ship is in range\n");
		}else
		{
			printf("Ship is not in the range\n");
		}
	}
	


	
	return 0;
}

