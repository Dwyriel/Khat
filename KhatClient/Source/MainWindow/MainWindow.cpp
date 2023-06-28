#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), qTcpSocket(new QTcpSocket()) {
    qTcpSocket->connectToHost(QHostAddress::LocalHost, SERVER_DEFAULT_PORT);
}

void MainWindow::connectSignals() {

}
