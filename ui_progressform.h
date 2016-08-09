/********************************************************************************
** Form generated from reading UI file 'progressform.ui'
**
** Created: Tue Jul 2 10:31:15 2013
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROGRESSFORM_H
#define UI_PROGRESSFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProgressForm
{
public:
    QProgressBar *progressBar;
    QLabel *label;

    void setupUi(QWidget *ProgressForm)
    {
        if (ProgressForm->objectName().isEmpty())
            ProgressForm->setObjectName(QString::fromUtf8("ProgressForm"));
        ProgressForm->resize(800, 480);
        progressBar = new QProgressBar(ProgressForm);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(150, 290, 461, 23));
        progressBar->setValue(24);
        label = new QLabel(ProgressForm);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(620, 280, 121, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("Abyssinica SIL"));
        font.setPointSize(72);
        label->setFont(font);

        retranslateUi(ProgressForm);

        QMetaObject::connectSlotsByName(ProgressForm);
    } // setupUi

    void retranslateUi(QWidget *ProgressForm)
    {
        ProgressForm->setWindowTitle(QApplication::translate("ProgressForm", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ProgressForm", "\350\275\275\345\205\245\344\270\255...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ProgressForm: public Ui_ProgressForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROGRESSFORM_H
