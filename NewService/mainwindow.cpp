#include "mainwindow.h"

MainWindow::MainWindow(int argc, char **argv)
    : QtService<QCoreApplication>(argc,argv,"ArankirService")
{
    setServiceDescription("This is My Service");
    setServiceFlags(QtServiceBase::CanBeSuspended);
}

MainWindow::~MainWindow()
{

}

void MainWindow::start(){
    QCoreApplication *app = application();
    QFile settings(QCoreApplication::applicationDirPath() + QDir::separator() + "settings.txt");
    settings.open(QFile::ReadOnly);
    _timer.setInterval(settings.readLine().toUInt());
    QObject::connect(&_timer,SIGNAL(timeout()),&_command,SLOT(MakeComand()));
    _timer.start();
    _command.Set(QCoreApplication::applicationDirPath() + QDir::separator());

    QFile log(QCoreApplication::applicationDirPath() + QDir::separator() + "log.txt");
    log.open(QFile::Append);
    QTextStream writeStream(&log);
    QDateTime time;
    writeStream <<time.currentDateTime().toString("yyyy-MM-dd  HH:mm:ss")+" Start "<<app->applicationDirPath()<<" Interval="<<_timer.interval()<<"\n";
    log.close();

}
void MainWindow::pause(){
    QFile log(QCoreApplication::applicationDirPath() + QDir::separator() + "log.txt");
    log.open(QFile::Append);
    QTextStream writeStream(&log);
    QDateTime time;
    writeStream <<time.currentDateTime().toString("yyyy-MM-dd  HH:mm:ss")+" Pause"<<"\n";
    log.close();
}
void MainWindow::resume(){
    QFile log(QCoreApplication::applicationDirPath() + QDir::separator() + "log.txt");
    log.open(QFile::Append);
    QTextStream writeStream(&log);
    QDateTime time;
    writeStream <<time.currentDateTime().toString("yyyy-MM-dd  HH:mm:ss")+" Resume"<<"\n";
    log.close();
}
void MainWindow::stop(){
    QFile log(QCoreApplication::applicationDirPath() + QDir::separator() + "log.txt");
    log.open(QFile::Append);
    QTextStream writeStream(&log);
    QDateTime time;
    writeStream <<time.currentDateTime().toString("yyyy-MM-dd  HH:mm:ss")+" Stop"<<"\n";
    log.close();
}
