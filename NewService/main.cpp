#include "mainwindow.h"
#include <QDebug>

QScopedPointer<QFile> logFile_;

void initLog();
void log(QtMsgType type, const QMessageLogContext &context, const QString &msg);

int main(int argc, char *argv[])
{
    MainWindow service(argc, argv);
    return service.exec();
}

void log(QtMsgType aType, const QMessageLogContext &aContext, const QString &aMessage) {
    const char *function = aContext.function ? aContext.function : "";
    QTextStream out(logFile_.data());

    switch (aType) {
    case QtInfoMsg:     out << "INFO "; break;
    case QtDebugMsg:    out << "DEBG "; break;
    case QtWarningMsg:  out << "WRNG "; break;
    case QtCriticalMsg: out << "CRCL "; break;
    case QtFatalMsg:    out << "FATL "; break;
    }

    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ");//"yyyy-MM-dd hh:mm:ss "
    out << /*aContext.category << ": " << */function << "  " << aMessage << endl;
    out.flush();

    QString output(function);
    output += "  " + aMessage + "\n";
}

void initLog() {
    QString logsPath = "logs/";

    //Удаление старых файлов
    QDir dirLogs(logsPath);
    dirLogs.setFilter(QDir::Files | QDir::NoSymLinks);
    dirLogs.setSorting(QDir::Name);
    QFileInfoList list = dirLogs.entryInfoList();
    for(auto &file: list) {
        if (file.fileName().indexOf("log_") == 0) {
            QDateTime date {QDateTime::fromString(file.fileName().remove("log_").remove(".txt"), "yyyy.MM.dd")};
            if (date < QDateTime::currentDateTime().addMonths(-1)) {
                QFile::remove(file.filePath() + "/" + file.fileName());
            }
        }
    }

    logFile_.reset(new QFile(logsPath + QDateTime::currentDateTime().toString("log_yyyy.MM.dd") + ".txt"));
    logFile_.data()->open(QFile::Append | QFile::Text);
    qInstallMessageHandler(log);
}
