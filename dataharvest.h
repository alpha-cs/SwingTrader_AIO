#ifndef DATAHARVEST_H
#define DATAHARVEST_H
#pragma once

#include <chrono> // for sleep_for // will be replaceced with chromo function
#include <thread> // for sleep_for // will be replaceced with chromo function
#include "chronometer.h"
#include "db_const.h"  // for database connection
#include "constants.h" // for constants library

void dataharvest();
void companySymbol();
void newCompanySymbol();
void stockData();
void insertData(std::list<std::string> userInputList);
void userInputData();

void dbConnectTest(); // used for testing

extern sql::Driver *driver;
extern sql::Connection *connectSql;
extern sql::PreparedStatement *stmt;
extern sql::ResultSet *result;

const std::string STdb = SWINGTRADER_DB;
const std::string PHdb = HISTORY_DB;

struct stockMarketData
{
    int id;
    std::string ticker, datetime;
    float open, close, high, low;
    int volume;
    float dividends;
    int stocksplit;
};

#endif // DATAHARVEST_H