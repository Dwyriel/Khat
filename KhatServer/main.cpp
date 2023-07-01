#include <QCoreApplication>

#include "Source/TcpServer/TcpServer.h"
#include "Source/SignalHandler/SignalHandler.h"
#include "KtLogger.h"
#include "cmake_config.h"

int main(int argc, char *argv[]) {
#if DEBUG_BUILD
    KtLogger::saveToFile = false;
#endif
    QCoreApplication a(argc, argv);
    qInstallMessageHandler(KtLogger::MessageHandler);
    QObject::connect(SignalHandler::instance(), &SignalHandler::CloseProgram, QCoreApplication::exit);
    TcpServer tcpServer;
    return QCoreApplication::exec();
}
