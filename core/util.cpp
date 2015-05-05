#include "util.hpp"
#include <iostream>
#include <QString>
#include <QThread>
#include <QFile>
#include <QXmlStreamReader>
#include <QCoreApplication>
#include <signal.h>
#include <QDir>

Server * Util::server = nullptr;
QCoreApplication *Util::app = nullptr;
QString Util::configFilePath = "./conf.xml";

QString Util::getLineFromConf(const QString &id)
{
    return getLineFromFile(configFilePath,id);
}

QString Util::getLineFromFile(QString pathToFile,const QString & id)
{
    QString output = "";
    QFile file(pathToFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Can not find the conf file in : " + QDir::currentPath();

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

void Util::initConfigFilePath(QCoreApplication *pApp)
{
    if(pApp->arguments().value(1) == "-c")
    {
        if(pApp->arguments().value(2) != NULL)
        {
            configFilePath = pApp->arguments().value(2);
        }
        else
        {
            Util::log("Invalid use : -c pathToConfigFile");
        }
    }
}

void Util::log(QString message)
{
    std::cout << message.toStdString() << std::endl;
}

void Util::catchUnixSignals(const std::vector<int>& quitSignals,
                            const std::vector<int>& ignoreSignals) {
    auto handler = [](int sig) ->void {
        (void)sig;
        server->close();
        Util::app->quit();
    };
    for ( int sig : ignoreSignals )
        signal(sig, SIG_IGN);
    for ( int sig : quitSignals )
        signal(sig, handler);
}
