#include "server.hpp"
#include <iostream>
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
    std::cout << "Incoming connection"
              << std::endl;
    SocketThread *socketThread = new SocketThread(socketDescriptor);
    QObject::connect(socketThread, SIGNAL(finished())
                     ,socketThread, SLOT(deleteLater()));
    QObject::connect(socketThread,SIGNAL(deconnection(SocketThread*))
                     ,this,SLOT(onDeconnection(SocketThread*)));
    listSocketThread.push_back(socketThread);
    socketThread->start();
    std::cout << listSocketThread.size()
    << " Active Connection"
    << std::endl;
}

void Server::onDeconnection(SocketThread * currentThread)
{
    std::cout << "Deconnection" << std::endl;
   //currentThread->deleteLater();
    listSocketThread.removeOne(currentThread);
    std::cout << listSocketThread.size()
    << " Active Connection"
    << std::endl;
}

