#include "mytcpserver.h"
#include <QDebug>

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{
    mTcpServer = new QTcpServer(this);

    connect(mTcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::slotNewConnection);

    if (!mTcpServer->listen(QHostAddress::Any, 33333)) {
        qDebug() << "server is not started:" << mTcpServer->errorString();
    } else {
        qDebug() << "server is started on port" << mTcpServer->serverPort();
    }
}

MyTcpServer::~MyTcpServer()
{
    for (auto sock : mSockets) {
        if (sock) {
            sock->disconnectFromHost();
            sock->close();
            sock->deleteLater();
        }
    }
    mSockets.clear();
    mBuffers.clear();

    if (mTcpServer->isListening()) {
        mTcpServer->close();
    }
}

void MyTcpServer::slotNewConnection()
{
    while (mTcpServer->hasPendingConnections()) {
        QTcpSocket *clientSocket = mTcpServer->nextPendingConnection();
        if (!clientSocket) continue;

        qintptr id = clientSocket->socketDescriptor();
        mSockets[id] = clientSocket;
        mBuffers[id] = QByteArray();

        qDebug() << "New client connected, id =" << id
                 << ", peer =" << clientSocket->peerAddress().toString()
                 << ":" << clientSocket->peerPort();

        connect(clientSocket, &QTcpSocket::readyRead, this, &MyTcpServer::slotServerRead);
        connect(clientSocket, &QTcpSocket::disconnected, this, &MyTcpServer::slotClientDisconnected);

        clientSocket->write("Hello, World!!! I am echo server!\r\n");
        clientSocket->flush();
    }
}

void MyTcpServer::slotServerRead()
{
    QTcpSocket *mTcpSocket = qobject_cast<QTcpSocket*>(sender());
    if (!mTcpSocket) return;

    QString res = "";

    while(mTcpSocket->bytesAvailable() > 0)
    {
        QByteArray array = mTcpSocket->readAll();
        qDebug() << array << "\n";

        if(array == "\x01")
        {
            mTcpSocket->write(res.toUtf8());
            res = "";
        }
        else
        {
            res.append(array);
        }
    }

    mTcpSocket->write(res.toUtf8());
}

void MyTcpServer::slotClientDisconnected()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (!socket) return;

    qintptr id = socket->socketDescriptor();
    qDebug() << "Client disconnected, id =" << id;

    // Remove from maps and schedule deletion
    mSockets.remove(id);
    mBuffers.remove(id);

    socket->close();
    socket->deleteLater();
}
