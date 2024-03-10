#include<stdlib.h>
#include<time.h>

float floatRandomNumber(float lower, float upper)
{
	srand(time(NULL));
	float random = (float) rand() / (float) RAND_MAX;
        return random * (upper - lower) + lower;
}

//Genrate a integer random number
int  intRandomNumber(int lower, int upper)
{
	srand(time(NULL));
        int num = (rand() % (upper - lower + 1)) + lower;
        return num;
} 
