#ifndef CLIENTCONTROLLER_H
#define CLIENTCONTROLLER_H

#include <QObject>
#include <QDebug>

class ClientController;

class ClientControllerDestroyer
{
private:
    ClientController* instance;
public:
    ~ClientControllerDestroyer() {delete instance;}
    void initialize(ClientController * p){instance = p;}
};

class ClientController: public QObject
{
    Q_OBJECT

private:
    static ClientController* instance;
    static ClientControllerDestroyer destroyer;
protected:
    ClientController(): QObject(nullptr) {}
    ClientController(const ClientController&);
    ClientController& operator = (ClientController &);
    ~ClientController() {}
    friend class ClientControllerDestroyer;
public:
    static ClientController* getInstance(){
        if (!instance){
            instance = new ClientController();
            destroyer.initialize(instance);
        }
        return instance;
    }

    QString makeLoginCommand(QString& login, QString& password);
    QString makeRegisterCommand(QString& login, QString& password, QString& email);
    QString makeTask1Command();
    QString makeTask2Command();
    QString makeTask3Command();
    QString makeTask4Command();
    QString makeEndTestCommand(QString login, QString ans1, QString ans2, QString ans3, QString ans4);
    QString makeStatCommand();

    QString parseServerResponse(QString& response);
};

#endif // CLIENTCONTROLLER_H
