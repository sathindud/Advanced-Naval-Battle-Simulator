#include<stdio.h>
#include<stdlib.h>

#include "../header_files/structure.h"
#include "../header_files/loadInitial.h"
#include "../header_files/getShip.h"

void printBattalianLog()
{
    printf("BattalianShip Log\n");

    BattalianShipLog battalian;

    FILE * log;
    log = fopen("../../log/battalianship_log.dat", "r");
    if(log == NULL)
        printf("Cannot open battalian ship log");

    char line[100];
    fgets(line, sizeof(line), log);
    printf("----------------------------------------------------------------\n");
    printf("Position    |   Status  | Cumilative Impact | EscortShip Index |\n");

    printf("----------------------------------------------------------------\n");
    while (fgets(line, sizeof(line), log))
    {
        sscanf(line, "%d, %d, %d, %f, %d", &battalian.position.x, &battalian.position.y, &battalian.battaleship_status, &battalian.cumulative_impact, &battalian.escort_index);
        if (battalian.escort_index != -1)
        {
            printf("|%d %d      |   %d      |         %.2f      |       %d         |\n", battalian.position.x, battalian.position.y, battalian.battaleship_status, battalian.cumulative_impact, battalian.escort_index);
        }
        
    }
    printf("---------------------------------------------------------------\n");

    fclose(log);
}

void printEscortLog()
{
    printf("Attacked Escort Ships Log\n");

    EscortShipsLog escort;

    float total_time = 0;

    FILE * log;
    log = fopen("../../log/escortsship_log.dat", "r");
    if(log == NULL)
        printf("Cannot open escort ship log");

    char line[100];
    fgets(line, sizeof(line), log);
    printf("------------------------------------\n");
    printf("EscortShip Index    | Time to Hit  |\n");
    printf("------------------------------------\n");
    while (fgets(line, sizeof(line), log))
    {
        sscanf(line, "%d, %f", &escort.index, &escort.time);
        printf("|        %d         |      %.2f    |\n", escort.index, escort.time);
        total_time += escort.time;
        
    }
    printf("------------------------------------\n");

    printf("Total Time to end the battle :- %.2f\n", total_time);

    fclose(log);
}

void printBattalianShipInitials()
{
    printf("BattalianShip Initials Values\n");

    InitialConditionsBattalian battalian;

    battalian = loadBattalianShip();

    printf("-----------------------------------------\n");
    printf("|   Notation  | Position | Max Velocity |\n");

    printf("-----------------------------------------\n");

    printf("|     %c     |     %d %d    |     %.2f    |\n", battalian.type, battalian.position.x, battalian.position.y, battalian.maxV);

    printf("-----------------------------------------\n");

} 

void printEscortShipInitials()
{
    printf("EscortShips Initial Values\n");
    int count;
    InitialConditionsEscort * escorts;

    escorts = loadEscortShip(&count);

    printf("---------------------------------------------------------------------------------------------------\n");
    printf("|%-10s|%-20s |%-15s|%-15s|%-10s|%-10s|%-10s|\n", "Index","Position","Max Velocity ","Min Velocity","Max Angle","Min Angle","type");

    printf("---------------------------------------------------------------------------------------------------\n");


    for (int i = 0; i < count; i++)
    {
        printf("|%-10d|%-10d %-10d|%-15.2f|%-15.2f|%-10.2f|%-10.2f|%-10.2s|\n", escorts[i].index, escorts[i].position.x, escorts[i].position.y, escorts[i].maxV, escorts[i].minV, escorts[i].maxA, escorts[i].minA, escorts[i].type);

    }
    

    printf("---------------------------------------------------------------------------------------------------\n");
    free(escorts);


}

void simulationStat()
{
    printf("----------------------\n");
    printf("Simulation Statistics\n");
    printf("----------------------\n");
    printf("\n");
    UserInput userInput = loadUserInput();

    printf("Canvas Size      :-  width: %d height: %d\n", userInput.canvas_size.x, userInput.canvas_size.y);
    printf("EscortShip Count :- %d\n", userInput.escort_count);
    printf("\n");
    printBattalianShipInitials();
    printf("\n");
    printBattalianLog();
    printf("\n");
    printEscortShipInitials();
    printf("\n");
    printEscortLog();

}

// int main()
// {
//     simulationStat();
// }