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
    void slot_auth();//авторизация подтверждена
    void slot_exit();//выход из окна mainform
    void slot_test();//старт теста
    void slot_exit_test();//завершение теста
public:
    static QString login;
    ManagerForm();

    //установить и получить логин авторизированного пользователя
    static void setLogin(QString log){
        login = log;
    }
    static QString getLogin(){
        return login;
    }
};

#endif // MANAGERFORM_H
