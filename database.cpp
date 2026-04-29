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
        "task1 TEXT DEFAULT 0,"
        "task2 TEXT DEFAULT 0,"
        "task3 TEXT DEFAULT 0,"
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
    query.prepare("SELECT * FROM tasks WHERE login = :login");
    query.bindValue(":login", login);

    if (!query.exec()) {
        return "Ошибка запроса";
    }

    if (query.first()) {
        int task1 = query.value("task1").toString().toInt();
        int task2 = query.value("task2").toString().toInt();
        int task3 = query.value("task3").toString().toInt();

        int solved = task1 + task2 + task3;

        return QString("%1/3").arg(solved);
    }

    return "Пользователь не найден или задачи отсутствуют";
}
int Database::getCorrectAnswer(int taskNumber) {
    switch(taskNumber) {
    case 1: return 3;
    case 2: return 2;
    case 3: return 3;
    default: return -1;
    }
}
bool Database::saveTaskResult(const QString& login, int taskNum, QString result) {
    QSqlQuery query;
    QString sql = QString("UPDATE tasks SET task%1 = :result WHERE login = :login").arg(taskNum);
    query.prepare("UPDATE tasks SET task%1 = :result WHERE login = :login");
    query.bindValue(":result", result);
    query.bindValue(":login", login);
    return query.exec();
}
