#include<stdio.h>
#include<stdlib.h>
#include"../header_files/structure.h"

InitialConditionsBattalian loadBattalianShip()
{
    InitialConditionsBattalian ship;

    FILE * ship_file;
    ship_file = fopen("../../log/initial_condition_battalian.dat", "r");

    if(ship_file == NULL)
        printf("Cannot open the Battalian Ship Initial Condition file\n");

    char line[100];
    fgets(line, sizeof(line), ship_file);
    

    while (fgets(line, sizeof(line), ship_file))
    {
        sscanf(line, "%d, %d, %c, %f", &ship.position.x, &ship.position.y, &ship.type, &ship.maxV);

    }
    if (line == NULL)
    {
        printf("File is empty no BattalianShip\n");
        ship.position.x = -1;
    }
    
    fclose(ship_file);

    return ship;
}

InitialConditionsEscort * loadEscortShip(int * count)
{
    //Need to change the size of the array according to the ship count
    InitialConditionsEscort * ship = (InitialConditionsEscort *)calloc (10, sizeof(InitialConditionsEscort));

    if(ship == NULL)
    {
        printf("Error while memory allocating\n");
    }

    FILE * ship_file;
    ship_file = fopen("../../log/initial_condition_escort.dat", "r");
    if (ship_file == NULL)
    {
        printf("Error while loading the escort ship file");
    }

    char line[100];
    fgets(line, sizeof(line), ship_file);
    int i = 0;
    while (fgets(line, sizeof(line), ship_file))
    {
        sscanf(line, "%d, %d, %d, %f, %f, %f, %f, %5c", &ship[i].index, &ship[i].position.x, &ship[i].position.y, &ship[i].maxV, &ship[i].minV, &ship[i].maxA, &ship[i].minA, ship[i].type);
        i++;
    }
    * count = i;
    return ship;
    
}
// int main()
// {
//     InitialConditionsBattalian ship = loadBattalianShip();
//     printf("%f", ship.maxV);
//     // InitialConditionsEscort *x = loadEscortShip();
//     // for(int i = 0; i < 10; i++)
//     // {
//     //         printf("%d\n",x[i].position.x);

//     // }
//     return 0;
// }