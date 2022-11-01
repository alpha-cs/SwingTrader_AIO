// This function is used to measure the time
#ifndef CRONOMETRO_H
#define CRONOMETRO_H

#pragma once

#include <stdio.h>
#include <cstdlib>
#include <time.h>

#define SECONDS 1000;
#define MINUTES 60000;
#define HOURS 3600000;
#define DAYS 86400000;

// make a define that takes in x for seconds and returns x * 1000

void compileTime();
void startRunTime();
void endRunTime();
int getnow();

#endif // CRONOMETRO_H