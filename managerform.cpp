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
    m->show();
}
