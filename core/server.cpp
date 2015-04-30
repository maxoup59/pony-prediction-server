#include "server.hpp"

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
    SocketThread *socketThread = new SocketThread(socketDescriptor);
    QObject::connect(socketThread, SIGNAL(finished()), socketThread, SLOT(deleteLater()));
    listSocketThread.push_back(socketThread);
    socketThread->start();
}

