#include "KtLogger.h"

bool KtLogger::printToConsole = true;
bool KtLogger::saveToFile = true;

void KtLogger::MessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    DISCARD(context);
    QString message = generateMessage(msg, type);
    if (printToConsole)
        writeMessageToConsole(message);
    if (saveToFile)
        writeMessageToFile(message);
}

QString KtLogger::getFormattedCurrentTime() {
    return QDateTime::currentDateTime().toString(DATE_FORMAT);
}

char KtLogger::getMessageTypeCharacter(QtMsgType type) {
    switch (type) {
        case QtDebugMsg:
            return 'D';
        case QtInfoMsg:
            return 'I';
        case QtWarningMsg:
            return 'W';
        case QtCriticalMsg:
            return 'E';
        case QtFatalMsg:
            return 'F';
        default:
            return '?';
    }
}

QString KtLogger::generateMessage(const QString &msg, QtMsgType type) {
    return QString("[%1] (%2) %3\n").arg(getFormattedCurrentTime()).arg(getMessageTypeCharacter(type)).arg(msg);
}

void KtLogger::writeMessageToConsole(const QStringView &msg) {
    fprintf(stderr, "%s", msg.toLocal8Bit().constData());
}

void KtLogger::writeMessageToFile(const QStringView &msg) {

}

