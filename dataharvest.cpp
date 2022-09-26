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

// init data harvest tool
void dataharvest()
{
    _LOG("\nConnector/C++ framework...");
    printf("\nConnecting to database");
    execDriver(); // begin

    companySymbol();
    stockData();

    deleteDriver(); // end

    // loop harvest tool
    // dataharvest();
}

// Get Stock ticker symbol
// [in] SELECT * FROM " + STdb + ".company
// [] ticker
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