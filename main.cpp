/*2022 - August 13
f6376707-afcc-4557-ba34-012396803d6b

A C/C++ project by alpha
*/

// lib
#include <stdio.h>
#include "chronometer.h"
#include "dataharvest.h"
#include <thread>

int now = getnow();
int last = getnow();
int delay = HOURS;

int main()
{

    compileTime();
    startRunTime();

    // Request data from the internet and update the database with user input
    dataharvest();

    // Thread 1 Update db every hour
    std::thread updateExternIO([]()
                               {
        while (true)
        {
            now = getnow();
            if (now - last >= (delay))
            {
                system_SwingTrader_py();
                last = now;
            }
        } });
    updateExternIO.join();
    // Thread 2 Run calculations every second to determine when to buy/sell

    endRunTime();
    return 0;
}
