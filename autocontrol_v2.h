#ifndef AUTOCONTROL_V2_H
#define AUTOCONTROL_V2_H

#include <QApplication>
#include <QUrl>
#include <QWidget>
#include <posix_qextserialport.h>
#include <qextserialbase.h>
#include <QTimer>
#include <QtSql>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QNetworkInterface>
#include "smartcar.h"
#include "set.h"
#include "smartshelf.h"
#include "yanshiban.h"
#include "inteshelf.h"
#include <QSound>
#include <QtCore>


struct SensorStruct
{
    int id;
   QString name;
   QString shortaddr;
   QString longaddr;
   QString dir;
   QString status;
};
Q_DECLARE_METATYPE(SensorStruct)

struct ThreeFiveStruct
{
   QString name;
   QString shortaddr;
   QString longaddr;
   QString dir;
   QString code;
};
Q_DECLARE_METATYPE(ThreeFiveStruct)

struct IRStruct
{
   QString name;
   QString shortaddr;
   QString longaddr;
   QString dir;
   QString code;
   QString function;
};
Q_DECLARE_METATYPE(IRStruct)


struct GuanXianStruct
{
   QString name;
   QString shortaddr;
   QString longaddr;
   QString dir;
   QString val;
   QString cname;
   QString cshortaddr;
   QString clongaddr;
   QString cdir;
   QString cfun;
   QString truefun;
};
Q_DECLARE_METATYPE(GuanXianStruct)

struct QiTiStruct
{
    QString name;
    QString shortaddr;
    QString longaddr;
    QString dir;
    QString cname;
    QString cshortaddr;
    QString clongaddr;
    QString cdir;
    QString cfun;
    QString truefun;
};
Q_DECLARE_METATYPE(QiTiStruct)

struct SmogStruct
{
    QString name;
    QString shortaddr;
    QString longaddr;
    QString dir;
    QString cname;
    QString cshortaddr;
    QString clongaddr;
    QString cdir;
    QString cfun;
    QString truefun;
};
Q_DECLARE_METATYPE(SmogStruct)

struct RainStruct
{
    QString name;
    QString shortaddr;
    QString longaddr;
    QString dir;
    QString cname;
    QString cshortaddr;
    QString clongaddr;
    QString cdir;
    QString cfun;
    QString truefun;
};
Q_DECLARE_METATYPE(RainStruct)

struct KeyStruct
{
    QString name;
    QString shortaddr;
    QString longaddr;
    QString dir;
    QString val;
    QString cname;
    QString cshortaddr;
    QString clongaddr;
    QString cdir;
    QString cfun;
    QString truefun;
};
Q_DECLARE_METATYPE(KeyStruct)

struct WenShiDuStruct
{
    QString name;
    QString shortaddr;
    QString longaddr;
    QString dir;
    QString wenduval;
    QString shiduval;
    QString cname;
    QString cshortaddr;
    QString clongaddr;
    QString cdir;
    QString cfun;
    QString truefun;
};
Q_DECLARE_METATYPE(WenShiDuStruct)

struct KongQiStruct
{
    QString name;
    QString shortaddr;
    QString longaddr;
    QString dir;
    QString cname;
    QString cshortaddr;
    QString clongaddr;
    QString cdir;
    QString cfun;
    QString truefun;
};
Q_DECLARE_METATYPE(KongQiStruct)

struct TelPhoneStruct
{
    QString telephone;
};
Q_DECLARE_METATYPE(TelPhoneStruct)

struct SensorValStruct
{
   QString name;
   QString shortaddr;
   QString longaddr;
   QString dir;
   QString highval;
   QString lowval;
};
Q_DECLARE_METATYPE(SensorValStruct)

struct ShevlesStruct
{
   QString name;
   QString rfidnum;
};
Q_DECLARE_METATYPE(ShevlesStruct)

struct ZhiWenStruct
{
   QString name;
   QString shortaddr;
   QString longaddr;
   QString dir;
   QString code;
};
Q_DECLARE_METATYPE(ZhiWenStruct)



namespace Ui {
class AutoControl_V2;
}



class AutoControl_V2 : public QWidget
{
    Q_OBJECT
    
public:
    explicit AutoControl_V2(QWidget *parent = 0);
    ~AutoControl_V2();
    void InitialSensor();
private:
    Ui::AutoControl_V2 *ui;
    //
   // QWidget *parent;
public:
    Posix_QextSerialPort *m_Com;
    QTimer *m_Timer;
   // QTimer *m_CheckIsRecv;
    bool bcheckisrecv;
    QTimer *m_TimerFun;
    bool bistimerfunopen;
    int itimerfuntype;
    QString btimerfunaddr;
    QString btimerfunmacaddr;

 #if 1

    int countnum[40];
    int JDSecond[40];
    int yanshibanID;
    int yanshibanID2;
    int powerID1;
    int powerID2;
    bool changeData1;
    bool changeData3;
    bool changeData4;
    bool changeHomeDB;
    bool changeAgriDB;
    bool shelfInteface;
    QString tempNow;
    QString humNow;
    QString sunNow;
    QString airNow;
    QString soiltempNow;
    QString soilhumNow;
    QString rainNow;
    QString qiyaNow;
    QString anjianNow;
    QString threefiveNow;
    QString huoyanNow;
    QString zhongliangNow;
    QString ds18b20Now;
    QString zhendongNow;
    QString chaogaopinNow;
    QString gaopinNow;
    QString dipinNow;
    QString zaoshengNow;
    QString guangxianNow;
    QString yangqiNow;
    QString shuiweiNow;
    QString co2Now;
    QString guangminNow;
    QString jieluNow;
    QString sanzhouNow;
    QString colorNow;
    InteShelf *m_ISF;
    QString ShelfData[12];

    bool GaopinFlag;

    int idnum;      //sensorTable当前数据 id号
    int rownum[32];
    bool addChange;  //数据库增添标志

    QTimer *alls_timer;
    bool JDFlag[32];
#endif

    QTcpServer *tcpServer;
    QTcpSocket *clientConnection;
    QUdpSocket *m_udp;
    QWidget *ISTparent;
 //   QTcpSocket *tcpClient;
    QSound *m_player;
    QString m_MacAddr;
    Set *m_set;
    int iaddtype;
    int whichdialog;
    bool JudgeIsAddTable(QString str);
    bool JudgeAddrIsTheSame(int itype,QString str);
    QString CharToStr(int itype,char cval1,char cval2);//
    QSqlDatabase m_sql;
    void ReadDatabase();
    void AddSensorDataTable(QString name,QString shortaddr,QString longaddr,QString dir,QString valhigh,QString vallow);
    void ReadSensorDataTable();
    void DeleteSensorDataTableToNull();
    QString RetDirByMacAddr(QString addr);
    ThreeFiveStruct m_threefivestruct[50];
    int ithreefivestructlength;
    IRStruct m_irstruct[50];
    int iirtructlength;
    SensorStruct m_sensorstruct[50];
    int isensorlength;
    GuanXianStruct m_guangxianstruct[50];
    int iguangxianstructlength;
    QiTiStruct m_qitistruct[50];
    int iqitistructlength;
    SmogStruct m_smogstruct[50];
    int ismogstructlength;
    RainStruct m_rainstruct[50];
    int irainstructlength;
    KeyStruct m_keystruct[50];
    int ikeystructlength;
    WenShiDuStruct m_wenshidustruct[50];
    int iwenshidustructlength;
    KongQiStruct m_kongqistruct[50];
    int ikongqistructlength;
    TelPhoneStruct m_telstruct[50];
    int itelephonelength;
    SensorValStruct m_sensorvalstruct[19];
    ShevlesStruct m_shevlesstruct[50];
    int ishelveslength;
    ZhiWenStruct m_zhiwenstruct[50];
    int izhiwenstructlen;
    void DeleteNullForTable();
    int tablerow;
    QChar qcharaddr;
    QString CutMACString(int itype,QString str);
    void KG_ON(QString addr, QString macaddr);
    void KG_OFF(QString addr, QString macaddr);
    void CUR_ON(QString addr, QString macaddr);
    void CUR_OFF(QString addr, QString macaddr);
    void SUN_ON(QString addr, QString macaddr, char initval);
    void SUN_OFF(QString addr, QString macaddr, char initval);
    void Ir_Send(QString addr,QString macaddr, QString code);//hongwai fasong
    void Car_AutoXun(QString caraddr, QString macaddr);
    void Car_Stop(QString caraddr, QString macaddr);
    void Car_Go(QString caraddr, QString macaddr);
    void Car_Back(QString caraddr, QString macaddr);
    void Car_Left(QString caraddr, QString macaddr);
    void Car_Right(QString caraddr, QString macaddr);
    void YuPengBettween(QString yupengaddr, QString macaddr);
    void YuPengStop(QString yupengaddr, QString macaddr);
    void YuPengOn(QString yupengaddr, QString macaddr);
    void DaPengUp(QString yupengaddr, QString macaddr);
    void DaPengStop(QString yupengaddr, QString macaddr);
    void DaPengDown(QString yupengaddr, QString macaddr);
    void YanShi_DianJi_Ting(QString addr, QString macaddr);//dianj
    void YanShi_DianJi_FanZhuan(QString addr, QString macaddr);//dianj
    void YanShi_DianJi_ZhengZhuan(QString addr, QString macaddr);
    void YanShi_ShuMaGuan(QString addr, QString macaddr,char cVal);//shumaguan
    void YanShi_BuGuangDeng_OFF(QString addr, QString macaddr);
    void YanShi_BuGuangDeng_ON(QString addr, QString macaddr);
    void YanShi_FengShan_OFF(QString addr, QString macaddr);
    void YanShi_FengShan_ON(QString addr, QString macaddr);
    void YanShi_DianCiFa_OFF(QString addr, QString macaddr);
    void YanShi_DianCiFa_ON(QString addr, QString macaddr);
    void MenSuo_ON(QString addr,QString longaddr);
    void ZhiWen_LuRu(QString addr,QString longaddr,QString code);
    void ZhiWen_Sousuo(QString addr,QString longaddr);
    void Send_PHZhi(QString addr,QString longaddr);
    void Send_Sound(QString addr,QString longaddr,char itype);
    QString FindMacAddrByNameNoDir(QString str,QString dir);
    void All_OFF();
    bool isKGType(QString addr);
    bool isThreeFiveType(QString addr);
    bool isIrType(QString addr);
    bool isSunType(QString addr);
    bool isCurType(QString addr);
    bool isYuPengType(QString addr);
    bool JudgeLianDongTheSameAddr(int itype,QString macaddr);
    QString RetIRCode(QString addr);
    QString RetIRCodeByFun(QString fun);
    QString FindMacAddrByName(QString str);
    void TrueControl(int itype,QString addr,QString macaddr, QString fval);
    SmartCar *m_car;
    QString mcaraddr;
    QString maccaraddr;
    smartshelf *m_smartshelf;
    YanShiBan *m_yanshiban;
    QString stryanshibanaddr;
    QString stryanshibanmacaddr;
    QString stryanshibanaddr2;
    QString stryanshibanmacaddr2;
    unsigned char shumaguanval;
    int ithreadsendtype;
    QString sthreadlongaddr;
    bool bthreadstart;
    void ReadControlTable();
    void ReadTelNumber();
    void ReadShevlesTable();
    void SendUpdate();
    void SendUpDateEnd();
    void ReadSensorValTable();
    void SendDataClient(char ctype);
    QString GetMacAddr();
    char strtohex(QString str);
    QString CutMacAddrStr(QString str,int itype);
    void SendDataToServerByUdpWenDu(QString dir, char ctype);
    void SendDataToServeByCar(QString dir,QString macaddr,char tempval);
    QString CarRFIDMacAddr;
    char CarTempVal;
   // bool bcaropen;
    void HexIntToNetwork( bool is64, char *str, char *result);

    QString telnumber;

    QString FindShortAddrByName(QString str);
    QString FindLongAddrByName(QString str);
    QString FindShortAddrWhile(QString name,QString dir);
    QString FindLongAddrWhile(QString name,QString dir);
    void SendWenDuOrderToCar(QString TelNum,QString macaddr);
    void SendWenDuOrderToCarNoDuanXin(QString macaddr);
    QString CutTelnumber(int itype,QString telnum);
//    void DeleteTempHum();
//    void DeleteGuangXian();
private slots:
    void ShowComMsg();
  //  void ShowComIsRecv();
//    void TimerFunForKG();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_tableWidget_cellClicked(int row, int column);
    void on_pushButton_4_clicked();


    void on_BackPB_clicked();

    void SensorFun();
};
extern AutoControl_V2 *m_control;
#endif // AUTOCONTROL_V2_H
