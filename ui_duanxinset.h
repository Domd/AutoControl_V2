/********************************************************************************
** Form generated from reading ui file 'duanxinset.ui'
**
** Created: Mon Jan 14 22:20:16 2013
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_DUANXINSET_H
#define UI_DUANXINSET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DuanXinSet
{
public:
    QPushButton *pushButton;
    QGroupBox *groupBox;
    QTableWidget *tableWidget;
    QGroupBox *groupBox_2;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QGroupBox *groupBox_3;
    QTableWidget *tableWidget_2;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QLabel *label;

    void setupUi(QWidget *DuanXinSet)
    {
        if (DuanXinSet->objectName().isEmpty())
            DuanXinSet->setObjectName(QString::fromUtf8("DuanXinSet"));
        DuanXinSet->resize(800, 480);
        DuanXinSet->setMinimumSize(QSize(800, 480));
        DuanXinSet->setMaximumSize(QSize(800, 480));
        pushButton = new QPushButton(DuanXinSet);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(690, 410, 91, 61));
        pushButton->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"color: rgb(170, 85, 0);\n"
"font: 75 72pt \"Ubuntu\";"));
        groupBox = new QGroupBox(DuanXinSet);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 20, 281, 451));
        groupBox->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"color: rgb(255, 170, 255);\n"
"gridline-color: rgb(255, 170, 127);\n"
"font: 75 72pt \"Ubuntu\";"));
        tableWidget = new QTableWidget(groupBox);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(10, 40, 261, 401));
        tableWidget->setStyleSheet(QString::fromUtf8("gridline-color: rgb(255, 170, 127);\n"
"font: 75 72pt \"Ubuntu\";\n"
"color: rgb(0, 0, 127);\n"
"background-color: rgb(255, 255, 255);"));
        groupBox_2 = new QGroupBox(DuanXinSet);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(320, 30, 461, 81));
        groupBox_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 170, 255);\n"
"background-color: rgba(255, 255, 255, 0);\n"
"font: 75 72pt \"Ubuntu\";"));
        radioButton = new QRadioButton(groupBox_2);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(70, 30, 111, 31));
        radioButton->setStyleSheet(QString::fromUtf8("font: 75 72pt \"Ubuntu\";\n"
"background-color: rgba(255, 255, 255, 0);\n"
"color: rgb(0, 0, 127);\n"
""));
        radioButton_2 = new QRadioButton(groupBox_2);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setGeometry(QRect(290, 30, 117, 31));
        radioButton_2->setStyleSheet(QString::fromUtf8("font: 75 72pt \"Ubuntu\";\n"
"background-color: rgba(255, 255, 255, 0);\n"
"color: rgb(0, 0, 127);\n"
""));
        groupBox_3 = new QGroupBox(DuanXinSet);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(320, 120, 471, 281));
        groupBox_3->setStyleSheet(QString::fromUtf8("font: 75 72pt \"Ubuntu\";\n"
"background-color: rgba(255, 255, 255, 0);\n"
"color: rgb(255, 170, 255);"));
        tableWidget_2 = new QTableWidget(groupBox_3);
        tableWidget_2->setObjectName(QString::fromUtf8("tableWidget_2"));
        tableWidget_2->setGeometry(QRect(10, 30, 451, 241));
        tableWidget_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 127);\n"
"font: 75 72pt \"Ubuntu\";\n"
"gridline-color: rgb(255, 170, 127);"));
        pushButton_2 = new QPushButton(DuanXinSet);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(450, 410, 91, 61));
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"font: 75 72pt \"Ubuntu\";\n"
"color: rgb(0, 0, 0);\n"
""));
        pushButton_3 = new QPushButton(DuanXinSet);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(570, 410, 91, 61));
        pushButton_3->setStyleSheet(QString::fromUtf8("font: 75 72pt \"Ubuntu\";\n"
"color: rgb(0, 0, 0);\n"
"background-color: rgba(255, 255, 255, 0);"));
        label = new QLabel(DuanXinSet);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(140, 0, 531, 21));
        label->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"color: rgb(255, 0, 0);\n"
"font: 75 48pt \"Ubuntu\";"));

        retranslateUi(DuanXinSet);

        QMetaObject::connectSlotsByName(DuanXinSet);
    } // setupUi

    void retranslateUi(QWidget *DuanXinSet)
    {
        DuanXinSet->setWindowTitle(QApplication::translate("DuanXinSet", "Form", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("DuanXinSet", "\350\277\224\345\233\236", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("DuanXinSet", "\345\217\257\346\216\247\350\256\276\345\244\207:", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("DuanXinSet", " \346\216\247\345\210\266\345\212\237\350\203\275", 0, QApplication::UnicodeUTF8));
        radioButton->setText(QApplication::translate("DuanXinSet", "\345\274\200", 0, QApplication::UnicodeUTF8));
        radioButton_2->setText(QApplication::translate("DuanXinSet", "\345\205\263", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("DuanXinSet", "\345\267\262\346\267\273\345\212\240\351\241\271:", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("DuanXinSet", "\346\267\273\345\212\240", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("DuanXinSet", "\345\210\240\351\231\244", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DuanXinSet", ".....", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(DuanXinSet);
    } // retranslateUi

};

namespace Ui {
    class DuanXinSet: public Ui_DuanXinSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DUANXINSET_H
