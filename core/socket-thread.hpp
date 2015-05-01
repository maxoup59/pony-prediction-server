#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H

#include <QThread>
#include <QTcpSocket>
class SocketThread : public QThread
{
    Q_OBJECT
public:
    SocketThread(int socketDescriptor);
    ~SocketThread();
    void run() Q_DECL_OVERRIDE;
public slots:
    void readyRead();
    void disconnected();
signals:
    void deconnection(SocketThread*);
private:
    QTcpSocket *socketClient;
    bool write(QString answer);
    QString read();
};

#endif // SOCKETTHREAD_H
