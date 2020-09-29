#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCoreApplication>
#include "qtservice/qtservice.h"
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QTimer>
#include <QObject>
#include <QProcess>
#include <QDateTime>

class MainWindow : public QObject, public QtService<QCoreApplication>
{
    Q_OBJECT
public:
    MainWindow(int argc, char **argv);
    ~MainWindow();
    void start();
    void pause();
    void resume();
    void stop();

    uint getSettingsInterval();
    void setInterval(uint msec);
    void updateInterval();
    void onTimerTimeout();
    void makeComand(QString command);
    void appendLog(QString text);

private:
    QTimer timer_;
    QProcess *process_;
};
#endif // MAINWINDOW_H
