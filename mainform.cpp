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

void MainForm::showStat(){//показ статистики в текстовом поле
    QString msg = ClientController::getInstance()->makeStatCommand();
    MyTcpClient::getInstance()->sendMessage(msg);
    QString res = MyTcpClient::getInstance()->getMsg();
    ui->textBrowser->setText(res);
}

void MainForm::on_pushButton_clicked()//нажатие на кнопку показать статистику
{
    showStat();
}


void MainForm::on_pushButton_2_clicked()//нажатие на кнопку выйти из окна
{
    emit exit_ok();
}


void MainForm::on_pushButton_3_clicked()//нажатие на кнопку старт теста
{
    emit test_ok();
}

