#include "socket-thread.hpp"
#include "qendian.h"
#include "core/util.hpp"
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrlQuery>
SocketThread::SocketThread(int socketDescriptor,
                           DatabaseManager * pDatabaseManager):
    socketClient(new QTcpSocket()),logged(false)
  ,downloadManager()
{
    socketClient->setSocketDescriptor(socketDescriptor);
    databaseManager = pDatabaseManager;
}

SocketThread::~SocketThread()
{
    socketClient->deleteLater();
    emit disconnection(this);
}

void SocketThread::run()
{
    connect(socketClient, SIGNAL(readyRead()), this, SLOT(readyRead()),
            Qt::DirectConnection);
    connect(socketClient, SIGNAL(disconnected()), this, SLOT(disconnect()));
    exec();
}

void SocketThread::readyRead()
{
    QString request = read();
    if(logged)
    {
        if(request == "HEY")
            write("Coucou");
    }
    else
    {
        if (request == "QUIT")
        {
            write("DISCONNECTED");
            disconnect();
        }
        else if(request.startsWith("LOG"))
        {
            downloadManager = new QNetworkAccessManager;
            QStringList split = request.split(" ");
            if(split.length() >= 3)
            {
                //QUrl url("http://ponyprediction.loicbourgois.com/php/scripts/check-password.php");
                QUrl url("http://localhost/passwordcheck.php");
                QUrlQuery postData;
                postData.addQueryItem("hash",
                                      databaseManager->getUserHash(split[1]));
                postData.addQueryItem("password", split[2]);
                connect(downloadManager, SIGNAL(finished(QNetworkReply*)),
                        this, SLOT(replyFinished(QNetworkReply*)));
                downloadManager->post(QNetworkRequest(url),
                                      postData.toString().toUtf8());
            }
        }
        else
        {
            write("999");
        }
    }
}

void SocketThread::disconnect()
{
    quit();
}

void SocketThread::replyFinished(QNetworkReply * reply)
{
    QString answer = reply->readAll();
    if(answer == "true")
    {
        logged=true;
        write("LOGGED");
    }
    else if(answer == "false")
    {
        write("BAD USERNAME OR PASSWORD");
    }
    else
    {
        write("Unknown error");
    }
    delete downloadManager;
}

QString SocketThread::read()
{
    QString request(socketClient->readAll());
    request = request.left(request.size()-2);
    return request;
}

bool SocketThread::write(QString answer)
{
    answer+="\n";
    QByteArray block;
    block.append(answer);
    if(socketClient->write(block)!= -1)
        return true;
    else
        return false;
}

