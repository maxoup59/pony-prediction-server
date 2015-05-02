#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include "core/databasemanager.hpp"
#include <QNetworkReply>

class SocketThread : public QThread
{
    Q_OBJECT
public:
    SocketThread(int socketDescriptor,DatabaseManager*);
    ~SocketThread();
    void run() Q_DECL_OVERRIDE;
public slots:
    void readyRead();
    void disconnect();
    void replyFinished(QNetworkReply*);
signals:
    void disconnection(SocketThread*);
private:
    QTcpSocket *socketClient;
    bool write(QString answer);
    QString read();
    bool logged;
    DatabaseManager* databaseManager;
                QNetworkAccessManager *downloadManager;
};

#endif // SOCKETTHREAD_H
