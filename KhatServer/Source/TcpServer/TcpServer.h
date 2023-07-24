#ifndef KHATSERVER_TCPSERVER_H
#define KHATSERVER_TCPSERVER_H

#include "definitions.h"

#include <QtLogging>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUuid>
#include <QMap>

class TcpServer : public QObject {
Q_OBJECT

public:
    explicit TcpServer(QObject *parent, quint16 port, quint64 limit);

    ~TcpServer() override;

private:
    quint64 connectionLimit;
    QTcpServer *qTcpServer;
    QMap<QUuid, QTcpSocket *> sockets;

    void connectSignals();

private slots:

    void ErrorOccurredOnNewConnection(QAbstractSocket::SocketError socketError);

    void newPendingConnection();

    void socketDisconnected(const QUuid &uuid);

    void socketSentMessage(const QUuid &uuid);
};

#endif //KHATSERVER_TCPSERVER_H
