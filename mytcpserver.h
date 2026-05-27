#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include <QByteArray>
#include "parsing.h"

/**
 * @class MyTcpServer
 * @brief Класс TCP-сервера для обработки входящих сетевых подключений.
 *
 * Управляет пулом клиентских сокетов, организует чтение данных во внутренние
 * буферы и передает входящие текстовые команды в компонент парсинга.
 */
class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Конструктор сервера. Инициализирует службы и запускает прослушивание.
     * @param parent Родительский объект QObject.
     */
    explicit MyTcpServer(QObject *parent = nullptr);

    /** @brief Деструктор. Закрывает сервер и освобождает сокеты. */
    ~MyTcpServer();

public slots:
    /** @brief Слот обработки нового клиентского подключения. */
    void slotNewConnection();

    /** @brief Слот обработки отключения клиента. Освобождает ресурсы сокета. */
    void slotClientDisconnected();

    /** @brief Слот чтения входящих данных от конкретного клиента. Накапливает буфер. */
    void slotServerRead();

private:
    CommandParsing* myparsing;                /**< Компонент разбора и обработки команд */
    QTcpServer *mTcpServer;                   /**< Указатель на объект Qt TCP-сервера */
    QMap<qintptr, QTcpSocket*> mSockets;      /**< Ассоциативный массив: дескриптор -> сокет клиента */
    QMap<qintptr, QByteArray> mBuffers;       /**< Ассоциативный массив: дескриптор -> буфер приема данных */
};

#endif // MYTCPSERVER_H
