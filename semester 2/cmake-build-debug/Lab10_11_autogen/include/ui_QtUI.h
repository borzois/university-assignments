/********************************************************************************
** Form generated from reading UI file 'QtUI.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTUI_H
#define UI_QTUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtUI
{
public:

    void setupUi(QWidget *QtUI)
    {
        if (QtUI->objectName().isEmpty())
            QtUI->setObjectName(QString::fromUtf8("QtUI"));
        QtUI->resize(400, 300);

        retranslateUi(QtUI);

        QMetaObject::connectSlotsByName(QtUI);
    } // setupUi

    void retranslateUi(QWidget *QtUI)
    {
        QtUI->setWindowTitle(QCoreApplication::translate("QtUI", "QtUI", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtUI: public Ui_QtUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTUI_H
