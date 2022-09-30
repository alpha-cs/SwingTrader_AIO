#ifndef DB_CONST_H
#define DB_CONST_H

#pragma once
#include "constants.h"
/*
  Include directly the different
  headers from cppconn/ and mysql_driver.h + mysql_util.h
  (and mysql_connection.h). This will reduce your build time!
*/
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

// for demonstration only. never save password in the code!
#define HOST "localhost" // server host
#define USER "root"		 // server user
#define PASS "5662"		 // server password | This is my name in number format. :)

#define SWINGTRADER_DB "swingtraderdb" // database name
#define HISTORY_DB "pricehistory"	   // database name

void execDriver();
void deleteDriver();
void system_SwingTrader_py();

// exchange_id enum of us exchanges
enum exchange_id
{
	NASDAQ = 0,	   // NASDAQ
	NYSE,		   // NYSE
	AMEX,		   // AMEX
	sizeofExchange // size of exchange_id
};

#endif // DB_CONST_H