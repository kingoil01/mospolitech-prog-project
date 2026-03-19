#include <QCoreApplication>
#include <QTimer>
#include "mytcpclient.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    MyTcpClient* User = MyTcpClient::getInstance();
    QTimer::singleShot(1000, [User]() {
        User->sendMessage("aboba");
    });
    QTimer::singleShot(1200, [User]() {
        User->sendMessage("aboba2");
    });

    return a.exec();
}
