/********************************************************************************
** Form generated from reading UI file 'test.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST_H
#define UI_TEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TEST
{
public:
    QPushButton *pushButton;
    QTextBrowser *textBrowser;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QTextBrowser *textBrowser_2;
    QTextBrowser *textBrowser_3;

    void setupUi(QWidget *TEST)
    {
        if (TEST->objectName().isEmpty())
            TEST->setObjectName("TEST");
        TEST->resize(640, 480);
        pushButton = new QPushButton(TEST);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(250, 380, 131, 29));
        textBrowser = new QTextBrowser(TEST);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setGeometry(QRect(30, 70, 581, 91));
        horizontalLayoutWidget = new QWidget(TEST);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(50, 20, 551, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_2 = new QPushButton(horizontalLayoutWidget);
        pushButton_2->setObjectName("pushButton_2");

        horizontalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(horizontalLayoutWidget);
        pushButton_3->setObjectName("pushButton_3");

        horizontalLayout->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(horizontalLayoutWidget);
        pushButton_4->setObjectName("pushButton_4");

        horizontalLayout->addWidget(pushButton_4);

        textBrowser_2 = new QTextBrowser(TEST);
        textBrowser_2->setObjectName("textBrowser_2");
        textBrowser_2->setGeometry(QRect(30, 170, 581, 91));
        textBrowser_3 = new QTextBrowser(TEST);
        textBrowser_3->setObjectName("textBrowser_3");
        textBrowser_3->setGeometry(QRect(30, 270, 581, 91));

        retranslateUi(TEST);

        QMetaObject::connectSlotsByName(TEST);
    } // setupUi

    void retranslateUi(QWidget *TEST)
    {
        TEST->setWindowTitle(QCoreApplication::translate("TEST", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("TEST", "\320\227\320\260\320\262\320\265\321\200\321\210\320\270\321\202\321\214 \321\202\320\265\321\201\321\202", nullptr));
        pushButton_2->setText(QCoreApplication::translate("TEST", "\320\227\320\260\320\264\320\260\321\207\320\260 1", nullptr));
        pushButton_3->setText(QCoreApplication::translate("TEST", "\320\227\320\260\320\264\320\260\321\207\320\260 2", nullptr));
        pushButton_4->setText(QCoreApplication::translate("TEST", "\320\227\320\260\320\264\320\260\321\207\320\260 3", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TEST: public Ui_TEST {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST_H
