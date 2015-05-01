#include "socket-thread.hpp"
#include "qendian.h"
SocketThread::SocketThread(int socketDescriptor):
    socketClient(new QTcpSocket())
{
    socketClient->setSocketDescriptor(socketDescriptor);
}

SocketThread::~SocketThread()
{
    emit deconnection(this);
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
    write(read());
}

void SocketThread::disconnected()
{
    socketClient->deleteLater();
    quit();
}

QString SocketThread::read()
{
    return QString(socketClient->readAll());
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

