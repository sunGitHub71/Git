/********************************************************************************
** Form generated from reading UI file 'hsplayer.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HSPLAYER_H
#define UI_HSPLAYER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HSPlayerClass
{
public:

    void setupUi(QWidget *HSPlayerClass)
    {
        if (HSPlayerClass->objectName().isEmpty())
            HSPlayerClass->setObjectName(QString::fromUtf8("HSPlayerClass"));
        HSPlayerClass->resize(600, 400);

        retranslateUi(HSPlayerClass);

        QMetaObject::connectSlotsByName(HSPlayerClass);
    } // setupUi

    void retranslateUi(QWidget *HSPlayerClass)
    {
        HSPlayerClass->setWindowTitle(QApplication::translate("HSPlayerClass", "HSPlayer", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class HSPlayerClass: public Ui_HSPlayerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HSPLAYER_H
