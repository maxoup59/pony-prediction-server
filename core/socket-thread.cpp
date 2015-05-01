#include "socket-thread.hpp"
#include "qendian.h"
#include "core/util.hpp"
SocketThread::SocketThread(int socketDescriptor):
    socketClient(new QTcpSocket()),logged(false)
{
    socketClient->setSocketDescriptor(socketDescriptor);
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
            write("Disconnected");
            disconnect();
        }
        else if(request.startsWith("LOG"))
        {
            logged = true;
            write("Logged");
        }
        else
        {
            write("999");
        }
    }
}

void SocketThread::disconnect()
{
    emit disconnection(this);
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

