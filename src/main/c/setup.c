#include<stdio.h>
#include<stdbool.h>
#include"../header_files/structure.h"

#include"../header_files/initializeEscortShips.h"
#include"../header_files/initializeBattalianShip.h"

//User input the size of the canvas
Coordinates initializeCanvas()
{
	
	Coordinates size;

	printf("Enter the 2D square canvas size: (x y) :");
	scanf("%d %d", &size.x, &size.y);

	FILE * log;
	log = fopen("../../log/canvas_size.dat", "w");
	fprintf(log, "wight, height\n");
	fprintf(log, "%d, %d", size.x, size.y);
	fclose(log);

	return size;
}


int menue()
{
	int menue_number;
	printf("1: Setting up Canvas \n");
	printf("2: BattalianShip Propoties \n");
	printf("3: EscortShips Propoties \n");
	printf("44: Go Back\n");
	scanf("%d", &menue_number);
	return menue_number;
}

void setup()
{
	int menue_number;
	Coordinates canvas_size;
	canvas_size.x = 0;
	menue_number = menue();

	int exit = true;
	while (true)
	{
		switch(menue_number){
			case 1:
				canvas_size = initializeCanvas();
				break;
			case 2:
				if (canvas_size.x == 0)
					printf("Enter the Canvas Size first\n");
				else
					initializeBattalianShip(canvas_size);
				break;

			case 3:
				if (canvas_size.x == 0)
					printf("Enter the Canvas Size first\n");
				else
					initializeEscortShips(canvas_size);
				break;

			case 44:
				exit = false;
				break;

			default:
				printf("Invalid Input");
				break;
		}
		if (exit)
			menue_number = menue();
		else
			break;
	}

}

int main()
{
	setup();
	return 0;
}
