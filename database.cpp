#include "database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QQueue>
#include <cmath>
#include <QRegularExpression>
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
        "task4 TEXT DEFAULT 0,"
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

QString Database::registerUser(const QString& login, const QString& pass, const QString& email){
    // Проверка логина: длина от 3 до 10 символов
    if (login.length() < 3 || login.length() > 10) {
        return "Логин должен быть от 3 до 10 символов";
    }

    QRegularExpression loginRegex("^[a-zA-Z0-9_]+$");
    if (!loginRegex.match(login).hasMatch()) {
        return "Логин может содержать только буквы A-Z, a-z и символ подчёркивания (_)";
    }

    // Проверка логина: без пробелов и табуляции
    if (login.contains(" ") || login.contains("\t")) {
        return "Логин не может содержать пробелы или табуляцию";
    }

    // Проверка пароля: длина от 6 до 10 символов
    if (pass.length() < 6 || pass.length() > 10) {
        return "Пароль должен быть от 6 до 10 символов";
    }

    // Проверка пароля: без пробелов и табуляции
    if (pass.contains(" ") || pass.contains("\t")) {
        return "Пароль не может содержать пробелы или табуляцию";
    }

    // Проверка email: наличие символа @
    if (!email.contains("@")) {
        return "Email должен содержать символ @";
    }

    QSqlQuery query;
    query.prepare("INSERT OR IGNORE INTO users (login, password, email) VALUES (:login, :password, :email)");
    query.bindValue(":login", login);
    query.bindValue(":password", pass);
    query.bindValue(":email", email);

    QSqlQuery query1;
    query1.prepare("INSERT INTO tasks (login, task1, task2, task3, task4) VALUES (:login, 0, 0, 0, 0)");
    query1.bindValue(":login", login);
    query1.exec();

    if (query.exec()) {
        if (query.numRowsAffected() > 0) {
            return "";
        } else {
            return "Пользователь с таким логином уже существует";
        }
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
        int task4 = query.value("task4").toString().toInt();
        int solved = task1 + task2 + task3 + task4;

        return QString("%1/4").arg(solved);
    }

    return "Пользователь не найден или задачи отсутствуют";
}

bool Database::saveTaskResult(const QString& login, int taskNum, QString result) {
    qDebug() << "Данные начали заноситься в таблицу";
    QSqlQuery query;
    QString sql = QString("UPDATE tasks SET task%1 = :result WHERE login = :login").arg(taskNum);
    query.prepare(sql);
    query.bindValue(":result", result);
    query.bindValue(":login", login);
    qDebug() << "Данные занесены в таблицу1";
    return query.exec();
    qDebug() << "Данные занесены в таблицу";
}
QString Database::get_Task1(){
    QStringList  alTasks = {"Найди кратчайшее расстояние от вершины 2 до вершины 6 в графе с рёбрами:"
                " 1-2, 1-5, 2-3, 3-4, 3-7, 4-5, 5-6, 6-7. "
                "Вес всех рёбер равен 1. В ответе укажи только количество шагов.",
                "Найди кратчайшее расстояние от вершины 2 до вершины 6 в графе с рёбрами:"
                " 1-2, 2-3, 3-4, 4-5, 5-6, 1-6. Вес всех рёбер равен 1."
                " В ответе укажи только количество шагов.",
                "Найди кратчайшее расстояние от вершины 3 до вершины 6 в графе с рёбрами: "
                "1-2, 2-3, 3-4, 4-5, 5-6, 2-5. Вес всех рёбер равен 1."
                            " В ответе укажи только количество шагов."};
    randomIndexTask1 = rand() % 3;
    qDebug()<< "randomIndexTask1"<< randomIndexTask1;
    return alTasks[randomIndexTask1];
}
QString Database::get_Task2(){
    QStringList  alTasks = {"Дано: полином x², найти погрешность метода Симпсона на отрезке [0; 2]", //везде ответ 0
                           "Дано: полином 2x² + 3x + 1, найти погрешность метода Симпсона на отрезке [0; 1]",
                           "Дано: полином 5x² - 2x + 4, найти погрешность метода Симпсона на отрезке [-1; 2]"};
    randomIndexTask2 = rand() % 3;
    qDebug()<< "randomIndexTask2"<< randomIndexTask2;
    return alTasks[randomIndexTask2];
}
QString Database::get_Task3(){
    QStringList  alTasks = {"ДУ: y' = y, y(0) = 1. Точное решение: y = e^x. Шаг h = 0.1. Найдите погрешность метода "
                           "Эйлера на первом шаге. Ответ округлите до 5 знаков.", // ответ 0.01
                           "ДУ: y' = 2x, y(0) = 0. Точное решение: y = x². Шаг h = 0.2. Найдите погрешность метода "
                           "Эйлера на первом шаге. Ответ округлите до 5 знаков.",// ответ 0.04
                           "ДУ: y' = y², y(0) = 1. Точное решение: y = 1/(1 - x). Шаг h = 0.1. Найдите погрешность "
                           "метода Эйлера на первом шаге. Ответ округлите до 5 знаков."};// ответ 0.01
    randomIndexTask3 = rand() % 3;
    qDebug()<< "randomIndexTask3"<< randomIndexTask3;
    return alTasks[randomIndexTask3];
}
QString Database::get_Task4(){
    QStringList  alTasks = {"Функция f(x)=2x на [0,2], разрыв в x=1: f(1⁻)=2, f(1⁺)=3. "
                           "Найдите интеграл методом прямоугольников. Ответ округлите до 2 знаков.", // ответ 4
                           "Функция f(x)=x² на [-2,2], разрыв в x=0: f(0⁻)=0, f(0⁺)=2. "
                           "Найдите интеграл методом прямоугольников.",// ответ 6
                           "Функция f(x)=x на [0,3], разрывы в x=1 и x=2: f(1⁻)=1, f(1⁺)=3; f(2⁻)=2, f(2⁺)=5."
                           "Найдите интеграл методом прямоугольников."};// ответ 8.5
    randomIndexTask4 = rand() % 3;
    qDebug()<< "randomIndexTask4"<< randomIndexTask4;
    return alTasks[randomIndexTask4];
}
struct TaskData {
    int id;
    int vertexCount;
    QVector<QPair<int,int>> edges;
    int start;
    int end;
};
static QVector<TaskData> allTasks = {
    {1, 7, {{1,2},{1,5},{2,3},{3,4},{3,7},{4,5},{5,6},{6,7}}, 2, 6},
    {2, 6, {{1,2},{2,3},{3,4},{4,5},{5,6},{1,6}}, 2, 6},
    {3, 6, {{1,2},{2,3},{3,4},{4,5},{5,6},{2,5}}, 3, 6}
};
struct SimpsonTask {
    int id;
    double a, b;
    QVector<double> coeffs;
};
static QVector<SimpsonTask> simpsonTasks = {
    {1, 0.0, 2.0, {3, 2, 1}},
    {2, -1.0, 1.0, {1, -2, 3, -4}},
    {3, 0.0, 2.0, {1, -2, 1, 0, 0}}
};
double f1(double x, double y) { return y; }
double exact1(double x) { return exp(x); }

double f2(double x, double y) { return 2*x; }
double exact2(double x) { return x*x; }

double f3(double x, double y) { return y*y; }
double exact3(double x) { return 1.0 / (1.0 - x); }

static QVector<EulerTask> eulerTasks = {
    {1, 0.0, 1.0, 0.1, f1, exact1},
    {2, 0.0, 0.0, 0.2, f2, exact2},
    {3, 0.0, 1.0, 0.1, f3, exact3}
};
struct DiscontinuityTask {
    int id;
    double a, b;                         // отрезок [a, b]
    QVector<double> breakpoints;         // точки разрыва
    double (*fOnSegment)(double x, int segmentIndex);  // значения на каждом отрезке
};

double f11(double x, int segment) {
    if (segment == 0) return 2*x;      // [0,1] → 2x
    return 3;                          // [1,2] → 3? Нет, f(1.5)=3
}

double f22(double x, int segment) {
    if (segment == 0) return x*x;      // [-2,0]
    return 2;                          // [0,2] → 2
}

double f33(double x, int segment) {
    if (segment == 0) return x;        // [0,1]
    if (segment == 1) return 3;        // [1,2]
    return 5;                          // [2,3]
}
static QVector<DiscontinuityTask> discontinuityTasks = {
    {1, 0.0, 2.0, {1.0}, f11},
    {2, -2.0, 2.0, {0.0}, f22},
    {3, 0.0, 3.0, {1.0, 2.0}, f33}
};
double  Database::calculateShortestPath(int taskNum){
    if (taskNum == 1){
        qDebug() << "Задача 1, randomIndexTask1 =" << randomIndexTask1;
        TaskData task1 = allTasks[randomIndexTask1];
        return Database::bfsShortestPath(task1.vertexCount, task1.edges, task1.start, task1.end);
    }
    if (taskNum == 2){
        qDebug() << "Задача 2, randomIndexTask2 =" << randomIndexTask2;
        qDebug() << "simpsonTasks.size() =" << simpsonTasks.size();
        SimpsonTask task2 = simpsonTasks[randomIndexTask2];
        return Database::simpsonError(task2.coeffs, task2.a, task2.b);
    }
    if (taskNum == 3){
        qDebug() << "Задача 3, randomIndexTask3 =" << randomIndexTask3;
        qDebug() << "eulerTasks.size() =" << eulerTasks.size();
        EulerTask task3 = eulerTasks[randomIndexTask3];
        return Database::eulerError(task3);
    }
    if (taskNum == 4) {
        qDebug() << "Задача 4, randomIndexTask4 =" << randomIndexTask4;
        qDebug() << "discontinuityTasks.size() =" << discontinuityTasks.size();
        DiscontinuityTask task4 = discontinuityTasks[randomIndexTask4];
        return discontinuityRectangleIntegral(task4.a, task4.b, task4.breakpoints, task4.fOnSegment);
    }
}
int  Database::bfsShortestPath(int vertexCount, const QVector<QPair<int,int>>& edges, int start, int end) {
    QVector<QVector<int>> graph(vertexCount + 2);

    for (const auto& edge : edges) {
        int u = edge.first;
        int v = edge.second;
        graph[u].append(v);
        graph[v].append(u);
    }

    QVector<int> dist(vertexCount + 1, -1);
    QQueue<int> queue;

    dist[start] = 0;
    queue.enqueue(start);

    while (!queue.isEmpty()) {
        int current = queue.dequeue();
        if (current == end) {
            return dist[current];
        }
        for (int neighbor : graph[current]) {
            if (dist[neighbor] == -1) {  // не посещена
                dist[neighbor] = dist[current] + 1;
                queue.enqueue(neighbor);
            }
        }
    }
    return -1;
}


double Database::simpsonError(const QVector<double>& coeffs, double a, double b) {
    // Вычисление точного значения интеграла (первообразная)
    double exact = 0.0;
    int degree = coeffs.size() - 1;
    for (int i = 0; i < coeffs.size(); i++) {
        int power = degree - i;
        double newPower = power + 1;
        exact += coeffs[i] * (pow(b, newPower) - pow(a, newPower)) / newPower;
    }

    auto eval = [&](double x) {
        double res = 0.0;
        for (int i = 0; i < coeffs.size(); i++)
            res += coeffs[i] * pow(x, degree - i);
        return res;
    };

    double approx = (b - a) / 6.0 * (eval(a) + 4.0 * eval((a + b) / 2.0) + eval(b));

    return fabs(exact - approx);
}
double Database::eulerError(const EulerTask& task) {
    double y1_euler = task.y0 + task.h * task.f(task.x0, task.y0);
    double x1 = task.x0 + task.h;
    double y1_exact = task.exact(x1);
    double error = fabs(y1_exact - y1_euler);
    return round(error * 100.0) / 100.0;
}
double Database::discontinuityRectangleIntegral(double a, double b, const QVector<double>& breakpoints,
    double (*func)(double x, int segmentIndex)) {
    QVector<double> points = breakpoints;
    points.append(a);
    points.append(b);
    std::sort(points.begin(), points.end());

    double integral = 0.0;

    for (int i = 0; i < points.size() - 1; i++) {
        double left = points[i];
        double right = points[i + 1];
        if (right > left + 1e-12) {
            double mid = (left + right) / 2.0;
            double value = func(mid, i);  // значение на этом отрезке
            integral += value * (right - left);
        }
    }

    return round(integral * 100.0) / 100.0;  // округление до 2 знаков
}
