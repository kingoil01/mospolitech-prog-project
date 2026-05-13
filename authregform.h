#ifndef AUTHREGFORM_H
#define AUTHREGFORM_H

#include "buttonhandler.h"
#include <QWidget>

namespace Ui {
class authregform;
}

class authregform : public QWidget
{
    Q_OBJECT

public:
    explicit authregform(QWidget *parent = nullptr);
    ~authregform();
    void showMsg(QString msg);
signals:
    void auth_ok();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    ButtonHandler* handler;
    Ui::authregform *ui;
};

#endif // AUTHREGFORM_H
