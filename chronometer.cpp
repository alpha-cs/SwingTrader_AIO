// This function is used to measure the time
#include "chronometer.h"

int *start = nullptr;
int *now = new int;
int *last = new int;
int *end = nullptr;

// this function is used to keep time of compile time
void compileTime()
{
    printf("\nDate: %s", __DATE__);
    printf("\nTime: %s\n", __TIME__);
}

// this function begins run time only
void startRunTime()
{
    start = (int *)malloc(sizeof(int));
    *start = clock();
}

// this function calculated run time
void endRunTime()
{
    end = (int *)malloc(sizeof(int));
    *end = clock();
    printf("\nRun Time: %d", *end - *start);
    delete start;
    delete end;
    start = nullptr;
    end = nullptr;
}

int getnow()
{
    *now = clock();
    return *now;
}