#include <stdio.h>

// Creating a Stucture for escort ships
typedef struct{
	int index;
	int x;
	int y;
	float maxV;
	float minV;
	float maxA;
	float minA;
	char type;
}InitialConditionsEscort;

// Creatinf a Structer for Battalian Ships
typedef struct{
	int x;
	int y;
	float maxV;
	char type;
}InitialConditionsBattalian;

void inputEscortShips();

int main()
{

	//Incializing the Battalian Ship variable
	InitialConditionsBattalian battalian;

	//creating the initial condition escort file
	FILE *battalian_file;
	battalian_file = fopen("initial_condition_battalian.dat", "w");
	
	printf("Enter the Battalian Ship Position (x y): ");
	scanf("%d %d", &battalian.x, &battalian.y);
	printf("Enter the Battalian Ship Type: ");
	scanf("%s", &battalian.type);
	printf("Enter the maximum velocity: ");
	scanf("%f", &battalian.maxV);

	//Inputting the inicial conditions for each escort ship and writing it to the file. 
	fprintf(battalian_file, "index, type, maxV\n");
	fprintf(battalian_file, "%d, %d, %c, %f\n", battalian.x, battalian.y, battalian.type, battalian.maxV);


	return 0;
}

void inputEscortShips()
{
	//Incializing the InicialConditionEscort variable
	InitialConditionsEscort escort;

	//creating the initial condition escort file
	FILE *escort_file;
	escort_file = fopen("initial_condition_escort.dat", "w");
	
	//Inputting the number of escort ships
	printf("Enter the number of escort ships: ");
	int n;
	scanf("%d", &n);

	//Inputting the inicial conditions for each escort ship and writing it to the file. 
	fprintf(escort_file, "index, position, maxV, minV, maxA, minA, type\n");
	for (int i = 0; i < n; i++)
	{
		escort.index = i;
		printf("Escort Ship number %d\n", escort.index + 1);
		printf("Enter the Escort Ship Position (x y): ");
		scanf("%d %d", &escort.x, &escort.y);
		printf("Enter the maximum velocity: ");
		scanf("%f", &escort.maxV);
		printf("Enter the minimum velocity: ");
		scanf("%f", &escort.minV);
		printf("Enter the maximum angle: ");
		scanf("%f", &escort.maxA);
		printf("Enter the minimum angle: ");
		scanf("%f", &escort.minA);
		printf("Enter the escort ship type: ");
		scanf("%s", &escort.type);

		fprintf(escort_file, "%d, %d, %d, %f, %f, %f, %f, %c\n", escort.index, escort.x, escort.y, escort.maxV, escort.minV, escort.maxA, escort.minA, escort.type);
	
	}
	fclose(escort_file);
}
