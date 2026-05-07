#include "test.h"
#include "ui_test.h"
#include "mytcpclient.h"
#include "buttonhandler.h"
#include "clientcontroller.h"

TEST::TEST(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TEST)
{
    ui->setupUi(this);
    showTask1();
    handler = new ButtonHandler();
}

TEST::~TEST()
{
    delete ui;
}

void TEST::on_pushButton_clicked()
{
    QString ans1 = ui->lineEdit->text();
    if (ans1 == "") ans1 = "1000";
    QString ans2 = ui->lineEdit_3->text();
    if (ans2 == "") ans2 = "1000";
    QString ans3 = ui->lineEdit_4->text();
    if (ans3 == "") ans3 = "1000";
    QString ans4 = ui->lineEdit_5->text();
    if (ans4 == "") ans4 = "1000";
    handler->onEndClicked(ans1, ans2, ans3, ans4);
    emit exit_test();
}

void TEST::showTask1(){//показать задачу 1 (надо перенести шовтаски в хендлер потом сделаю)
    QString msg = ClientController::getInstance()->makeTask1Command();
    MyTcpClient::getInstance()->sendMessage(msg);
    QString res = MyTcpClient::getInstance()->getMsg();
    ui->textBrowser->show();
    ui->textBrowser->setText(res);
    ui->lineEdit->show();
    ui->lineEdit_3->hide();
    ui->lineEdit_4->hide();
    ui->textBrowser_2->hide();
    ui->textBrowser_3->hide();
    ui->lineEdit_5->hide();
    ui->textBrowser_4->hide();
}

void TEST::showTask2(){//показать задачу 2
    QString msg = ClientController::getInstance()->makeTask2Command();
    MyTcpClient::getInstance()->sendMessage(msg);
    QString res = MyTcpClient::getInstance()->getMsg();
    ui->textBrowser_2->show();
    ui->lineEdit_3->show();
    ui->lineEdit->hide();
    ui->lineEdit_4->hide();
    ui->textBrowser_2->setText(res);
    ui->textBrowser_3->hide();
    ui->textBrowser->hide();
}

void TEST::showTask3(){//показать задачу 3
    QString msg = ClientController::getInstance()->makeTask3Command();
    MyTcpClient::getInstance()->sendMessage(msg);
    QString res = MyTcpClient::getInstance()->getMsg();
    ui->textBrowser_3->show();
    ui->lineEdit_4->show();
    ui->lineEdit_3->hide();
    ui->lineEdit->hide();
    ui->textBrowser_3->setText(res);
    ui->textBrowser->hide();
    ui->textBrowser_2->hide();
    ui->lineEdit_5->hide();
    ui->textBrowser_4->hide();
}

void TEST::showTask4(){//показать задачу 4
    QString msg = ClientController::getInstance()->makeTask4Command();
    MyTcpClient::getInstance()->sendMessage(msg);
    QString res = MyTcpClient::getInstance()->getMsg();
    ui->textBrowser_4->show();
    ui->lineEdit_5->show();
    ui->lineEdit_3->hide();
    ui->lineEdit_4->hide();
    ui->lineEdit->hide();
    ui->textBrowser_4->setText(res);
    ui->textBrowser->hide();
    ui->textBrowser_2->hide();
    ui->textBrowser_3->hide();
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




void TEST::on_pushButton_5_clicked()
{
    showTask4();
}

