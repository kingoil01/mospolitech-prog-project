#ifndef MANAGERFORM_H
#define MANAGERFORM_H

#include "authregform.h"
#include "mainform.h"
#include "test.h"
#include <QObject>

class ManagerForm: public QObject
{
        Q_OBJECT
private:
    authregform *w;
    MainForm *m;
    TEST *t;
public slots:
    void slot_auth();
    void slot_exit();
    void slot_test();
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
