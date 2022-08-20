// This function is used to measure the time
#include "chronometer.h"

#define SECONDS_PER_MINUTE = 60;
#define SECONDS_PER_HOUR = SECONDS_PER_MINUTE * 60;
#define SECONDS_PER_DAY = SECONDS_PER_HOUR * 24;

int *start = nullptr;
int *end = nullptr;

// this function is used to keep time of compile time
void compileTime()
{
    printf("\nDate: %s", __DATE__);
    printf("\nTime: %s", __TIME__);
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