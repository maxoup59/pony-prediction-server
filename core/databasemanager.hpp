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
private:
    bool connected;
    bool connect();
    QString databaseName;
    QSqlDatabase database;
};

#endif // DATABASEMANAGER_H
