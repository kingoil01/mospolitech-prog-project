#include "mytcpclient.h"

MyTcpClient* MyTcpClient::instance = nullptr;
MyTcpClientDestroyer MyTcpClient::destroyer;

void MyTcpClient::sendMessage(QString msg)
{
    if (!msocket || msocket->state() != QAbstractSocket::ConnectedState){
        qDebug() << "not connected to the server" << "\n";
        return;
    }
    msocket->write(msg.toUtf8());
    msocket->flush();
}
