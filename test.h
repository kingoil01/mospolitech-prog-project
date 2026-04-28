#ifndef TEST_H
#define TEST_H

#include <QWidget>

namespace Ui {
class TEST;
}

class TEST : public QWidget
{
    Q_OBJECT

public:
    explicit TEST(QWidget *parent = nullptr);
    ~TEST();

    //показать задания
    void showTask1();
    void showTask2();
    void showTask3();
signals:
    //сигнал выхода из теста
    void exit_test();
private slots:
    //слот для кнопки завершения теста
    void on_pushButton_clicked();

    //слоты для кнопок показа задач
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

private:
    Ui::TEST *ui;
};

#endif // TEST_H
