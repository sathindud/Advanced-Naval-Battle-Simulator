#include<stdlib.h>
#include<time.h>

void initializeRandom()
{
	srand(time(NULL));
}

float floatRandomNumber(float lower, float upper)
{
	float random = (float) rand() / (float) RAND_MAX;
        return random * (upper - lower) + lower;
}

//Genrate a integer random number
int  intRandomNumber(int lower, int upper)
{
        int num = (rand() % (upper - lower + 1)) + lower;
        return num;
} 
