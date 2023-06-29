#include "SignalHandler.h"

SignalHandler *SignalHandler::instance() {
    return signalHandler;
}

SignalHandler *SignalHandler::signalHandler = new SignalHandler();

SignalHandler::SignalHandler() {
    const int closeSignals[] = {SIGHUP, SIGINT, SIGQUIT, SIGABRT, SIGTERM};
#ifdef Q_OS_WIN
    for (int sig: closeSignals)
        signal(sig, SignalReceived);
#else
    struct sigaction handler, old_handler;
    handler.sa_handler = SignalReceived;
    sigemptyset(&handler.sa_mask);
    handler.sa_flags = 0;
    for (int signal: closeSignals) {
        sigaction(signal, NULL, &old_handler);
        if (old_handler.sa_handler != SIG_IGN)
            sigaction(signal, &handler, NULL);
    }
#endif
}

void SignalHandler::SignalReceived(int signal) {
    qDebug("%s signal received. (SIG%s(%d))", sigdescr_np(signal), sigabbrev_np(signal), signal);
    instance()->emitCloseAppSignal(0);
}

void SignalHandler::emitCloseAppSignal(int exitCode) {
    emit CloseApp(exitCode);
}
