#include "command.h"

Command::Command(QString path, QObject *parent) : QObject(parent){
    _path=path;
}

void Command::MakeComand(){
    QFile commands(_path + "commands.txt");
    QProcess console;
    commands.open(QFile::ReadOnly);
    QStringList args;
    while(!commands.atEnd()){
        args << QString::fromLocal8Bit(commands.readLine()).remove("\r\n").remove("\n");
    }
    QStringList list;
    list<<"/K";
    for(int i=0;i<args.size();i++){
        list<<args[i].split(" ")<<"&";
    }
    console.start("C:\\Windows\\System32\\cmd.exe",list);
    console.waitForFinished();
    console.close();
    QFile log(_path + "log.txt");
    log.open(QFile::Append);
    QTextStream writeStream(&log);
    log.close();
}

void Command::Set(QString path){
    _path=path;
}
