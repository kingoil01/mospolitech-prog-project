#include "mytcpclient.h"

MyTcpClient* MyTcpClient::instance = nullptr;
MyTcpClientDestroyer MyTcpClient::destroyer;

void MyTcpClient::sendMessage(QString msg)//отправить сообщение серверу
{
    if (!msocket || msocket->state() != QAbstractSocket::ConnectedState){
        qDebug() << "not connected to the server" << "\n";
        return;
    }
    msocket->write(msg.toUtf8());
}

QString MyTcpClient::getMsg(){//получить сообщение от сервера
    msocket->waitForReadyRead();
    QString res = "";
    while(msocket->bytesAvailable() > 0)
    {
        QByteArray array = msocket->readAll();

        if(array == "\x01")
        {
            res = "";
        }
        else
        {
            res.append(array);
        }
    }
    return res;
}
