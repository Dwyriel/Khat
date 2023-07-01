#include "SignalHandler.h"

const QList<int> closeSignals = {SIGHUP, SIGINT, SIGQUIT, SIGABRT, SIGTERM};
const QList<int> errorSignals = {SIGILL, SIGBUS, SIGFPE, SIGSEGV};
const QList<int> alarmSignals = {SIGALRM, SIGVTALRM, SIGPROF};
const QList<int> otherSignals = {};

SignalHandler *SignalHandler::instance() {
    return signalHandler;
}

SignalHandler *SignalHandler::signalHandler = new SignalHandler();

SignalHandler::SignalHandler() {
    QList<int> ignoreSignals;
    GenerateIgnoreSignalsList(ignoreSignals);
#ifdef Q_OS_WIN
    AssignSignalHandler(closeSignals, CloseProgramSignalReceived);
    AssignSignalHandler(errorSignals, ErrorSignalReceived);
    AssignSignalHandler(alarmSignals, AlarmSignalReceived);
    AssignSignalHandler(otherSignals, OtherSignalReceived);
    AssignSignalHandler(ignoreSignals, SIG_IGN);
#else
    struct sigaction closeHandler, errorHandler, alarmHandler, otherSignalHandler, ignoreHandler, oldHandler;
    InitializeAndAssignHandler(&closeHandler, closeSignals, CloseProgramSignalReceived, &oldHandler);
    InitializeAndAssignHandler(&errorHandler, errorSignals, ErrorSignalReceived, &oldHandler);
    InitializeAndAssignHandler(&alarmHandler, alarmSignals, AlarmSignalReceived, &oldHandler);
    InitializeAndAssignHandler(&otherSignalHandler, otherSignals, OtherSignalReceived, &oldHandler);
    InitializeAndAssignHandler(&ignoreHandler, ignoreSignals, SIG_IGN, &oldHandler);
#endif
}

void SignalHandler::GenerateIgnoreSignalsList(QList<int> &ignoreSignals) {
    const QList<int> unignorableSignals = {SIGKILL, SIGCONT, SIGSTOP};
    QList<int> existingSignals = closeSignals + errorSignals + alarmSignals + otherSignals;
    ignoreSignals.clear();
    for (int i = 1; i < 32; i++) {
        if (existingSignals.contains(i) || unignorableSignals.contains(i))
            continue;
        ignoreSignals.append(i);
    }
#ifdef Q_OS_LINUX
    for (int i = SIGRTMIN; i <= SIGRTMAX; i++) {
        if (existingSignals.contains(i))
            continue;
        ignoreSignals.append(i);
    }
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

QString SignalHandler::GenerateSignalMessage(int signal) {
    return signal < 32 ? QString("%1 signal received. (SIG%2(%3))").arg(sigdescr_np(signal), sigabbrev_np(signal)).arg(signal) : QString("Real time signal received. (SIGRTMIN+%1(%2))").arg(signal - SIGRTMIN).arg(signal);
}

void SignalHandler::CloseProgramSignalReceived(int signal) {
    qInfo("%s", GenerateSignalMessage(signal).toUtf8().constData());
    emit instance()->CloseProgram();
}

void SignalHandler::ErrorSignalReceived(int signal) {
    qCritical("%s", GenerateSignalMessage(signal).toUtf8().constData());
    emit instance()->Error(signal);
}

void SignalHandler::AlarmSignalReceived(int signal) {
    qInfo("%s", GenerateSignalMessage(signal).toUtf8().constData());
    emit instance()->AlarmTimeout(signal);
}

void SignalHandler::OtherSignalReceived(int signal) {
    qInfo("%s", GenerateSignalMessage(signal).toUtf8().constData());
    emit instance()->OtherSignal(signal);
}
