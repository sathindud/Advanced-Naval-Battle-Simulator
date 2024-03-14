#include<stdlib.h>
#include<time.h>
#include<stdio.h>

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
		printf("%d\n", num);
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
