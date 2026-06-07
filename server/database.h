#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QVector>
#include <QPair>

/**
 * @struct EulerTask
 * @brief Структура, описывающая задачу для численного решения ДУ методом Эйлера.
 */
struct EulerTask {
    int id;                        /**< Идентификатор задачи */
    double x0;                     /**< Начальная точка x */
    double y0;                     /**< Начальное условие y(x0) */
    double h;                      /**< Шаг интегрирования */
    double (*f)(double, double);   /**< Указатель на функцию правой части ДУ y' = f(x, y) */
    double (*exact)(double);       /**< Указатель на функцию точного решения для проверки */
};

/**
 * @class Database
 * @brief Класс-синглтон для управления подключением к базе данных SQLite и выполнения вычислений.
 *
 * Обеспечивает авторизацию, регистрацию, хранение прогресса пользователей,
 * а также содержит математическую логику для генерации и проверки серверных задач.
 */
class Database : public QObject
{
    Q_OBJECT

private:
    /**
     * @brief Приватный конструктор. Запрещает создание объектов класса извне.
     * @param parent Родительский объект QObject.
     */
    explicit Database(QObject *parent = nullptr);

    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    static Database* p_instance; /**< Указатель на единственный экземпляр класса */

    /**
     * @class DatabaseDestroyer
     * @brief Вспомогательный класс для автоматического удаления синглтона при завершении программы.
     */
    static class DatabaseDestroyer {
    public:
        /** @brief Деструктор, освобождающий память синглтона. */
        ~DatabaseDestroyer() { delete p_instance; }
        /**
         * @brief Инициализирует деструктор указателем на синглтон.
         * @param p Указатель на экземпляр Database.
         */
        void initialize(Database* p) { p_instance = p; }
    } destroyer;

    QSqlDatabase db; /**< Объект подключения к базе данных SQLite */

    int randomIndexTask1; /**< Индекс текущего варианта для задачи 1 */
    int randomIndexTask2; /**< Индекс текущего варианта для задачи 2 */
    int randomIndexTask3; /**< Индекс текущего варианта для задачи 3 */
    int randomIndexTask4; /**< Индекс текущего варианта для задачи 4 */

public:
    /**
     * @brief Возвращает единственный экземпляр класса Database.
     * @return Указатель на экземпляр Database.
     */
    static Database* getInstance();

    /** @brief Деструктор. Закрывает соединение с базой данных. */
    ~Database();

    /**
     * @brief Открывает соединение с файлом базы данных.
     * @param dbName Имя файла базы данных.
     * @return true, если соединение успешно открыто, иначе false.
     */
    bool openDatabase(const QString& dbName);

    /** @brief Закрывает текущее соединение с базой данных. */
    void closeDatabase();

    /**
     * @brief Создает таблицы 'users' и 'tasks', если они отсутствуют.
     * @return true, если таблицы успешно созданы/существуют, иначе false.
     */
    bool createTables();

    /**
     * @brief Регистрирует нового пользователя с валидацией входных данных.
     * @param login Логин (3-10 символов, без пробелов, только A-Z, a-z, 0-9, _)
     * @param pass Пароль (6-10 символов, без пробелов)
     * @param email Адрес электронной почты (должен содержать '@')
     * @return Пустая строка в случае успеха, или текст ошибки при провале валидации/дублировании логина.
     */
    QString registerUser(const QString& login, const QString& pass, const QString& email);

    /**
     * @brief Аутентифицирует пользователя по логину и паролю.
     * @param login Логин пользователя.
     * @param pass Пароль пользователя.
     * @return true, если учетные данные верны, иначе false.
     */
    bool authoUser(const QString& login, const QString& pass);

    /**
     * @brief Возвращает статистику выполнения задач пользователя.
     * @param login Логин пользователя.
     * @return Строка формата "X/4", где X — количество решенных задач, либо сообщение об ошибке.
     */
    QString stataUser(const QString& login);

    /**
     * @brief Сохраняет результат (статус выполнения) конкретной задачи в базу данных.
     * @param login Логин пользователя.
     * @param taskNum Номер задачи (1-4).
     * @param result Статус выполнения (например, "1" — решено, "0" — нет).
     * @return true, если обновление прошло успешно, иначе false.
     */
    bool saveTaskResult(const QString& login, int taskNum, QString result);

    /** @brief Генерирует текст и выбирает случайный вариант для Задачи 1 (Графы). */
    QString get_Task1();
    /** @brief Генерирует текст и выбирает случайный вариант для Задачи 2 (Метод Симпсона). */
    QString get_Task2();
    /** @brief Генерирует текст и выбирает случайный вариант для Задачи 3 (Метод Эйлера). */
    QString get_Task3();
    /** @brief Генерирует текст и выбирает случайный вариант для Задачи 4 (Интеграл с разрывом). */
    QString get_Task4();

    /**
     * @brief Рассчитывает эталонный ответ для задачи на основе выбранного случайного индекса.
     * @param taskIndex Номер задачи (1-4).
     * @return Численный результат (расстояние, погрешность или значение интеграла).
     */
    double calculateShortestPath(int taskIndex);

    /**
     * @brief Поиск кратчайшего пути в неразмеченном графе методом обхода в ширину (BFS).
     * @param vertexCount Количество вершин в графе.
     * @param edges Список ребер графа (пары смежных вершин).
     * @param start Начальная вершина.
     * @param end Конечная вершина.
     * @return Количество шагов (ребер) в кратчайшем пути, или -1, если путь не найден.
     */
    int bfsShortestPath(int vertexCount, const QVector<QPair<int,int>>& edges, int start, int end);

    /**
     * @brief Вычисляет абсолютную погрешность метода Симпсона для полинома по сравнению с точным интегралом.
     * @param coeffs Вектор коэффициентов полинома (от старшей степени к младшей).
     * @param a Левая граница интегрирования.
     * @param b Правая граница интегрирования.
     * @return Абсолютная величина погрешности.
     */
    double simpsonError(const QVector<double>& coeffs, double a, double b);

    /**
     * @brief Вычисляет абсолютную погрешность метода Эйлера на первом шаге для ОДУ.
     * @param task Структура с параметрами задачи Эйлера.
     * @return Абсолютная погрешность, округленная до 2 знаков после запятой.
     */
    double eulerError(const EulerTask& task);

    /**
     * @brief Интегрирует разрывную функцию методом прямоугольников по непрерывным сегментам.
     * @param a Левая граница интегрирования.
     * @param b Правая граница интегрирования.
     * @param breakpoints Вектор точек разрыва внутри отрезка.
     * @param func Указатель на функцию, принимающую x и индекс текущего непрерывного сегмента.
     * @return Значение интеграла, округленное до 2 знаков после запятой.
     */
    double discontinuityRectangleIntegral(double a, double b, const QVector<double>& breakpoints,
                                          double (*func)(double x, int segmentIndex));

    /* Сигнатуры тестовых математических функций и точных решений */
    double f1(double x, double y);
    double exact1(double x);
    double f2(double x, double y);
    double exact2(double x);
    double f3(double x, double y);
    double exact3(double x);
    double f11(double x, int segment);
    double f22(double x, int segment);
    double f33(double x, int segment);
};

#endif // DATABASE_H
