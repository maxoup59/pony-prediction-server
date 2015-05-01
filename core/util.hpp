#ifndef UTIL_H
#define UTIL_H
#include "server.hpp"

class Util
{
public:
    static QString getLineFromConf(const QString & id);
    static void init(Server * pServer);
    static void log(QString);
private :
    static Server * server;
};

#endif // UTIL_H
