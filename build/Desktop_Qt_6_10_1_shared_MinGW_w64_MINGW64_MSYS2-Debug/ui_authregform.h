/********************************************************************************
** Form generated from reading UI file 'authregform.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTHREGFORM_H
#define UI_AUTHREGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_authregform
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QTextBrowser *textBrowser;

    void setupUi(QWidget *authregform)
    {
        if (authregform->objectName().isEmpty())
            authregform->setObjectName("authregform");
        authregform->resize(1280, 720);
        verticalLayoutWidget = new QWidget(authregform);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(360, 190, 561, 171));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(verticalLayoutWidget);
        lineEdit->setObjectName("lineEdit");

        horizontalLayout->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        lineEdit_2 = new QLineEdit(verticalLayoutWidget);
        lineEdit_2->setObjectName("lineEdit_2");

        horizontalLayout_2->addWidget(lineEdit_2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName("label_3");

        horizontalLayout_4->addWidget(label_3);

        lineEdit_3 = new QLineEdit(verticalLayoutWidget);
        lineEdit_3->setObjectName("lineEdit_3");

        horizontalLayout_4->addWidget(lineEdit_3);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayoutWidget_3 = new QWidget(authregform);
        horizontalLayoutWidget_3->setObjectName("horizontalLayoutWidget_3");
        horizontalLayoutWidget_3->setGeometry(QRect(500, 440, 271, 41));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(horizontalLayoutWidget_3);
        pushButton->setObjectName("pushButton");

        horizontalLayout_3->addWidget(pushButton);

        pushButton_2 = new QPushButton(horizontalLayoutWidget_3);
        pushButton_2->setObjectName("pushButton_2");

        horizontalLayout_3->addWidget(pushButton_2);

        textBrowser = new QTextBrowser(authregform);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setGeometry(QRect(500, 390, 271, 41));

        retranslateUi(authregform);

        QMetaObject::connectSlotsByName(authregform);
    } // setupUi

    void retranslateUi(QWidget *authregform)
    {
        authregform->setWindowTitle(QCoreApplication::translate("authregform", "Form", nullptr));
        label->setText(QCoreApplication::translate("authregform", "Login", nullptr));
        label_2->setText(QCoreApplication::translate("authregform", "Password", nullptr));
        label_3->setText(QCoreApplication::translate("authregform", "E-mail", nullptr));
        pushButton->setText(QCoreApplication::translate("authregform", "Auth", nullptr));
        pushButton_2->setText(QCoreApplication::translate("authregform", "Reg", nullptr));
    } // retranslateUi

};

namespace Ui {
    class authregform: public Ui_authregform {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTHREGFORM_H
