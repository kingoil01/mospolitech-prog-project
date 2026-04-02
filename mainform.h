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

private slots:
    void on_pushButton_clicked();

private:
    ButtonHandler* handler;
    Ui::MainForm *ui;
};

#endif // MAINFORM_H
