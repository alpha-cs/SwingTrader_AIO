#ifndef DATAHARVEST_H
#define DATAHARVEST_H
#pragma once

#include <stdio.h>
#include "db_const.h"
#include "constants.h"

void dataharvest();
void companySymbol();
void stockData();

void dbConnectTest(); // used for testing

#endif // DATAHARVEST_H