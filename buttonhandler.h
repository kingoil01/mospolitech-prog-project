#ifndef BUTTONHANDLER_H
#define BUTTONHANDLER_H

#include "clientcontroller.h"
#include <QObject>

class ButtonHandler: public QObject
{
    Q_OBJECT
private:
    ClientController* controller;
public:
    ButtonHandler();

    void onLoginClicked(QString login, QString password);
    void onRegisterClicked(QString login, QString password, QString email);
    onGetStatClicked();
};

#endif // BUTTONHANDLER_H
