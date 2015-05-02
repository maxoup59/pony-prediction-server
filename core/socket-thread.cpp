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
  ,downloadManager(new QNetworkAccessManager())
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
            QStringList split = request.split(" ");
            if(split.length() == 3)
            {
                QUrl url("http://ponyprediction.loicbourgois.com/passwordcheck.php");
                QUrlQuery postData;
                postData.addQueryItem("hash", databaseManager->getUserHash(split[1]));
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
    //emit disconnection(this);
    quit();
}

void SocketThread::replyFinished(QNetworkReply * reply)
{
    //Contains pour le moment : /n en trop je pense
    // A remplacer par == après test
    QString answer = reply->readAll();
    if(answer.contains("true"))
    {
        write("LOGGED");
    }
    else if(answer.contains("false"))
    {
        write("BAD USERNAME OR PASSWORD");
    }
    else
    {
        write("Unknown error");
    }
}

QString SocketThread::read()
{
    QString request(socketClient->readAll());
    request = request.left(request.size()-2);
    return request;
}

bool SocketThread::write(QString answer)
{
    QByteArray block;
    block.append(answer);
    if(socketClient->write(block)!= -1)
        return true;
    else
        return false;
}

