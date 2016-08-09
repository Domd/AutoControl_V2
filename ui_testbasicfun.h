/********************************************************************************
** Form generated from reading ui file 'testbasicfun.ui'
**
** Created: Sat Jun 29 09:15:39 2013
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_TESTBASICFUN_H
#define UI_TESTBASICFUN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TestBasicFun
{
public:
    QPushButton *TbBack;
    QGroupBox *groupBox;
    QPushButton *Tb_Device0;
    QPushButton *Tb_Device1;
    QPushButton *Tb_Device2;
    QPushButton *Tb_Device3;
    QLabel *label_3;
    QGroupBox *groupBox_2;
    QPushButton *Tb_SBF;
    QPushButton *Tb_Add;
    QPushButton *Tb_Reduce;
    QPushButton *Tb_Stop;
    QGroupBox *groupBox_3;
    QPushButton *LEDtB4;
    QPushButton *LEDtB3;
    QPushButton *LEDtB2;
    QPushButton *LEDtB1;
    QPushButton *LEDtB5;
    QPushButton *LEDtB6;
    QPushButton *LEDtB7;
    QPushButton *LEDtB8;
    QGroupBox *groupBox_4;
    QLabel *label_2;
    QLabel *labelbutton;
    QGroupBox *groupBox_5;
    QLabel *st1;
    QLabel *st2;
    QLabel *st3;
    QLabel *st4;
    QCheckBox *Cb_LED;
    QCheckBox *Cb_ADC;
    QCheckBox *Cb_KEY;
    QCheckBox *Cb_PWM;
    QLabel *label;
    QGroupBox *groupBox_6;
    QPushButton *pushButton_3;

    void setupUi(QWidget *TestBasicFun)
    {
        if (TestBasicFun->objectName().isEmpty())
            TestBasicFun->setObjectName(QString::fromUtf8("TestBasicFun"));
        TestBasicFun->resize(800, 480);
        QFont font;
        font.setFamily(QString::fromUtf8("Abyssinica SIL"));
        font.setPointSize(20);
        TestBasicFun->setFont(font);
        TbBack = new QPushButton(TestBasicFun);
        TbBack->setObjectName(QString::fromUtf8("TbBack"));
        TbBack->setGeometry(QRect(640, 420, 120, 36));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Bitstream Charter"));
        font1.setPointSize(28);
        font1.setBold(false);
        font1.setItalic(true);
        font1.setWeight(50);
        TbBack->setFont(font1);
        groupBox = new QGroupBox(TestBasicFun);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(220, 210, 400, 111));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Bitstream Charter"));
        font2.setPointSize(20);
        font2.setBold(true);
        font2.setWeight(75);
        groupBox->setFont(font2);
        Tb_Device0 = new QPushButton(groupBox);
        Tb_Device0->setObjectName(QString::fromUtf8("Tb_Device0"));
        Tb_Device0->setGeometry(QRect(13, 10, 91, 42));
        Tb_Device0->setFont(font2);
        Tb_Device1 = new QPushButton(groupBox);
        Tb_Device1->setObjectName(QString::fromUtf8("Tb_Device1"));
        Tb_Device1->setGeometry(QRect(110, 10, 91, 42));
        Tb_Device1->setFont(font2);
        Tb_Device2 = new QPushButton(groupBox);
        Tb_Device2->setObjectName(QString::fromUtf8("Tb_Device2"));
        Tb_Device2->setGeometry(QRect(13, 60, 91, 42));
        Tb_Device2->setFont(font2);
        Tb_Device3 = new QPushButton(groupBox);
        Tb_Device3->setObjectName(QString::fromUtf8("Tb_Device3"));
        Tb_Device3->setGeometry(QRect(110, 60, 91, 42));
        Tb_Device3->setFont(font2);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(210, 40, 191, 41));
        label_3->setFont(font1);
        groupBox_2 = new QGroupBox(TestBasicFun);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(220, 340, 400, 111));
        groupBox_2->setFont(font2);
        Tb_SBF = new QPushButton(groupBox_2);
        Tb_SBF->setObjectName(QString::fromUtf8("Tb_SBF"));
        Tb_SBF->setGeometry(QRect(30, 10, 120, 36));
        Tb_SBF->setFont(font2);
        Tb_Add = new QPushButton(groupBox_2);
        Tb_Add->setObjectName(QString::fromUtf8("Tb_Add"));
        Tb_Add->setGeometry(QRect(30, 60, 120, 36));
        Tb_Add->setFont(font2);
        Tb_Reduce = new QPushButton(groupBox_2);
        Tb_Reduce->setObjectName(QString::fromUtf8("Tb_Reduce"));
        Tb_Reduce->setGeometry(QRect(230, 60, 120, 36));
        Tb_Reduce->setFont(font2);
        Tb_Stop = new QPushButton(groupBox_2);
        Tb_Stop->setObjectName(QString::fromUtf8("Tb_Stop"));
        Tb_Stop->setGeometry(QRect(230, 10, 120, 36));
        Tb_Stop->setFont(font2);
        groupBox_3 = new QGroupBox(TestBasicFun);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(220, 20, 400, 101));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Bitstream Charter"));
        font3.setPointSize(20);
        groupBox_3->setFont(font3);
        LEDtB4 = new QPushButton(groupBox_3);
        LEDtB4->setObjectName(QString::fromUtf8("LEDtB4"));
        LEDtB4->setGeometry(QRect(290, 10, 70, 32));
        LEDtB4->setFont(font2);
        LEDtB3 = new QPushButton(groupBox_3);
        LEDtB3->setObjectName(QString::fromUtf8("LEDtB3"));
        LEDtB3->setGeometry(QRect(200, 10, 70, 32));
        LEDtB3->setFont(font2);
        LEDtB2 = new QPushButton(groupBox_3);
        LEDtB2->setObjectName(QString::fromUtf8("LEDtB2"));
        LEDtB2->setGeometry(QRect(110, 10, 70, 32));
        LEDtB2->setFont(font2);
        LEDtB1 = new QPushButton(groupBox_3);
        LEDtB1->setObjectName(QString::fromUtf8("LEDtB1"));
        LEDtB1->setGeometry(QRect(10, 10, 70, 32));
        LEDtB1->setFont(font2);
        LEDtB5 = new QPushButton(groupBox_3);
        LEDtB5->setObjectName(QString::fromUtf8("LEDtB5"));
        LEDtB5->setGeometry(QRect(10, 60, 70, 32));
        LEDtB5->setFont(font2);
        LEDtB6 = new QPushButton(groupBox_3);
        LEDtB6->setObjectName(QString::fromUtf8("LEDtB6"));
        LEDtB6->setGeometry(QRect(110, 60, 70, 32));
        LEDtB6->setFont(font2);
        LEDtB7 = new QPushButton(groupBox_3);
        LEDtB7->setObjectName(QString::fromUtf8("LEDtB7"));
        LEDtB7->setGeometry(QRect(200, 60, 70, 32));
        LEDtB7->setFont(font2);
        LEDtB8 = new QPushButton(groupBox_3);
        LEDtB8->setObjectName(QString::fromUtf8("LEDtB8"));
        LEDtB8->setGeometry(QRect(290, 60, 70, 32));
        LEDtB8->setFont(font2);
        groupBox_4 = new QGroupBox(TestBasicFun);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(220, 130, 400, 61));
        groupBox_4->setFont(font3);
        label_2 = new QLabel(groupBox_4);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(0, 20, 211, 20));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Bitstream Charter"));
        font4.setPointSize(20);
        font4.setItalic(true);
        label_2->setFont(font4);
        labelbutton = new QLabel(groupBox_4);
        labelbutton->setObjectName(QString::fromUtf8("labelbutton"));
        labelbutton->setGeometry(QRect(150, 10, 91, 31));
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(0, 0, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        QBrush brush2(QColor(118, 118, 117, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        labelbutton->setPalette(palette);
        QFont font5;
        font5.setFamily(QString::fromUtf8("Bitstream Charter"));
        font5.setPointSize(20);
        font5.setBold(false);
        font5.setWeight(50);
        labelbutton->setFont(font5);
        groupBox_5 = new QGroupBox(TestBasicFun);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(30, 40, 181, 191));
        QFont font6;
        font6.setFamily(QString::fromUtf8("Bitstream Charter"));
        font6.setPointSize(16);
        font6.setItalic(true);
        groupBox_5->setFont(font6);
        st1 = new QLabel(groupBox_5);
        st1->setObjectName(QString::fromUtf8("st1"));
        st1->setGeometry(QRect(140, 31, 30, 30));
        st2 = new QLabel(groupBox_5);
        st2->setObjectName(QString::fromUtf8("st2"));
        st2->setGeometry(QRect(140, 69, 30, 30));
        st3 = new QLabel(groupBox_5);
        st3->setObjectName(QString::fromUtf8("st3"));
        st3->setGeometry(QRect(140, 107, 30, 30));
        st4 = new QLabel(groupBox_5);
        st4->setObjectName(QString::fromUtf8("st4"));
        st4->setGeometry(QRect(140, 145, 30, 30));
        Cb_LED = new QCheckBox(groupBox_5);
        Cb_LED->setObjectName(QString::fromUtf8("Cb_LED"));
        Cb_LED->setGeometry(QRect(21, 31, 110, 32));
        Cb_ADC = new QCheckBox(groupBox_5);
        Cb_ADC->setObjectName(QString::fromUtf8("Cb_ADC"));
        Cb_ADC->setGeometry(QRect(21, 107, 113, 32));
        Cb_KEY = new QCheckBox(groupBox_5);
        Cb_KEY->setObjectName(QString::fromUtf8("Cb_KEY"));
        Cb_KEY->setGeometry(QRect(21, 69, 110, 32));
        Cb_PWM = new QCheckBox(groupBox_5);
        Cb_PWM->setObjectName(QString::fromUtf8("Cb_PWM"));
        Cb_PWM->setGeometry(QRect(21, 145, 122, 32));
        label = new QLabel(TestBasicFun);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(530, 240, 191, 41));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        label->setPalette(palette1);
        label->setFont(font1);
        label->setFrameShape(QFrame::NoFrame);
        label->setLineWidth(1);
        groupBox_6 = new QGroupBox(TestBasicFun);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(40, 250, 171, 101));
        pushButton_3 = new QPushButton(groupBox_6);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(20, 40, 111, 36));
        QPalette palette2;
        QBrush brush3(QColor(0, 0, 0, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush3);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush3);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush3);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush3);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        pushButton_3->setPalette(palette2);
        pushButton_3->setFont(font5);

        retranslateUi(TestBasicFun);

        QMetaObject::connectSlotsByName(TestBasicFun);
    } // setupUi

    void retranslateUi(QWidget *TestBasicFun)
    {
        TestBasicFun->setWindowTitle(QApplication::translate("TestBasicFun", "Form", 0, QApplication::UnicodeUTF8));
        TbBack->setText(QApplication::translate("TestBasicFun", "\350\277\224\345\233\236", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        Tb_Device0->setText(QApplication::translate("TestBasicFun", "\351\200\232\351\201\2230", 0, QApplication::UnicodeUTF8));
        Tb_Device1->setText(QApplication::translate("TestBasicFun", "\351\200\232\351\201\2231", 0, QApplication::UnicodeUTF8));
        Tb_Device2->setText(QApplication::translate("TestBasicFun", "\351\200\232\351\201\2232", 0, QApplication::UnicodeUTF8));
        Tb_Device3->setText(QApplication::translate("TestBasicFun", "\351\200\232\351\201\2233", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("TestBasicFun", "ADC Value:", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QString());
        Tb_SBF->setText(QApplication::translate("TestBasicFun", "\345\210\235\345\247\213\350\234\202\351\270\243\345\231\250", 0, QApplication::UnicodeUTF8));
        Tb_Add->setText(QApplication::translate("TestBasicFun", "\345\242\236\345\212\240PWM", 0, QApplication::UnicodeUTF8));
        Tb_Reduce->setText(QApplication::translate("TestBasicFun", "\351\231\215\344\275\216PWM", 0, QApplication::UnicodeUTF8));
        Tb_Stop->setText(QApplication::translate("TestBasicFun", "\345\201\234\346\255\242\350\234\202\351\270\243\345\231\250", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QString());
        LEDtB4->setText(QApplication::translate("TestBasicFun", "LED4", 0, QApplication::UnicodeUTF8));
        LEDtB3->setText(QApplication::translate("TestBasicFun", "LED3", 0, QApplication::UnicodeUTF8));
        LEDtB2->setText(QApplication::translate("TestBasicFun", "LED2", 0, QApplication::UnicodeUTF8));
        LEDtB1->setText(QApplication::translate("TestBasicFun", "LED1", 0, QApplication::UnicodeUTF8));
        LEDtB5->setText(QApplication::translate("TestBasicFun", "LED5", 0, QApplication::UnicodeUTF8));
        LEDtB6->setText(QApplication::translate("TestBasicFun", "LED6", 0, QApplication::UnicodeUTF8));
        LEDtB7->setText(QApplication::translate("TestBasicFun", "LED7", 0, QApplication::UnicodeUTF8));
        LEDtB8->setText(QApplication::translate("TestBasicFun", "LED8", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QString());
        label_2->setText(QApplication::translate("TestBasicFun", "\345\275\223\345\211\215\351\200\211\346\213\251\347\232\204\346\214\211\351\224\256\357\274\232", 0, QApplication::UnicodeUTF8));
        labelbutton->setText(QString());
        groupBox_5->setTitle(QApplication::translate("TestBasicFun", "\346\216\247\345\210\266\346\250\241\345\235\227", 0, QApplication::UnicodeUTF8));
        st1->setText(QApplication::translate("TestBasicFun", "1", 0, QApplication::UnicodeUTF8));
        st2->setText(QApplication::translate("TestBasicFun", "1", 0, QApplication::UnicodeUTF8));
        st3->setText(QApplication::translate("TestBasicFun", "1", 0, QApplication::UnicodeUTF8));
        st4->setText(QApplication::translate("TestBasicFun", "1", 0, QApplication::UnicodeUTF8));
        Cb_LED->setText(QApplication::translate("TestBasicFun", "LED-OFF", 0, QApplication::UnicodeUTF8));
        Cb_ADC->setText(QApplication::translate("TestBasicFun", "ADC-OFF", 0, QApplication::UnicodeUTF8));
        Cb_KEY->setText(QApplication::translate("TestBasicFun", "KEY-OFF", 0, QApplication::UnicodeUTF8));
        Cb_PWM->setText(QApplication::translate("TestBasicFun", "PWM-OFF", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        groupBox_6->setTitle(QApplication::translate("TestBasicFun", "\346\214\211\351\224\256\346\216\247\345\210\266\347\201\257", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("TestBasicFun", "OFF", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(TestBasicFun);
    } // retranslateUi

};

namespace Ui {
    class TestBasicFun: public Ui_TestBasicFun {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTBASICFUN_H
