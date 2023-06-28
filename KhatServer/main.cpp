#include <QCoreApplication>

#include "Source/TcpServer/TcpServer.h"
#include "Source/SignalHandler/SignalHandler.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    QObject::connect(SignalHandler::instance(), &SignalHandler::CloseApp, QCoreApplication::exit);
    TcpServer tcpServer;
    return QCoreApplication::exec();
}
