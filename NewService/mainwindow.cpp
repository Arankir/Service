#include "mainwindow.h"

const QString c_logPath = "log.txt";
const QString c_settingsPath = "settings.txt";
const QString c_commandsPath = "commands.txt";

MainWindow::MainWindow(int argc, char **argv) : QtService<QCoreApplication> (argc, argv, "ArankirService") {
    setServiceDescription("This is My Service");
    setServiceFlags(QtServiceBase::CanBeSuspended);
    process_ = new QProcess(this);
    connect(&timer_, &QTimer::timeout, this, &MainWindow::onTimerTimeout);
}

MainWindow::~MainWindow() {
    delete process_;
}

void MainWindow::start() {
    QCoreApplication *app = application();
    appendLog("Service is started on " + app->applicationDirPath());

    updateInterval();
    timer_.start();
}

void MainWindow::pause() {
    appendLog("Service is paused");
}

void MainWindow::resume() {
    appendLog("Service is resumed");
}

void MainWindow::stop() {
    timer_.stop();
    appendLog("Service is stopped");
}

uint MainWindow::getSettingsInterval() {
    QFile settings(QCoreApplication::applicationDirPath() + QDir::separator() + c_settingsPath);
    settings.open(QFile::ReadOnly);
    uint interval = settings.readLine().toUInt();
    settings.close();

    return interval;
}

void MainWindow::setInterval(uint aMsec) {
    timer_.setInterval(aMsec);
    appendLog("Interval = " + QString::number(timer_.interval()));
}

void MainWindow::updateInterval() {
    uint interval = getSettingsInterval();
    if (interval > 0 && (interval != static_cast<uint>(timer_.interval()))) {
        setInterval(interval);
    }
}

void MainWindow::onTimerTimeout() {
    QFile fileCommands(QCoreApplication::applicationDirPath() + QDir::separator() + c_commandsPath);
    fileCommands.open(QFile::ReadOnly);
    QStringList strCommands;
    while(!fileCommands.atEnd()){
        strCommands << QString::fromLocal8Bit(fileCommands.readLine()).remove("\r\n").remove("\n");
    }

    makeComand(strCommands.join("&"));
    updateInterval();
}

void MainWindow::makeComand(QString aCommand) {
    QString strCommand;
    if (QSysInfo::productType() == "windows") {
        strCommand = "cmd /C \"";
    }
    strCommand += aCommand +"\"";

    process_->startDetached(strCommand);
    appendLog("Make " + strCommand);

    bool isFinished = process_->waitForFinished(1000);
    appendLog(isFinished ? "Error " + strCommand : "Complete " + strCommand);
}

void MainWindow::appendLog(QString aText) {
    QFile fileLog(QCoreApplication::applicationDirPath() + QDir::separator() + c_logPath);
    fileLog.open(QFile::Append);
    QTextStream writeStream(&fileLog);
    writeStream << QDateTime::currentDateTime().toString("yyyy-MM-dd  HH:mm:ss") + " " + aText << "\n";
    fileLog.close();
}
