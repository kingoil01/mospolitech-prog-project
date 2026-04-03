#include "managerform.h"

QString ManagerForm::login;

ManagerForm::ManagerForm() {
    w = new authregform();
    connect(w, &authregform::auth_ok, this, &ManagerForm::slot_auth);
    w->show();
}

void ManagerForm::slot_auth()
{
    if (w) {
        w->hide();
    }
    m = new MainForm();
    connect(m, &MainForm::exit_ok, this, &ManagerForm::slot_exit);
    connect(m, &MainForm::test_ok, this, &ManagerForm::slot_test);
    m->show();
}

void ManagerForm::slot_exit()
{
    if (m) {
        m->hide();
    }
    w->show();
}

void ManagerForm::slot_test(){
    if (m) {
        m->hide();
    }
    t = new TEST();
    t->show();
}

