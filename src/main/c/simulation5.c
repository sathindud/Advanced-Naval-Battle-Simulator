#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
#include<string.h>

#include "../header_files/structure.h"
#include "../header_files/random.h"
#include "../header_files/loadInitial.h"
#include "../header_files/saveSimulation.h"
#include "../header_files/simulationStat.h"
#include "../header_files/simulationHelper.h"
#include "../header_files/getShip.h"



/**
 * Time for each escort ship for attacking battalian
*/

Time * escortAttackTime(int * can_attack_count, int * escort_count,Coordinates battalian, InitialConditionsEscort * escort)
{
    //Creating the array
    Time * ship = (Time *)calloc(*escort_count, sizeof(Time));
    int count = 0;
    printf("escort :%d\n", *escort_count);

    //Looping each escort ship
    for (int i = 0; i < *escort_count; i++)
    {
        printf("escort :%d\n", escort[i].index);

        //finding the velocity for escort ship
        // float exact_velocity = floatRandomNumber(escort[i].minV, escort[i].maxV);
        float exact_velocity = escort[i].maxV;

        findMaxMinAngle(&escort[i].minA, &escort[i].maxA);
        // printf("escort angle min max:%f %f\n", escort[i].minA, escort[i].maxA);

        float ship_max_range = range(escort[i].maxA, exact_velocity);
        float ship_min_range = range(escort[i].minA,  exact_velocity);

        //Getting the distance between escort and battle ship 
        float distance = getDistance(escort[i].position, battalian);
        // printf("escort min max:%f %f\n", ship_max_range, ship_min_range);
        // printf("Distance:%f\n", distance);


        if(check(distance, ship_min_range, ship_max_range))
        {
            ship[count].index = escort[i].index;
            ship[count].time = calculateTime(exact_velocity, distance) + escort[i].time;
            count ++;
        }else
        {
            removeRowEscort(escort_count, escort, i);
            i--;
        }
    }
    *can_attack_count = count;
    *escort_count = count;
    return ship;
    
}
/**
 * Time for battalian to attack escort ships
*/

Time * battalianAttackTime(int * in_range_count ,int * escort_count, InitialConditionsBattalian battalian, InitialConditionsEscort * escort)
{
    Time * ship = (Time *)calloc(* escort_count, sizeof(Time));
    
    float ship_max_range = range(battalian.max_angle, battalian.maxV);
    int attack_count = 0;

    for (int i = 0; i < * escort_count; i++)
    {
        float distance = getDistance(battalian.position, escort[i].position);
        if (check(distance, 0, ship_max_range))
        {
            ship[attack_count].index = escort[i].index;
            ship[attack_count].time = calculateTime(battalian.maxV, distance) + battalian.time;
            // printf("ships: %d\n", ship[attack_count].index);
            removeRowEscort(escort_count, escort, i);
            attack_count ++;
        }
    }
    * in_range_count = attack_count;
    * escort_count = attack_count;
    return ship;
    
}

void eleminateEscort(int * attack_count, Time * escorts_time, int index)
{
    EscortShipsLog Elog;
    Elog.index = escorts_time[index].index;
    Elog.time = escorts_time[index].time;
    // printf("eleminated ships: %d\n", Elog.index);
    saveEscortLog(Elog);
    removeRowTime(attack_count, escorts_time, index);
}

void eleminateBattalian(int count, Time * battalian_time, int index)
{
    for (int i = 0; i < count; i++)
    {
        if (battalian_time[i].index == index)
        {       
            removeRowTime(&count, battalian_time, i);
        }
        
    }
    
}

// Function to swap two elements
void swapT(Time *x, Time *y) {
    Time temp = *x;
    *x = *y;
    *y = temp;
}
void swapE(InitialConditionsEscort *x, InitialConditionsEscort *y) {
    InitialConditionsEscort temp = *x;
    *x = *y;
    *y = temp;
}


void bubbleSort(int escort_count, Time * escort_time, InitialConditionsEscort * escort)
{
    for (int i = 0; i < escort_count - 1; i++) {
        for (int j = 0; j < escort_count - i - 1; j++) {
            if (escort_time[j].time > escort_time[j + 1].time) {
                swapT(&escort_time[j], & escort_time[j+1]);
                swapE(&escort[j], &escort[j + 1]);
            }
        }
    }
}

bool baseSimulation(InitialConditionsBattalian battalian, InitialConditionsEscort * escort_ships, float * health, int escort_count)
{
    if (!escortSimulation(escort_count, escort_ships, battalian.position, health))
    {
        int in_range_count = 0;
        Time * escorts_time = battalianAttackTime(&in_range_count, &escort_count, battalian, escort_ships);
        // for (int i = 0; i < in_range_count; i++)
        // {
        //         printf("%d, %f \n", escort_ships[i].index,  escorts_time[i].time);

        // }

        //Sorting the time in acending order
        bubbleSort(in_range_count, escorts_time, escort_ships);

        //elemenate it one by one
        while (in_range_count > 0)
        {
            eleminateEscort(&in_range_count, escorts_time,in_range_count - 1);
        }
        
        free(escorts_time);
        return true;
    }else{
        return false;
    }
}

void partA()
{
    int escort_ship_count = loadUserInput().escort_count;
    InitialConditionsEscort * escort_ships = loadEscortShip();
    InitialConditionsBattalian battalian = loadBattalianShip();

    resetLog(battalian);

    //rearranging the escortships according to time 

    float health = 0;

    //Running the simulation
    printf("Simulation is in Progress ...\n ");
    baseSimulation(battalian,escort_ships, &health, escort_ship_count);

    free(escort_ships);
    simulationStat();
}

void partB()
{
    int escort_ship_count = loadUserInput().escort_count;
    InitialConditionsEscort * escort_ships = loadEscortShip();
    InitialConditionsBattalian battalian = loadBattalianShip();

    resetLog(battalian);

    //rearranging the escortships according to time 

    float health = 0;
    Coordinates canvas_size = loadUserInput().canvas_size;
    
    Coordinates destination;
    destination.x = intRandomNumber(0, canvas_size.x);
    destination.y = intRandomNumber(0, canvas_size.y);

    //Running the simulation
    printf("Simulation is in Progress ...\n ");
    while (battalian.position.x != destination.x || battalian.position.y != destination.y)
    {
        if(baseSimulation(battalian,escort_ships, &health, escort_ship_count))
        {
            battalian.position = changeCoordinate(battalian.position, destination);
        }else
        {
            break;
        }

    }
    free(escort_ships);
    simulationStat();
}

void partC()
{
    int escort_ship_count = loadUserInput().escort_count;
    InitialConditionsEscort * escort_ships = loadEscortShip();
    InitialConditionsBattalian battalian = loadBattalianShip();

    resetLog(battalian);

    //rearranging the escortships according to time 

    float health = 100;
    Coordinates canvas_size = loadUserInput().canvas_size;
    
    Coordinates destination;
    destination.x = intRandomNumber(0, canvas_size.x);
    destination.y = intRandomNumber(0, canvas_size.y);

    //Running the simulation
    printf("Simulation is in Progress ...\n ");
    while (battalian.position.x != destination.x || battalian.position.y != destination.y)
    {
        if(baseSimulation(battalian,escort_ships, &health, escort_ship_count))
        {
            battalian.position = changeCoordinate(battalian.position, destination);
        }else
        {
            break;
        }

    }
    free(escort_ships);
    simulationStat();
}

void simulation5()
{
    printf("\n");
    printf("--------- Part 1 A  ------ \n");
    partA();
    printf("\n");
    printf("--------- Part 1 B  ------ \n");
    partB();
    printf("\n");
    printf("--------- Part 1 C  ------ \n");
    partC();

}

bool impactBattalian(float * health, InitialConditionsEscort escort, Coordinates battalian)
{
    BattalianShipLog Blog;
    Blog.position = battalian;
    Blog.escort_index = escort.index;

    if (*health > 0)
    {
        * health -= HEALTH * escort.impact_power;
        Blog.battaleship_status = 1;
        Blog.cumulative_impact = * health;
        saveBattalianLog(Blog);
        return true;

    }else{
        Blog.battaleship_status = 0;
        Blog.cumulative_impact = * health;
        saveBattalianLog(Blog);
        return false;
    }

}
/**
 * Remember there is two index
 * escort index and the array index
*/

bool baseEscortSimulation(InitialConditionsBattalian battalian, float * health, int  escort_count_for_battalian,InitialConditionsEscort * escorts1)
{
    //Duplicating array
    InitialConditionsEscort * escorts2 = (InitialConditionsEscort *)calloc(escort_count_for_battalian, sizeof(InitialConditionsEscort));
    for (int i = 0; i < escort_count_for_battalian; i++)
    {
        memcpy(&escorts2[i], &escorts1[i], sizeof(InitialConditionsEscort));

    }
    
    int escort_count_for_escorts = escort_count_for_battalian;

    
    int in_range_count = 0;
    Time * battalian_time = battalianAttackTime(&in_range_count, &escort_count_for_battalian, battalian, escorts1);

    //load the escort the work is finsh

    int can_attack_count = 0;
    Time * escort_time = escortAttackTime(&can_attack_count, &escort_count_for_escorts, battalian.position, escorts2);
    // printf("%d %d\n", * escort_count_for_battalian, escort_count_for_escorts);
    printf("1--%d %d\n", can_attack_count, in_range_count);


    //Sorting the time in acending order
    bubbleSort(in_range_count, battalian_time, escorts1);

    //elemenate it one by one

    //In First time
    for (int j = 0; j < can_attack_count; j++)
    {
        if (!impactBattalian(health, escorts2[j], battalian.position))
        {
            return false;
        }
                
    }

    if (in_range_count > 0)
    {
        eleminateBattalian(can_attack_count, escort_time, battalian_time[0].index);
        eleminateEscort(&in_range_count, battalian_time, 0);
    }else{
        // eleminateEscort(&in_range_count, battalian_time, 0);
        return true;
    }
    printf("2 --%d %d\n", can_attack_count, in_range_count);

    // printf("%d\n", in_range_count);

    
    // Loopinf until the battalinship destroy all escort ships in its range.
    while (in_range_count > 0 || can_attack_count > 0)
    {
        printf("Check\n");
        printf("3 --%d %d\n", can_attack_count, in_range_count);

        bool battalian_shoot = false;

        if (can_attack_count > 0)
        {
            for (int i = 0; i < in_range_count; i++)
            {
                for (int j = 0; j < can_attack_count; j++)
                {
                    if (battalian_time[i].time <= escort_time[j].time)
                    {
                        printf("????\n");
                        eleminateBattalian(can_attack_count, escort_time, battalian_time[i].index );
                        eleminateEscort(&in_range_count, battalian_time, i);
                        i--;
                        battalian_shoot = true;
                        break;
                    }else{
                        if (!impactBattalian(health, escorts2[j], battalian.position))
                        {
                            return false;
                        }
                    }

                    if (battalian_shoot)
                    {
                        break;
                    }
                    
                }           
            }
        }else{
            for (int i = 0; i < in_range_count; i++)
            {
                printf("h\n");
                eleminateEscort(&in_range_count, battalian_time, i);
            }        
            
        }
        
        
        // // Else Escort Ship can make a impackt
        // for (int j = 0; j < can_attack_count; j++)
        // {
        //     if (!impactBattalian(health, escorts2[j], battalian.position))
        //     {
        //         return false;
        //     }
            
        // }
        // printf("%d\n", in_range_count);

    }

    free(escorts2);
    free(battalian_time);
    free(escort_time);

    // free(escort_time);
    return true;
}

void part6A()
{
    //Loading inisial files
    InitialConditionsBattalian battalian = loadBattalianShip();
    InitialConditionsEscort * escorts = loadEscortShip();

    //Reseting the log file
    resetLog(battalian);

    //Loading User Inputs
    Coordinates canvas_size = loadUserInput().canvas_size;
    int escort_count = loadUserInput().escort_count;

    //finding the battlian ship range
    float battalianship_range = range(battalian.max_angle, battalian.maxV);

    float  health = 100;
    printf("Simulation is in Progress ...\n ");
    baseEscortSimulation(battalian, &health, escort_count, escorts);
    free(escorts);

    simulationStat();
}

void part6B()
{
    int escort_ship_count = loadUserInput().escort_count;
    InitialConditionsBattalian battalian = loadBattalianShip();
    InitialConditionsEscort * escorts = loadEscortShip();


    resetLog(battalian);

    //rearranging the escortships according to time 

    float health = 0;
    Coordinates canvas_size = loadUserInput().canvas_size;
    int escort_count = loadUserInput().escort_count;

    
    Coordinates destination;
    destination.x = intRandomNumber(0, canvas_size.x);
    destination.y = intRandomNumber(0, canvas_size.y);

    //Running the simulation
    printf("Simulation is in Progress ...\n ");
    while (battalian.position.x != destination.x || battalian.position.y != destination.y)
    {
        if(baseEscortSimulation(battalian, &health, escort_count, escorts))
        {
            battalian.position = changeCoordinate(battalian.position, destination);
        }else
        {
            break;
        }

    }
    free(escorts);

    simulationStat();
}

void part6C()
{
    int escort_ship_count = loadUserInput().escort_count;
    InitialConditionsBattalian battalian = loadBattalianShip();
    InitialConditionsEscort * escorts = loadEscortShip();



    resetLog(battalian);

    //rearranging the escortships according to time 

    float health = 100;
    Coordinates canvas_size = loadUserInput().canvas_size;
    int escort_count = loadUserInput().escort_count;

    
    Coordinates destination;
    // destination.x = intRandomNumber(0, canvas_size.x);
    // destination.y = intRandomNumber(0, canvas_size.y);
    destination.x = 15;
    destination.y = 15;

    //Running the simulation
    printf("Simulation is in Progress ...\n ");
    while (battalian.position.x != destination.x || battalian.position.y != destination.y)
    {
        if(baseEscortSimulation(battalian, &health, escort_count, escorts))
        {
            battalian.position = changeCoordinate(battalian.position, destination);
        }else
        {
            break;
        }
        printf("break\n");

    }
    free(escorts);

    simulationStat();
}


void simulation6()
{
    // printf("\n");
    // printf("--------- Part 1 A  ------ \n");
    // part6A();
    // printf("\n");
    // printf("--------- Part 1 B  ------ \n");
    // part6B();
    printf("\n");
    printf("--------- Part 1 C  ------ \n");
    part6C();
    // InitialConditionsBattalian battalian = loadBattalianShip();
    // InitialConditionsEscort * escorts = loadEscortShip();
    // int count= loadUserInput().escort_count;
    // int can_attack_count = 0;
    // Time * escort_time = escortAttackTime(&can_attack_count, &count, battalian.position, escorts);
    // printf("%d %d\n", can_attack_count, count );
}

void simulation7()
{
    //Loading inisial files
    InitialConditionsBattalian battalian = loadBattalianShip();
    InitialConditionsEscort * escorts = loadEscortShip();

    //Reseting the log file
    resetLog(battalian);

    //Loading User Inputs
    Coordinates canvas_size = loadUserInput().canvas_size;
    int escort_count = loadUserInput().escort_count;

    //finding the battlian ship range
    float battalianship_range = range(battalian.max_angle, battalian.maxV);

    //Creating a health for each escort ship
    float escort_health[escort_count];


    for (int i = 0; i < escort_count; i++)
    {
        escort_health[i] = floatRandomNumber(0 , 100);
    }

}


// int main()
// {
//     simulation5();
//     return 0;
// }