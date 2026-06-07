#ifndef MAINFORM_H
#define MAINFORM_H

#include "buttonhandler.h"

#include <QWidget>

namespace Ui {
class MainForm;
}

class MainForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = nullptr);
    ~MainForm();
    void showStat();
signals:
    void exit_ok();
    void test_ok();
private slots:
    void on_pushButton_clicked();//показать статистику

    void on_pushButton_2_clicked();//выход из окна

    void on_pushButton_3_clicked();//старт теста

private:
    ButtonHandler* handler;
    Ui::MainForm *ui;
};

#endif // MAINFORM_H
