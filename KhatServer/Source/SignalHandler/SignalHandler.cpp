#include "SignalHandler.h"

SignalHandler *SignalHandler::instance() {
    return signalHandler;
}

SignalHandler *SignalHandler::signalHandler = new SignalHandler();

SignalHandler::SignalHandler() {
    signal(SIGHUP, SignalReceived);
    signal(SIGINT, SignalReceived);
    signal(SIGQUIT, SignalReceived);
    signal(SIGABRT, SignalReceived);
    signal(SIGTERM, SignalReceived);
}

void SignalHandler::SignalReceived(int signal) {
    qDebug("%s signal received. (SIG%s(%d))", sigdescr_np(signal), sigabbrev_np(signal), signal);
    instance()->emitCloseAppSignal(0);
}

void SignalHandler::emitCloseAppSignal(int exitCode) {
    emit CloseApp(exitCode);
}
