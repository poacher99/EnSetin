/********************************************************************************
** Form generated from reading UI file 'gamewindow1.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWINDOW1_H
#define UI_GAMEWINDOW1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_gamewindow1
{
public:
    QPushButton *pushButton;

    void setupUi(QDialog *gamewindow1)
    {
        if (gamewindow1->objectName().isEmpty())
            gamewindow1->setObjectName(QString::fromUtf8("gamewindow1"));
        gamewindow1->resize(805, 671);
        pushButton = new QPushButton(gamewindow1);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(710, 70, 93, 28));

        retranslateUi(gamewindow1);

        QMetaObject::connectSlotsByName(gamewindow1);
    } // setupUi

    void retranslateUi(QDialog *gamewindow1)
    {
        gamewindow1->setWindowTitle(QApplication::translate("gamewindow1", "Dialog", nullptr));
        pushButton->setText(QApplication::translate("gamewindow1", "\351\252\260\345\255\220\347\202\271\346\225\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gamewindow1: public Ui_gamewindow1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWINDOW1_H
