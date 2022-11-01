#include "dataharvest.h"

// In the future change this to search thorugh a defined user profile. This way we can change
// which stocks we want and limit the memory size.
std::string *ticker = nullptr;
std::string *newCompanyTicker = nullptr;
int tickerSize = 0;
int newTickerSize = 0;
stockMarketData *marketData = nullptr;

/**
 * @brief dataharvest
 * @details This function will be used to harvest data from the internet and store it in the database.
 * This function will be called by the main function.
 *
 */
void dataharvest()
{
    execDriver(); // begin connection to database

    companySymbol();
    newCompanySymbol();

    userInputData();

    stockData();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    deleteDriver(); // end connection to database

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
        stmt = connectSql->prepareStatement("SELECT * FROM " + STdb + ".company");
        result = stmt->executeQuery();
        ticker = new std::string[result->rowsCount()];
        for (int i = 0; result->next(); i++)
        {
            ticker[i] = result->getString(3);
            tickerSize++;
            // printf("\n%s", ticker[i]);
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
 * @brief newCompanySymbol
 * @details This function will search the database for the company symbol and store it in a
 *          dynamic array.
 * [out] newCompanyTicker - dynamic array of company symbols
 */
void newCompanySymbol()
{
    try
    {
        stmt = connectSql->prepareStatement("SELECT * FROM " + STdb + ".newcompany");
        result = stmt->executeQuery();
        newCompanyTicker = new std::string[result->rowsCount()];
        for (int i = 0; result->next(); i++)
        {
            newCompanyTicker[i] = result->getString(1);
            newTickerSize++;
            // printf("\n%s", newCompanyTicker[i]);
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
        stmt = connectSql->prepareStatement("SELECT * FROM " + STdb + ".stockdata");
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
            // printf("\n%d %s %s %f %f %f %f %d %f %d", marketData[i].id, marketData[i].ticker.c_str(), marketData[i].datetime.c_str(), marketData[i].open, marketData[i].close, marketData[i].high, marketData[i].low, marketData[i].volume, marketData[i].dividends, marketData[i].stocksplit);
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
 * @brief insertData
 * @details This function will insert data into the database.
 * [in] userInputList - list of user input data
 */
void insertData(std::list<std::string> userInputList)
{
    try
    {
        stmt = connectSql->prepareStatement("INSERT INTO " + STdb + ".newcompany (ticker) VALUES (?)");
        for (std::string userInput : userInputList)
        {
            stmt->setString(1, userInput);
            stmt->executeUpdate();
        }
    }
    catch (sql::SQLException &e)
    {
        printf("\nfail - insertData.");
        std::cout << "Err: " << e.what() << std::endl;
        system("pause");
        exit(1);
    }
}

/**
 * @brief userInputData
 * @details This function will ask the user for input and store it in a list.
 * [out] userInputList - list of user input data
 */
void userInputData()
{
    std::list<std::string> *userInputList = nullptr;
    std::list<std::string> *dupe = nullptr;
    dupe = new std::list<std::string>;

    for (int i = 0; i < tickerSize; i++)
    {
        dupe->push_back(ticker[i]);
    }
    for (int i = 0; i < newTickerSize; i++)
    {
        dupe->push_back(newCompanyTicker[i]);
    }

    userInputList = new std::list<std::string>;
    bool exit = false;
    printf("\nPlease enter a company symbol to add to the database. (Enter '0' to 0.)");
    while (!exit)
    {
        printf("\nEnter a company symbol: ");
        std::string userStr;
        std::cin >> userStr;
        if (userStr == "0")
        {
            exit = true;
        }
        else
        {
            if (std::find(dupe->begin(), dupe->end(), userStr) != dupe->end())
            {
                std::cout << "Duplicate company symbol found.\n";
            }
            else
            {
                userInputList->push_back(userStr);
            }
        }
    }
    if (userInputList != nullptr)
    {
        insertData(*userInputList);
    }

    system_SwingTrader_py(); // call python script
    printf("\nSleeping for 30 seconds...\nPlease Wait...");
    std::this_thread::sleep_for(std::chrono::seconds(30));
    delete userInputList;
}
