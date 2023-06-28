#ifndef KHAT_SIGNALHANDLER_H
#define KHAT_SIGNALHANDLER_H

#include <QCoreApplication>
#include <QObject>
#include <csignal>

class SignalHandler : public QObject {
Q_OBJECT

public:
    static SignalHandler *instance();

private:
    static SignalHandler *signalHandler;

    SignalHandler();

    static void SignalReceived(int signal);

    void emitCloseAppSignal(int exitCode);

signals:

    void CloseApp(int exitCode);
};

#endif //KHAT_SIGNALHANDLER_H
