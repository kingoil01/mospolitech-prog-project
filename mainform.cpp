#include "mainform.h"
#include "ui_mainform.h"
#include "mytcpclient.h"
#include "clientcontroller.h"

MainForm::MainForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainForm)
{
    ui->setupUi(this);
    handler = new ButtonHandler();
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::showStat(){
    QString msg = ClientController::getInstance()->makeStatCommand();
    MyTcpClient::getInstance()->sendMessage(msg);
    QString res = MyTcpClient::getInstance()->getMsg();
    ui->textBrowser->setText(res);
}

void MainForm::on_pushButton_clicked()
{
    showStat();
}

