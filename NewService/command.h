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
    Command(QObject *parent = nullptr);
    void Set(QString path);
signals:

public slots:
    void MakeComand();

private:
    QString path_;
    QProcess *process_;
};

#endif // COMMAND_H
