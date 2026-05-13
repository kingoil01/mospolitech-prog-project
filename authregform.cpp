#include "authregform.h"
#include "ui_authregform.h"
#include "buttonhandler.h"
#include "mytcpclient.h"
#include "clientcontroller.h"
#include "managerform.h"

#include <QObject>

void authregform::showMsg(QString msg){//показ ответа на запрос регистрации
    ui->textBrowser->setText(msg);
}

authregform::authregform(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::authregform)
{
    ui->setupUi(this);
    handler = new ButtonHandler();
}

authregform::~authregform()
{
    delete ui;
}

void authregform::on_pushButton_clicked()//нажатие на кнопку авторизации
{
    QString log = ui->lineEdit->text();
    QString pass = ui->lineEdit_2->text();
    if (log == "" or pass == ""){
        showMsg("Fill in all fields");
        return;
    }
    handler->onLoginClicked(log, pass);
    QString msg = MyTcpClient::getInstance()->getMsg();
    QString res = ClientController::getInstance()->parseServerResponse(msg);
    showMsg(res);
    if (res == "SUCCESS") {
        ManagerForm::setLogin(log);
        emit auth_ok();
    }
}


void authregform::on_pushButton_2_clicked()//нажатие на кнопку регистрации
{
    QString log = ui->lineEdit->text();
    QString pass = ui->lineEdit_2->text();
    QString email = ui->lineEdit_3->text();
    if (log == "" or pass == "" or email == "") {
        showMsg("Fill in all fields");
        return;
    }
    handler->onRegisterClicked(log, pass, email);
    QString msg = MyTcpClient::getInstance()->getMsg();
    showMsg(ClientController::getInstance()->parseServerResponse(msg));
}
