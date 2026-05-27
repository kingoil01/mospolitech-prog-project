#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>

///
/// \brief The Database class Класс для управления подключением к базе данных SQLite
///
/// Реализован по паттерну "синглтон" — гарантирует наличие только одного
/// экземпляра подключения к БД на всю программу.
///
/// Основные возможности:
/// - Открытие и закрытие базы данных SQLite
/// - Создание таблиц users и tasks (если не существуют)
/// - Регистрация и авторизация пользователей
/// - Получение статуса задач пользователя
/// - Сохранение результатов задач
/// - Генерация текстов задач (4 типа)
/// - Вычисление правильных ответов для задач
///
/// Управление памятью осуществляется автоматически через вложенный класс DatabaseDestroyer.
///
struct EulerTask {
    int id;             ///< Идентификатор задачи
    double x0, y0;      ///< Начальные условия (x0, y0)
    double h;           ///< Шаг метода Эйлера
    double (*f)(double x, double y);      ///< Правая часть ДУ y' = f(x,y)
    double (*exact)(double x);            ///< Точное решение ДУ
};

class Database : public QObject
{
    Q_OBJECT

private:
    /// \brief Приватный конструктор (синглтон)
    /// Запрещает создание объектов класса извне
    explicit Database(QObject *parent = nullptr);

    /// \brief Запрет конструктора копирования
    Database(const Database&) = delete;

    /// \brief Запрет оператора присваивания
    Database& operator=(const Database&) = delete;

    /// \brief p_instance Указатель на единственный экземпляр (синглтон)
    static Database* p_instance;

    /// \brief Вспомогательный класс для автоматического удаления синглтона
    static class DatabaseDestroyer {
    public:
        /// \brief Деструктор удаляет синглтон при завершении программы
        ~DatabaseDestroyer() { delete p_instance; }
        /// \brief Сохраняет указатель на синглтон
        void initialize(Database* p) { p_instance = p; }
    } destroyer;

    /// \brief Объект подключения к базе данных
    QSqlDatabase db;

    /// \brief Случайные индексы для выбора варианта каждой задачи
    int randomIndexTask1;
    int randomIndexTask2;
    int randomIndexTask3;
    int randomIndexTask4;

public:
    ///
    /// \brief Получает единственный экземпляр класса Database (синглтон)
    /// Создаёт объект Database при первом вызове и возвращает указатель на него.
    /// При последующих вызовах возвращает тот же объект.
    /// Удаление объекта происходит автоматически при завершении программы
    /// благодаря классу DatabaseDestroyer.
    /// \return Указатель на единственный экземпляр Database
    ///
    static Database* getInstance();

    /// \brief Деструктор, закрывает подключение к базе данных
    ~Database();

    ///
    /// \brief Открывает соединение с базой данных SQLite
    /// \param dbName Имя файла базы данных
    /// \return true, если удалось открыть, false — ошибка
    ///
    bool openDatabase(const QString& dbName);

    ///
    /// \brief Закрывает соединение с базой данных
    ///
    void closeDatabase();

    ///
    /// \brief Создаёт таблицы users и tasks, если они не существуют
    ///
    /// Таблицы:
    /// - users: id, login, password, email, socket_id
    /// - tasks: user_id, login, task1-task4
    ///
    /// \return true, если обе таблицы успешно созданы (или уже существуют)
    ///
    bool createTables();

    ///
    /// \brief Регистрирует нового пользователя в системе
    /// Добавляет запись в таблицу users и создаёт запись задач со значениями 0
    /// \param login Логин пользователя (уникальный)
    /// \param pass Пароль пользователя
    /// \param email Адрес электронной почты
    /// \return true, если регистрация успешна, false — пользователь уже существует
    ///
    bool registerUser(const QString& login, const QString& pass, const QString& email);

    ///
    /// \brief Проверяет учётные данные пользователя
    /// \param login Логин пользователя
    /// \param pass Пароль пользователя
    /// \return true, если логин и пароль верны
    ///
    bool authoUser(const QString& login, const QString& pass);

    ///
    /// \brief Возвращает статистику решённых задач пользователя
    /// \param login Логин пользователя
    /// \return Строка формата "X/4", где X — количество решённых задач
    ///
    QString stataUser(const QString& login);

    ///
    /// \brief Сохраняет результат выполнения задачи
    /// \param login Логин пользователя
    /// \param taskNum Номер задачи (1-4)
    /// \param result Результат ("1" — решено, "0" — не решено)
    /// \return true, если сохранение успешно
    ///
    bool saveTaskResult(const QString& login, int taskNum, QString result);

    ///
    /// \brief Возвращает текст задания №1 (поиск кратчайшего пути в графе)
    /// \return Строка с условием задачи
    ///
    QString get_Task1();

    ///
    /// \brief Возвращает текст задания №2 (погрешность метода Симпсона)
    /// \return Строка с условием задачи
    ///
    QString get_Task2();

    ///
    /// \brief Возвращает текст задания №3 (погрешность метода Эйлера)
    /// \return Строка с условием задачи
    ///
    QString get_Task3();

    ///
    /// \brief Возвращает текст задания №4 (интеграл с разрывами)
    /// \return Строка с условием задачи
    ///
    QString get_Task4();

    ///
    /// \brief Вычисляет правильный ответ для задачи по её номеру
    /// \param taskNum Номер задачи (1-4)
    /// \return Числовое значение правильного ответа
    ///
    double calculateShortestPath(int taskIndex);

    ///
    /// \brief Поиск кратчайшего пути в графе (BFS)
    /// \param vertexCount Количество вершин
    /// \param edges Список рёбер
    /// \param start Стартовая вершина
    /// \param end Конечная вершина
    /// \return Длина кратчайшего пути или -1, если путь не найден
    ///
    int bfsShortestPath(int vertexCount, const QVector<QPair<int,int>>& edges, int start, int end);

    ///
    /// \brief Вычисляет погрешность метода Симпсона для полинома
    /// \param coeffs Коэффициенты полинома (начиная со старшей степени)
    /// \param a Нижний предел интегрирования
    /// \param b Верхний предел интегрирования
    /// \return Абсолютная погрешность
    ///
    double simpsonError(const QVector<double>& coeffs, double a, double b);

    ///
    /// \brief Вычисляет погрешность метода Эйлера на первом шаге
    /// \param task Структура с параметрами задачи
    /// \return Погрешность, округлённая до 2 знаков
    ///
    double eulerError(const EulerTask& task);

    ///
    /// \brief Вычисляет интеграл методом прямоугольников для функций с разрывами
    /// \param a Нижний предел
    /// \param b Верхний предел
    /// \param breakpoints Точки разрыва
    /// \param func Функция, возвращающая значение на каждом сегменте
    /// \return Значение интеграла, округлённое до 2 знаков
    ///
    double discontinuityRectangleIntegral(double a, double b, const QVector<double>& breakpoints,
                                          double (*func)(double x, int segmentIndex));

    ///
    /// \brief Возвращает объект подключения к БД (для тестов)
    ///
    QSqlDatabase getDatabase() { return db; }
};

#endif