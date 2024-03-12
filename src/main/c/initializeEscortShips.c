#include<stdio.h>
#include<string.h>
#include<stdbool.h>

#include"../header_files/structure.h"
#include"../header_files/getShip.h"
#include"../header_files/random.h"

#define MAXVELOCITY 1.2
#define MINANGLE 1
#define MAXANGLE 90

Coordinates initializePosition(Coordinates canvas_size)
{
	Coordinates position;
	position.x = intRandomNumber(0, canvas_size.x);
	position.y = intRandomNumber(0, canvas_size.y);
	
	return position;
}

bool validatePosition(Coordinates position, int record_count,  Coordinates position_record[record_count])
{	
	for(int i = 0; i < record_count; i++)
	{
		if (position.x == position_record[i].x || position.y == position_record[i].y)
			return false;
		else
			return true;
	}

}	

void initializeEscortShips(Coordinates battalian, Coordinates canvas_size)
{
	//Escort ship type
	EscortShipType ship_type;

        //Incializing the InicialConditionEscort variable
        InitialConditionsEscort escort;
	
        //Inputting the number of escort ships
        printf("Enter the number of escort ships: ");
        int n;
        scanf("%d", &n);

	Coordinates ship_positions[n+1];
	ship_positions[0] = battalian;

        //creating the initial condition escort file
        FILE *escort_file;
        escort_file = fopen("../../log/initial_condition_escort.dat", "w");
        
	//Inputting the inicial conditions for each escort ship and writing it to the file.
        fprintf(escort_file, "index, position, maxV, minV, maxA, minA, type\n");
        for (int i = 0; i < n; i++)
        {
		//getting a random ship
		ship_type = getRandomShip();

                escort.index = i;
		printf("--------------------------------------------");
                printf("Escort Ship number: %d\n", escort.index + 1);
                printf("Escort Ship type %s\n", ship_type.type );
		
		strcpy(escort.type, ship_type.type);

                printf("Escort Ship name %s\n", ship_type.name );

		/**
		 * Need to implement this for getting the random value includeing the 2d map
		 */
		Coordinates temp_position = initializePosition(canvas_size);
		while(true)
		{
			if ( validatePosition(temp_position, n+1, ship_positions))
			{
				ship_positions[i+1] = temp_position;
				escort.position = temp_position;
				break;
			}else
				temp_position =  initializePosition(canvas_size);
		}

 
		if(ship_type.maxV > 0)
			escort.maxV = ship_type.maxV;
		else
			//max velocity must be less than the value correct this later
			escort.maxV = floatRandomNumber(0, MAXVELOCITY);	
                printf("Escort Ship maximum velocity: %f\n", escort.maxV);

		//Setting the minimum velocity
		escort.minV = floatRandomNumber(0, MAXVELOCITY);
                printf("Escort Ship minimum velocity: %f\n", escort.minV );

		//Calculating the maximum angle
		escort.minA = floatRandomNumber(MINANGLE, MAXANGLE);
                printf("Escort Ship minimum angle: %f\n", escort.minA);

		escort.maxA = escort.minA + ship_type.angle_range;
		if (escort.maxA > 90)
			escort.maxA = 90;
                printf("Escort Ship maximum angle  %f\n", escort.maxA);


		//printing in the file
                fprintf(escort_file, "%d, %d, %d, %f, %f, %f, %f, %s\n", escort.index, escort.position.x, escort.position.y, escort.maxV, escort.minV, escort.maxA, escort.minA, escort.type);

        }
        fclose(escort_file);
}

int main()
{
	initializeRandom();
//	initializeRandom();
	Coordinates val;
	val.x = 2;
	val.y = 3;
	
	Coordinates val2;
	val2.x = 5;
	val2.y = 5;


	initializeEscortShips(val, val2);
	return 0;
}
