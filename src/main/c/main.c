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
#include "../header_files/simulation5.h"
#include "../header_files/simulationStat.h"
#include "../header_files/instructions.h"
void setup()
{
	Coordinates canvas_size;

	int user_input;
	printf("1. Setting Up the Canvas\n");
	printf("2. Battalianship Propoties\n");
	printf("3. Escortship Propoties\n");
	printf("4. Initialize Seed value\n");
	printf("44. Go Back\n");
	printf("Enter the menue number: ");

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
			initializeBattalianShip(canvas_size);
			break;

		case 3:
			printf("Set a Canvas Size for first time to Continue\n");
			initializeEscortShips(canvas_size);
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
		printf("Enter the menue number: ");

		scanf("%d", &user_input);
	}


}

void simulation()
{

	int user_input;

	printf("1. Part 1 A Simulation\n");
	printf("2. Part 1 B Simulation 1\n");
	printf("3. Part 1 B Simulation 2\n");
	printf("4. Part 1 C Simulation\n");
	printf("5. Part 2 A Simulation\n");
	printf("6. Part 2 B Simulation\n");
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
		case 3:
			simulation3();
			break;
		case 4:
			simulation4();
			break;
		case 5:
			simulation5();
			break;
		case 6:
			simulation6();
			break;
		default:
			printf("Invaild Input\n");
			break;
		}

		printf("1. Part 1 A Simulation\n");
		printf("2. Part 1 B Simulation 1\n");
		printf("3. Part 1 B Simulation 2\n");
		printf("4. Part 1 C Simulation\n");
		printf("5. Part 2 A Simulation\n");
		printf("6. Part 2 B Simulation\n");
		printf("44. Go Back\n");
		printf("Enter the menue number: ");
		scanf("%d", &user_input);
	}

	
}

void sub_main()
{


	
	/**
	 * Test data need to remove
	*/
	initializeRandom();
		
	int user_input;
	printf("1. Set Up \n");
	printf("2. Show Simulation\n");
	printf("44. Go back\n");
	printf("Enter the menue number: ");
	scanf("%d", &user_input);

	while (user_input != 44)
	{
		switch (user_input)
		{
		case 1:
			setup();
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
	

}

int main()
{
	simulation6();
	// printf("------------------------------------\n");
    // printf("    Advanced Naval Simulator \n");
    // printf("------------------------------------\n");
	// int user_input;
	// printf("1. Main Menue Options\n");
	// printf("2. View Instructions\n");
	// printf("3. Simulation Statistics\n");
	// printf("44. Exit\n");
	// printf("Enter the menue number: ");
	// scanf("%d", &user_input);

	// while (user_input != 44)
	// {
	// 	switch (user_input)	
	// 	{
	// 	case 1:
	// 		sub_main();
	// 		break;
	// 	case 2:
	// 		instructions();
	// 		break;
	// 	case 3:
	// 		simulationStat();
	// 		break;
	// 	default:
	// 		printf("Invalid User Input\n");
	// 		break;
	// 	}
	// 	printf("1. Main Menue Options\n");
	// 	printf("2. View Instructions\n");
	// 	printf("3. Simulation Statistics\n");
	// 	printf("44. Exit\n");
	// 	printf("Enter the menue number: ");
	// 	scanf("%d", &user_input);
	// }
	
	

	return 0;
}
