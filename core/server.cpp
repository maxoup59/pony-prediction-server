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
        listSocketThread[i]->quit();
        while (listSocketThread[i]->isRunning());
        delete listSocketThread[i];
    }
    Util::log("Server successfully close");
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    Util::log("Incoming Connection");
    SocketThread *socketThread = new SocketThread(socketDescriptor
                                                  ,&databaseManager);
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
    Util::log("Outgoing connection");
    //listSocketThread.removeOne(currentThread);
    if(listSocketThread.indexOf(currentThread) != -1)
        listSocketThread.removeAt(listSocketThread.indexOf(currentThread));
    Util::log(QString::number(listSocketThread.size()) + " Active Connection");
}

