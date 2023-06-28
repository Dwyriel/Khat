#ifndef KHATCLIENT_MAINWINDOW_H
#define KHATCLIENT_MAINWINDOW_H

#include "definitions.h"

#include <QMainWindow>
#include <QTcpSocket>

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    QTcpSocket *qTcpSocket;

    void connectSignals();
};

#endif //KHATCLIENT_MAINWINDOW_H
