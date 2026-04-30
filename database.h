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
/// - Создание записей задач
///
/// Управление памятью осуществляется автоматически через вложенный класс DatabaseDestroyer.
///
class Database : public QObject
{
    Q_OBJECT

private:
    /// \brief Приватный конструктор (синглтон)
    /// Запрещает создание объектов класса извне
    explicit Database(QObject *parent = nullptr);
    /// \brief Запрет конструктора копирования
    Database(const Database&) = delete;
    ///
    /// \brief operator= Запрет оператора присваивания
    /// \return
    ///
    Database& operator=(const Database&) = delete;
    /// \brief p_instance Указатель на единственный экземпляр (синглтон)
    static Database* p_instance;
    /// \brief class DatabaseDestroyer Вспомогательный класс для автоматического удаления синглтона
    static class DatabaseDestroyer {
    public:
        /// \brief Деструктор удаляет синглтон при завершении программы
        ~DatabaseDestroyer() { delete p_instance; }
        /// \brief Сохраняет указатель на синглтон
        void initialize(Database* p) { p_instance = p; }
    } destroyer;
    /// \brief Объект подключения к базе данных
    QSqlDatabase db;

public:
    ///
    /// \brief getInstance Получает единственный экземпляр класса Database (синглтон)
    /// Создаёт объект Database при первом вызове и возвращает указатель на него.
    /// При последующих вызовах возвращает тот же объект.
    /// Удаление объекта происходит автоматически при завершении программы
    /// благодаря классу DatabaseDestroyer.
    /// \return Указатель на единственный экземпляр Database
    static Database* getInstance();
    /// \brief Деструктор, закрывает подключение к базе данных
    ~Database();
    ///
    /// \brief openDatabase открывает соединение с базой данных
    /// \param dbName переменная с названием файла базы данных
    /// \return true, если удалось открыть, false — ошибка
    ///
    bool openDatabase(const QString& dbName);
    ///
    /// \brief closeDatabase закрывает соединение с базой данных
    ///
    void closeDatabase();
    ///
    /// \brief createTables Создаёт таблицы users и tasks, если они не существуют
    ///
    /// Метод выполняет SQL-запросы для создания двух таблиц:
    /// - users: хранит данные пользователей (id, login, password, email, socket_id)
    /// - tasks: хранит статистику задач пользователей (user_id, login, task1-task4)
    ///
    /// Таблица tasks связана с users по полю login через внешний ключ.
    /// При удалении пользователя из таблицы users его задачи удаляются автоматически
    /// благодаря ON DELETE CASCADE.
    ///
    /// \return true, если обе таблицы успешно созданы (или уже существуют),
    ///  false, если произошла ошибка при создании любой из таблиц
    ///
    bool createTables();
    ///
    /// \brief registerUser Регистрирует нового пользователя в системе
    /// Метод добавляет запись в таблицу users с указанными логином, паролем и email.
    /// Если пользователь с таким логином уже существует, запрос игнорируется (INSERT OR IGNORE).
    /// \param login Логин пользователя (должен быть уникальным)
    /// \param pass Пароль пользователя
    /// \param email Адрес электронной почты
    /// \return true, если регистрация успешна, false — если пользователь уже существует
    ///
    bool registerUser(const QString& login, const QString& pass, const QString& email);
    ///
    /// \brief authoUser Проверяет учётные данные пользователя
    ///
    /// Метод выполняет поиск в таблице users по логину и паролю.
    /// Возвращает true, если найдена запись с указанными данными.
    ///
    /// \param login Логин пользователя
    /// \param pass Пароль пользователя
    /// \return true, если логин и пароль верны, false — в противном случае или при ошибке запроса
    ///
    bool authoUser(const QString& login, const QString& pass);
    ///
    /// \brief stataUser Возвращает статус задач пользователя
    ///
    /// Метод ищет в таблице tasks запись с указанным логином.
    /// Возвращает строку с состояниями всех четырёх задач.
    ///
    /// \param login Логин пользователя, чьи задачи запрашиваются
    /// \return Строка формата "Задачи: X X X X", где X — 0 или 1,
    ///         либо сообщение об ошибке, если пользователь не найден
    ///
    QString stataUser(const QString& login);
    ///
    /// \brief createUserTasks Создаёт запись с задачами для пользователя
    ///
    /// Метод вставляет в таблицу tasks новую запись с указанным user_id, логином
    /// и состояниями задач. Если запись с таким user_id уже существует,
    /// вставка будет проигнорирована (так как user_id является первичным ключом).
    ///
    /// \param user_id Идентификатор пользователя (из таблицы users)
    /// \param login Логин пользователя
    /// \param task1 Состояние задачи 1 (0 — не выполнена, 1 — выполнена)
    /// \param task2 Состояние задачи 2
    /// \param task3 Состояние задачи 3
    /// \param task4 Состояние задачи 4
    /// \return true, если запись успешно создана, false — при ошибке запроса
    ///
    int getCorrectAnswer(int taskNumber);
    bool saveTaskResult(const QString& login, int taskNum, QString result);
};

#endif
