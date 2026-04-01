#include "mytcpserver.h"
#include <QDebug>
#include "parsing.h"
MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{
    myparsing = new CommandParsing(this);
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

    QString resp = "";

    while(mTcpSocket->bytesAvailable() > 0)
    {
        QByteArray array = mTcpSocket->readAll();
        qDebug() << array << "\n";
        QString dataStr = QString::fromUtf8(array).trimmed();
        resp = myparsing->Command(dataStr);

    }
    mTcpSocket->write(resp.toUtf8());

}

void MyTcpServer::slotClientDisconnected()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (!socket) return;

    qintptr id = socket->socketDescriptor();
    qDebug() << "Client disconnected, id =" << id;

    // Remove from maps and schedule deletion
    mSockets.remove(id);

    socket->close();
    socket->deleteLater();
}
