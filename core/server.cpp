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
    QObject::connect(socketThread,SIGNAL(disconnection(SocketThread*))
                     ,this,SLOT(onDisconnection(SocketThread*)));
    listSocketThread.push_back(socketThread);
    socketThread->start();
    Util::log(QString::number(listSocketThread.size()) + " Active Connection");
}

void Server::onDisconnection(SocketThread * currentThread)
{
    Util::log("Disconnection");
    listSocketThread.removeOne(currentThread);
    Util::log(QString::number(listSocketThread.size()) + " Active Connection");
}

