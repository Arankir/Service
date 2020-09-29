#include "command.h"

Command::Command(QString aPath, QObject *parent) : QObject(parent), path_(aPath) {

}

Command::Command(QObject *parent) : QObject(parent), path_("") {

}

void Command::MakeComand() {
    QProcess console;
    QFile commands(path_ + "commands.txt");
    commands.open(QFile::ReadOnly);
    QDateTime time;
    QFile log(path_ + "log.txt");
    QStringList args;
    while(!commands.atEnd()){
        args << QString::fromLocal8Bit(commands.readLine()).remove("\r\n").remove("\n");
    }
    QStringList command;
    for(int i=0;i<args.size();i++){
        command<<args[i].split(" ");
        if(i<args.size()-1)
            command.append("&");
    }
    log.open(QFile::Append);
    QTextStream writeStream(&log);
    writeStream<<time.currentDateTime().toString("yyyy-MM-dd  HH:mm:ss")+" Make \""+command.join(" ")+"\"\n";
    log.close();

    console.start("C:\\Windows\\System32\\cmd.exe",QStringList()<<"/K"<<command);
    console.waitForStarted();
    bool complete=console.waitForFinished();
    console.close();

    log.open(QFile::Append);
    writeStream<<time.currentDateTime().toString("yyyy-MM-dd  HH:mm:ss")+(complete?" Complete succesfull\n":" error timeout\n");
    log.close();


}

void Command::Set(QString aPath) {
    path_ = aPath;
}
