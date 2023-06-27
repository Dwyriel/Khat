#ifndef KHATSERVER_TCPSERVER_H
#define KHATSERVER_TCPSERVER_H

#include <QtLogging>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>

#include "definitions.h"

class TcpServer : public QObject {
Q_OBJECT

public:
    explicit TcpServer(QObject *parent = nullptr, quint16 port = SERVER_DEFAULT_PORT);

    ~TcpServer() override;

private:
    QTcpServer *qTcpServer;
    QList<QTcpSocket*> sockets; //will be changed later

    void connectSignals();
};

#endif //KHATSERVER_TCPSERVER_H
