#include "server.hpp"
#include <iostream>
#include "core/util.hpp"
Server::Server()
{

}

Server::~Server()
{
    for(int i = 0 ; i < listSocketThread.size() ; i++)
    {
        listSocketThread[i]->deleteLater();
    }
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    Util::log("Incoming Connection");
    SocketThread *socketThread = new SocketThread(socketDescriptor);
    QObject::connect(socketThread, SIGNAL(finished())
                     ,socketThread, SLOT(deleteLater()));
    QObject::connect(socketThread,SIGNAL(deconnection(SocketThread*))
                     ,this,SLOT(onDeconnection(SocketThread*)));
    listSocketThread.push_back(socketThread);
    socketThread->start();
    Util::log(QString::number(listSocketThread.size()) + " Active Connection");
}

void Server::onDeconnection(SocketThread * currentThread)
{
    Util::log("Deconnection");
    listSocketThread.removeOne(currentThread);
    Util::log(QString::number(listSocketThread.size()) + " Active Connection");
}

