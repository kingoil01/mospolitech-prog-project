#include "buttonhandler.h"
#include "clientcontroller.h"
#include "mytcpclient.h"
#include "managerform.h"
#include <QObject>

ButtonHandler::ButtonHandler() {
    controller = ClientController::getInstance();
}

void ButtonHandler::onLoginClicked(QString login, QString password){//отправить запрос на авторизацию после нажатия
    QString q = controller->makeLoginCommand(login, password);
    MyTcpClient::getInstance()->sendMessage(q);
}

void ButtonHandler::onRegisterClicked(QString login, QString password, QString email){//отправить запрос на регистрацию после нажатия
    QString q = controller->makeRegisterCommand(login, password, email);
    MyTcpClient::getInstance()->sendMessage(q);
}

void ButtonHandler::onEndClicked(QString ans1, QString ans2, QString ans3){
    QString log = ManagerForm::getLogin();
    QString q = controller->makeEndTestCommand(log, ans1, ans2, ans3);
    MyTcpClient::getInstance()->sendMessage(q);
}
