#include "managerform.h"
#include "mytcpclient.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyTcpClient* c = MyTcpClient::getInstance();
    ManagerForm s;


    return a.exec();
}
