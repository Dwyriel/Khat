#include "SignalHandler.h"

SignalHandler *SignalHandler::instance() {
    return signalHandler;
}

SignalHandler *SignalHandler::signalHandler = new SignalHandler();

SignalHandler::SignalHandler() {
#ifdef Q_OS_WIN
    AssignSignalHandler(closeSignals, CloseProgramSignalReceived);
    AssignSignalHandler(errorSignals, ErrorSignalReceived);
    AssignSignalHandler(alarmSignals, AlarmSignalReceived);
    AssignSignalHandler(ignoreSignals, SIG_IGN);
#else
    struct sigaction closeHandler, errorHandler, alarmHandler, ignoreHandler, oldHandler;
    InitializeAndAssignHandler(&closeHandler, closeSignals, CloseProgramSignalReceived, &oldHandler);
    InitializeAndAssignHandler(&errorHandler, errorSignals, ErrorSignalReceived, &oldHandler);
    InitializeAndAssignHandler(&alarmHandler, alarmSignals, AlarmSignalReceived, &oldHandler);
    InitializeAndAssignHandler(&ignoreHandler, ignoreSignals, SIG_IGN, &oldHandler);
#endif
}

#ifdef Q_OS_WIN

void SignalHandler::AssignSignalHandler(const QList<int> &sysSignals, void (*action)(int)) {
    for (int sysSignal: sysSignals)
        if (signal(sysSignal, action) == SIG_IGN && action != SIG_IGN)
            signal(sysSignal, SIG_IGN);
}

#else

void SignalHandler::InitializeAndAssignHandler(struct sigaction *handler, const QList<int> &sysSignals, void (*action)(int), struct sigaction *oldHandler) {
    handler->sa_handler = action;
    sigemptyset(&handler->sa_mask);
    handler->sa_flags = 0;
    for (int signal: sysSignals) {
        sigaction(signal, NULL, oldHandler);
        if (oldHandler->sa_handler != SIG_IGN)
            sigaction(signal, handler, NULL);
    }
}

#endif

void SignalHandler::PrintDebugMessage(int signal) {
    qDebug("%s signal received. (SIG%s(%d))", sigdescr_np(signal), sigabbrev_np(signal), signal);
}

void SignalHandler::CloseProgramSignalReceived(int signal) {
    PrintDebugMessage(signal);
    emit instance()->CloseProgram(0);
}

void SignalHandler::ErrorSignalReceived(int signal) {
    PrintDebugMessage(signal);
    emit instance()->Error(signal);
}

void SignalHandler::AlarmSignalReceived(int signal) {
    PrintDebugMessage(signal);
    emit instance()->AlarmTimeout();
}
