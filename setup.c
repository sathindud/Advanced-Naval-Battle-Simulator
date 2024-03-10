#include<stdio.h>
#include"initializeEscortShips.h"
#include"structure.h"

void setup()
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

        fclose(battalian_file);

