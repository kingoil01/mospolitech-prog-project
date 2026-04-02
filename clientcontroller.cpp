#include "clientcontroller.h"
#include "managerform.h"

#include <QObject>

ClientController* ClientController::instance = nullptr;
ClientControllerDestroyer ClientController::destroyer;

QString ClientController::makeLoginCommand(QString& login, QString& password){
    return QString("auth %1 %2").arg(login).arg(password);
}

QString ClientController::makeRegisterCommand(QString& login, QString& password, QString& email){
    return QString("reg %1 %2 %3").arg(login).arg(password).arg(email);
}

QString ClientController::makeStatCommand(){
    return QString("stata %1").arg(ManagerForm::login);
}

QString ClientController::parseServerResponse(QString &response){
    if (response.contains("успешно") || response.contains("success")) {
        return "SUCCESS";
    }
    if (response.contains("не удалась") || response.contains("failed")) {
        return "FAILED";
    }
}
