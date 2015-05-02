#include "databasemanager.hpp"
#include "core/util.hpp"
#include <QSqlRecord>
DatabaseManager::DatabaseManager():
    connected(false),
    databaseName(Util::getLineFromConf("databaseName")),
    database()
{
    connect();
}

DatabaseManager::~DatabaseManager()
{

}

bool DatabaseManager::checkUser(QString username, QString hash)
{
    if(connected)
    {
        QSqlQuery query;
        QString statement = " SELECT COUNT(*) nb FROM users where username='"
                + username
                + "' AND hash='"
                + hash
                + "';";
        query.prepare(statement);
        if(query.exec())
        {
            while(query.next())
            {
                QSqlRecord record = query.record();
                if(record.value(record.indexOf("nb")).toInt() != 0)
                {
                    Util::log("User " + username + " just logged in");
                    return true;
                }
            }
        }
    }
    else
    {
        Util::log("Not connected to the database");
    }
    return false;
}

bool DatabaseManager::connect()
{
    bool ok = true;
    QString error = "";
    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("localhost");
    database.setUserName(Util::getLineFromConf("username"));
    database.setPassword(Util::getLineFromConf("password"));
    database.setDatabaseName(Util::getLineFromConf("databaseName"));
    if(!database.open() || !database.isValid())
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



