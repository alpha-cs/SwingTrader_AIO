#include "dataharvest.h"
sql::Driver *driver;
sql::Connection *connect;
sql::PreparedStatement *stmt;
sql::ResultSet *result;

// init data harvest tool
void dataharvest()
{
    _LOG("\nConnector/C++ framework...");
    printf("\nConnecting to database");
    execDriver();      // begin
    query();           // query database
    insert();          // insert data
    query();           // query database
    deleteFromTable(); // delete data from table
    harvest();         // harvest data
    deleteDriver();    // end

    // loop harvest tool
    // dataharvest();
}

// exec db driver for partition
// Connect to database
void execDriver()
{
    try
    {
        driver = get_driver_instance();
        connect = driver->connect(_HOST, _USER, _PASS);
        // connect->setSchema("swingtraderdb");
    }
    catch (sql::SQLException &e)
    {
        printf("\nfail - dbConnect");
        std::cout << "Err: " << e.what() << std::endl;
        system("pause");
        exit(1);
    }
    // printf("\ndbConnect");
}

// delete driver connection
void deleteDriver()
{
    delete connect;
}

// query select all from table
void query()
{
    stmt = connect->prepareStatement("SELECT * FROM swingtraderdb.company");
    result = stmt->executeQuery();

    // while (result->next())
    //     printf("\n%d, %s, %s, %d, %s, %d\n", result->getInt(1), result->getString(2).c_str(), result->getString(3).c_str(), result->getInt(4), result->getString(5).c_str(), result->getInt(6));
}

// insert data into table
void insert()
{
    try
    {
        stmt = connect->prepareStatement("INSERT INTO swingtraderdb.company (id, name, ticker, exchange_id, marketcap, flag) VALUES (?, ?, ?, ?, ?, ?)");
        stmt->setInt(1, 99999);          // id
        stmt->setString(2, "test .inc"); // name
        stmt->setString(3, "test");      // ticker
        stmt->setInt(4, 1);              // exchange_id
        stmt->setString(5, "1.2T");      // marketcap
        stmt->setInt(6, 1);              // flag
        stmt->executeUpdate();           // execute
    }
    catch (sql::SQLException &e)
    {
        printf("\nfail - insert");
        std::cout << "\nErr: " << e.what() << std::endl;
        system("pause");
        exit(1);
    }
    delete stmt;
}

// delete data from table
void deleteFromTable()
{
    try
    {
        stmt = connect->prepareStatement("DELETE FROM swingtraderdb.company WHERE id = ?");
        stmt->setInt(1, 99999);
        stmt->executeUpdate();
    }
    catch (sql::SQLException &e)
    {
        printf("\nfail - delete");
        std::cout << "\nErr: " << e.what() << std::endl;
        system("pause");
        exit(1);
    }
    delete stmt;
}

// Collect data from the internet
void harvest()
{
}

// test db connection
// remake connection with no prints
void dbConnectTest()
{
    try
    {
        execDriver();
        query();
        insert();
        deleteFromTable();
    }
    catch (const std::exception &e)
    {
        std::cout << "\nErr: " << e.what() << std::endl;
    }
    printf("\npassed - dbConnect");
    deleteDriver();
}