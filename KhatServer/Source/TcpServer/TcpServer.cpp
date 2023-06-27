#include "TcpServer.h"

TcpServer::TcpServer(QObject *parent, quint16 port) : QObject(parent), qTcpServer(new QTcpServer(this)) {
    connectSignals();
    qDebug() << "Creating Server";
    qTcpServer->listen(QHostAddress::AnyIPv4, port);
    qDebug() << port;
}

TcpServer::~TcpServer() {
    qDebug() << "Deleting Server";
    while (!sockets.empty()) {//temporary TODO modify later
        sockets.last()->disconnect();
        sockets.last()->close();
        sockets.removeLast();
    }
    qTcpServer->close();
    delete qTcpServer;
}

void TcpServer::connectSignals() {

}
