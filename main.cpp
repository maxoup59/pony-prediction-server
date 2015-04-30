#include <QCoreApplication>
#include <QDEBUG>
#include "core/server.hpp"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Server server;
    if (!server.listen(QHostAddress::Any,50002)) {
        qDebug() << "Unable to start the server: " << server.errorString();
    }
    return a.exec();
}
