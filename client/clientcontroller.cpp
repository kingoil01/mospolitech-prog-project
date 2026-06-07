#include "clientcontroller.h"
#include "managerform.h"

#include <QObject>

ClientController* ClientController::instance = nullptr;
ClientControllerDestroyer ClientController::destroyer;

QString ClientController::makeLoginCommand(QString& login, QString& password){//создать команду логин
    return QString("auth %1 %2").arg(login).arg(password);
}

QString ClientController::makeTask1Command(){//создать команду получить задачу
    return QString("task1");
}

QString ClientController::makeTask2Command(){//создать команду получить задачу
    return QString("task2");
}

QString ClientController::makeTask3Command(){//создать команду получить задачу
    return QString("task3");
}

QString ClientController::makeTask4Command(){//создать команду получить задачу
    return QString("task4");
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
    return response;
}

QString ClientController::makeEndTestCommand(QString log, QString ans1, QString ans2, QString ans3, QString ans4){
    return QString("submit 1:%1 2:%2 3:%3 4:%4 %5").arg(ans1).arg(ans2).arg(ans3).arg(ans4).arg(log);
}
