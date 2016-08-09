#ifndef INTEHOMEFURN_H
#define INTEHOMEFURN_H

#include <QWidget>
#include <QEvent>
#include <QMouseEvent>
#include "autocontrol_v2.h"
#include "vkey.h"
#include <QTimer>
#include "adddevice.h"

namespace Ui {
class InteHomeFurn;
}

class InteHomeFurn : public QWidget
{
    Q_OBJECT
    
public:
    explicit InteHomeFurn(QWidget *parent = 0);
    ~InteHomeFurn();
    QWidget *parent;

    bool fengshanStatus;
    bool yuyinStatus;
    bool changeNum[3];

    float FsunPreVal;
    float FtempPreVal;
    float FhumPreVal;

    QTimer *m_timer;
    QPixmap pixmap1;
    QPixmap pixmap2;

    QPixmap fan_pix[8];
    QTimer *fan_timer;
    int fan_count;

    int countNum[4];
    int countSMG;

    bool LEDStatus;
    bool SMGStatus;
    bool power1Status;
    bool power2Status;

    char initval;
    void InfraredControlFun(QString ,QString );
    void fanControl();

    AddDevice *m_add;
public slots:
    void mousePressEvent(QMouseEvent * event);
    void lineClick1();
    void lineClick2();
    void lineClick3();
private slots:

    void on_toolButton_7_clicked();
    void on_toolButton_8_clicked();
    void on_toolButton_clicked();
    void on_toolButton_2_clicked();
    void on_toolButton_3_clicked();
    void on_toolButton_4_clicked();
    void on_toolButton_5_clicked();
    void on_toolButton_6_clicked();
    void on_toolButton_9_clicked();
    
    void readInfo();
    void on_addlightTB_clicked();
    void on_redulightTB_clicked();
    void on_powerOpenTB1_clicked();
    void on_powerCloseTB1_clicked();
    void on_powerOpenTB2_clicked();
    void on_powerCloseTB2_clicked();
    void on_equipopenTB_clicked();
    void on_equipcloseTB_clicked();
    void on_equipstopTB_clicked();
    void on_P1_openTB_clicked();
    void on_P1_closeTB_clicked();
    void on_P2_openTB_clicked();
    void on_P2_closeTB_clicked();
    void on_P2_addsoundTB_clicked();
    void on_P2_redusoundTB_clicked();
    void on_P2_AVtypeTB_clicked();
    void on_P2_addchannelTB_clicked();
    void on_P2_reduchannelTB_clicked();
    void on_P3_openTB_clicked();
    void on_P3_closeTB_clicked();
    void on_P3_windspeedTB_clicked();
    void on_P3_winddireTB_clicked();
    void on_P4_openTB_clicked();
    void on_P4_closeTB_clicked();
    void on_P4_presetTB_clicked();
    void on_P4_windspeedTB_clicked();
    void on_P4_winddireTB_clicked();
    void on_P5_openTB_clicked();
    void on_P5_closeTB_clicked();
    void on_P5_addsoundTB_clicked();
    void on_P5_redusoundTB_clicked();
    void on_P6_oporclTB_clicked();
    void on_P6_addsoundTB_clicked();
    void on_P6_redusoundTB_clicked();
    void on_P6_intooroutTB_clicked();
    void on_P6_playorpauseTB_clicked();
    void on_P6_fastforwardTB_clicked();
    void on_P6_rewindTB_clicked();
    void on_projectorRB_clicked();
    void on_televisionRB_clicked();
    void on_aircondRB_clicked();
    void on_aircondfanRB_clicked();
    void on_speakerRB_clicked();
    void on_DVDplayerRB_clicked();

    void runFan();
private:
    Ui::InteHomeFurn *ui;
    VKey *vKey;
};

#endif // INTEHOMEFURN_H
