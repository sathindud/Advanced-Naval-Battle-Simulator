#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>

#include"../header_files/structure.h"
#include"../header_files/getShip.h"
#include"../header_files/random.h"
#include"../header_files/loadInitial.h"

#define MAXVELOCITY 100
#define MINANGLE 1
#define MAXANGLE 90

/**
 * Validate the randomly generated position value 
 * 	-> because some times it generate the same value
*/
bool validatePosition(Coordinates position, int record_count,  Coordinates position_record[record_count])
{	
	for(int i = 0; i < record_count; i++)
	{
		if (position.x == position_record[i].x && position.y == position_record[i].y)
			return false;
		else
			return true;
	}

}	

/**
 * Generating Random Positions for Escort Ships
*/
Coordinates initializeEPosition()
{
	Coordinates canvas_size = loadUserInput().canvas_size;
	Coordinates position;
	position.x = intRandomNumber(0, canvas_size.x);
	position.y = intRandomNumber(0, canvas_size.y);
	
	return position;
}

/**
 * Determine the Velocity Range according to the Canvas Size
*/
float findMaxVelocity(Coordinates canvas_size)
{
	return sqrt((canvas_size.x / 2.0)* GRAVITY);
}

/**
 * Initialize Escort Ships
*/
void initializeEscortShips(Coordinates canvas_size)
{
	//Escort ship type
	EscortShipType ship_type;

	//Incializing the InicialConditionEscort variable
	InitialConditionsEscort escort;

	//Input the number of escort ships
	printf("Enter the number of escort ships: ");
	int n;
	scanf("%d", &n);
	
	//validate the user input according to the canvas size
	while (n <= 0 && n > (canvas_size.x * canvas_size.y) -1)
	{
		printf("Enter a valid escort ship count\n");
		printf("Enter the number of escort ships: \n");
		scanf("%d", &n);
	}

	//creating the User Input file and save the canvas size and the escort count
	FILE *user_input;
	user_input = fopen("../../log/user_input.dat", "w");
	fprintf(user_input, "canvas_w, canvas_h, escort_count\n");
	fprintf(user_input, "%d, %d, %d\n", canvas_size.x, canvas_size.y, n);
	fclose(user_input);

	
	//Eleminate Battalian Ship position from getting escorts
	InitialConditionsBattalian battalian = loadBattalianShip();	
	Coordinates ship_positions[n+1];
	ship_positions[0] = battalian.position;

	//creating the initial condition escort file
	FILE *escort_file;
	escort_file = fopen("../../log/initial_condition_escort.dat", "w");
	
	//Inputting the inicial conditions for each escort ship and writing it to the file.
	fprintf(escort_file, "index, position, impact_power, maxV, minV, maxA, minA, time, type\n");
	for (int i = 0; i < n; i++)
	{
		//getting a random ship
		ship_type = getRandomShip();

		//Setting the Index
		escort.index = i;

		printf("--------------------------------------------\n");
				printf("Escort Ship number: %d\n", escort.index + 1);
				printf("Escort Ship type %s\n", ship_type.type );
		
		strcpy(escort.type, ship_type.type);

				printf("Escort Ship name %s\n", ship_type.name );

		//Setting Escort Ship Position
		Coordinates temp_position = initializeEPosition(canvas_size);
		while(true)
		{
			if (validatePosition(temp_position, i+1, ship_positions))
			{
				ship_positions[i+1] = temp_position;
				escort.position = temp_position;
				break;
			}else
				temp_position =  initializeEPosition(canvas_size);
		}


		//Finding the Maximum range that can apply and save the random value withing that range
		float max_velocity = findMaxVelocity(canvas_size);

		escort.maxV = floatRandomNumber(0, max_velocity);	
		printf("Escort Ship maximum velocity: %.2f\n", escort.maxV);

		if(ship_type.maxV > 0)
			escort.maxV = ship_type.maxV * escort.maxV;

		//Finding the minimum velocity
		escort.minV = floatRandomNumber(0, escort.maxV);
		printf("Escort Ship minimum velocity: %.2f\n", escort.minV );

		//Calculating the maximum angle
		escort.minA = floatRandomNumber(MINANGLE, MAXANGLE);
		printf("Escort Ship minimum angle: %f\n", escort.minA);
		escort.maxA = escort.minA + ship_type.angle_range;
		//Checking the max angle inside the range 0 - 90
		if (escort.maxA > 90)
			escort.maxA = 90;
		
		printf("Escort Ship maximum angle  %.2f\n", escort.maxA);

		//saving in the file
				fprintf(escort_file, "%d, %d, %d, %.2f, %.2f, %.2f, %.2f, %.2f, %d, %s\n", escort.index, escort.position.x, escort.position.y, ship_type.impact_power, escort.maxV, escort.minV, escort.maxA, escort.minA, ship_type.time, escort.type);

	}
	fclose(escort_file);
}

// int main()
// {
// 	initializeRandom();
// //	initializeRandom();
// 	Coordinates val;
// 	val.x = 2;
// 	val.y = 3;
	
// 	Coordinates val2;
// 	val2.x = 10;
// 	val2.y = 10;


// 	initializeEscortShips(val, val2);
// 	return 0;
// }
