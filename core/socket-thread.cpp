#include "socket-thread.hpp"
#include "qendian.h"
#include "core/util.hpp"
SocketThread::SocketThread(int socketDescriptor):
    socketClient(new QTcpSocket())
{
    socketClient->setSocketDescriptor(socketDescriptor);
}

SocketThread::~SocketThread()
{
    emit disconnection(this);
}

void SocketThread::run()
{
    connect(socketClient, SIGNAL(readyRead()), this, SLOT(readyRead()),
            Qt::DirectConnection);
    connect(socketClient, SIGNAL(disconnected()), this, SLOT(disconnected()));
    exec();
}

void SocketThread::readyRead()
{
    QString request = read();
    if (request == "QUIT")
    {
        disconnected();
    }
    else
    {
        write("999");
    }
}

void SocketThread::disconnected()
{
    socketClient->deleteLater();
    quit();
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

