/********************************************************************************
** Form generated from reading UI file 'mainlayout.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINLAYOUT_H
#define UI_MAINLAYOUT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainLayout
{
public:

    void setupUi(QWidget *MainLayout)
    {
        if (MainLayout->objectName().isEmpty())
            MainLayout->setObjectName(QString::fromUtf8("MainLayout"));
        MainLayout->resize(400, 300);

        retranslateUi(MainLayout);

        QMetaObject::connectSlotsByName(MainLayout);
    } // setupUi

    void retranslateUi(QWidget *MainLayout)
    {
        MainLayout->setWindowTitle(QApplication::translate("MainLayout", "MainLayout", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainLayout: public Ui_MainLayout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINLAYOUT_H
