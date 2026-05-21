#include "parsing.h"
#include <QDebug>
CommandParsing::CommandParsing(QObject *parent) : QObject(parent){
    my_database = Database::getInstance();
    my_database->openDatabase("test1.db");
    my_database->createTables();
}
QString CommandParsing::handleSubmit(QStringList& parts, QString login) {
    qDebug() << "handleSubmit";
    int correctCount = 0;
    int totalTasks = parts.size() - 2;

    for (int i = 1; i <= totalTasks; i++) {
        QStringList taskParts = parts[i].split(":");
        int taskNum = taskParts[0].toInt();
        int userAnswer = taskParts[1].toInt();
        int correctAnswer = my_database->calculateShortestPath(taskNum);
        qDebug() <<"taskNum"<<taskNum<<"userAnswer" << userAnswer << ", correctAnswer" << correctAnswer;
        if (userAnswer == correctAnswer) {
            correctCount++;
            my_database->saveTaskResult(login, taskNum, "1");
        } else {
            my_database->saveTaskResult(login, taskNum, "0");
        }
    }

    return "";
}
QString CommandParsing::Command(const QString &dataStr){
    QStringList parts = dataStr.split(" ");
    QString command = parts[0];
    QString res = "";
    if (command == "auth"){
        qDebug() << "PARSING: Обрабатываю команду:" << command;
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
        qDebug() << "PARSING: Обрабатываю команду:" << command;
        if (parts.size()<4){
            res = "Данные введены не полностью";
        }
        else {
        QString Login = parts[1];
        QString Pass = parts[2];
        QString Email = parts[3];
        QString result = my_database->registerUser(Login, Pass, Email);
        if (result.isEmpty()) {
            res = "Регистрация успешна";
        } else {
            res = "Ошибка: " + result;
        }
    }
    }
    else if (command == "stata"){
        qDebug() << "PARSING: Обрабатываю команду:" << command;
        QString Login = parts[1];
        res = my_database->stataUser(Login);
    }
    else if (command == "task1"){
        res = my_database->get_Task1();
    }
    else if (command == "task2"){
        res = my_database->get_Task2();
    }
    else if (command == "task3"){
        res = my_database->get_Task3();

    }
    else if (command == "task4"){
        res = my_database->get_Task4();
    }
    else if (command == "submit") {
        qDebug() << "PARSING: Обрабатываю команду:" << command;
        // parts = ["submit", "1:3", "2:2", "3:3", ]
        QString login = parts.last();
        res = handleSubmit(parts, login);
    }
    return res;
}
