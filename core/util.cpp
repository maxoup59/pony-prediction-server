#include "util.hpp"
#include <iostream>
#include <QString>
#include <QThread>
#include <QFile>
#include <QXmlStreamReader>

Server * Util::server = nullptr;

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

void Util::init(Server * pServer)
{
    Util::server = pServer;
}

void Util::log(QString message)
{
    std::cout << message.toStdString();
}
