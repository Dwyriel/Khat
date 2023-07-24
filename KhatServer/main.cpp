#include <QCoreApplication>

#include "cmake_config.h"
#include "Utility.h"
#include "DArgumentParser.h"
#include "KtLogger.h"

#include "Source/TcpServer/TcpServer.h"
#include "Source/SignalHandler/SignalHandler.h"

std::tuple<int, int> parseArgs(int argc, char **argv) {
    DArgumentOption portOption(DArgumentOptionType::InputOption, {'p'}, {"port"}, "The port the server should listen to.");
    DArgumentOption connectionLimitOption(DArgumentOptionType::InputOption, {'l'}, {"limit"}, "The maximum simultaneous connections the server can have.");
    DArgumentOption helpOption(DArgumentOptionType::HelpOption, {'h'}, {"help"}, "Print this message.");
    DArgumentOption versionOption(DArgumentOptionType::VersionOption, {'v'}, {"version"}, "Print the program version.");
    DArgumentParser parser(argc, argv);
    parser.SetAppInfo(PROJECT_NAME, PROJECT_VER);
    parser.AddArgumentOption({&helpOption, &versionOption, &portOption, &connectionLimitOption});
    auto parseResult = parser.Parse();
    if (parseResult != DParseResult::ParseSuccessful) {
        qCritical() << parser.ErrorText();
        exit(EXIT_FAILURE);
    }
    if (helpOption.WasSet() || versionOption.WasSet()) {
        qInfo("%s%s", (versionOption.WasSet() ? parser.VersionText() : "").c_str(), (helpOption.WasSet() ? parser.HelpText() : "").c_str());
        exit(EXIT_SUCCESS);
    }
    uint16_t port = 0;
    if (portOption.WasSet()) {
        port = convertToUnsignedInteger<uint16_t>(portOption.GetValue(), UINT16_MAX);
        if (port < 1) {
            qCritical("Invalid value passed to option \"port\".\nValue should be an integer number between 1 and 65535.");
            exit(EXIT_FAILURE);
        }
    }
    uint64_t limit = 0;
    if (connectionLimitOption.WasSet()) {
        limit = convertToUnsignedInteger<uint64_t>(connectionLimitOption.GetValue(), UINT64_MAX);
        if (limit < 1) {
            qCritical("Invalid value passed to option \"limit\".\nValue should be an integer number between 1 and 18446744073709551615.");
            exit(EXIT_FAILURE);
        }
    }
    return std::make_tuple(port, limit);
}

int main(int argc, char *argv[]) {
#if DEBUG_BUILD
    KtLogger::saveToFile = false;
#endif
    auto [port, limit] = parseArgs(argc, argv);
    QCoreApplication a(argc, argv);
    qInstallMessageHandler(KtLogger::MessageHandler);
    qInfo("%s version %s", PROJECT_NAME, PROJECT_VER);
    QObject::connect(SignalHandler::instance(), &SignalHandler::CloseProgram, QCoreApplication::exit);
    TcpServer tcpServer(nullptr, port, limit);
    return QCoreApplication::exec();
}
