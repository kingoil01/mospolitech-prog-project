#include "clientcontroller.h"
#include "managerform.h"

#include <QObject>

ClientController* ClientController::instance = nullptr;
ClientControllerDestroyer ClientController::destroyer;

QString ClientController::makeLoginCommand(QString& login, QString& password){//создать команду логин
    return QString("auth %1 %2").arg(login).arg(password);
}

QString ClientController::makeTaskCommand(){//создать команду получить задачу
    return QString("zadacha");
}

QString ClientController::makeRegisterCommand(QString& login, QString& password, QString& email){//создать команду регистрации
    return QString("reg %1 %2 %3").arg(login).arg(password).arg(email);
}

QString ClientController::makeStatCommand(){//создать команду получить статистику
    return QString("stata %1").arg(ManagerForm::login);
}

QString ClientController::parseServerResponse(QString &response){//парсинг ответа сервера
    if (response.contains("успешно") || response.contains("success")) {
        return "SUCCESS";
    }
    if (response.contains("не удалась") || response.contains("failed")) {
        return "FAILED";
    }
}
