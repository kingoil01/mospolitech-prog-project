#include "parsing.h"
#include <QDebug>
CommandParsing::CommandParsing(QObject *parent) : QObject(parent){
    my_database = Database::getInstance();
    my_database->openDatabase("test1.db");
    my_database->createTables();
}
QString CommandParsing::handleSubmit(QStringList& parts, QString login) {
    int correctCount = 0;
    int totalTasks = parts.size() - 1;

    for (int i = 1; i <= totalTasks; i++) {
        QStringList taskParts = parts[i].split(":");
        int taskNum = taskParts[0].toInt();
        int userAnswer = taskParts[1].toInt();

        int correctAnswer = my_database->getCorrectAnswer(taskNum);

        if (userAnswer == correctAnswer) {
            correctCount++;
            my_database->saveTaskResult(login, taskNum, "1");
        } else {
            // Сохраняем в БД: задача не решена
            my_database->saveTaskResult(login, taskNum, "0");
        }
    }

    return "Ответы приняты";
}

QString CommandParsing::Command(const QString &dataStr){
    QStringList parts = dataStr.split(" ");
    QString command = parts[0];
    QString res = "";
    if (command == "Echo"){
        res = dataStr;
    }
    else if (command == "auth"){
        if (parts.size()<3){
            res = "Данные введены не полностью";
        }
        else {
        QString Login = parts[1];
        QString Pass = parts[2];
        bool true_or_false = my_database->authoUser(Login, Pass);
        if (true_or_false){
            res = "Авторизация выполнена успешно";
        }
        else res = "Авторизация не удалась";
        }
    }
    else if (command == "reg"){
        if (parts.size()<4){
            res = "Данные введены не полностью";
        }
        else {
        QString Login = parts[1];
        QString Pass = parts[2];
        QString Email = parts[3];
        bool true_or_false = my_database->registerUser(Login, Pass, Email);
        if (true_or_false){
            res = "Регистрация выполнена успешно";
        }
        else res = "Регистрация не удалась";
        }
    }

    else if (command == "stata"){
        QString Login = parts[1];
        res = my_database->stataUser(Login);
    }
    else if (command == "task1"){
        res = "Найди кратчайшее расстояние от вершины 2 до вершины 6 в графе с рёбрами:"
              " 1-2, 1-5, 2-3, 3-4, 3-7, 4-5, 5-6, 6-7. "
              "Вес всех рёбер равен 1. В ответе укажи только количество шагов.";
    }
    else if (command == "task2"){
        res = "Найди кратчайшее расстояние от вершины 2 до вершины 6 в графе с рёбрами:"
              " 1-2, 2-3, 3-4, 4-5, 5-6, 1-6. Вес всех рёбер равен 1."
              " В ответе укажи только количество шагов.";
    }
    else if (command == "task3"){
        res = "Найди кратчайшее расстояние от вершины 3 до вершины 6 в графе с рёбрами: "
              "1-2, 2-3, 3-4, 4-5, 5-6, 2-5. Вес всех рёбер равен 1."
              " В ответе укажи только количество шагов.";
    }
    else if (command == "submit") {
        // parts = ["submit", "1:3", "2:2", "3:3", ]
        QString login = parts[-1];
        res = handleSubmit(parts, login);
    }
    return res;
}
