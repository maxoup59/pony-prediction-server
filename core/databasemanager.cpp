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

bool DatabaseManager::saveBrain(float ratio, int jobId, int userId)
{
    bool retour = false;
    if(connected)
    {
        QSqlQuery query;
        QString statement = "INSERT INTO brains(ratio,jobId,userId) "
                            "VALUES(:ratio,:jobId,:userId);";

        query.prepare(statement);
        query.bindValue(":ratio",ratio);
        query.bindValue(":jobId",jobId);
        query.bindValue(":userId",userId);
        if(!query.exec())
        {
            retour = true;
            Util::log("Error when saving brain");
        }
    }
    else
    {
        Util::log("Not connected to the database");
    }
    return retour;
}

int DatabaseManager::getUserId(QString username)
{
    if(connected)
    {
        QSqlQuery query;
        QString statement = "Select id from users where username "
                            "= :username;";
        query.prepare(statement);
        query.bindValue(":username",username);
        if(query.exec())
        {
            while(query.next())
            {
                QSqlRecord record = query.record();
                if(!record.value(record.indexOf("id")).isNull())
                {
                    return record.value(record.indexOf("id")).toInt();
                }
            }
        }
    }
    else
    {
        Util::log("Not connected to the database");
    }
    return -1;
}

int DatabaseManager::getIdBestBrain(int idJob)
{
    if(connected)
    {
        QSqlQuery query;
        QString statement = "Select idBestBrain from jobs;";
        query.prepare(statement);
        if(query.exec())
        {
            while(query.next())
            {
                QSqlRecord record = query.record();
                if(!record.value(record.indexOf("idBestBrain")).isNull())
                {
                    return record.value(record.indexOf("idBestBrain")).toInt();
                }
            }
        }
    }
    else
    {
        Util::log("Not connected to the database");
    }
    return -1;
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



