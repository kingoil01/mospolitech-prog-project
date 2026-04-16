#include "parsing.h"
#include <QDebug>
CommandParsing::CommandParsing(QObject *parent) : QObject(parent){
    my_database = Database::getInstance();
    my_database->openDatabase("test1.db");
    my_database->createTables();
}
QString CommandParsing::Calc(){
    return "Калькулятор: ";
}
QString CommandParsing::Rebra(){
    return "Здесь будут рёбра: ";
}
QString CommandParsing::Way(){
    return "Здесь будет путь: ";
}

QString CommandParsing::Command(const QString &dataStr){
    QStringList parts = dataStr.split(" ");
    QString command = parts[0];
    QString res = "";
    if (command == "Echo"){
        res = dataStr;
    }
    else if (command == "Calc"){
        res = Calc();
    }
    else if (command == "Way"){
        res = Way();
    }
    else if (command == "Rebra"){
        res = Rebra();
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
    else if (command == "cr"){
        int User_id = parts[1].toInt();
        QString Login = parts[2];
        int Task1 = parts[3].toInt();
        int Task2 = parts[4].toInt();
        int Task3 = parts[5].toInt();
        int Task4 = parts[6].toInt();
        bool true_or_false = my_database->createUserTasks(User_id, Login, Task1, Task2, Task3, Task4);
        if (true_or_false){
            res = "Данные заполнены";
        }
        else res = "Данные не заполнены";
    }
    else if (command == "zadacha"){
        res = "Задача подгружается с сервера, сколько будет 2 + 2";
    }
    return res;
}
