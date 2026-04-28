#include "test.h"
#include "ui_test.h"
#include "mytcpclient.h"
#include "clientcontroller.h"

TEST::TEST(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TEST)
{
    ui->setupUi(this);
    showTask1();
}

TEST::~TEST()
{
    delete ui;
}

void TEST::on_pushButton_clicked()
{
    emit exit_test();
}

void TEST::showTask1(){//показать задачу 1 (надо перенести шовтаски в хендлер потом сделаю)
    QString msg = ClientController::getInstance()->makeTaskCommand();
    MyTcpClient::getInstance()->sendMessage(msg);
    QString res = MyTcpClient::getInstance()->getMsg();
    ui->textBrowser->show();
    ui->textBrowser->setText(res);
    ui->textBrowser_2->hide();
    ui->textBrowser_3->hide();
}

void TEST::showTask2(){//показать задачу 2
    QString msg = ClientController::getInstance()->makeTaskCommand();
    MyTcpClient::getInstance()->sendMessage(msg);
    QString res = MyTcpClient::getInstance()->getMsg();
    ui->textBrowser_2->show();
    ui->textBrowser_2->setText(res);
    ui->textBrowser_3->hide();
    ui->textBrowser->hide();
}

void TEST::showTask3(){//показать задачу 3
    QString msg = ClientController::getInstance()->makeTaskCommand();
    MyTcpClient::getInstance()->sendMessage(msg);
    QString res = MyTcpClient::getInstance()->getMsg();
    ui->textBrowser_3->show();
    ui->textBrowser_3->setText(res);
    ui->textBrowser->hide();
    ui->textBrowser_2->hide();
}


void TEST::on_pushButton_2_clicked()//нажатие кнопки показа задачи 1
{
    showTask1();
}


void TEST::on_pushButton_3_clicked()//нажатие кнопки показа задачи 2
{
    showTask2();
}


void TEST::on_pushButton_4_clicked()//нажатие кнопки показа задачи 3
{
    showTask3();
}

