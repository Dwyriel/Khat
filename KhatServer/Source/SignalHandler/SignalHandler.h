#ifndef KHAT_SIGNALHANDLER_H
#define KHAT_SIGNALHANDLER_H

#include <QCoreApplication>
#include <QtGlobal>
#include <QObject>
#include <csignal>

class SignalHandler : public QObject {
Q_OBJECT

public:
    static SignalHandler *instance();

private:
    static SignalHandler *signalHandler;

    SignalHandler();

#ifdef Q_OS_UNIX

    static void InitializeAndAssignHandler(struct sigaction *handler, const QList<int> &sysSignals, void (*action)(int), struct sigaction *oldHandler);

#endif

    static void PrintDebugMessage(int signal);

    static void CloseProgramSignalReceived(int signal);

    static void ErrorSignalReceived(int signal);

    static void AlarmSignalReceived(int signal);

signals:

    void CloseProgram(int exitCode);

    void Error(int signalCode);

    void AlarmTimeout();
};

#endif //KHAT_SIGNALHANDLER_H
