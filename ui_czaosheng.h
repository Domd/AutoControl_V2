/********************************************************************************
** Form generated from reading ui file 'czaosheng.ui'
**
** Created: Fri Sep 21 13:14:35 2012
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CZAOSHENG_H
#define UI_CZAOSHENG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CZaoSheng
{
public:
    QGroupBox *groupBox;

    void setupUi(QWidget *CZaoSheng)
    {
        if (CZaoSheng->objectName().isEmpty())
            CZaoSheng->setObjectName(QString::fromUtf8("CZaoSheng"));
        CZaoSheng->resize(800, 480);
        CZaoSheng->setMinimumSize(QSize(800, 480));
        CZaoSheng->setMaximumSize(QSize(800, 480));
        groupBox = new QGroupBox(CZaoSheng);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(30, 50, 181, 381));

        retranslateUi(CZaoSheng);

        QMetaObject::connectSlotsByName(CZaoSheng);
    } // setupUi

    void retranslateUi(QWidget *CZaoSheng)
    {
        CZaoSheng->setWindowTitle(QApplication::translate("CZaoSheng", "Form", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("CZaoSheng", "GroupBox", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(CZaoSheng);
    } // retranslateUi

};

namespace Ui {
    class CZaoSheng: public Ui_CZaoSheng {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CZAOSHENG_H
