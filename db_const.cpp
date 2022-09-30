#include "db_const.h"

sql::Driver *driver;
sql::Connection *connectSql;
sql::PreparedStatement *stmt;
sql::ResultSet *result;

/**
 * @brief dbConnectTest
 * @details This function is used for initializating the connection to the database.
 */
void execDriver()
{
    try
    {
        driver = get_driver_instance();
        connectSql = driver->connect(HOST, USER, PASS);
        // connect->setSchema("swingtraderdb");
    }
    catch (sql::SQLException &e)
    {
        printf("\nfail - dbConnect");
        std::cout << "Err: " << e.what() << std::endl;
        system("pause");
        exit(1);
    }
    printf("\ndbConnect\n");
    printf("\n==============================\n");
}

/**
 * @brief dbConnectTest
 * @details This function is used to terminate the connection to the database.
 */
void deleteDriver()
{
    delete connectSql;
}

/**
 * @brief system
 * @details This function will harvest the data from the yahoo finance website.
 */
void system_SwingTrader_py()
{
    system("start cmd /k D:\\_Programs\\Swing_Trader_Scraper\\main.py");
    MessageBox(nullptr, TEXT("Sleeping for 1 minute\nUpdating Database"), TEXT("SwingTrader.AIO"), MB_ICONEXCLAMATION | MB_OK);
}
