#include "KtLogger.h"

bool KtLogger::printToConsole = true;
bool KtLogger::saveToFile = true;
QFile KtLogger::file;

void KtLogger::MessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    DISCARD(context);
    QString message = generateMessage(msg, type);
    if (printToConsole)
        writeMessageToConsole(message);
    if (saveToFile)
        writeMessageToFile(message);
}

QString KtLogger::BytesToHexRepresentation(char *bytes, int size) {
    QString rep;
    rep.reserve(size * 2);
    for (int i = 0; i < size; i++)
        rep.append(QString("%1").arg((unsigned char) bytes[i], 0, 16));
    return rep;
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

void KtLogger::writeMessageToConsole(const QString &msg) {
    fprintf(stderr, "%s", msg.toLocal8Bit().constData());
}

void KtLogger::writeMessageToFile(const QStringView &msg) {
    if (!QCoreApplication::instance())
        return;
    static _internalStruct internalStruct;
    file.open(QIODeviceBase::Append | QIODeviceBase::ReadWrite);
    QTextStream fileOutput(&file);
    fileOutput << msg;
    file.close();
}

KtLogger::_internalStruct::_internalStruct() {
    QDir logDir(QCoreApplication::applicationDirPath() + QDir::separator() + LOGS_DIR_NAME);
    if (!logDir.exists())
        logDir.mkdir(logDir.path());
    KtLogger::file.setFileName(logDir.path() + QDir::separator() + getFormattedCurrentTime() + LOG_FILE_EXTENSION);
    int fileExistCounter = 1;
    while (KtLogger::file.exists())
        KtLogger::file.setFileName(logDir.path() + QDir::separator() + getFormattedCurrentTime() + "_" + QString::number(++fileExistCounter) + LOG_FILE_EXTENSION);
}
