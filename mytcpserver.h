#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

///
/// \file mytcpserver.h
/// \brief Заголовочный файл многоклиентского TCP-сервера
///

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include <QByteArray>
#include "parsing.h"

///
/// \class MyTcpServer
/// \brief Многоклиентский TCP-сервер на базе Qt, который принимает подключения клиенто на порту 33333
///
class MyTcpServer : public QObject
{
    Q_OBJECT

public:

    ///
    /// \brief Конструктор запускает сервер на порту 33333 и подключает сокет
    /// \param parent Родительский объект Qt, по умолчанию nullptr
    ///
    explicit MyTcpServer(QObject *parent = nullptr);

    ///
    /// \brief Деструктор — закрывает все сокеты из mSockets и останавливает сервер
    ///
    ~MyTcpServer();

public slots:

    ///
    /// \brief Принимает новое подключение и сохраняет сокет в mSockets
    ///
    void slotNewConnection();

    ///
    /// \brief Удаляет отключившийся сокет из mSockets
    ///
    void slotClientDisconnected();

    ///
    /// \brief Читает данные из сокета и отправляет ответ от CommandParsing
    ///
    void slotServerRead();

private:

    CommandParsing* myparsing;                 ///< Объект парсера входящих команд
    QTcpServer*     mTcpServer;                ///< Основной QtTCP-сервер
    QMap<qintptr, QTcpSocket*> mSockets;       ///< Словарь активных сокетов
};

#endif // MYTCPSERVER_H
