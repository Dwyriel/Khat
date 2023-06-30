#ifndef KTLOGGER_LIBRARY_H
#define KTLOGGER_LIBRARY_H

#include "definitions.h"

#include <QCoreApplication>
#include <QtLogging>
#include <QString>
#include <QDir>
#include <QFile>
#include <QDateTime>

class KtLogger {
public:
    KtLogger() = delete;

    ~KtLogger() = delete;

    static bool printToConsole;

    static bool saveToFile;

    static void MessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

    static QString BytesToHexRepresentation(char *bytes, int size);

private:
    static QFile file;

    static inline QString getFormattedCurrentTime();

    static inline char getMessageTypeCharacter(QtMsgType type);

    static inline QString generateMessage(const QString &msg, QtMsgType type);

    static inline void writeMessageToConsole(const QString &msg);

    static inline void writeMessageToFile(const QStringView &msg);

    struct _internalStruct{
        _internalStruct();
    };
};

#endif //KTLOGGER_LIBRARY_H
