/*2022 - August 13
f6376707-afcc-4557-ba34-012396803d6b

A C/C++ project by alpha
*/

// lib
#include <stdio.h>
// multithread partitions
#include "chronometer.h"
#include "dataharvest.h"


int main()
{

    compileTime();
    startRunTime();

    // test
    // test();

    printf("\nInitializing program ...");

    // partitions
    dataharvest();

    endRunTime();
    return 0;
}
