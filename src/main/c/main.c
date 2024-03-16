#include <stdio.h>
#include<math.h>
#include<stdbool.h>
#include<stdlib.h>


#include "../header_files/structure.h"
#include "../header_files/random.h"
#include "../header_files/initializeBattalianShip.h"
#include "../header_files/initializeEscortShips.h"
#include "../header_files/loadInitial.h"
#include "../header_files/simulation.h"


void setup(Coordinates canvas_size)
{
	InitialConditionsBattalian battalian = loadBattalianShip();

	int user_input;
	printf("1. Setting Up the Canvas\n");
	printf("2. Battalianship Propoties\n");
	printf("3. Escortship Propoties\n");
	printf("4. Initialize Seed value");
	printf("44. Go Back\n");
	scanf("%d", &user_input);

	while(user_input != 44)
	{
		switch (user_input)
		{
		case 1:
			printf("Enter the canvas size (x y): ");
			scanf("%d %d", &canvas_size.x, &canvas_size.y);
			break;
		case 2:
		/**
		 * This is not working figure it out later
		*/
			if(canvas_size.x == 0)
			{
				printf("Set a Canvas Size to continue\n");
			}else
			{
				initializeBattalianShip(canvas_size);
			}
			break;
		case 3:
			if (canvas_size.x == 0)
			{
				printf("Set a Canvas Size for first time to Continue\n");

			}else if (battalian.position.x == -1)
			{
				printf("Set the BattalianShip Coordinates for first time to Continue \n");
			}else{
				initializeEscortShips(canvas_size);
			}
			break;
		case 4:
			initializeRandom();
			break;
		default:
			printf("Invalid Input\n");
			break;
		}
		printf("1. Setting Up the Canvas\n");
		printf("2. Battalianship Propoties\n");
		printf("3. Escortship Propoties\n");
		printf("44. Go Back\n");
		scanf("%d", &user_input);
	}


}

void simulation()
{
	int user_input;

	printf("1. Simulation 01\n");
	printf("2. Simulation 02\n");
	printf("3. Simulation 03\n");
	printf("44. Go Back\n");
	printf("Enter the menue number: ");
	scanf("%d", &user_input);
	while (user_input != 44)
	{
		switch (user_input)
		{
		case 1:
			simulation1();
			break;
		case 2:
			simulation2();
			break;
		default:
			printf("Invaild Input\n");
			break;
		}

		printf("1. Simulation 01\n");
		printf("2. Simulation 02\n");
		printf("3. Simulation 03\n");
		printf("44. Go Back\n");
		printf("Enter the menue number: ");
		scanf("%d", &user_input);
	}
	
}

int main()
{
	//need to save this canvas size later

	Coordinates canvas_size;
	
	/**
	 * Test data need to remove
	*/
	initializeRandom();
	canvas_size.x = 100;
	canvas_size.y = 100;
	
	int user_input;
	printf("1. Set Up \n");
	printf("2. Show Simulation\n");
	printf("44. Exit\n");
	printf("Enter the menue number: ");
	scanf("%d", &user_input);

	while (user_input != 44)
	{
		switch (user_input)
		{
		case 1:
			setup(canvas_size);
			break;
		case 2:
			simulation();
			break;
		case 3:
			break;
		default:
			printf("Invalid User Input\n");
			break;
		}
		printf("1. Set Up \n");
		printf("2. Show Simulation\n");
		printf("44. Exit\n");
		printf("Enter the menue number: ");
		scanf("%d", &user_input);
	}
	

	return 0;
}

