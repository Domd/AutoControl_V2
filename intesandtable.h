#ifndef INTESANDTABLE_H
#define INTESANDTABLE_H

#include <QWidget>
#include <QtGui>
#include <QTime>
#include <QTimer>
#include "autocontrol_v2.h"
#include "smartcar.h"
#include "testbasic.h"
#include "testwifi.h"
#include "testcom.h"
#include "testgprs.h"
#include "testgps.h"
#include "testthreeg.h"
#include "adddevice.h"
#include "set.h"

namespace Ui {
class InteSandTable;
}

class InteSandTable : public QWidget
{
    Q_OBJECT
    
public:
    explicit InteSandTable(QWidget *parent = 0);
    ~InteSandTable();

    AddDevice *m_add;
//    Set *m_set;

    QString TimeNowText;
    QString DateNowText;
//    QString GetWeek(int );
   QWidget *parent;
   QTimer *timer;
   SmartCar *m_car;
   smartshelf *m_smartshelf;
   YanShiBan *m_yanshiban;
   //void showData();
   void ReadDatabase();
   int isensorlength;
   void DeleteNullForTable();
   void InputDbOnline(int );
   void InputDbOffline(int );
//   bool JudgeDb(int );
   void addStatusDb();
   void InfraredControlFun(QString ,QString );
    char initval;
   int aTob[40];
   int bToa[40];
//   bool changeAgriDB;
    TestBasic *m_TBF;
    TestWifi *m_TWF;
    TestCom *m_TCM;
    TestGprs *m_TGprs;
    TestGps *m_TGps;
    TestThreeG *m_TTG;

private:
    Ui::InteSandTable *ui;

private slots:
    void mousePressEvent(QMouseEvent * event);

   void on_toolButton1_clicked();//界面1
   void on_toolButton2_clicked();
   void on_toolButton3_clicked();
   void on_toolButton4_clicked();
   void on_toolButton_clicked();  //设置界面
   void TimerOut();

   void on_carcontrolTB_clicked();
   void on_demoboradTB_clicked();
   void on_smartshelfTB_clicked();
   void on_gatelockTB_clicked();
   void on_PHvalueTB_clicked();

   void on_fingerprintTB_clicked();

   void on_projectorRB_clicked();
   void on_televisionRB_clicked();
   void on_aircondfanRB_clicked();
   void on_aircondRB_clicked();
   void on_speakerRB_clicked();
   void on_DVDplayerRB_clicked();

   void on_P3_openTB_clicked();
   void on_P3_closeTB_clicked();
   void on_P3_windspeedTB_clicked();
   void on_P3_winddireTB_clicked();
   void on_P1_openTB_clicked();
   void on_P1_closeTB_clicked();
   void on_P2_openTB_clicked();
   void on_P2_closeTB_clicked();
   void on_P2_addsoundTB_clicked();
   void on_P2_redusoundTB_clicked();
   void on_P2_AVtypeTB_clicked();
   void on_P2_addchannelTB_clicked();
   void on_P2_reduchannelTB_clicked();
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
   void on_equipopenTB_clicked();
   void on_equipcloseTB_clicked();
   void on_equipstopTB_clicked();

   void on_addlightTB_clicked();
   void on_redulightTB_clicked();
   void on_SersonStatusTW_cellClicked(int row, int column);
   void on_toolButton5_clicked();
   void on_curtainsRB_clicked();
   void on_canopyRB_clicked();

   void on_qiangdianTB_clicked();
   void on_qiangdianTB2_clicked();
   void on_qiangdianTB_2_clicked();
   void on_qiangdianTB2_2_clicked();

//   void on_Tb_jiaoping_clicked();
};

#endif // INTESANDTABLE_H
