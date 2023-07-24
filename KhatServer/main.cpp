#include <QCoreApplication>

#include "Source/TcpServer/TcpServer.h"
#include "Source/SignalHandler/SignalHandler.h"
#include "KtLogger.h"
#include "DArgumentParser.h"
#include "cmake_config.h"

void parseArgs(int argc, char **argv) {
    DArgumentOption portOption(DArgumentOptionType::InputOption, {'p'}, {"port"}, "The port the server should listen to.");
    DArgumentOption connectionLimitOption(DArgumentOptionType::InputOption, {'l'}, {"limit"}, "The maximum simultaneous connections the server can have.");
    DArgumentOption helpOption(DArgumentOptionType::HelpOption, {'h'}, {"help"}, "Print this message.");
    DArgumentOption versionOption(DArgumentOptionType::VersionOption, {'v'}, {"version"}, "Print the program version.");
    DArgumentParser parser(argc, argv);
    parser.SetAppInfo(PROJECT_NAME, PROJECT_VER);
    parser.AddArgumentOption({&helpOption, &versionOption, &portOption, &connectionLimitOption});
    auto parseResult = parser.Parse();
    if(parseResult != DParseResult::ParseSuccessful){
        qCritical() << parser.ErrorText();
        exit(EXIT_FAILURE);
    }
    if (helpOption.WasSet() || versionOption.WasSet()) {
        qInfo("%s%s", (versionOption.WasSet() ? parser.VersionText() : "").c_str(), (helpOption.WasSet() ? parser.HelpText() : "").c_str());
        exit(EXIT_SUCCESS);
    }
    if(portOption.WasSet())
        qInfo("port received: %s", portOption.GetValue().c_str());//todo check if port is valid, start server with port, error message
    if(connectionLimitOption.WasSet())
        qInfo("limit received: %s", connectionLimitOption.GetValue().c_str());//todo check if value is valid, set limit, error message
}

int main(int argc, char *argv[]) {
#if DEBUG_BUILD
    KtLogger::saveToFile = false;
#endif
    parseArgs(argc, argv);
    QCoreApplication a(argc, argv);
    qInstallMessageHandler(KtLogger::MessageHandler);
    QObject::connect(SignalHandler::instance(), &SignalHandler::CloseProgram, QCoreApplication::exit);
    TcpServer tcpServer;
    return QCoreApplication::exec();
}
