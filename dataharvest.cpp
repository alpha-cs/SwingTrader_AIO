#include "dataharvest.h"
sql::Driver *driver;
sql::Connection *connect;
sql::PreparedStatement *stmt;
sql::ResultSet *result;

// init data harvest tool
void dataharvest()
{
    printf("\nInit Data Harvest");
    query();
    harvest();

    // loop harvest tool
    // dataharvest();
}

// connect to database
void dbConnect()
{
    printf("\nConnecting to database");
    try
    {
        driver = get_driver_instance();
        connect = driver->connect(_HOST, _USER, _PASS);
    }
    catch (sql::SQLException &e)
    {
        std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
        system("pause");
        exit(1);
    }
    printf("\npassed - dbConnect");
    delete connect;
}

// this function is used to query the database
void query()
{
    _LOG("\nConnector/C++ framework...");
    printf("\nExec Query\n");

    try
    {
        driver = get_driver_instance();
        connect = driver->connect(_HOST, _USER, _PASS);
    }
    catch (sql::SQLException &e)
    {
        /*
          MySQL Connector/C++ throws three different exceptions:

          - sql::MethodNotImplementedException (derived from sql::SQLException)
          - sql::InvalidArgumentException (derived from sql::SQLException)
          - sql::SQLException (derived from std::runtime_error)
        */
        std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
        system("pause");
        exit(1);
    }

    // connect->setSchema("world");

    stmt = connect->prepareStatement("SELECT * FROM swingtraderdb.company");
    result = stmt->executeQuery();

    while (result->next())
        printf("\n%d, %s, %s, %d, %s, %d\n", result->getInt(1), result->getString(2).c_str(), result->getString(3).c_str(), result->getInt(4), result->getString(5).c_str(), result->getInt(6));

    delete result;
    delete stmt;
    delete connect;
}

// Collect data from the internet
void harvest()
{
    printf("\nHarvesting Data ");
}