#include<stdio.h>
#include<stdlib.h>
#include"../header_files/structure.h"

UserInput loadUserInput()
{
    UserInput user_input;

    FILE * file;
    file = fopen("../../log/user_input.dat", "r");
    if (file == NULL)   
    {
        printf("Error while loading the canvas size file");
    }

    char line[50];
    fgets(line, sizeof(line), file);

    fgets(line, sizeof(line), file);
    sscanf(line, "%d, %d ,%d", &user_input.canvas_size.x, &user_input.canvas_size.y, &user_input.escort_count);
    fclose(file);

    return user_input;

    
}

InitialConditionsBattalian loadBattalianShip()
{
    InitialConditionsBattalian ship;

    FILE * ship_file;
    ship_file = fopen("../../log/initial_condition_battalian.dat", "r");

    if(ship_file == NULL)
        printf("Cannot open the Battalian Ship Initial Condition file\n");

    char line[100];
    fgets(line, sizeof(line), ship_file);
    

    fgets(line, sizeof(line), ship_file);
    if (line == NULL)
    {
        printf("File is empty no BattalianShip\n");
        ship.position.x = -1;
    }else{
        sscanf(line, "%d, %d, %c, %f, %f", &ship.position.x, &ship.position.y, &ship.type, &ship.maxV, &ship.time);
        ship.max_angle = BMAX_ANGLE;
    }
    
    fclose(ship_file);

    return ship;
}

InitialConditionsEscort * loadEscortShip()
{
    InitialConditionsEscort * ship = (InitialConditionsEscort *)calloc (loadUserInput().escort_count, sizeof(InitialConditionsEscort));

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
        sscanf(line, "%d, %d, %d, %f, %f, %f, %f, %f, %d, %5c", &ship[i].index, &ship[i].position.x, &ship[i].position.y, &ship[i].impact_power, &ship[i].maxV, &ship[i].minV, &ship[i].maxA, &ship[i].minA, &ship[i].time, ship[i].type);
        // printf("%d\n", ship[i].time);
        i++;
    }
    fclose(ship_file);
    return ship;
    
}



int * loadSinkedEscorts(int * count)
{
    int * index = (int *)malloc(sizeof(int) * loadUserInput().escort_count);

    FILE *file;
    file = fopen("../../log/escortsship_log.dat", "r");
    if(file == NULL)
    {
        printf("Error while loading the the sinked ships");
    }

    char line[20];
    fgets(line, sizeof(line), file);
    
    int i = 0;
    while (fgets(line, sizeof(line), file))
    {
        sscanf(line, "%d", &index[i]);
        // printf("loading:: %d\n", index[i]);

        i++;
    }
    fclose(file);

    * count = i;
    return index;
}

int * loadAttackedEscorts(int * count)
{
    int * index = (int *)malloc(sizeof(int) * loadUserInput().escort_count);

    FILE *file;
    file = fopen("../../log/battalianship_log.dat", "r");
    
    if(file == NULL)
    {
        printf("Error while loading the the attacked ships");
    }

    char line[100];
    fgets(line, sizeof(line), file);
    
    int tempi;
    int temp_val;
    float tempf; 
    
    int i = 0;
    while (fgets(line, sizeof(line), file))
    {
        sscanf(line, "%d, %d, %d, %f, %d", &tempi, &tempi, &tempi, &tempf, &temp_val);
        if (temp_val > 0)
        {
            index[i] = temp_val;
            i++;
        }
    }
    fclose(file);

    * count = i;
    return index;
}
// int main()
// {
//     int count = 0;
//     int * x;
//     x = loadAttackedEscorts(&count);
//     printf("%d", count);
//     free(x);
//     // int  count = 0;
//     // InitialConditionsEscort * s = loadEscortShip(&count);
//     // free(s);
//     // // Coordinates x = loadCanvasSize();
//     // printf("%d %d", x.x, x.y);
//     // // InitialConditionsBattalian ship = loadBattalianShip();
//     // // printf("%f", ship.maxV);
//     // // // InitialConditionsEscort *x = loadEscortShip();
//     // // // for(int i = 0; i < 10; i++)
//     // // // {
//     // // //         printf("%d\n",x[i].position.x);

//     // // // }
//     return 0;
// }