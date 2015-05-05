#ifndef UTIL_H
#define UTIL_H
#include "server.hpp"
#include <QCoreApplication>

class Util
{
public:
    static QString getLineFromConf(const QString & id);
    static void init(QCoreApplication *, Server * );
    static void log(QString);
    static void catchUnixSignals(const std::vector<int>&,
                                 const std::vector<int>& = std::vector<int>());
    static void initConfigFilePath(QCoreApplication*);
private :
    static Server * server;
    static QCoreApplication * app;
    static QString configFilePath;
};

#endif // UTIL_H
