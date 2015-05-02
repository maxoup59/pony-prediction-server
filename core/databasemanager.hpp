#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class DatabaseManager
{
public:
    DatabaseManager();
    ~DatabaseManager();
    bool checkUser(QString username,QString password);
    bool isConnected(){return connected;}
private:
    bool connected;
    bool connect();
    QString databaseName;
    QSqlDatabase database;
};

#endif // DATABASEMANAGER_H
