#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>

    class Database : public QObject
{
    Q_OBJECT

private:
    explicit Database(QObject *parent = nullptr);

    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    static Database* p_instance;
    static class DatabaseDestroyer {
    public:
        ~DatabaseDestroyer() { delete p_instance; }
        void initialize(Database* p) { p_instance = p; }
    } destroyer;

    QSqlDatabase db;

public:
    static Database* getInstance();
    ~Database();
    // void get_task();
    bool openDatabase(const QString& dbName);
    void closeDatabase();
    bool createTables();
    bool registerUser(const QString& login, const QString& pass, const QString& email);
    bool authoUser(const QString& login, const QString& pass);
    QString stataUser(const QString& login);
    void read_test();
    bool createUserTasks(const int& user_id, const QString& login, const int& task1, const int& task2, const int& task3, const int& task4);
};

#endif
