/********************************************************************************
** Form generated from reading UI file 'gamewindow2.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWINDOW2_H
#define UI_GAMEWINDOW2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_gamewindow2
{
public:

    void setupUi(QDialog *gamewindow2)
    {
        if (gamewindow2->objectName().isEmpty())
            gamewindow2->setObjectName(QString::fromUtf8("gamewindow2"));
        gamewindow2->resize(400, 300);

        retranslateUi(gamewindow2);

        QMetaObject::connectSlotsByName(gamewindow2);
    } // setupUi

    void retranslateUi(QDialog *gamewindow2)
    {
        gamewindow2->setWindowTitle(QApplication::translate("gamewindow2", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gamewindow2: public Ui_gamewindow2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWINDOW2_H
