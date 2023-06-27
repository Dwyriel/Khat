#include <QCoreApplication>

#include "Source/TcpServer/TcpServer.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    TcpServer tcpServer;
    return QCoreApplication::exec();
}
