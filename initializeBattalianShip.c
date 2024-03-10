#include<stdio.h>
#include"structure.h"
#include"getShip.h"
#include"random.h"
#include<stdlib.h>

void initializeBattalianShip()
{

	
	InitialConditionsBattalian battalian;

        //creating the initial condition escort file
        FILE *battalian_file;
        battalian_file = fopen("initial_condition_battalian.dat", "w");

        /**
	 *Setting up the battalian ship position
	 */
	char *types = getBattalianShips();

	int found = 0;
        do{
        	printf("Enter the Battalian Ship Notation you like: ");
		scanf("%s", &battalian.type);
		int n = BATTALIAN_SHIP_COUNT;
		while(n >0)
		{
			if(types[n] == battalian.type)
			{
				found = 1;
				break;
			}
			n--;
		}

	}while(!found);

	free(types);

	printf("Do you need generate random value for maximum velocity (y/n): ");
	char val;
	scanf("%s", &val);

	if(val == 'y' || val == 'Y')
		battalian.maxV = floatRandomNumber(0, 1.2);
	else
	{
		printf("Enter the maximum velocity: ");
        	scanf("%f", &battalian.maxV);
	}

        //writing the inicial conditions for each escort ship and writing it to the file.
        fprintf(battalian_file, "index, type, maxV\n");
        fprintf(battalian_file, "%d, %d, %c, %f\n", battalian.x, battalian.y, battalian.type, battalian.maxV);

        fclose(battalian_file);

}

int main()
{
	initializeBattalianShip();
	return 0;
}
