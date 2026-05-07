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
    void onEndClicked(QString ans1, QString ans2, QString ans3, QString ans4);
    onGetStatClicked();
};

#endif // BUTTONHANDLER_H
