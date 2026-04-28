#include "managerform.h"

QString ManagerForm::login;

ManagerForm::ManagerForm() {
    w = new authregform();
    connect(w, &authregform::auth_ok, this, &ManagerForm::slot_auth);
    w->show();
}

void ManagerForm::slot_auth()//слот для авторизации
{
    if (w) {
        w->hide();
    }
    m = new MainForm();
    connect(m, &MainForm::exit_ok, this, &ManagerForm::slot_exit);
    connect(m, &MainForm::test_ok, this, &ManagerForm::slot_test);
    m->show();
}

void ManagerForm::slot_exit()//слот для выхода из окна mainform
{
    if (m) {
        m->hide();
    }
    w->show();
}

void ManagerForm::slot_exit_test(){//слот для завершения теста
    if (t){
        t->hide();
    }
    m->show();
}

void ManagerForm::slot_test(){//слот для старта теста
    if (m) {
        m->hide();
    }
    t = new TEST();
    connect(t, &TEST::exit_test, this, &ManagerForm::slot_exit_test);
    t->show();
}



