#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#include<stdbool.h>

#include"../header_files/structure.h"
//Initializing the random function
void initializeRandom()
{
	srand(time(NULL));
}

//Genrate a float random number

float floatRandomNumber(float lower, float upper)
{
	float random = (float) rand() / (float) RAND_MAX;
        return random * (upper - lower) + lower;
}

//Genrate a integer random number
int  intRandomNumber(int lower, int upper)
{
        int num = (rand() % (upper - lower + 1)) + lower;
		// printf("%d\n", num);
        return num;
}

/*
int main()
{
	initializeRandom();
	printf("%d\n", intRandomNumber(0, 10));
	return 0;
}
*/
