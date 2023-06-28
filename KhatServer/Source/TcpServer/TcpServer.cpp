#include "TcpServer.h"

TcpServer::TcpServer(QObject *parent, quint16 port) : QObject(parent), qTcpServer(new QTcpServer(this)) {
    connectSignals();
    qDebug("Creating Server on port %d.", port);
    qTcpServer->listen(QHostAddress::Any, port);
}

TcpServer::~TcpServer() {
    qInfo("Notifying Clients...");
    while (!sockets.empty()) {
        TcpClient *tcpClient = sockets.last();
        tcpClient->disconnect();
        tcpClient->close();
        tcpClient->deleteLater();
        sockets.removeLast();
    }
    qInfo("Done");
    qInfo("Closing Server...");
    qTcpServer->close();
    delete qTcpServer;
    qInfo("Done");
}

void TcpServer::connectSignals() {
    connect(qTcpServer, &QTcpServer::acceptError, this, &TcpServer::ErrorOccurredOnNewConnection);
    connect(qTcpServer, &QTcpServer::pendingConnectionAvailable, this, &TcpServer::newPendingConnection);
}

void TcpServer::ErrorOccurredOnNewConnection(QAbstractSocket::SocketError socketError) {
    qDebug() << "Client tried to connect but an error occurred. Socket Error number: " << QString::number(socketError);
}

void TcpServer::newPendingConnection() {
    if (!qTcpServer->hasPendingConnections())
        return;
    qInfo("New client connection pending.");
    auto socket = qTcpServer->nextPendingConnection();
    auto uuid = QUuid::createUuid();
    while (sockets.contains(uuid))
        uuid = QUuid::createUuid();
    sockets.insert(uuid, socket);
    connect(socket, &QTcpSocket::disconnected, [this, uuid] { socketDisconnected(uuid); });
    connect(socket, &QTcpSocket::readyRead, [this, uuid] { socketSentMessage(uuid); });
    qInfo("Client was assigned the UUID of %s and added to the client list.", qUtf8Printable(uuid.toString()));
}

void TcpServer::socketDisconnected(const QUuid &uuid) {

}

void TcpServer::socketSentMessage(const QUuid &uuid) {

}

