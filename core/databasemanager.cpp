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

QString DatabaseManager::getUserHash(QString username)
{
    if(connected)
    {
        QSqlQuery query;
        QString statement = "Select hash from users where username ='"
                + username
                + "';";
        query.prepare(statement);
        if(query.exec())
        {
            while(query.next())
            {
                QSqlRecord record = query.record();
                if(!record.value(record.indexOf("hash")).isNull())
                {
                    return record.value(record.indexOf("hash")).toString();
                }
            }
        }
    }
    else
    {
        Util::log("Not connected to the database");
    }
    return QString();
}

bool DatabaseManager::getUserConfirmation(QString username)
{
    if(connected)
    {
        QSqlQuery query;
        QString statement = "Select confirmed from users where username ='"
                + username
                + "';";
        query.prepare(statement);
        if(query.exec())
        {
            while(query.next())
            {
                QSqlRecord record = query.record();
                if(!record.value(record.indexOf("confirmed")).isNull())
                {
                    return record.value(record.indexOf("confirmed")).toInt();
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



