#include "dataharvest.h"

extern sql::Driver *driver;
extern sql::Connection *connect;
extern sql::PreparedStatement *stmt;
extern sql::ResultSet *result;
const std::string db = DB;

std::string *ticker = nullptr;

// init data harvest tool
void dataharvest()
{
    _LOG("\nConnector/C++ framework...");
    printf("\nConnecting to database");
    execDriver(); // begin

    execQuery();

    deleteDriver(); // end

    // loop harvest tool
    // dataharvest();
}

void execQuery()
{
    try
    {
        stmt = connect->prepareStatement("SELECT * FROM " + db + ".company");
        result = stmt->executeQuery();
        ticker = new std::string[result->rowsCount()];
        for (int i = 0; result->next(); i++)
        {
            ticker[i] = result->getString(3).c_str();
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
