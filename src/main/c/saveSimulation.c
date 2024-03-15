#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#include "../header_files/structure.h"

// char * getTime()
// {
//     char * format_time = (char *)malloc(30);

//     time_t rawtime;
//     time (&rawtime);
//     sprintf(format_time,"%s",ctime(&rawtime) );

//     return format_time;
// }

void resetBattalianLog()
{
    FILE *log;
    log = fopen("../../log/battaloanship_log.dat", "w");
    fprintf(log, "Battalian.x, Battalian.y, status, Hitted_escort_index\n");
    fclose(log);
}

void saveBattalianLog(BattalianShipLog details)
{
    FILE *log;
    log = fopen("../../log/battaloanship_log.dat", "a");

    if(log == NULL)
        printf("Cannot open the log file\n");

    fprintf(log, "%d, %d, %d, %d\n", details.position.x, details.position.y, details.battaleship_status, details.escort_index);
    fclose(log);
}
void resetEscortLog()
{
    FILE *log;
    log = fopen("../../log/escortsship_log.dat", "w");
    fprintf(log, "index, time_to_hit\n");
    fclose(log);

}

void saveEscortLog(EscortShipsLog details)
{
    FILE *log;
    log = fopen("../../log/escortsship_log.dat", "a");

    if(log == NULL)
        printf("Cannot open the log file\n");
    
    
    fprintf(log, "%d, %f\n", details.index, details.time);
    
    fclose(log);
    
}
