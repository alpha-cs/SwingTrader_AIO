#include "db_const.h"

sql::Driver *driver;
sql::Connection *connect;
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
        connect = driver->connect(HOST, USER, PASS);
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
    delete connect;
}
