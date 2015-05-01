#include "databasemanager.hpp"
#include "core/util.hpp"
DatabaseManager::DatabaseManager():
    connected(false),
    databaseName(Util::getLineFromConf("databaseName")),
    database()
{

}

DatabaseManager::~DatabaseManager()
{

}

bool DatabaseManager::connect()
{
    bool ok = true;
    QString error = "";
    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("localhost");
    database.setUserName(Util::getLineFromConf("username"));
    database.setPassword(Util::getLineFromConf("password"));
    database.setDatabaseName(databaseName);
    if(ok && !database.open())
    {
      ok = false;
      error = "Couldn't connect to database (" + databaseName + ") "
          + database.lastError().text();
    }
    if(!ok)
    {
      Util::log("ERROR: " + error);
      database.close();
    }
    else if(ok)
    {
      Util::log("Connected to database (" + databaseName + ")");
    }
    connected = ok;
    return ok;
}

