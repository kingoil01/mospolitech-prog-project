#ifndef PARSING_H
#define PARSING_H

#include <QObject>
#include "database.h"

/**
 * @class CommandParsing
 * @brief Класс бизнес-логики для парсинга и обработки текстовых протокольных команд от клиентов.
 *
 * Принимает сырые строки команд, разбивает их на параметры, осуществляет необходимую
 * диспетчеризацию в методы базы данных или вычислительные функции и формирует текстовый ответ.
 */
class CommandParsing : public QObject {
    Q_OBJECT
private:
    Database* my_database; /**< Указатель на единственный экземпляр базы данных (Синглтон) */

public:
    /**
     * @brief Конструктор компонента парсинга.
     * @param parent Родительский объект QObject.
     */
    explicit CommandParsing(QObject *parent = nullptr);

    /**
     * @brief Основной метод диспетчеризации строковых команд.
     * * Поддерживает обработку команд авторизации (auth), регистрации (reg),
     * запроса статистики (stata) и эхо-ответов (Echo).
     * * @param command Полная строка команды с аргументами, разделенными пробелами.
     * @return Строка ответа, готовая к отправке клиенту по сети.
     */
    QString Command(const QString &command);

    /**
     * @brief Обрабатывает отправку ответов на задачи пользователем.
     * @param parts Расплитованный список аргументов команды (номер задачи, ответ).
     * @param login Логин пользователя, отправившего ответ.
     * @return Результат проверки ("Верно", "Неверно" или сообщение об ошибке).
     */
    QString handleSubmit(QStringList& parts, QString login);
};

#endif // PARSING_H
