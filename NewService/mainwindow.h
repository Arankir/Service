#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCoreApplication>
#include "qtservice/qtservice.h"
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QTimer>
#include <QObject>
#include <command.h>

class MainWindow : public QtService<QCoreApplication>
{

public:
    MainWindow(int argc, char **argv);
    ~MainWindow();
    void start();
    void pause();
    void resume();
    void stop();

private:
    QTimer _timer;
    Command _command;

};
#endif // MAINWINDOW_H
