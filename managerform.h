#ifndef MANAGERFORM_H
#define MANAGERFORM_H

#include "authregform.h"
#include "mainform.h"
#include <QObject>

class ManagerForm: public QObject
{
        Q_OBJECT
private:
    authregform *w;
    MainForm *m;
public slots:
    void slot_auth();
public:
    static QString login;
    ManagerForm();
    static void setLogin(QString log){
        login = log;
    }
    static QString getLogin(){
        return login;
    }
};

#endif // MANAGERFORM_H
