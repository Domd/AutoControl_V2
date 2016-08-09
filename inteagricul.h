#ifndef INTEAGRICUL_H
#define INTEAGRICUL_H

#include <QWidget>
#include <QTimer>
#include <QEvent>
#include <QMouseEvent>
#include "autocontrol_v2.h"
#include "vkey.h"
#include <QMessageBox>
#include "adddevice.h"

namespace Ui {
class InteAgricul;
}

class InteAgricul : public QWidget
{
    Q_OBJECT
    
public:
    explicit InteAgricul(QWidget *parent = 0);
    ~InteAgricul();
    QWidget *parent;
    QTimer *m_timer;
    bool changeNum[5];

    bool fengshanStatus;
    bool ledStatus;
    bool diguanStatus;
//浮点型当前值
    float FsunPreVal;
    float FtempPreVal;
    float FhumPreVal;
    float FsoiltempPreVal;
    float FsoilhumPreVal;

    bool controlMode;//控制方式  true自动  false手动

    QMessageBox *messagebox;
    int countSMG;

    QPixmap pixmap1;
    QPixmap pixmap2;
    QPixmap pix1;
    QPixmap pix2;

    QPixmap fan_pix[8];
    QTimer *fan_timer;
    int fan_count;
    AddDevice *m_add;
public slots:
//    void mousePressEvent(QMouseEvent * event);
private slots:
    void on_toolButton_7_clicked();
    void on_toolButton_clicked();
    void on_toolButton_2_clicked();
    void on_toolButton_3_clicked();
    void on_toolButton_4_clicked();
    void on_toolButton_5_clicked();
    void on_toolButton_6_clicked();

    void readInfo();
    void lineClick1();
    void lineClick2();
    void lineClick3();
    void lineClick4();
    void lineClick5();
    void on_sureTB_clicked();
    void on_toolButton_8_clicked();
//    void on_toolButton_9_clicked();
//    void on_toolButton_11_clicked();
//    void on_toolButton_12_clicked();
//    void on_toolButton_10_clicked();

    void on_Pb_OpenDG_clicked();
    void on_Pb_closeDG_clicked();
    void on_Pb_OpenLED_clicked();
    void on_Pb_closeLED_clicked();
    void on_Pb_OpenFan_clicked();
    void on_Pb_closeFan_clicked();

    void runFan();

    void on_Pb_controlMode_clicked();

private:
    Ui::InteAgricul *ui;
    VKey *vKey;
};

#endif // INTEAGRICUL_H
