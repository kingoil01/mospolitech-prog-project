#ifndef MYTCPCLIENT_H
#define MYTCPCLIENT_H

#include <QTcpSocket>
#include <QObject>

class MyTcpClient;

class MyTcpClientDestroyer
{
private:
    MyTcpClient* instance;
public:
    ~MyTcpClientDestroyer() {delete instance;}
    void initialize(MyTcpClient * p){instance = p;}
};

class MyTcpClient: public QObject
{
    Q_OBJECT
private:
    QTcpSocket* msocket;
    static MyTcpClient* instance;
    static MyTcpClientDestroyer destroyer;
protected:
    MyTcpClient(): QObject(nullptr){
        msocket = new QTcpSocket(this);
        msocket->connectToHost("127.0.0.1", 33333);//подключение к серверу
    }
    MyTcpClient(const MyTcpClient&);
    MyTcpClient& operator = (MyTcpClient &);
    ~MyTcpClient() {}
    friend class MyTcpClientDestroyer;
public:
    static MyTcpClient* getInstance(){//получить ссылку на обьект класса
        if (!instance){
            instance = new MyTcpClient();
            destroyer.initialize(instance);
        }
        return instance;
    }

    //отправить и получить сообщение
    void sendMessage(QString);
    QString getMsg();
};

#endif // MYTCPCLIENT_H
