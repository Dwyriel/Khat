#include <QCoreApplication>

#include "Source/TcpServer/TcpServer.h"
#include "Source/SignalHandler/SignalHandler.h"
#include "KtLogger.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    qInstallMessageHandler(KtLogger::MessageHandler);
    QObject::connect(SignalHandler::instance(), &SignalHandler::CloseProgram, QCoreApplication::exit);
    TcpServer tcpServer;
    return QCoreApplication::exec();
}
