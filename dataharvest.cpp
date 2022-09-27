#include "dataharvest.h"

extern sql::Driver *driver;
extern sql::Connection *connect;
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

// In the future change this to search thorugh a defined user profile. This way we can change
// which stocks we want and limit the memory size.
std::string *ticker = nullptr;
stockMarketData *marketData = nullptr;

/**
 * @brief dataharvest
 * @details This function will be used to harvest data from the internet and store it in the database.
 * This function will be called by the main function.
 *
 */
void dataharvest()
{
    _LOG("\nConnector/C++ framework...");
    printf("\nConnecting to database");
    execDriver(); // begin
    insertData();

    companySymbol();
    stockData();

    deleteDriver(); // end

    // loop harvest tool
    // dataharvest();
}

/**
 * @brief companySymbol
 * @details This function will search the database for the company symbol and store it in a
 *          dynamic array.
 * [out] ticker - dynamic array of company symbols
 */
void companySymbol()
{
    try
    {
        stmt = connect->prepareStatement("SELECT * FROM " + STdb + ".company");
        result = stmt->executeQuery();
        ticker = new std::string[result->rowsCount()];
        for (int i = 0; result->next(); i++)
        {
            ticker[i] = result->getString(3);
            printf("\n%s", ticker[i]);
        }
    }
    catch (sql::SQLException &e)
    {
        printf("\nfail - execQuery");
        std::cout << "Err: " << e.what() << std::endl;
        system("pause");
        exit(1);
    }
}

/**
 * @brief stockData
 * @details This function will search the database for the company symbol and store it in a
 *          dynamic array.
 * [out] marketData - dynamic array of stock market data
 */
void stockData()
{
    try
    {
        stmt = connect->prepareStatement("SELECT * FROM " + STdb + ".stockdata");
        result = stmt->executeQuery();
        marketData = new stockMarketData[result->rowsCount()];
        for (int i = 0; result->next(); i++)
        {
            marketData[i].id = result->getInt("id");
            marketData[i].ticker = result->getString("ticker");
            marketData[i].datetime = result->getString("date");
            marketData[i].open = result->getDouble("open");
            marketData[i].close = result->getDouble("close");
            marketData[i].high = result->getDouble("high");
            marketData[i].low = result->getDouble("low");
            marketData[i].volume = result->getInt("volume");
            marketData[i].dividends = result->getDouble("dividends");
            marketData[i].stocksplit = result->getInt("stocksplit");
            printf("\n%d %s %s %f %f %f %f %d %f %d", marketData[i].id, marketData[i].ticker.c_str(), marketData[i].datetime.c_str(), marketData[i].open, marketData[i].close, marketData[i].high, marketData[i].low, marketData[i].volume, marketData[i].dividends, marketData[i].stocksplit);
        }
    }
    catch (sql::SQLException &e)
    {
        printf("\nfail - stockData.");
        std::cout << "Err: " << e.what() << std::endl;
        system("pause");
        exit(1);
    }
}

/**
 * We need to get user input as string
 * store it in unordered_map
 *      if it doesnt exist in stockData
 *      if it doesnt exist in newcompanydb
 *      if it doesnt exist in unordered_map
 * once while (!exit) loop ends
 * insert data into insertData()
 *      loop in-till all the new data from unordered_map has been insereted into newcompany
 * pause program
 * promt to restart harvester
 */