#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include <QByteArray>
#include "parsing.h"

///
/// \brief The MyTcpServer class TCP-сервер для обработки клиентских подключений
///
/// Реализует многопользовательский TCP-сервер на порту 33333.
/// Для каждого подключения создаётся отдельный сокет, который сохраняется
/// в ассоциативном массиве с идентификатором дескриптора.
///
/// Основные возможности:
/// - Прослушивание входящих соединений
/// - Асинхронное чтение данных от клиентов
/// - Передача команд в парсер (CommandParsing)
/// - Отправка ответов клиентам
/// - Обработка отключений клиентов
///
class MyTcpServer : public QObject
{
    Q_OBJECT

public:
    ///
    /// \brief Конструктор сервера
    /// Создаёт QTcpServer и начинает прослушивание на всех интерфейсах, порт 33333
    /// \param parent Родительский объект (для автоматического управления памятью)
    ///
    explicit MyTcpServer(QObject *parent = nullptr);

    ///
    /// \brief Деструктор сервера
    /// Закрывает все активные соединения, удаляет сокеты и останавливает сервер
    ///
    ~MyTcpServer();

public slots:
    ///
    /// \brief Обрабатывает новое входящее соединение
    /// Создаёт QTcpSocket для клиента, сохраняет его в mSockets,
    /// подключает сигналы readyRead и disconnected,
    /// отправляет приветственное сообщение.
    ///
    void slotNewConnection();

    ///
    /// \brief Обрабатывает отключение клиента
    /// Удаляет сокет из карты mSockets, очищает буфер, закрывает сокет
    ///
    void slotClientDisconnected();

    ///
    /// \brief Обрабатывает входящие данные от клиента
    /// Читает все доступные байты, передаёт строку в CommandParsing::Command(),
    /// отправляет полученный ответ обратно клиенту.
    ///
    void slotServerRead();

private:
    ///
    /// \brief myparsing Указатель на объект парсера команд
    /// Используется для обработки текстовых команд от клиентов
    ///
    CommandParsing* myparsing;

    ///
    /// \brief mTcpServer Объект TCP-сервера
    /// Слушает входящие соединения и создаёт клиентские сокеты
    ///
    QTcpServer *mTcpServer;

    ///
    /// \brief mSockets Ассоциативный массив активных клиентских сокетов
    /// Ключ — socketDescriptor(), значение — указатель на QTcpSocket
    ///
    QMap<qintptr, QTcpSocket*> mSockets;

    ///
    /// \brief mBuffers Буферы для каждого сокета (зарезервировано для будущего использования)
    /// Позволяет накапливать данные при частичном получении сообщений
    ///
    QMap<qintptr, QByteArray> mBuffers;
};

#endif // MYTCPSERVER_H