#include<stdio.h>
#include"structure.h"
#include"getShip.h"
#include"random.h"
#include<stdlib.h>
#include<stdbool.h>

Coordinates initializePosition(Coordinates canvas_size)
{
	/**
	 * Implemnet the user to see the 2d canvas by displaying the canvas
	 */
	Coordinates position;
	
	printf("Enter position of the Battalian Ship between (%d %d)", canvas_size.x, canvas_size.y);
	scanf("%d %d", &position.x, &position.y);

	while (true){
		if( position.x < canvas_size.x && position.y < canvas_size.y)
			break;
		else
		{
			printf("Enter the Battalian Ship Position inside the canvas");	
			printf("Enter position of the Battalian Ship between (%d %d)", canvas_size.x, canvas_size.y);
			scanf("%d %d", &position.x, &position.y);
		}
	}

	return position;

}

void initializeBattalianShip(Coordinates canvas_size)
{

	
	InitialConditionsBattalian battalian;


        /**
	 *Setting up the battalian ship position
	 */
	char *types = getBattalianShips();

	bool found = false;
	printf("Enter the Battalian Ship Notation you like: ");
	scanf("%s", &battalian.type);
        while(true)
	{

		int n = BATTALIAN_SHIP_COUNT;
		while(n >0)
		{
			if(types[n] == battalian.type)
			{
				found = true;
				break;
			}
			
			n--;
		}

		if(found)
			break;
		else
		{
			printf("Error: enter a Valid Notation\n ");
			scanf("%s", &battalian.type);
		}

	}
	free(types);

	Coordinates position = initializePosition(canvas_size);

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
        
	//creating the initial condition escort file
        FILE *battalian_file;
        battalian_file = fopen("initial_condition_battalian.dat", "w");

        //writing the inicial conditions for each escort ship and writing it to the file.
        fprintf(battalian_file, "index, type, maxV\n");
        fprintf(battalian_file, "%d, %d, %c, %f\n", position.x, position.y, battalian.type, battalian.maxV);

        fclose(battalian_file);

}
/*
int main()
{
	initializeBattalianShip();
	return 0;
}
*/
