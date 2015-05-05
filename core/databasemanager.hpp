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
    bool isConnected(){return connected;}
    QString getUserHash(QString username);
    bool getUserConfirmation(QString username);
    bool saveBrain(float ratio,int jobId,int userid);
    int getUserId(QString username);
    int getIdBestBrain(int idJob);
private:
    bool connected;
    bool connect();
    QString databaseName;
    QSqlDatabase database;
};

#endif // DATABASEMANAGER_H
