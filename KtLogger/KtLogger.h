#ifndef KTLOGGER_LIBRARY_H
#define KTLOGGER_LIBRARY_H

#include "definitions.h"

#include <QCoreApplication>
#include <QtLogging>
#include <QString>
#include <QDateTime>

class KtLogger {
public:
    KtLogger() = delete;

    ~KtLogger() = delete;

    static bool printToConsole;

    static bool saveToFile;

    static void MessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);
private:
    static inline QString getFormattedCurrentTime();

    static inline char getMessageTypeCharacter(QtMsgType type);

    static inline QString generateMessage(const QString &msg, QtMsgType type);

    static inline void writeMessageToConsole(const QStringView &msg);

    static inline void writeMessageToFile(const QStringView &msg);
};

class Logger : QObject {
Q_OBJECT

};

#endif //KTLOGGER_LIBRARY_H
