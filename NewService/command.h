#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>
#include <QProcess>
#include <QFile>
#include <QDir>
#include <QStringList>
#include <QTextStream>
#include <QDateTime>

class Command : public QObject
{
    Q_OBJECT
public:
    explicit Command(QString path, QObject *parent = nullptr);
    Command() {};
    void Set(QString path);
signals:

public slots:
    void MakeComand();

private:
    QString _path;
};

#endif // COMMAND_H
