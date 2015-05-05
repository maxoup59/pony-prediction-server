#include <QCoreApplication>
#include "core/server.hpp"
#include <iostream>
#include "core/util.hpp"
#include <signal.h>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Util::initConfigFilePath(&a);
    Server server;
    Util::init(&a,&server);

#ifdef  _WIN32
    Util::log("Cannot handle ctrl+C : you're on windows... Sucker !");
#else
    Util::catchUnixSignals({SIGQUIT, SIGINT, SIGTERM, SIGHUP});
#endif

    if (!server.listen(QHostAddress::Any,
                       Util::getLineFromConf("port").toInt())) {
        Util::log("Unable to start the server: " + server.errorString());
        return 0;
    }
    else
    {
        Util::log("Server started on : " +
                  QString::number(server.serverPort()) + " !");
    }
    return a.exec();
}
