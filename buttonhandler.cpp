#include "buttonhandler.h"
#include "clientcontroller.h"
#include "mytcpclient.h"
#include <QObject>

ButtonHandler::ButtonHandler() {
    controller = ClientController::getInstance();
}

void ButtonHandler::onLoginClicked(QString login, QString password){
    QString q = controller->makeLoginCommand(login, password);
    MyTcpClient::getInstance()->sendMessage(q);
}

void ButtonHandler::onRegisterClicked(QString login, QString password, QString email){
    QString q = controller->makeRegisterCommand(login, password, email);
    MyTcpClient::getInstance()->sendMessage(q);
}
