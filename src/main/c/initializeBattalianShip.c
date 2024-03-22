#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>

#include"../header_files/structure.h"
#include"../header_files/getShip.h"
#include"../header_files/random.h"
#include "../header_files/loadInitial.h"


/**
 * Input Battalian ship position and validation
*/
Coordinates initializeBPosition(Coordinates canvas_size)
{
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

/**
 * Initializing the Battle Ship
*/

void initializeBattalianShip()
{
	Coordinates canvas_size = loadUserInput().canvas_size;
	
	InitialConditionsBattalian battalian;

    
	//Loading the Battle ship types from a file
	BattalianShipType * types = getBattalianShips();

	bool found = false;
	int index = 0;

	//Promting the user to input the battalian ship index
	printf("Enter the Battalian Ship Notation index you like: ");
	scanf("%d", &index);

	//Validating the user input index 
    while(true)
	{
		if (index < 4 || index > 0)
		{
			battalian.type = types[index].type;
			break;
		}else{
			printf("Error: enter a Valid Notation\n ");
			scanf("%d", &index);
		}

	}
	printf("type: %c\n", battalian.type);
	free(types);


	//Entering the BattalianShip Coordinates
	Coordinates position = initializeBPosition(canvas_size);

	//Setting the Maximum velocity for Battalian ship
	printf("Do you need generate random value for maximum velocity (y/n): ");
	char val;
	scanf("%s", &val);

	//Finding the best maximum velcity according to the canvas size
	float max_velocity = sqrt((canvas_size.x / 2.0)* GRAVITY);

	//Setting the maximum Velocity
	if(val == 'y' || val == 'Y')
		battalian.time = floatRandomNumber(0, max_velocity);
	else
	{
		printf("Enter the maximum velocity:\n");
		printf("note: Maximum velocity according to the canvas size is: %f\n", max_velocity);
		printf("Entering a value less than value for better performance: ");
        scanf("%f", &battalian.maxV);
	}

	//Setting the Time between two gun firering
	printf("Do you need generate random value for time for two firing (y/n): ");
	scanf("%s", &val);

    if(val == 'y' || val == 'Y')
		battalian.time = floatRandomNumber(0, 30);
	else
	{
		printf("Enter the time duration for two firing:\n");
		printf("note: Normal Battalian Ship takes 30 seconds between two gun firerings\n");
		printf("Enter a value: ");
        scanf("%f", &battalian.time);
	}

	//creating the file initial condition battalian ship file
        FILE *battalian_file;
        battalian_file = fopen("../../log/initial_condition_battalian.dat", "w");

        //writing the inicial conditions for each escort ship and writing it to the file.
        fprintf(battalian_file, "position, type, maxV, time\n");
        fprintf(battalian_file, "%d, %d, %c, %.2f, %.2f\n", position.x, position.y, battalian.type, battalian.maxV, battalian.time);

        fclose(battalian_file);
		
}

/*
int main()
{
	initializeBattalianShip();
	return 0;
}
*/
