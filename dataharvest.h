#ifndef DATAHARVEST_H
#define DATAHARVEST_H
#pragma once

#include <stdio.h>
#include "db_const.h"
#include "constants.h"
#include "datalogger.h"

void dataharvest();

void execQuery();
void harvest();
void dbConnectTest(); // used for testing

#endif // DATAHARVEST_H