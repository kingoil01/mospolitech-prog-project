#ifndef PARSING_H
#define PARSING_H
#include <QObject>
#include "database.h"
class CommandParsing : public QObject{
    Q_OBJECT
private:
    QString Calc();
    QString Way();
    QString Rebra();
    Database* my_database;
public:
    explicit CommandParsing(QObject *parent = nullptr);
    QString Command(const QString &command);
};


#endif
