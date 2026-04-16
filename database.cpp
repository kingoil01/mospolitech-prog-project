#include "database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
Database* Database::p_instance = nullptr;
Database::DatabaseDestroyer Database::destroyer;
Database::Database(QObject *parent) : QObject(parent)
{
    qDebug() << "Database constructor";
}

Database::~Database()
{
    closeDatabase();
    qDebug() << "Database destructor";
}

Database* Database::getInstance()
{
    if (!p_instance) {
        p_instance = new Database();
        destroyer.initialize(p_instance);
    }
    return p_instance;
}
bool Database::openDatabase(const QString& dbName)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);

    if (!db.open()) {
        qDebug() << "Ошибка открытия БД:" << db.lastError().text();
        return false;
    }
    qDebug() << "База данных открыта:" << dbName;
    return true;
}

void Database::closeDatabase()
{
    if (db.isOpen()) {
        db.close();
        qDebug() << "База данных закрыта";
    }
}

bool Database::createTables()
{
    QSqlQuery query;
    bool success = query.exec(
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "login TEXT NOT NULL UNIQUE, "
        "password TEXT NOT NULL, "
        "email TEXT NOT NULL, "
        "socket_id INTEGER DEFAULT -1)"
        );
    bool success1 = query.exec(
    "CREATE TABLE IF NOT EXISTS tasks ("
        "user_id INTEGER PRIMARY KEY, "
        "login TEXT NOT NULL UNIQUE, "
        "task1 INTEGER DEFAULT 0,"
        "task2 INTEGER DEFAULT 0,"
        "task3 INTEGER DEFAULT 0,"
        "task4 INTEGER DEFAULT 0,"
        "FOREIGN KEY (login) REFERENCES users (login) ON DELETE CASCADE)"
        );
    if (!success) {
        qDebug() << "Ошибка создания таблицы users:" << query.lastError().text();
        return false;
    }
    if (!success1) {
        qDebug() << "Ошибка создания таблицы tasks:" << query.lastError().text();
        return false;
    }
    else qDebug() << "Таблица tasks создана";

    qDebug() << "Таблицы созданы (или уже существуют)";
    return true;
}

bool Database::registerUser(const QString& login, const QString& pass, const QString& email){
    QSqlQuery query;
    query.prepare("INSERT OR IGNORE INTO users (login, password, email) VALUES (:login, :password, :email)");
    query.bindValue(":login", login);
    query.bindValue(":password", pass);
    query.bindValue(":email", email);

    if (query.exec()) {
        qDebug() << "Тестовый пользователь добавлен";
        return true;
    }
}
bool Database::authoUser(const QString& login, const QString& pass){
   QSqlQuery query;
   query.prepare("SELECT COUNT(*) FROM users WHERE login = :login and password = :password");
   query.bindValue(":login", login);
   query.bindValue(":password", pass);
   query.exec();
   query.next();
   return query.value(0).toInt() == 1;
}

QString Database::stataUser(const QString& login){
    QSqlQuery query;
    query.prepare("select * from tasks "
                  "where login = :login");
    query.bindValue(":login", login);
    query.exec();
    qDebug() << "Bound values:" << query.boundValues();
    qDebug() << "Ошибка:" << query.lastError().text();
    qDebug() << "Запрос выполнен, rows:" << query.size();
    qDebug() << "Запрос выполнен, first row exists:" << query.first();
    if (query.first()) {
        int task1 = query.value("task1").toInt();
        int task2 = query.value("task2").toInt();
        int task3 = query.value("task3").toInt();
        int task4 = query.value("task4").toInt();
        return QString("Задачи: %1 %2 %3 %4")
            .arg(task1).arg(task2).arg(task3).arg(task4);
    }
    return "Пользователь не найден или задачи отсутствуют";
}
bool Database::createUserTasks(const int& user_id, const QString& login, const int& task1, const int& task2, const int& task3, const int& task4)
{
    QSqlQuery query;
    query.prepare("INSERT INTO tasks (user_id, login, task1, task2, task3, task4) "
                  "VALUES (:user_id, :login, :task1, :task2, :task3, :task4)");
    query.bindValue(":user_id", user_id);
    query.bindValue(":login", login);
    query.bindValue(":task1", task1);
    query.bindValue(":task2", task2);
    query.bindValue(":task3", task3);
    query.bindValue(":task4", task4);

    if (!query.exec()) {
        qDebug() << "Ошибка создания задач:" << query.lastError().text();
        return false;
    }
    return true;
}
