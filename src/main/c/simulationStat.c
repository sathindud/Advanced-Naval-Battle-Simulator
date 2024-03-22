#include<stdio.h>
#include<stdlib.h>

#include "../header_files/structure.h"
#include "../header_files/loadInitial.h"
#include "../header_files/getShip.h"
#include "../header_files/saveSimulation.h"

void printBattalianLog()
{
    printf("BattalianShip  Health Record \n");

    BattalianShipLog battalian;

    FILE * log;
    log = fopen("../../log/battalianship_log.dat", "r");
    if(log == NULL)
        printf("Cannot open battalian ship log");

    char line[100];
    fgets(line, sizeof(line), log);
    printf("------------------------------------------------------------------\n");
    printf("|%-10s |%-10s |%-20s|%-20s|\n", "Position","Status","Cumilative Impact", "EscortShip Index");
    printf("------------------------------------------------------------------\n");
    while (fgets(line, sizeof(line), log))
    {
        sscanf(line, "%d, %d, %d, %f, %d", &battalian.position.x, &battalian.position.y, &battalian.battaleship_status, &battalian.cumulative_impact, &battalian.escort_index);
        if (battalian.escort_index != -1)
        {
            if(battalian.escort_index == -2)
                printf("|%-5d %-5d|%-10d |%-20.2f|%-20s|\n", battalian.position.x, battalian.position.y, battalian.battaleship_status, battalian.cumulative_impact, "-");
            else
                printf("|%-5d %-5d|%-10d |%-20.2f|%-20d|\n", battalian.position.x, battalian.position.y, battalian.battaleship_status, battalian.cumulative_impact, battalian.escort_index);
        }
        
    }
    printf("-------------------------------------------------------------------\n");

    fclose(log);
}

void printEscortLog()
{
    printf("EscortShips Attack Order\n");

    EscortShipsLog escort;

    float total_time = 0;
    int count = 0;

    FILE * log;
    log = fopen("../../log/escortsship_log.dat", "r");
    if(log == NULL)
        printf("Cannot open escort ship log");

    char line[100];
    fgets(line, sizeof(line), log);
    printf("---------------------------------------------\n");
    printf("|%-20s |%-20s |\n", "EscortShip Index","Time to Hit");
    printf("---------------------------------------------\n");
    while (fgets(line, sizeof(line), log))
    {
        sscanf(line, "%d, %f", &escort.index, &escort.time);
        printf("|%-20d |%-20.2f |\n", escort.index, escort.time);
        total_time += escort.time;
        count ++;
        
    }
    printf("---------------------------------------------\n");

    printf("Attacked Escort Ship Count :- %d\n", count);
    printf("Total Time to end the battle :- %.2f s\n\n", total_time);

    fclose(log);
}

void printBattalianShipInitials()
{
    printf("BattalianShip Initials Values\n");

    InitialConditionsBattalian battalian;

    battalian = loadBattalianShip();

    printf("--------------------------------------\n");
    printf("|%-10s|%-10s |%-10s|\n", "Notation","Position","Max Velocity ");


    printf("--------------------------------------\n");

    printf("|%-10c|%-5d %-5d|%-10f|\n", battalian.type, battalian.position.x, battalian.position.y, battalian.maxV);

    printf("--------------------------------------\n");

} 

void printEscortShipInitials()
{
    printf("EscortShips Initial Values\n");
    int count = loadUserInput().escort_count;
    InitialConditionsEscort * escorts;

    escorts = loadEscortShip();

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


void resetLog(InitialConditionsBattalian battalian)
{
    BattalianShipLog initial;
    //Resetiing the log files before running the simulation
    initial.position = battalian.position;
    initial.battaleship_status = 1;
    initial.escort_index = -2;
    initial.cumulative_impact = HEALTH;
    resetBattalianLog(initial);
    resetEscortLog();
}

// int main()
// {
//     simulationStat();
// }