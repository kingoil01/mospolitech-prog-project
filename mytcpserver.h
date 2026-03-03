#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include <QByteArray>

class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);
    ~MyTcpServer();

public slots:
    void slotNewConnection();
    void slotClientDisconnected();
    void slotServerRead();

private:
    QTcpServer *mTcpServer;
    QMap<qintptr, QTcpSocket*> mSockets;       // socketDescriptor() -> socket
    QMap<qintptr, QByteArray> mBuffers;       // per-socket receive buffer
};

#endif // MYTCPSERVER_H
