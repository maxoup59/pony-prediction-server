#include "util.hpp"
#include <iostream>
#include <QString>
#include <QThread>
#include <QFile>
#include <QXmlStreamReader>
#include <QCoreApplication>
#include <signal.h>

Server * Util::server = nullptr;
QCoreApplication *Util::app = nullptr;

QString Util::getLineFromConf(const QString &id)
{
    QString output = "";
    QFile file("./conf.xml");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Can not find the conf file";
        return QString();
    }
    QXmlStreamReader xml(&file);
    while (!xml.atEnd())
    {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartElement)
        {
            if(xml.name() == id)
            {
                output = xml.readElementText();
            }
        }
    }
    return output;
}

void Util::init(QCoreApplication *pApp, Server * pServer)
{
    Util::server = pServer;
    Util::app = pApp;
}

void Util::log(QString message)
{
    std::cout << message.toStdString() << std::endl;
}

void Util::catchUnixSignals(const std::vector<int>& quitSignals,
                            const std::vector<int>& ignoreSignals) {
    auto handler = [](int sig) ->void {
        Util::app->quit();
        server->close();
    };
    for ( int sig : ignoreSignals )
        signal(sig, SIG_IGN);
    for ( int sig : quitSignals )
        signal(sig, handler);
}
