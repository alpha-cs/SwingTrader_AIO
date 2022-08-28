#include "db_const.h"

sql::Driver *driver;
sql::Connection *connect;
sql::PreparedStatement *stmt;
sql::ResultSet *result;

// exec db driver for partition
// Connect to database
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

// delete driver connection
void deleteDriver()
{
    delete connect;
}
