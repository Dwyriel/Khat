#include "TcpServer.h"

TcpServer::TcpServer(QObject *parent, quint16 port, quint64 limit) : QObject(parent), qTcpServer(new QTcpServer(this)), connectionLimit(limit) {
    connectSignals();
    qInfo("Creating Server on port %d.", port);
    qTcpServer->listen(QHostAddress::Any, port ? port : SERVER_DEFAULT_PORT);
}

TcpServer::~TcpServer() {
    if (!sockets.empty()) {
        qInfo("Notifying Clients...");
        while (!sockets.empty()) {
            auto *tcpClient = sockets.take(sockets.lastKey());
            tcpClient->disconnect();
            tcpClient->close();
            tcpClient->deleteLater();
        }
        qInfo("Done");
    }
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
    qWarning("Client tried to connect but an error occurred. Socket Error: %d - %s", socketError, qTcpServer->errorString().toUtf8().constData());
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
    qInfo("Peer Info:\n  Address: %s\n  Port: %d", qUtf8Printable(socket->peerAddress().toString()), socket->peerPort());
}

void TcpServer::socketDisconnected(const QUuid &uuid) {
    if (!sockets.contains(uuid))
        return;
    sockets.value(uuid)->disconnect();
    sockets.remove(uuid);
    qInfo("Socket of UUID %s disconnected and was removed from the client list.", qUtf8Printable(uuid.toString()));
}

void TcpServer::socketSentMessage(const QUuid &uuid) {

}

