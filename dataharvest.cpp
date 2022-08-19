#include "dataharvest.h"
sql::Driver *driver;
sql::Connection *connect;
sql::PreparedStatement *stmt;
sql::ResultSet *result;

// init data harvest tool
void dataharvest()
{
    printf("\nInit Data Harvest");
    _LOG("\nConnector/C++ framework...");
    execDriver(); // begin
    query();
    harvest();
    deleteDriver(); // end
	

    // loop harvest tool
    // dataharvest();
}

// exec db driver for partition
void execDriver() {
    printf("\nConnecting to database");
    try
    {
        driver = get_driver_instance();
        connect = driver->connect(_HOST, _USER, _PASS);
    }
    catch (sql::SQLException& e)
    {
        printf("\nfail - dbConnect");
        std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
        system("pause");
        exit(1);
    }
    printf("\ndbConnect");
}


// delete driver connection
void deleteDriver() {
	printf("\nDelete Driver / Connection");
	delete connect;
}

// test db connection
void dbConnectTest()
{
    execDriver();
    printf("\npassed - dbConnect");
    deleteDriver();
}

// query select all from table
void query()
{
    printf("\nExec Query\n");


    // connect->setSchema("world");

    stmt = connect->prepareStatement("SELECT * FROM swingtraderdb.company");
    result = stmt->executeQuery();

    while (result->next())
        printf("\n%d, %s, %s, %d, %s, %d\n", result->getInt(1), result->getString(2).c_str(), result->getString(3).c_str(), result->getInt(4), result->getString(5).c_str(), result->getInt(6));

    delete result;
    delete stmt;
    delete connect;
}

// insert data into table
void inser() {
	
}

// Collect data from the internet
void harvest()
{
    printf("\nHarvesting Data ");
}