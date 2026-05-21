/********************************************************************************
** Form generated from reading UI file 'mainform.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFORM_H
#define UI_MAINFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainForm
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QTextBrowser *textBrowser;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;

    void setupUi(QWidget *MainForm)
    {
        if (MainForm->objectName().isEmpty())
            MainForm->setObjectName("MainForm");
        MainForm->resize(1280, 720);
        verticalLayoutWidget = new QWidget(MainForm);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(230, 90, 831, 221));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName("pushButton");

        verticalLayout->addWidget(pushButton);

        textBrowser = new QTextBrowser(verticalLayoutWidget);
        textBrowser->setObjectName("textBrowser");

        verticalLayout->addWidget(textBrowser);

        pushButton_2 = new QPushButton(MainForm);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(60, 640, 90, 29));
        pushButton_3 = new QPushButton(MainForm);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(420, 350, 461, 61));

        retranslateUi(MainForm);

        QMetaObject::connectSlotsByName(MainForm);
    } // setupUi

    void retranslateUi(QWidget *MainForm)
    {
        MainForm->setWindowTitle(QCoreApplication::translate("MainForm", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("MainForm", "Stats", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainForm", "Exit", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainForm", "TEST", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainForm: public Ui_MainForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFORM_H
