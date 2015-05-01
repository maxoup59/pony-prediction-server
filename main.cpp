#include <QCoreApplication>
#include "core/server.hpp"
#include <iostream>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Server server;
    if (!server.listen(QHostAddress::Any,50000)) {
        std::cout << "Unable to start the server: "
                  << server.errorString().toStdString()
                  << std::endl;
        return 0;
    }
    return a.exec();
}
