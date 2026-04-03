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
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TEST
{
public:
    QLabel *label;

    void setupUi(QWidget *TEST)
    {
        if (TEST->objectName().isEmpty())
            TEST->setObjectName("TEST");
        TEST->resize(640, 480);
        label = new QLabel(TEST);
        label->setObjectName("label");
        label->setGeometry(QRect(250, 230, 231, 20));

        retranslateUi(TEST);

        QMetaObject::connectSlotsByName(TEST);
    } // setupUi

    void retranslateUi(QWidget *TEST)
    {
        TEST->setWindowTitle(QCoreApplication::translate("TEST", "Form", nullptr));
        label->setText(QCoreApplication::translate("TEST", "\321\201\320\276\320\264\320\265\321\200\320\266\320\270\320\274\320\276\320\265 \321\202\320\265\321\201\321\202\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TEST: public Ui_TEST {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST_H
