#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include"../header_files/structure.h"
#include"../header_files/random.h"

BattalianShipType * getBattalianShips()
{
	// char * ship_notation = (char *)(BATTALIAN_SHIP_COUNT); 
	BattalianShipType * ship_notation = (BattalianShipType *)calloc(BATTALIAN_SHIPS_TYPES, sizeof(BattalianShipType));

	
	//opening the battalian ships file
	FILE *battalian;
	battalian= fopen("../../resource/battalian_types.dat", "r");
	
	if (battalian == NULL)
		printf("Cannot open the battalian ship file\n");

	char buffer[1024];

	fgets(buffer, sizeof(buffer), battalian);

	//Reading the file row
	int i = 0;
	printf("-------------------------------------------------------------------------------------\n");

	printf("|%10s|%-30s|%-10s|%-30s|\n","index","Name","Notation","Gun Name ");
	printf("-------------------------------------------------------------------------------------\n");


	while (fgets(buffer, 1024, battalian))
	{
		sscanf(buffer, "%s %c %s", ship_notation[i].name, &ship_notation[i].type, ship_notation[i].gun_name);
		printf("|%-10d|%-30s|%-10c |%-30s|\n", i, ship_notation[i].name, ship_notation[i].type, ship_notation[i].gun_name);
		i++;

	}
	printf("--------------------------------------------------------------------------------------\n");


	fclose(battalian);

	return ship_notation;
}


EscortShipType getRandomShip()
{
	EscortShipType ship;

	//getting random value between 5 types of ships
	int random = intRandomNumber(2, 6);

	//opening the escort ships file
	FILE *escort;
	escort = fopen("../../resource/ecorts_types.dat", "r");
	
	if (escort == NULL)
		printf("Cannot open the escort ship file");


	char buffer[1024];
	int row = 0;
	int colum = 0;

	//Reading the file row
	while (fgets(buffer, 1024, escort))
	{
		colum = 0;
		row ++;

		if (row == 1)
			continue;


		//spliting the values by comma
		//sscanf(line, "%[^,],%d,%d", name, &age, &salary);
		char * value = strtok(buffer, ", ");
		while (value) {
		
			switch (colum){
				case 0:
					strcpy(ship.type, value);
					break;
				case 1:
					strcpy(ship.name, value);
					break;
				case 2:
					strcpy(ship.gun_name,value);
					break;
				case 3:
					ship.impact_power = atof(value);
					break;
				case 4:
					ship.angle_range = atoi(value);
					break;
				case 5:
					ship.minA = atof(value);
					break;
				case 6:
					ship.minV = atof(value);
					break;
				case 7:
					ship.maxV = atof(value);
					break;
				
			}
		//	printf("%s\n", value);
			value = strtok(NULL, ", ");
			colum++;
		}

		//breaking the loop after the random ship rinitializeBattalianShip(canvas_size);eads
		if (row == random)
			break;
	}

	fclose(escort);

	return ship;
}

// int main()
// {

// 	// EscortShipType e;
// 	// e = getRandomShip();
// 	// printf("%d", e.angle_range);
// 	BattalianShipType * x = getBattalianShips();
// 	// EscortShipType ship;
// 	// int x = intRandomNumber(2, 6);
// 	// loadFile(&ship, x);
// 	// printf("Ransom: %d Value: %s\n", x,ship.type);
// 	return 0;
// }

