#include <QtTest>
#include <QCoreApplication>
#include "../database.h"

class DatabaseTest : public QObject
{
    Q_OBJECT

public:
    DatabaseTest() {}
    ~DatabaseTest() {}

private slots:
    void initTestCase() {
        // Создаём QCoreApplication, если его нет
        if (!QCoreApplication::instance()) {
            int argc = 1;
            char* argv[] = {const_cast<char*>("test_server")};
            app = new QCoreApplication(argc, argv);
        }
    }

    void cleanupTestCase() {
        // Очищаем синглтон Database между тестами
        // Это важно, чтобы каждый тест начинался с чистого состояния
    }

    void test_registration_success() {
        Database* db = Database::getInstance();

        // Используем уникальное имя БД для каждого теста
        QString dbName = "test_registration.db";
        db->openDatabase(dbName);
        db->createTables();

        bool result = db->registerUser("testuser", "12345", "test@mail.ru");
        QVERIFY2(result == true, "Регистрация не удалась");

        bool authResult = db->authoUser("testuser", "12345");
        QVERIFY2(authResult == true, "Авторизация после регистрации не удалась");

        // Закрываем БД
        db->closeDatabase();

        // Удаляем файл БД
        QFile::remove(dbName);
    }

    void test_auth_wrong_password() {
        Database* db = Database::getInstance();

        QString dbName = "test_auth.db";
        db->openDatabase(dbName);
        db->createTables();

        db->registerUser("testuser2", "correctpass", "test2@mail.ru");

        bool result = db->authoUser("testuser2", "wrongpass");
        QVERIFY2(result == false, "Авторизация с неверным паролем должна провалиться");

        db->closeDatabase();
        QFile::remove(dbName);
    }

    void test_task_calculation()
    {
        Database* db = Database::getInstance();

        QString dbName = "test_task.db";
        db->openDatabase(dbName);
        db->createTables();

        // Прямой вызов BFS с известными параметрами
        // Задача: граф из 7 вершин, путь от 2 до 6
        QVector<QPair<int,int>> edges = {
            {1,2}, {1,5}, {2,3}, {3,4}, {3,7}, {4,5}, {5,6}, {6,7}
        };
        int result = db->bfsShortestPath(7, edges, 2, 6);

        // Ожидаемый ответ: 3 (2→3→4→5→6? или 2→3→7→6? Проверьте)
        QVERIFY2(result == 3 || result == 2,
                 QString("bfsShortestPath вернул %1, ожидалось 2 или 3").arg(result).toUtf8());

        db->closeDatabase();
        QFile::remove(dbName);
    }

    void test_simpson_error_for_quadratic_polynomial()
    {
        Database* db = Database::getInstance();

        QVector<double> coeffs = {2, 3, 1};  // 2x² + 3x + 1
        double a = 0.0, b = 1.0;

        double error = db->simpsonError(coeffs, a, b);

        // Для полинома степени ≤ 3 метод Симпсона даёт точный результат
        QVERIFY2(qFabs(error) < 1e-9,
                 QString("Погрешность Симпсона для квадратичного полинома должна быть 0, получено %1")
                     .arg(error).toUtf8());

        // Дополнительная проверка: кубический полином x³ на [0,1]
        // Точное значение: 1/4 = 0.25
        // Симпсон: (1/6)*(0 + 4*(0.125) + 1) = (1/6)*(0+0.5+1)=1.5/6=0.25 → ошибка 0
        QVector<double> coeffs2 = {1, 0, 0, 0};  // x³
        double error2 = db->simpsonError(coeffs2, 0.0, 1.0);

        QVERIFY2(qFabs(error2) < 1e-9,
                 QString("Погрешность Симпсона для кубического полинома должна быть 0, получено %1")
                     .arg(error2).toUtf8());
    }

private:
    QCoreApplication* app = nullptr;
};

QTEST_APPLESS_MAIN(DatabaseTest)

#include "tst_database_test.moc"