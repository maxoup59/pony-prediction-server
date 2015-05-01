#include <QCoreApplication>
#include "core/server.hpp"
#include <iostream>

Server server;
void catchUnixSignals(const std::vector<int>& quitSignals,
                      const std::vector<int>& ignoreSignals = std::vector<int>()) {

    auto handler = [](int sig) ->void {
        server.close();
        QCoreApplication::quit();
    };

    for ( int sig : ignoreSignals )
        signal(sig, SIG_IGN);
    for ( int sig : quitSignals )
        signal(sig, handler);
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    catchUnixSignals({SIGQUIT, SIGINT, SIGTERM, SIGHUP});
    if (!server.listen(QHostAddress::Any,50000)) {
        std::cout << "Unable to start the server: "
                  << server.errorString().toStdString()
                  << std::endl;
        return 0;
    }
    return a.exec();
}
