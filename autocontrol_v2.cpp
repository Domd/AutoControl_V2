#include "autocontrol_v2.h"
#include "ui_autocontrol_v2.h"
#include "intesandtable.h"
#include <QMessageBox>
#include <QDebug>

/*===========================================================================================================
    CopyRight By Yuanyuan From WuXi FanTai at 2012-10-08
*/
//===========================================================================================================
AutoControl_V2 *m_control;

char send[21]={0xFD,0x0F,0x0A,0xFF,0x00,0x00,'K',0x0A,0xFF,0xDD,0x01,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00};
char sendir[21]={0xFD,0x0F,0x0A,0xFF,0x00,0x00,'K',0x0A,0xFF,0xDD,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
char sendclientdata[22]={0x00};
char initval=0x40;
char gaopinval[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
char dipinval[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
//char chaogaopinval[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
char rfidoval[16]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
char sendcar[32]={0xFD,0x1A,0x0A,0xFF,0x00,0x00,0x06,0x0A,0xFF,0xEA,0x0B,0xEA,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0X00};
char sendcarnoduanxin[21]={0xFD,0x0F,0x0A,0xFF,0x00,0x00,0x06,0x0A,0xFF,0xEA,0x00,0xEA,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

AutoControl_V2::AutoControl_V2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AutoControl_V2)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    iaddtype=-1;whichdialog=-1;iirtructlength=-1;ithreefivestructlength=-1;tablerow=-1;mcaraddr="";
    bcheckisrecv=false;m_MacAddr="";bistimerfunopen=false;btimerfunaddr="";btimerfunmacaddr="";stryanshibanaddr="";stryanshibanmacaddr="";shumaguanval=0x30;
    telnumber="NULL";maccaraddr="NULL";ithreadsendtype=-1;sthreadlongaddr="NULL";bthreadstart=false;CarRFIDMacAddr="";CarTempVal=0x00;
   // bcaropen=false;

    ui->pushButton_2->setVisible(false);  //隐藏按键
    ui->pushButton_3->setVisible(false);
    ui->pushButton_4->setVisible(false);
//=====================================================================================================================
    m_sql=QSqlDatabase::addDatabase("QSQLITE");
    m_sql.setDatabaseName("/mnt/sdcard/DeviceMessage.db");  //创建db数据库
    //m_sql.setDatabaseName("/DeviceMessage.db");
    if(!m_sql.open())
    {
       QMessageBox::warning(this, trUtf8("提示"), trUtf8("数据库打开失败。。"),QMessageBox::Ok);
       return;
    }
    else
    {
        QSqlQuery m_query(m_sql);

        m_query.prepare("CREATE TABLE IF NOT EXISTS SensorTable (id INTEGER PRIMARY KEY AUTOINCREMENT,name STRING(40),shortaddr STRING(40),longaddr STRING(40),direction STRING(40),status STRING(40))");
        if(!m_query.exec())
        {
            QMessageBox::warning(this, trUtf8("提示"), trUtf8("创建表1错误。。"),QMessageBox::Ok);
            ui->label->setText(trUtf8("创建表1错误"));
            return;
        }
        m_query.prepare("CREATE TABLE IF NOT EXISTS IRHWTable (name STRING(40),shortaddr STRING(40),longaddr STRING(40),direction STRING(40),code STRING(40),cfunction STRING(40))");
        if(!m_query.exec())
        {
            QMessageBox::warning(this, trUtf8("提示"), trUtf8("创建表2错误。。"),QMessageBox::Ok);
            ui->label->setText(trUtf8("创建表2错误"));
            return;
        }
        m_query.prepare("CREATE TABLE IF NOT EXISTS SensorDataTable (name STRING(40),shortaddr STRING(40),longaddr STRING(40),dir STRING(40),valhigh STRING(40),vallow STRING(40))");
        if(!m_query.exec())
        {
            QMessageBox::warning(this, trUtf8("提示"), trUtf8("创建表3错误。。"),QMessageBox::Ok);
            ui->label->setText(trUtf8("创建表3错误"));
            return;
        }
        m_query.prepare("CREATE TABLE IF NOT EXISTS ThreeFiveDevTable (name STRING(40),shortaddr STRING(40),longaddr STRING(40),dir STRING(40),code STRING(40))");
        if(!m_query.exec())
        {
            QMessageBox::warning(this, trUtf8("提示"), trUtf8("创建表4错误。。"),QMessageBox::Ok);
            ui->label->setText(trUtf8("创建表4错误"));
            return;
        }
        m_query.prepare("CREATE TABLE IF NOT EXISTS GuanXianTable (name STRING(40),shortaddr STRING(40),longaddr STRING(40),dir STRING(40),guanxianval STRING(40),cname STRING(40),cshortaddr STRING(40),clongaddr STRING(40),cdir STRING(40),cfunction STRING(40),truefunction STRING(40))");
        if(!m_query.exec())
        {
            QMessageBox::warning(this, trUtf8("提示"), trUtf8("创建表5错误。。"),QMessageBox::Ok);
            ui->label->setText(trUtf8("创建表5错误"));
            return;
        }
        m_query.prepare("CREATE TABLE IF NOT EXISTS QiTiTable (name STRING(40),shortaddr STRING(40),longaddr STRING(40),dir STRING(40),cname STRING(40),cshortaddr STRING(40),clongaddr STRING(40),cdir STRING(40),cfunction STRING(40),truefunction STRING(40))");
        if(!m_query.exec())
        {
            QMessageBox::warning(this, trUtf8("提示"), trUtf8("创建表6错误。。"),QMessageBox::Ok);
            ui->label->setText(trUtf8("创建表6错误"));
            return;
        }
        m_query.prepare("CREATE TABLE IF NOT EXISTS SmogTable (name STRING(40),shortaddr STRING(40),longaddr STRING(40),dir STRING(40),cname STRING(40),cshortaddr STRING(40),clongaddr STRING(40),cdir STRING(40),cfunction STRING(40),truefunction STRING(40))");
        if(!m_query.exec())
        {
            QMessageBox::warning(this, trUtf8("提示"), trUtf8("创建表7错误。。"),QMessageBox::Ok);
            ui->label->setText(trUtf8("创建表7错误"));
            return;
        }
        m_query.prepare("CREATE TABLE IF NOT EXISTS RainTable (name STRING(40),shortaddr STRING(40),longaddr STRING(40),dir STRING(40),cname STRING(40),cshortaddr STRING(40),clongaddr STRING(40),cdir STRING(40),cfunction STRING(40),truefunction STRING(40))");
        if(!m_query.exec())
        {
            QMessageBox::warning(this, trUtf8("提示"), trUtf8("创建表8错误。。"),QMessageBox::Ok);
            ui->label->setText(trUtf8("创建表8错误"));
            return;
        }
        m_query.prepare("CREATE TABLE IF NOT EXISTS KeyTable (name STRING(40),shortaddr STRING(40),longaddr STRING(40),dir STRING(40),keyval STRING(40),cname STRING(40),cshortaddr STRING(40),clongaddr STRING(40),cdir STRING(40),cfunction STRING(40),truefunction STRING(40))");
        if(!m_query.exec())
        {
            QMessageBox::warning(this, trUtf8("提示"), trUtf8("创建表9错误。。"),QMessageBox::Ok);
            ui->label->setText(trUtf8("创建表9错误"));
            return;
        }
        m_query.prepare("CREATE TABLE IF NOT EXISTS WenShiDuTable (name STRING(40),shortaddr STRING(40),longaddr STRING(40),dir STRING(40),wenduval STRING(40),shiduval STRING(40),cname STRING(40),cshortaddr STRING(40),clongaddr STRING(40),cdir STRING(40),cfunction STRING(40),truefunction STRING(40))");
        if(!m_query.exec())
        {
            QMessageBox::warning(this, trUtf8("提示"), trUtf8("创建表10错误。。"),QMessageBox::Ok);
            ui->label->setText(trUtf8("创建表10错误"));
            return;
        }
        m_query.prepare("CREATE TABLE IF NOT EXISTS KongQiTable (name STRING(40),shortaddr STRING(40),longaddr STRING(40),dir STRING(40),cname STRING(40),cshortaddr STRING(40),clongaddr STRING(40),cdir STRING(40),cfunction STRING(40),truefunction STRING(40))");
        if(!m_query.exec())
        {
            QMessageBox::warning(this, trUtf8("提示"), trUtf8("创建表11错误。。"),QMessageBox::Ok);
            ui->label->setText(trUtf8("创建表11错误"));
            return;
        }
        m_query.prepare("CREATE TABLE IF NOT EXISTS DuanXinSetTable (msg STRING(40),shortaddr STRING(40),longaddr STRING(40),code STRING(40),fun STRING(40))");
        if(!m_query.exec())
        {
            QMessageBox::warning(this, trUtf8("提示"), trUtf8("创建表12错误。。"),QMessageBox::Ok);
            ui->label->setText(trUtf8("创建表12错误"));
            return;
        }
        m_query.prepare("CREATE TABLE IF NOT EXISTS TelNumTable (number STRING(40))");
        if(!m_query.exec())
        {
            QMessageBox::warning(this, trUtf8("提示"), trUtf8("创建表13错误。。"),QMessageBox::Ok);
            ui->label->setText(trUtf8("创建表13错误"));
            return;
        }
        m_query.prepare("CREATE TABLE IF NOT EXISTS ShelvesMessTable (name STRING(40),rfidnum STRING(40))");
        if(!m_query.exec())
        {
            QMessageBox::warning(this, trUtf8("提示"), trUtf8("创建表14错误。。"),QMessageBox::Ok);
            ui->label->setText(trUtf8("创建表14错误"));
            return;
        }
        m_query.prepare("CREATE TABLE IF NOT EXISTS ZhiWenTable (name STRING(40),shortaddr STRING(40),longaddr STRING(40),dir STRING(40),code STRING(40))");
        if(!m_query.exec())
        {
            QMessageBox::warning(this, trUtf8("提示"), trUtf8("创建表15错误。。"),QMessageBox::Ok);
            ui->label->setText(trUtf8("创建表15错误"));
            return;
        }
    }
    QStringList header;
    header.append(trUtf8("节点名称"));
    header.append(trUtf8("节点位置"));
    header.append(trUtf8("短地址"));
    header.append(trUtf8("MAC节点地址"));

    header.append(trUtf8("节点状态"));

    ui->tableWidget->setColumnCount(5);   //设置4列数据
    ui->tableWidget->setColumnWidth(0, 130);
    ui->tableWidget->setColumnWidth(1, 140);
    ui->tableWidget->setColumnWidth(2, 140);
    ui->tableWidget->setColumnWidth(3, 300);

    ui->tableWidget->setColumnWidth(4,300);

    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //设置选择行为 ，以行为单位
    //ui->tableWidget->verticalHeader()->setVisible(false);     //隐藏列表头
    //ui->tableWidget->horizontalHeader()->setVisible(false);  //隐藏行表头
    ui->tableWidget->setFrameShape(QFrame::Box);//QFrame在它的内容周围画一个框
    //ui->tableWidget->setFrameShape(QFrame::NoFrame);  //设置边框 (不画任何东西)

    ReadDatabase();
    ReadControlTable();
    ReadShevlesTable();
    ReadTelNumber();
////==========================================================================================
//    m_CheckIsRecv=new QTimer(this);
//    connect(m_CheckIsRecv,SIGNAL(timeout()),this, SLOT(ShowComIsRecv()));
//==========================================================================================
//    m_TimerFun=new QTimer(this);
//    connect(m_TimerFun,SIGNAL(timeout()),this, SLOT(TimerFunForKG()));
   // m_TimerFun->start(1000);
//==========================================================================================
    //--
    InitialSensor();
    //--

//===========================================================================================
    m_udp=new QUdpSocket(this);
    m_udp->bind(QHostAddress::Any,19891);//19891988  //bind监听某个端口
    //m_udp->bind(QHostAddress::LocalHost,16888);
//    connect(m_udp,SIGNAL(readyRead()),this,SLOT(UdpRecving()));
    ui->label->setText(" udp connect ...");
    m_MacAddr=GetMacAddr();  //得到计算机的网卡地址
//=======================================================================================================================

//=======================================================================================================================
    QFile f("/dev/ttySAC3");
    if (f.exists())
    {
        m_Com = new Posix_QextSerialPort("/dev/ttySAC3",QextSerialBase::Polling);//定义串口对象，指定串口名,使用查询方式
        if (m_Com->open(QIODevice::ReadWrite))//ttySAC3
        {
            m_Com->setBaudRate(BAUD38400);//波特率
            m_Com->setDataBits(DATA_8);
            m_Com->setParity(PAR_NONE);
            m_Com->setStopBits(STOP_1);
            m_Com->setFlowControl(FLOW_OFF);
            m_Com->setTimeout(10);
            ui->textlabel->setText(trUtf8("ttySAC3 已打开 38400bps 8"));
            m_Timer = new QTimer(this);
            m_Timer->start(100);

        }
        else
        {
            ui->label->setText(trUtf8("ttySAC3 串口打开失败"));
            QMessageBox::warning(this, trUtf8("提示"),trUtf8("串口打开失败！"), QMessageBox::Ok);
            return;
        }
    }
    else
    {
        ui->label->setText(trUtf8("ttySAC3 串口不存在"));
        QMessageBox::warning(this, trUtf8("提示"), trUtf8("串口不存在！"),QMessageBox::Ok);
        return;
    }
    connect(m_Timer, SIGNAL(timeout()), this, SLOT(ShowComMsg()));

    DeleteSensorDataTableToNull();
}

AutoControl_V2::~AutoControl_V2()
{

    tcpServer->close();
    delete tcpServer;

    m_udp->close();
    delete m_udp;

    clientConnection->close();
    delete clientConnection;

//    m_TimerFun->stop();
//    delete m_TimerFun;

    m_Timer->stop();
    delete m_Timer;

    m_Com->close();
    delete m_Com;



    alls_timer->stop();
    delete alls_timer;

    delete ui;
}

//--
void AutoControl_V2::InitialSensor()
{
    for(int j=0;j<18;j++)
    {
        rownum[j]=0;
        JDSecond[j]=0;
    }

    QPixmap pb0011;  //返回 按钮
    pb0011.load(":/images/button/0011.png");
    ui->BackPB->setIcon(pb0011);
    ui->BackPB->setIconSize(pb0011.size());
    ui->BackPB->setStyleSheet("QPushButton{border-radius:5px;border-width:0px;}");
    changeHomeDB=false;
    changeAgriDB=false;
    addChange=false;
    changeData1=false;
    changeData3=false;
    changeData4=false;//判断数据更新
    GaopinFlag=false;
    powerID1=0;
    idnum=1;
    int m=0;
    for(;m<isensorlength;m++)
    {
        if(m_sensorstruct[m].name==trUtf8("三轴加速度"))
        {
            rownum[0]=m_sensorstruct[m].id;
        }
        else if(m_sensorstruct[m].name==trUtf8("颜色"))
        {
            rownum[1]=m_sensorstruct[m].id;
        }
        else if(m_sensorstruct[m].name==trUtf8("温湿度") && m_sensorstruct[m].dir==trUtf8("智能家居"))
        {
            rownum[2]=m_sensorstruct[m].id;
        }
        else if(m_sensorstruct[m].name==trUtf8("火焰") && m_sensorstruct[m].dir==trUtf8("智能家居"))
        {
            rownum[3]=m_sensorstruct[m].id;
        }
        else if(m_sensorstruct[m].name==trUtf8("空气质量"))
        {
            rownum[4]=m_sensorstruct[m].id;
        }
        else if(m_sensorstruct[m].name==trUtf8("气压"))
        {
            rownum[5]=m_sensorstruct[m].id;
        }
        else if(m_sensorstruct[m].name==trUtf8("结露"))
        {
            rownum[6]=m_sensorstruct[m].id;
        }
        else if(m_sensorstruct[m].name==trUtf8("按键"))
        {
            rownum[7]=m_sensorstruct[m].id;
        }
        else if(m_sensorstruct[m].name==trUtf8("光敏"))
        {
            rownum[8]=m_sensorstruct[m].id;
        }
        else if(m_sensorstruct[m].name==trUtf8("演示板") && m_sensorstruct[m].dir==trUtf8("智能家居"))
        {
            rownum[9]=m_sensorstruct[m].id;
            stryanshibanaddr=m_sensorstruct[m].shortaddr;
            stryanshibanmacaddr=m_sensorstruct[m].longaddr;
        }
        else if(m_sensorstruct[m].name==trUtf8("光线") )
        {
            rownum[10]=m_sensorstruct[m].id;
        }
        else if(m_sensorstruct[m].name==trUtf8("温湿度") &&  m_sensorstruct[m].dir==trUtf8("智慧农业"))
        {
            rownum[11]=m_sensorstruct[m].id;
        }
        else if(m_sensorstruct[m].name==trUtf8("土壤温湿度"))
        {
            rownum[12]=m_sensorstruct[m].id;
        }
        else if(m_sensorstruct[m].name==trUtf8("二氧化碳"))
        {
            rownum[13]=m_sensorstruct[m].id;
        }
        else if(m_sensorstruct[m].name==trUtf8("火焰") && m_sensorstruct[m].dir==trUtf8("智慧农业"))
        {
            rownum[14]=m_sensorstruct[m].id;
        }
        else if(m_sensorstruct[m].name==trUtf8("演示板") &&  m_sensorstruct[m].dir==trUtf8("智慧农业"))
        {
            rownum[15]=m_sensorstruct[m].id;
            stryanshibanaddr2=m_sensorstruct[m].shortaddr;
            stryanshibanmacaddr2=m_sensorstruct[m].longaddr;
        }
        else if(m_sensorstruct[m].name==trUtf8("货架"))
        {
            rownum[16]=m_sensorstruct[m].id;
        }
        else if(m_sensorstruct[m].name==trUtf8("高频"))
        {
            rownum[17]=m_sensorstruct[m].id;
        }
        else if(m_sensorstruct[m].name==trUtf8("设备1"))
        {
            powerID1=m_sensorstruct[m].id;
        }
        else if(m_sensorstruct[m].name==trUtf8("设备2"))
        {
            powerID2=m_sensorstruct[m].id;
        }
        if(m==isensorlength-1)
            idnum=m_sensorstruct[m].id+1;
    }

//    char buf[10];
//    sprintf(buf,"isensor=%d",isensorlength);
//    QMessageBox::warning(0,"Tip",QString(buf));
//    char buff[10];
//    sprintf(buff,"m=%d",m);
//    QMessageBox::warning(0,"Tip",QString(buff));
//    char bufff[10];
//    sprintf(bufff,"idnum=%d",idnum);
//    QMessageBox::warning(0,"Tip",QString(bufff));
    //设置每个节点状态定时器
    for(int k=0;k<18;k++)
    {
        JDFlag[k]=false;
    }

    shelfInteface=false;

    alls_timer=new QTimer(this);
    connect(alls_timer,SIGNAL(timeout()),this,SLOT(SensorFun()));
    alls_timer->start(1000);
}


void AutoControl_V2::ShowComMsg()
{

    char cData[64];
    if (m_Com->isOpen())//
    {
        memset(cData, 0, sizeof(cData));
        int iLen = m_Com->read(cData, sizeof(cData));//读取串口数据
        if (iLen > 0)
        {
               if(cData[0]==0xFD||cData[0]==0xFA)//数据标志
               {
                   ui->label->setText("");
                   QString str="";QString str1="";
                   str.sprintf("%02x",cData[4]);
                   str1.sprintf("%02x",cData[5]);
                   str=str+str1;  //短地址

                   QString str2="";QString sLAddr="";
                   int ibegin=(int)cData[1];
                   for(int ic=(6+ibegin-8);ic<(6+ibegin-8)+8;ic++)
                   {
                       str2.sprintf("%02x",cData[ic]);
                       sLAddr=sLAddr+str2;//取他的IEEE地址位 （MAC地址）
                   }
                   switch(cData[6])//判断传感器数据类型
                   {
                      case 'A'://雨滴  J
                      {
                        if(whichdialog==1&&iaddtype==6)
                        {
                            if(JudgeAddrIsTheSame(whichdialog,sLAddr)==false)
                            {
                                (m_set->m_add->m_table)->setRowCount((m_set->m_add->m_table)->rowCount()+1);
                                (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),0,new QTableWidgetItem(trUtf8("雨滴")));
                                (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),1,new QTableWidgetItem(str));
                                (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),2,new QTableWidgetItem(sLAddr));
                                (m_set->m_add->m_table)->setRowHeight(((m_set->m_add->m_table)->rowCount()-1),50);

                            }
                        }
                        else
                        {
                            if(JudgeIsAddTable(sLAddr)==true)
                            {
                                switch(cData[7])
                                {
                                    case 0x00://no
                                    {
                                       DeleteSensorDataTableToNull();
                                       ui->label->setText(trUtf8("没雨"));
                                       rainNow=trUtf8("没雨");
                                       QString s2=CharToStr(4,cData[7],0x00);
                                       AddSensorDataTable(trUtf8("雨滴"),str,sLAddr,RetDirByMacAddr(sLAddr),s2,"NULL");
                                       if(JudgeLianDongTheSameAddr(4,sLAddr)==true)//shifou control
                                       {
                                           TrueControl(5,str,sLAddr,s2);
                                       }
                                       break;
                                    }
                                    case 0x01://y
                                    {
                                       DeleteSensorDataTableToNull();
                                       ui->label->setText(trUtf8("监测到有雨"));
                                       rainNow=trUtf8("有雨");
                                       QString s2=CharToStr(4,cData[7],0x00);
                                       AddSensorDataTable(trUtf8("雨滴"),str,sLAddr,RetDirByMacAddr(sLAddr),s2,"NULL");
                                       if(JudgeLianDongTheSameAddr(4,sLAddr)==true)//shifou control
                                       {
                                           TrueControl(4,str,sLAddr,s2);
                                       }
                                       break;
                                    }
                                }
                            }
                            else
                            {
                                ui->label->setText(trUtf8("您未添加此设备"));
                            }
                        }
                          break;
                      }
                      case 'C'://光线   J
                      {
                        if(whichdialog==1&&iaddtype==6)
                        {
                            if(JudgeAddrIsTheSame(whichdialog,sLAddr)==false)
                            {
                                (m_set->m_add->m_table)->setRowCount((m_set->m_add->m_table)->rowCount()+1);
                                (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),0,new QTableWidgetItem(trUtf8("光线")));
                                (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),1,new QTableWidgetItem(str));
                                (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),2,new QTableWidgetItem(sLAddr));
                                (m_set->m_add->m_table)->setRowHeight(((m_set->m_add->m_table)->rowCount()-1),50);

                            }
                        }
                       else
                       {
                           if(JudgeIsAddTable(sLAddr)==true)
                           {
                               DeleteSensorDataTableToNull();
                               ui->label->setText(trUtf8("当前光线强度:")+CharToStr(4,cData[7],0x01));
                               sunNow=CharToStr(4,cData[7],0x01);
//                               changeData3=true;
                               changeData4=true;
                               AddSensorDataTable(trUtf8("光线"),str,sLAddr,RetDirByMacAddr(sLAddr),CharToStr(4,cData[/*ilength+*/7],0x00),"NULL");
                           }
                            else
                           {
                                ui->label->setText(trUtf8("您未添加此设备"));
                           }

                       }
                        break;
                      }
                      case 'E'://温湿度   J
                      {                 
                       if(whichdialog==1&&iaddtype==6)
                       {
                           if(JudgeAddrIsTheSame(whichdialog,sLAddr)==false)
                           {
                               (m_set->m_add->m_table)->setRowCount((m_set->m_add->m_table)->rowCount()+1);
                               (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),0,new QTableWidgetItem(trUtf8("温湿度")));
                               (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),1,new QTableWidgetItem(str));
                               (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),2,new QTableWidgetItem(sLAddr));
                               (m_set->m_add->m_table)->setRowHeight(((m_set->m_add->m_table)->rowCount()-1),50);
                           }
                       }
                       else
                       {
                           if(JudgeIsAddTable(sLAddr)==true)
                           {
                               changeData4=true;
                               ui->label->setText(trUtf8("当前湿度:")+CharToStr(3,cData[7],cData[8])+"%RH"+trUtf8("  当前温度:")+CharToStr(3,cData[9],cData[10]));                               
                               for(int i=0;i<isensorlength;i++)
                               {
                                   if(trUtf8("土壤温湿度")==m_sensorstruct[i].name&& QString::compare(sLAddr,m_sensorstruct[i].longaddr)==0)
                                   {
                                       JDSecond[12]=0;
                                       JDFlag[12]=true;
                                       changeData3=true;
                                       soilhumNow=CharToStr(3,cData[7],cData[8]);
                                       soiltempNow=CharToStr(3,cData[9],cData[10]);
                                        break;
                                   }
                                   if(trUtf8("温湿度")==m_sensorstruct[i].name && QString::compare(sLAddr,m_sensorstruct[i].longaddr)==0&&trUtf8("智能家居")==m_sensorstruct[i].dir)
                                   {
                                       JDSecond[2]=0;
                                       JDFlag[2]=true;
                                       changeData1=true;
                                       humNow=CharToStr(3,cData[7],cData[8]);
                                       tempNow=CharToStr(3,cData[9],cData[10]);
                                       break;
                                   }
                                   if(trUtf8("温湿度")==m_sensorstruct[i].name && QString::compare(sLAddr,m_sensorstruct[i].longaddr)==0&&trUtf8("智慧农业")==m_sensorstruct[i].dir)
                                   {
                                       JDSecond[11]=0;
                                       JDFlag[11]=true;
                                       changeData3=true;
                                       humNow=CharToStr(3,cData[7],cData[8]);
                                       tempNow=CharToStr(3,cData[9],cData[10]);
                                       break;
                                   }
                               }

                               DeleteSensorDataTableToNull();
                               AddSensorDataTable(trUtf8("湿度"),str,sLAddr,RetDirByMacAddr(sLAddr),CharToStr(4,cData[7],0x00),CharToStr(4,cData[8],0x00));
                               AddSensorDataTable(trUtf8("温度"),str,sLAddr,RetDirByMacAddr(sLAddr),CharToStr(4,cData[9],0x00),CharToStr(4,cData[10],0x00));

                               if(JudgeLianDongTheSameAddr(6,sLAddr)==true)
                               {
                                   TrueControl(7,str,sLAddr,CharToStr(3,cData[9],cData[10]));
                                   TrueControl(8,str,sLAddr,CharToStr(3,cData[7],cData[8]));
                               }
                               //=================UDPSending==========================================
                               ithreadsendtype=1;
                               sthreadlongaddr=sLAddr;
//                               SendDataToServerByUdpWenDu(RetDirByMacAddr(sLAddr),0x05);
//                               SendDataToServerByUdpWenDu(RetDirByMacAddr(sLAddr),0x06);

                           }
                           else
                           {
                             ui->label->setText(trUtf8("您未添加此设备"));
                           }
                       }
                       break;
                      }
                      case 'J'://空气质量   J
                      {
                       JDSecond[4]=0;
                       JDFlag[4]=true;
                       if(whichdialog==1&&iaddtype==6)
                       {
                           if(JudgeAddrIsTheSame(whichdialog,sLAddr)==false)
                           {
                               (m_set->m_add->m_table)->setRowCount((m_set->m_add->m_table)->rowCount()+1);
                               (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),0,new QTableWidgetItem(trUtf8("空气质量")));
                               (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),1,new QTableWidgetItem(str));
                               (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),2,new QTableWidgetItem(sLAddr));
                               (m_set->m_add->m_table)->setRowHeight(((m_set->m_add->m_table)->rowCount()-1),50);

                           }
                       }
                       else
                       {
                          if(JudgeIsAddTable(sLAddr)==true)
                          {
                              changeData1=true;
                              changeData4=true;
                              switch(cData[7])
                              {
                                  case 0x00://y
                                  {
                                     ui->label->setText(trUtf8("空气质量异常"));

                                     DeleteSensorDataTableToNull();

                                     AddSensorDataTable(trUtf8("空气质量"),str,sLAddr,RetDirByMacAddr(sLAddr),CharToStr(4,cData[/*ilength+*/7],0x00),"NULL");
                                     airNow=trUtf8("空气质量异常");
                                     if(JudgeLianDongTheSameAddr(7,sLAddr)==true)
                                     {
                                         TrueControl(9,str,sLAddr,CharToStr(4,cData[/*ilength+*/7],0x00));
                                     }
                                     //===========================================================================================
                                     ithreadsendtype=2;
                                     sthreadlongaddr=sLAddr;
                                    // SendDataToServerByUdpWenDu(RetDirByMacAddr(sLAddr),0x22);

                                     break;
                                  }
                                  case 0x01://y
                                  {
                                     ui->label->setText(trUtf8("空气质量正常"));

                                     AddSensorDataTable(trUtf8("空气质量"),str,sLAddr,RetDirByMacAddr(sLAddr),CharToStr(4,cData[/*ilength+*/7],0x00),"NULL");
                                    airNow=trUtf8("空气质量正常");
                                     if(JudgeLianDongTheSameAddr(7,sLAddr)==true)
                                     {
                                         TrueControl(10,str,sLAddr,CharToStr(4,cData[7],0x00));
                                     }
                                     //===========================================================================================
                                     ithreadsendtype=2;
                                     sthreadlongaddr=sLAddr;
                                     // SendDataToServerByUdpWenDu(RetDirByMacAddr(sLAddr),0x22);
                                     break;
                                  }
                              }
                          }
                          else
                          {
                              ui->label->setText(trUtf8("您未添加此设备"));
                          }
                       }
                          break;
                      }
                      case 'F'://气压   J
                      {
                       JDSecond[5]=0;
                       JDFlag[5]=true;
                       if(whichdialog==1&&iaddtype==6)
                       {
                           if(JudgeAddrIsTheSame(whichdialog,sLAddr)==false)
                           {
                               (m_set->m_add->m_table)->setRowCount((m_set->m_add->m_table)->rowCount()+1);
                               (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),0,new QTableWidgetItem(trUtf8("气压")));
                               (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),1,new QTableWidgetItem(str));
                               (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),2,new QTableWidgetItem(sLAddr));
                               (m_set->m_add->m_table)->setRowHeight(((m_set->m_add->m_table)->rowCount()-1),50);

                           }
                       }
                       else
                       {
                           if(JudgeIsAddTable(sLAddr)==true)
                           {
                               changeData1=true;                               
                               changeData4=true;
                               DeleteSensorDataTableToNull();
                               ui->label->setText(trUtf8("当前气压值:")+CharToStr(3,cData[9],cData[10])+"Pa");
                               QString s1=CharToStr(2,cData[4],cData[5]);
                               AddSensorDataTable(trUtf8("气压"),s1,sLAddr,RetDirByMacAddr(sLAddr),CharToStr(4,cData[7],0x00),CharToStr(4,cData[8],0x00));
                               qiyaNow=CharToStr(3,cData[9],cData[10])+"Pa";
                           }
                           else
                           {
                              ui->label->setText(trUtf8("您未添加此设备"));
                           }
                       }
                          break;
                      }
                      case 'N'://火焰   J
                      {
                       JDSecond[14]=0;
                       JDFlag[14]=true;
                       if(whichdialog==1&&iaddtype==6)
                       {
                           if(JudgeAddrIsTheSame(whichdialog,sLAddr)==false)
                           {
                               (m_set->m_add->m_table)->setRowCount((m_set->m_add->m_table)->rowCount()+1);
                               (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),0,new QTableWidgetItem(trUtf8("火焰")));
                               (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),1,new QTableWidgetItem(str));
                               (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),2,new QTableWidgetItem(sLAddr));
                               (m_set->m_add->m_table)->setRowHeight(((m_set->m_add->m_table)->rowCount()-1),50);

                           }
                       }
                       else
                       {
                           if(JudgeIsAddTable(sLAddr)==true)
                           {
                               changeData1=true;
                               changeData3=true;
                               changeData4=true;
                               switch(cData[/*ilength+*/7])
                               {
                                   case 0x00://y
                                   {
                                      DeleteSensorDataTableToNull();
                                      ui->label->setText(trUtf8("火焰正常状态"));
                                      QString s1=CharToStr(2,cData[4],cData[5]);
                                      AddSensorDataTable(trUtf8("火焰"),s1,sLAddr,RetDirByMacAddr(sLAddr),CharToStr(4,cData[7],0x00),"NULL");
                                      huoyanNow=trUtf8("火焰正常状态");
                                      break;
                                   }
                                   case 0x01://y
                                   {
                                      DeleteSensorDataTableToNull();
                                      ui->label->setText(trUtf8("监测有火"));
                                      QString s1=CharToStr(2,cData[4],cData[5]);
                                      AddSensorDataTable(trUtf8("火焰"),s1,sLAddr,RetDirByMacAddr(sLAddr),CharToStr(4,cData[7],0x00),"NULL");
                                      huoyanNow=trUtf8("监测有火");
                                      break;
                                   }
                               }
                           }
                           else
                           {
                               ui->label->setText(trUtf8("您未添加此设备"));
                           }
                       }
                          break;
                      }
                      case 'S'://调光    K
                      {
                         if(cData[7]==0xAA&&cData[8]==0xAA&&cData[9]==0xAA)
                         {

                           if(whichdialog==1&&iaddtype==3)
                           {
                               if(JudgeAddrIsTheSame(whichdialog,sLAddr)==false)
                               {
                                   (m_set->m_add->m_table)->setRowCount((m_set->m_add->m_table)->rowCount()+1);
                                   (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),0,new QTableWidgetItem(trUtf8("调光")));
                                   (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),1,new QTableWidgetItem(str));
                                   (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),2,new QTableWidgetItem(sLAddr));
                                   (m_set->m_add->m_table)->setRowHeight(((m_set->m_add->m_table)->rowCount()-1),50);
                               }
                               m_set->m_add->label1->setText(trUtf8("调光确认添加"));

                           }
                           else if(JudgeIsAddTable(sLAddr)==true)
                           {
                               ui->label->setText(trUtf8("调光确认添加"));
                           }
                           else
                           {
                               ui->label->setText(trUtf8("未添加此节点"));
                           }


                       }
                       if(cData[7]==0xBB&&cData[8]==0xBB&&cData[9]==0xBB)
                       {
                           if(whichdialog==1&&iaddtype==3)
                           {
                               if(JudgeAddrIsTheSame(whichdialog,sLAddr)==false)
                               {

                                   (m_set->m_add->m_table)->setRowCount((m_set->m_add->m_table)->rowCount()+1);
                                   (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),0,new QTableWidgetItem(trUtf8("调光")));
                                   (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),1,new QTableWidgetItem(str));
                                   (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),2,new QTableWidgetItem(sLAddr));
                                   (m_set->m_add->m_table)->setRowHeight(((m_set->m_add->m_table)->rowCount()-1),50);
                               }
                               m_set->m_add->label1->setText(trUtf8("调光确认控制接收"));
                           }
                           else if(JudgeIsAddTable(sLAddr)==true)
                           {
                               ui->label->setText(trUtf8("调光确认控制接收"));

                           }
                           else
                           {
                               ui->label->setText(trUtf8("未添加此节点"));
                           }
                       }
                       break;
                      }
                      case 'P'://红外遥控  K
                      {

                       if(cData[7]==0xAA&&cData[8]==0xAA&&cData[9]==0xAA)
                       {

                           if(whichdialog==2&&iaddtype==4)
                           {
                               if(JudgeAddrIsTheSame(whichdialog,sLAddr)==false)
                               {
                                   (m_set->m_add->m_irdev->m_table)->setRowCount((m_set->m_add->m_irdev->m_table)->rowCount()+1);
                                   (m_set->m_add->m_irdev->m_table)->setItem(((m_set->m_add->m_irdev->m_table)->rowCount()-1),0,new QTableWidgetItem(trUtf8("红外")));
                                   (m_set->m_add->m_irdev->m_table)->setItem(((m_set->m_add->m_irdev->m_table)->rowCount()-1),1,new QTableWidgetItem(str));
                                   (m_set->m_add->m_irdev->m_table)->setItem(((m_set->m_add->m_irdev->m_table)->rowCount()-1),2,new QTableWidgetItem(sLAddr));
                                   (m_set->m_add->m_irdev->m_table)->setRowHeight(((m_set->m_add->m_irdev->m_table)->rowCount()-1),50);



                               }
                               m_set->m_add->m_irdev->label1->setText(trUtf8("红外确认添加"));
                           }
                           else if(JudgeIsAddTable(sLAddr)==true)
                           {
                               ui->label->setText(trUtf8("红外确认添加"));
                           }
                           else
                           {
                               ui->label->setText(trUtf8("您未添加此设备"));
                           }

                        }
                        if(cData[7]==0xBB&&cData[8]==0xBB&&cData[9]==0xBB)
                        {

                           if(whichdialog==2&&iaddtype==4)
                           {
                               if(JudgeAddrIsTheSame(whichdialog,sLAddr)==false)
                               {
                                   (m_set->m_add->m_irdev->m_table)->setRowCount((m_set->m_add->m_irdev->m_table)->rowCount()+1);
                                   (m_set->m_add->m_irdev->m_table)->setItem(((m_set->m_add->m_irdev->m_table)->rowCount()-1),0,new QTableWidgetItem(trUtf8("红外")));
                                   (m_set->m_add->m_irdev->m_table)->setItem(((m_set->m_add->m_irdev->m_table)->rowCount()-1),1,new QTableWidgetItem(str));
                                   (m_set->m_add->m_irdev->m_table)->setItem(((m_set->m_add->m_irdev->m_table)->rowCount()-1),2,new QTableWidgetItem(sLAddr));
                                   (m_set->m_add->m_irdev->m_table)->setRowHeight(((m_set->m_add->m_irdev->m_table)->rowCount()-1),50);

                              }
                               m_set->m_add->m_irdev->label1->setText(trUtf8("红外确认控制接收"));

                           }
                           else if(JudgeIsAddTable(sLAddr)==true)
                           {
                               ui->label->setText(trUtf8("红外确认控制接收"));

                           }
                           else
                           {
                               ui->label->setText(trUtf8("您未添加此设备"));
                           }
                         }
                         break;
                      }
                      case 'H'://窗帘     K
                      {
                         if(cData[7]==0xAA&&cData[8]==0xAA&&cData[9]==0xAA)
                         {
                              if(whichdialog==1&&iaddtype==2)
                              {
                                 if(JudgeAddrIsTheSame(whichdialog,sLAddr)==false)
                                 {
                                   (m_set->m_add->m_table)->setRowCount((m_set->m_add->m_table)->rowCount()+1);
                                   (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),0,new QTableWidgetItem(trUtf8("窗帘")));
                                   (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),1,new QTableWidgetItem(str));
                                   (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),2,new QTableWidgetItem(sLAddr));
                                   (m_set->m_add->m_table)->setRowHeight(((m_set->m_add->m_table)->rowCount()-1),50);

                                 }
                                 m_set->m_add->label1->setText(trUtf8("窗帘确认添加"));
                              }
                              else if(JudgeIsAddTable(sLAddr)==true)
                              {
                                   ui->label->setText(trUtf8("窗帘确认添加"));
                              }
                              else
                              {
                                   ui->label->setText(trUtf8("您未添加此设备"));
                              }
                         }
                         if(cData[7]==0xBB&&cData[8]==0xBB&&cData[9]==0xBB)
                         {
                             if(whichdialog==1&&iaddtype==2)
                             {
                                if(JudgeAddrIsTheSame(whichdialog,sLAddr)==false)
                                {
                                  (m_set->m_add->m_table)->setRowCount((m_set->m_add->m_table)->rowCount()+1);
                                    (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),0,new QTableWidgetItem(trUtf8("窗帘")));
                                    (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),1,new QTableWidgetItem(str));
                                    (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),2,new QTableWidgetItem(sLAddr));
                                    (m_set->m_add->m_table)->setRowHeight(((m_set->m_add->m_table)->rowCount()-1),50);
                                }
                                 m_set->m_add->label1->setText(trUtf8("窗帘确认添加接收"));

                             }
                             else if(JudgeIsAddTable(sLAddr)==true)
                             {
                                  ui->label->setText(trUtf8("窗帘确认接收"));


                             }
                             else
                             {
                                  ui->label->setText(trUtf8("您未添加此设备"));
                             }
                          }
                          break;
                      }
                      case 'K'://强电   K
                      {

                         if(cData[7]==0xAA&&cData[8]==0xAA&&cData[9]==0xAA)
                         {

                            if(whichdialog==1&&iaddtype==1)
                            {
                                if(JudgeAddrIsTheSame(whichdialog,sLAddr)==false)
                                {
                                  (m_set->m_add->m_table)->setRowCount((m_set->m_add->m_table)->rowCount()+1);
                                  (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),0,new QTableWidgetItem(trUtf8("开关")));
                                  (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),1,new QTableWidgetItem(str));
                                  (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),2,new QTableWidgetItem(sLAddr));
                                  (m_set->m_add->m_table)->setRowHeight(((m_set->m_add->m_table)->rowCount()-1),50);

                                }
                                m_set->m_add->label1->setText(trUtf8("确认添加"));
                             }
                             else if(JudgeIsAddTable(sLAddr)==true)
                             {
                                   ui->label->setText(trUtf8("确认添加"));
                             }
                             else
                             {
                                   ui->label->setText(trUtf8("您未添加此设备"));
                             }
                          }
                          if(cData[7]==0xBB&&cData[8]==0xBB&&cData[9]==0xBB)
                          {
                              if(whichdialog==1&&iaddtype==1)
                              {
                                  m_set->m_add->label1->setText(trUtf8("继电器确认控制接收"));
                              }
                              else if(JudgeIsAddTable(sLAddr)==true)
                              {
                                  ui->label->setText(trUtf8("继电器确认控制接收"));
                              }
                              else
                              {
                                  ui->label->setText(trUtf8("您未添加此设备"));
                              }
                          }
                         break;
                      }
                      case 'I'://遥控按键    J
                      {
                        JDSecond[7]=0;
                        JDFlag[7]=true;
                         if(whichdialog==1&&iaddtype==6)
                         {
                             if(JudgeAddrIsTheSame(whichdialog,sLAddr)==false)
                             {
                               (m_set->m_add->m_table)->setRowCount((m_set->m_add->m_table)->rowCount()+1);
                               (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),0,new QTableWidgetItem(trUtf8("按键")));
                               (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),1,new QTableWidgetItem(str));
                               (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),2,new QTableWidgetItem(sLAddr));
                               (m_set->m_add->m_table)->setRowHeight(((m_set->m_add->m_table)->rowCount()-1),50);

                             }
                         }

                         if(JudgeIsAddTable(sLAddr)==true)
                         {
                            changeData4=true;
                             if(whichdialog==9)
                             {
                                  (m_set->m_connectset->m_key->m_text)->setText(CharToStr(4,cData[/*ilength+*/7],0x00));
                             }
                             DeleteSensorDataTableToNull();
                             ui->label->setText(trUtf8("当前按键值:")+CharToStr(4,cData[7],0x00));
                             QString s1=CharToStr(2,cData[4],cData[5]);
                             anjianNow=trUtf8("当前按键值:")+CharToStr(4,cData[7],0x00);
                             AddSensorDataTable(trUtf8("按键"),s1,sLAddr,RetDirByMacAddr(sLAddr),CharToStr(4,cData[/*ilength+*/7],0x00),"NULL");
                             if(JudgeLianDongTheSameAddr(5,sLAddr)==true)
                             {
                                 TrueControl(6,str,sLAddr,CharToStr(4,cData[7],0x00));
                             }
                         }
                          else
                          {
                               ui->label->setText(trUtf8("您未添加此设备"));
                          }

                         break;
                      }
                      case 0x03://315   J
                      {
                       if(whichdialog==3&&iaddtype==5)
                       {
                           if(JudgeAddrIsTheSame(whichdialog,sLAddr)==false)
                           {
                               (m_set->m_add->m_threefive->m_table)->setRowCount((m_set->m_add->m_threefive->m_table)->rowCount()+1);
                               (m_set->m_add->m_threefive->m_table)->setItem(((m_set->m_add->m_threefive->m_table)->rowCount()-1),0,new QTableWidgetItem(trUtf8("315")));
                               (m_set->m_add->m_threefive->m_table)->setItem(((m_set->m_add->m_threefive->m_table)->rowCount()-1),1,new QTableWidgetItem(str));
                               (m_set->m_add->m_threefive->m_table)->setItem(((m_set->m_add->m_threefive->m_table)->rowCount()-1),2,new QTableWidgetItem(sLAddr));
                               (m_set->m_add->m_threefive->m_table)->setRowHeight(((m_set->m_add->m_threefive->m_table)->rowCount()-1),50);
                           }
                           (m_set->m_add->m_threefive->m_text)->setText(CharToStr(1,cData[/*ilength+*/7],0x00));
                       }
                       else
                       {
                           if(JudgeIsAddTable(sLAddr)==true)
                           {
                               changeData1=true;
                               changeData4=true;
                               DeleteSensorDataTableToNull();
                               QString s1="";bool bisadd=false;
                               s1=CharToStr(1,cData[7],0x00);
                               for(int i=0;i<ithreefivestructlength;i++)
                               {
                                   if(QString::compare(s1,m_threefivestruct[i].code)==0)
                                   {
                                       ui->label->setText(m_threefivestruct[i].dir+m_threefivestruct[i].name+trUtf8("有警情"));
                                       threefiveNow=m_threefivestruct[i].name+trUtf8("有警情");
                                       AddSensorDataTable(m_threefivestruct[i].name,m_threefivestruct[i].shortaddr,m_threefivestruct[i].longaddr,m_threefivestruct[i].dir,QString::number(1),"NULL");
                                       bisadd=true;
                                       if(m_threefivestruct[i].name.contains(trUtf8("烟雾"))==true)
                                       {
//                                           QString ret="";QString ret1="";
//                                           ret=FindMacAddrByNameNoDir(trUtf8("语音播报"),trUtf8("门锁"));
//                                           if(ret!="NULL")
//                                           {
//                                                ret1=FindShortAddrByNameNoDir(trUtf8("语音播报"),trUtf8("门锁"));
//                                                if(ret1!="NULL")
//                                                {
//                                                       Send_Sound(ret1,ret,0x01);
//                                                }
//                                           }
                                           if(JudgeLianDongTheSameAddr(3,m_threefivestruct[i].longaddr)==true)
                                           {
                                               TrueControl(3,m_threefivestruct[i].shortaddr,m_threefivestruct[i].longaddr,m_threefivestruct[i].code);
                                           }
                                           //==================================================
                                           ithreadsendtype=3;
                                           sthreadlongaddr=sLAddr;
                                           //SendDataToServerByUdpWenDu(RetDirByMacAddr(sLAddr),0x21);
                                           break;
                                       }
                                       if(m_threefivestruct[i].name.contains(trUtf8("气体"))==true)
                                       {

                                           if(JudgeLianDongTheSameAddr(2,m_threefivestruct[i].longaddr)==true)
                                           {
                                               TrueControl(2,m_threefivestruct[i].shortaddr,m_threefivestruct[i].longaddr,m_threefivestruct[i].code);
                                           }
                                           //==================================================
                                           ithreadsendtype=4;
                                           sthreadlongaddr=sLAddr;
                                           //SendDataToServerByUdpWenDu(RetDirByMacAddr(sLAddr),0x09);
                                           break;
                                       }
                                       if(m_threefivestruct[i].name.contains(trUtf8("人体"))==true)
                                       {
                                           //==================================================
                                           ithreadsendtype=5;
                                           sthreadlongaddr=sLAddr;
                                           //SendDataToServerByUdpWenDu(RetDirByMacAddr(sLAddr),0x14);
                                           break;
                                       }
                                       if(m_threefivestruct[i].name.contains(trUtf8("门磁"))==true)
                                       {
                                           //==================================================
                                           ithreadsendtype=6;
                                           sthreadlongaddr=sLAddr;
                                          // SendDataToServerByUdpWenDu(RetDirByMacAddr(sLAddr),0x43);
                                           break;
                                       }

                                   }
                               }
                               if(bisadd==false)
                               {
                                   ui->label->setText(trUtf8("未添加该节点码"));
                               }
                           }
                           else
                           {
                               ui->label->setText(trUtf8("您未添加此设备"));
                           }
                       }
                      break;
                      }
                      case 0x04://震动   J
                      {
                       if(whichdialog==1&&iaddtype==6)
                       {
                           if(JudgeAddrIsTheSame(whichdialog,sLAddr)==false)
                           {
                               (m_set->m_add->m_table)->setRowCount((m_set->m_add->m_table)->rowCount()+1);
                               (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),0,new QTableWidgetItem(trUtf8("震动")));
                               (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),1,new QTableWidgetItem(str));
                               (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),2,new QTableWidgetItem(sLAddr));
                               (m_set->m_add->m_table)->setRowHeight(((m_set->m_add->m_table)->rowCount()-1),50);

                           }
                       }
                       else
                       {
                           if(JudgeIsAddTable(sLAddr)==true)
                           {
                               changeData4=true;
                               switch(cData[/*ilength+*/7])
                               {
                                   case 0x00://y
                                   {
                                      DeleteSensorDataTableToNull();
                                      ui->label->setText(trUtf8("震动正常状态"));
                                      zhendongNow=trUtf8("震动正常状态");
                                      QString s1=CharToStr(2,cData[4],cData[5]);
                                      AddSensorDataTable(trUtf8("震动"),s1,sLAddr,RetDirByMacAddr(sLAddr),CharToStr(4,cData[/*ilength+*/7],0x00),"NULL");
                                      break;
                                   }
                                   case 0x01://y
                                   {
                                      DeleteSensorDataTableToNull();
                                      ui->label->setText(trUtf8("有震动，有动静"));
                                      zhendongNow=trUtf8("有震动，有动静");
                                      QString s1=CharToStr(2,cData[4],cData[5]);
                                      AddSensorDataTable(trUtf8("震动"),s1,sLAddr,RetDirByMacAddr(sLAddr),CharToStr(4,cData[/*ilength+*/7],0x00),"NULL");
                                      break;
                                   }
                               }
                           }
                           else
                           {
                               ui->label->setText(trUtf8("您未添加此设备"));
                           }
                       }
                         break;
                      }
                      case 0x05://雨蓬   K
                      {
                        if(cData[7]==0xAA&&cData[8]==0xAA&&cData[9]==0xAA)
                        {
                            if(whichdialog==1&&iaddtype==7)
                            {
                               if(JudgeAddrIsTheSame(whichdialog,sLAddr)==false)
                               {
                                   (m_set->m_add->m_table)->setRowCount((m_set->m_add->m_table)->rowCount()+1);
                                   (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),0,new QTableWidgetItem(trUtf8("雨蓬")));
                                   (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),1,new QTableWidgetItem(str));
                                   (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),2,new QTableWidgetItem(sLAddr));
                                   (m_set->m_add->m_table)->setRowHeight(((m_set->m_add->m_table)->rowCount()-1),50);

                               }
                               else
                               {
                                   m_set->m_add->label1->setText(trUtf8("雨蓬已添加"));
                               }
                            }
                            else if(JudgeIsAddTable(sLAddr)==true)
                            {
                               ui->label->setText(trUtf8("雨蓬确认添加"));
                            }
                            else
                            {
                               ui->label->setText(trUtf8("雨蓬未添加"));
                            }
                        }
                        if(cData[7]==0xBB&&cData[8]==0xBB&&cData[9]==0xBB)
                        {
                            if(whichdialog==1&&iaddtype==7)
                            {
                                 m_set->m_add->label1->setText(trUtf8("雨蓬确认控制接收"));
                            }
                            else if(JudgeIsAddTable(sLAddr)==true)
                            {
                                ui->label->setText(trUtf8("雨蓬确认控制接收"));
                            }
                            else
                            {
                                ui->label->setText(trUtf8("您未添加此设备"));
                            }
                        }
                         break;
                      }
                      case 0x06://car   K
                      {
                       if(cData[7]==0xAA&&cData[8]==0xAA&&cData[9]==0xAA)
                       {
                           if(whichdialog==1&&iaddtype==6)
                           {
                               if(JudgeAddrIsTheSame(whichdialog,sLAddr)==false)
                               {
                                   (m_set->m_add->m_table)->setRowCount((m_set->m_add->m_table)->rowCount()+1);
                                   (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),0,new QTableWidgetItem(trUtf8("小车")));
                                   (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),1,new QTableWidgetItem(str));
                                   (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),2,new QTableWidgetItem(sLAddr));
                                   (m_set->m_add->m_table)->setRowHeight(((m_set->m_add->m_table)->rowCount()-1),50);
                               }
                               else
                               {
                                    m_set->m_add->label1->setText(trUtf8("小车已添加"));
                               }
                           }
                           else if(JudgeIsAddTable(sLAddr)==true)
                           {
                               if(whichdialog==-1)
                               {
                                 ui->label->setText(trUtf8("小车确认添加"));
                               }
                           }
                           else
                           {
                               if(whichdialog==-1)
                               {
                                 ui->label->setText(trUtf8("小车未添加"));
                               }
                           }
                       }

                       if(cData[8]!=0xBB&&cData[7]==0xBB&&cData[9]==0xBB)
                       {
                           //==================================================
                           ithreadsendtype=16;
                           sthreadlongaddr=sLAddr;
                           CarTempVal=cData[8];
                          //SendDataToServeByCar(RetDirByMacAddr(CarRFIDMacAddr),sLAddr,cData[8]);
                       }
                       else
                       {
                           if(cData[7]==0xBB&&cData[8]==0xBB&&cData[9]==0xBB)
                          {
                              if(whichdialog==1&&iaddtype==6)
                              {
                                 m_set->m_add->label1->setText(trUtf8("小车确认控制"));
                              }
                              else if(JudgeIsAddTable(sLAddr)==true)
                              {
                                 if(whichdialog==-1)
                                 {
                                    ui->label->setText(trUtf8("小车确认控制接收"));
                                 }
                              }
                              else
                              {
                                 if(whichdialog==-1)
                                 {
                                     ui->label->setText(trUtf8("您未添加此设备"));
                                 }
                              }
                            }
                       }


                         break;
                      }
                      case 0x07://未来超市超高频   J
                      {
                       if(whichdialog==1&&iaddtype==6)
                       {
                           if(JudgeAddrIsTheSame(whichdialog,sLAddr)==false)
                           {
                               (m_set->m_add->m_table)->setRowCount((m_set->m_add->m_table)->rowCount()+1);
                               (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),0,new QTableWidgetItem(trUtf8("超高频")));
                               (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),1,new QTableWidgetItem(str));
                               (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),2,new QTableWidgetItem(sLAddr));
                               (m_set->m_add->m_table)->setRowHeight(((m_set->m_add->m_table)->rowCount()-1),50);

                           }
                       }
                       else
                       {
                           if(JudgeIsAddTable(sLAddr)==true)
                           {
                               changeData4=true;
                               if(cData[7]==0x01)
                               {
                                    QString s1="";QString s2="";
                                    memset(rfidoval,0,8);
                                    int gval=0;
                                   for(int rval=8;rval<16;rval++)
                                   {
                                      s1=CharToStr(1,cData[rval],0x00);
                                      s2=s2+s1;
                                      rfidoval[gval]=cData[rval];
                                      gval++;
                                   }
                                   ui->label->setText(trUtf8("超高频: ")+s2);
                                   chaogaopinNow=s2;
                                   //SendRFIDServer(3,cData[4],cData[5]);
                                   //==================================================
                                   ithreadsendtype=7;
                                   sthreadlongaddr=sLAddr;
                               //    SendRFIDServer(3,sLAddr);
                                   if(RetDirByMacAddr(sLAddr).contains(trUtf8("大棚"))==true)
                                   {
                                       YanShi_DianJi_ZhengZhuan(FindShortAddrByName(trUtf8("演示板")),FindLongAddrByName(trUtf8("演示板")));
                                   }
                               }
                           }
                           else
                           {
                             ui->label->setText(trUtf8("您未添加此设备"));
                           }
                       }
                          break;
                      }
                      case 0x08://gaopin   J
                      {
                       JDSecond[17]=0;
                       JDFlag[17]=true;
                       if(whichdialog==1&&iaddtype==6)
                       {
                           if(JudgeAddrIsTheSame(whichdialog,sLAddr)==false)
                           {
                               (m_set->m_add->m_table)->setRowCount((m_set->m_add->m_table)->rowCount()+1);
                               (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),0,new QTableWidgetItem(trUtf8("高频")));
                               (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),1,new QTableWidgetItem(str));
                               (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),2,new QTableWidgetItem(sLAddr));
                               (m_set->m_add->m_table)->setRowHeight(((m_set->m_add->m_table)->rowCount()-1),50);

                           }
                       }
                       else
                       {
                           if(JudgeIsAddTable(sLAddr)==true)
                           {
                               changeData4=true;
                               if(whichdialog==13)
                               {
                                   switch(cData[7])
                                   {
                                      case 0xA1://15693
                                      {
                                           QString s1="";QString s2="";
                                           for(int rval=8;rval<24;rval++)
                                           {
                                               s1=CharToStr(5,cData[rval],0x00);
                                               s2=s2+s1;
                                           }
                                           if(whichdialog==13)
                                                m_control->m_smartshelf->m_inshelf->m_text->setText(s2);
                                         break;
                                      }
                                      default:
                                      {
                                         break;
                                      }
                                   }
                               }
                               else
                               {
                                   QString s1="";QString s2="";
                                   memset(gaopinval,0,16);
                                   int gval=0;
                                   switch(cData[7])
                                   {
                                      case 0xA1://15693
                                      {
                                         for(int rval=8;rval<24;rval++)
                                         {
                                             s1=CharToStr(5,cData[rval],0x00);
                                             s2=s2+s1;
                                             gaopinval[gval]=cData[rval];
                                             gval++;
                                         }
                                         ui->label->setText(trUtf8("高频-15693: ")+s2);
                                         gaopinNow=s2;
                                         if(shelfInteface==true)
                                         {
                                             GaopinFlag=true;
                                         }
                                         CarRFIDMacAddr=sLAddr;

                                        // SendRFIDServer(1,cData[4],cData[5]);
                                         //==================================================

                                        // SendRFIDServer(1,sLAddr);
                                         if(RetDirByMacAddr(sLAddr)==trUtf8("大棚生产"))
                                         {
                                             ithreadsendtype=11;
                                             sthreadlongaddr=sLAddr;
                                         }
                                         else
                                         {
                                             ithreadsendtype=8;
                                             sthreadlongaddr=sLAddr;
                                         }
                                         if(RetDirByMacAddr(sLAddr)==trUtf8("大棚"))
                                         {
                                           if((FindShortAddrWhile(trUtf8("演示板"),trUtf8("大棚"))!="NULL")&&(FindLongAddrWhile(trUtf8("演示板"),trUtf8("大棚"))!="NULL"))
                                           {
                                             // YanShi_DianJi_ZhengZhuan(FindShortAddrWhile(trUtf8("演示板"),trUtf8("大棚")),FindLongAddrWhile(trUtf8("演示板"),trUtf8("大棚")));
                                              bistimerfunopen=true;
                                              itimerfuntype=1;
//                                              m_TimerFun->start(1300);
                                           }
                                         }
                                         if(RetDirByMacAddr(sLAddr)==trUtf8("加工厂"))
                                         {
                                             if((FindShortAddrWhile(trUtf8("演示板"),trUtf8("加工厂"))!="NULL")&&(FindLongAddrWhile(trUtf8("演示板"),trUtf8("加工厂"))!="NULL"))
                                             {
                                                 //YanShi_DianJi_ZhengZhuan(FindShortAddrWhile(trUtf8("演示板"),trUtf8("加工厂")),FindLongAddrWhile(trUtf8("演示板"),trUtf8("加工厂")));
                                                 bistimerfunopen=true;
                                                 itimerfuntype=2;
//                                                 m_TimerFun->start(1300);
                                             }
                                         }
                                         if(RetDirByMacAddr(sLAddr)==trUtf8("仓储")&&telnumber!="NULL"&&maccaraddr!="NULL")
                                         {

                                           // SendWenDuOrderToCar(telnumber,maccaraddr);
                                            bistimerfunopen=true;
                                            itimerfuntype=3;
//                                            m_TimerFun->start(1300);
                                         }
                                         break;
                                      }
                                      case 0xA2://14443A
                                      {
                                        s1="";s2="";
                                        memset(rfidoval,0,8);
                                        int gval=0;
                                        for(int rval=8;rval<16;rval++)
                                        {
                                            s1=CharToStr(5,cData[rval],0x00);
                                            s2=s2+s1;
                                            rfidoval[gval]=cData[rval];
                                            gval++;
                                        }
                                        ui->label->setText(trUtf8("高频-14443A: ")+s2);
                                        //==================================================
                                        ithreadsendtype=9;
                                        sthreadlongaddr=sLAddr;
                                       // SendRFIDServer(2,sLAddr);
                                         break;
                                      }
                                      default:
                                      {
                                        break;
                                      }
                                    }
                               }
                             }
                             else
                             {
                                ui->label->setText(trUtf8("您未添加此设备"));
                             }

                       }

                          break;
                      }




                   case 0x0B://低频   J
                   {
//                    JDSecond[18]=0;
//                    JDFlag[18]=true;
                    if(whichdialog==1&&iaddtype==6)
                    {
                        if(JudgeAddrIsTheSame(whichdialog,sLAddr)==false)
                        {
                            (m_set->m_add->m_table)->setRowCount((m_set->m_add->m_table)->rowCount()+1);
                            (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),0,new QTableWidgetItem(trUtf8("低频")));
                            (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),1,new QTableWidgetItem(str));
                            (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),2,new QTableWidgetItem(sLAddr));
                            (m_set->m_add->m_table)->setRowHeight(((m_set->m_add->m_table)->rowCount()-1),50);

                        }
                    }
                    else
                    {
                        if(JudgeIsAddTable(sLAddr)==true)
                        {
                            changeData4=true;
                            QString s1="";QString s2="";
                            memset(dipinval,0,17);
                            int dval=0;
                            if(cData[7]==0x01)
                            {
                                    for(int rval=8;rval<25;rval++)
                                    {
                                          s1=CharToStr(5,cData[rval],0x00);
                                          s2=s2+s1;
                                          dipinval[dval]=cData[rval];
                                          dval++;
                                    }
                                    ui->label->setText(trUtf8("125K低频卡: ")+s2);
                                    dipinNow=s2;
                                    if(shelfInteface==true)
                                    {
                                          GaopinFlag=true;
                                    }
                                   CarRFIDMacAddr=sLAddr;

                               }
                          }
                          else
                          {
                             ui->label->setText(trUtf8("您未添加此设备"));
                          }

                    }
                       break;
                   }

                      case 0x09://演示板   K
                      {
                       JDSecond[9]=0;
                       JDFlag[9]=true;
                           if(cData[7]==0xAA&&cData[8]==0xAA&&cData[9]==0xAA)
                           {
                              if(whichdialog==1&&iaddtype==6)
                              {
                                  if(JudgeAddrIsTheSame(whichdialog,sLAddr)==false)
                                  {
                                    (m_set->m_add->m_table)->setRowCount((m_set->m_add->m_table)->rowCount()+1);
                                    (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),0,new QTableWidgetItem(trUtf8("演示板")));
                                    (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),1,new QTableWidgetItem(str));
                                    (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),2,new QTableWidgetItem(sLAddr));
                                    (m_set->m_add->m_table)->setRowHeight(((m_set->m_add->m_table)->rowCount()-1),50);
                                  }
                                  m_set->m_add->label1->setText(trUtf8("演示板确认添加"));
                               }
                               else if(JudgeIsAddTable(sLAddr)==true)
                               {
                                     ui->label->setText(trUtf8("演示板确认添加"));
                               }
                               else
                               {
                                     ui->label->setText(trUtf8("您未添加此设备"));
                               }
                            }
                            if(cData[7]==0xBB&&cData[8]==0xBB&&cData[9]==0xBB)
                            {
//                                stryanshibanaddr=str;
//                                stryanshibanmacaddr=sLAddr;
                                if(whichdialog==1&&iaddtype==6)
                                {
                                    m_set->m_add->label1->setText(trUtf8("演示板确认控制接收"));
                                }
                                else if(JudgeIsAddTable(sLAddr)==true)
                                {
                                    ui->label->setText(trUtf8("演示板确认控制接收"));
                                }
                                else
                                {
                                    ui->label->setText(trUtf8("您未添加此设备"));
                                }
                            }
                           break;

                      }
                      case 0x20://噪声    J
                      {
                       if(whichdialog==1&&iaddtype==6)
                       {
                           if(JudgeAddrIsTheSame(whichdialog,sLAddr)==false)
                           {
                               (m_set->m_add->m_table)->setRowCount((m_set->m_add->m_table)->rowCount()+1);
                               (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),0,new QTableWidgetItem(trUtf8("噪声")));
                               (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),1,new QTableWidgetItem(str));
                               (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),2,new QTableWidgetItem(sLAddr));
                               (m_set->m_add->m_table)->setRowHeight(((m_set->m_add->m_table)->rowCount()-1),50);
                           }
                       }
                       else
                       {
                           if(JudgeIsAddTable(sLAddr)==true)
                           {
                               changeData4=true;
                               DeleteSensorDataTableToNull();
                               ui->label->setText(trUtf8("当前噪声指数:")+CharToStr(3,cData[8],cData[9]));
                               zaoshengNow=CharToStr(3,cData[8],cData[9]);
                               AddSensorDataTable(trUtf8("噪声"),str,sLAddr,RetDirByMacAddr(sLAddr),CharToStr(4,cData[8],0x00),CharToStr(4,cData[/*ilength+*/9],0x00));
                           }
                           else
                           {
                             ui->label->setText(trUtf8("您未添加此设备"));
                           }
                       }
                         break;
                      }
                      case 0x21://光线    J
                      {
                         if(whichdialog==1&&iaddtype==6)
                         {
                             if(JudgeAddrIsTheSame(whichdialog,sLAddr)==false)
                             {
                               (m_set->m_add->m_table)->setRowCount((m_set->m_add->m_table)->rowCount()+1);
                               (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),0,new QTableWidgetItem(trUtf8("光线")));
                               (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),1,new QTableWidgetItem(str));
                               (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),2,new QTableWidgetItem(sLAddr));
                               (m_set->m_add->m_table)->setRowHeight(((m_set->m_add->m_table)->rowCount()-1),50);
                             }
                         }
                         else
                         {
                             if(JudgeIsAddTable(sLAddr)==true)
                             {
                                 changeData4=true;
                                  QString s2=CharToStr(4,cData[7],0x00);
                                  ui->label->setText(trUtf8("当前光线值:")+s2);
                                 for(int i=0;i<isensorlength;i++)
                                 {
                                     if(trUtf8("光线")==m_sensorstruct[i].name && QString::compare(sLAddr,m_sensorstruct[i].longaddr)==0&&trUtf8("智能家居")==m_sensorstruct[i].dir)
                                     {
                                         JDSecond[3]=0;
                                         JDFlag[3]=true;
                                         guangxianNow=s2;
                                         changeData1=true;
                                         break;
                                     }
                                     if(trUtf8("光线")==m_sensorstruct[i].name && QString::compare(sLAddr,m_sensorstruct[i].longaddr)==0&&trUtf8("智慧农业")==m_sensorstruct[i].dir)
                                     {
                                         JDSecond[10]=0;
                                         JDFlag[10]=true;
                                         guangxianNow=s2;
                                         changeData3=true;
                                         break;
                                     }
                                 }

                                  DeleteSensorDataTableToNull();

                                  AddSensorDataTable(trUtf8("光线"),str,sLAddr,RetDirByMacAddr(sLAddr),s2,"NULL");

                                  if(JudgeLianDongTheSameAddr(1,sLAddr)==true)//shifou control
                                  {
                                      TrueControl(1,str,sLAddr,s2);
                                  }
                                  //========================================================================================
                                  ithreadsendtype=10;
                                  sthreadlongaddr=sLAddr;
                               //   SendDataToServerByUdpWenDu(RetDirByMacAddr(sLAddr),0x20);

                             }
                              else
                              {
                                 ui->label->setText(trUtf8("您未添加此设备"));
                              }
                         }
                         break;
                      }
                      case 0x0A: //货架    J
                      {
                       JDSecond[16]=0;
                       JDFlag[16]=true;
                           if(whichdialog==1&&iaddtype==6)
                           {
                               if(JudgeAddrIsTheSame(whichdialog,sLAddr)==false)
                               {
                                   (m_set->m_add->m_table)->setRowCount((m_set->m_add->m_table)->rowCount()+1);
                                   (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),0,new QTableWidgetItem(trUtf8("货架")));
                                   (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),1,new QTableWidgetItem(str));
                                   (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),2,new QTableWidgetItem(sLAddr));
                                   (m_set->m_add->m_table)->setRowHeight(((m_set->m_add->m_table)->rowCount()-1),50);
                               }
                           }
                           else
                           {
                               if(JudgeIsAddTable(sLAddr)==true)
                               {
                                   if(whichdialog==12||shelfInteface==true)
                                   {
                                       QString s1="";QString s2="";QString s3="";
                                       for(int ival=8;ival<26;ival++)
                                       {
                                           s1=CharToStr(5,cData[ival],0x00);
                                           s2=s2+s1;
                                       }
                                       qDebug()<<s2;
                                       s1=s2.mid(2);//卡号
                                       qDebug()<<s1;
                                       s3=s2.mid(0,2);
                                       qDebug()<<s3;
                                       if(s3=="FF")//没卡
                                       {
                                           QString s4="";
                                           s4=s2.mid(2,2);
                                           qDebug()<<s4;
                                           if(s4=="01")
                                           {
                                               if(shelfInteface)
                                               {
                                                   ShelfData[0]="";
                                                   ShelfData[1]="";
                                                   GaopinFlag=true;
                                               }
                                               if(whichdialog==12)
                                               {
                                                    m_control->m_smartshelf->m_gbox1->setTitle(trUtf8("1号货架：空"));//原版
                                                    m_control->m_smartshelf->m_label2->setText("");
                                                    m_control->m_smartshelf->m_label1->setPixmap(QPixmap(":/images/16.png"));
                                                }
                                           }
                                           if(s4=="02")
                                           {
                                               if(shelfInteface)
                                               {
                                                   ShelfData[2]="";
                                                   ShelfData[3]="";
                                                   GaopinFlag=true;
                                               }
                                               if(whichdialog==12)
                                               {
                                                    m_control->m_smartshelf->m_gbox2->setTitle(trUtf8("2号货架：空"));
                                                    m_control->m_smartshelf->m_label4->setText("");
                                                    m_control->m_smartshelf->m_label3->setPixmap(QPixmap(":/images/16.png"));
                                                }
                                           }
                                           if(s4=="03")
                                           {
                                               if(shelfInteface)
                                               {
                                                   ShelfData[4]="";
                                                   ShelfData[5]="";
                                                   GaopinFlag=true;
                                               }
                                               if(whichdialog==12)
                                               {
                                                    m_control->m_smartshelf->m_gbox3->setTitle(trUtf8("3号货架：空"));//原版
                                                    m_control->m_smartshelf->m_label6->setText("");
                                                    m_control->m_smartshelf->m_label5->setPixmap(QPixmap(":/images/16.png"));
                                                }
                                           }
                                           if(s4=="04")
                                           {
                                               if(shelfInteface)
                                               {
                                                   ShelfData[6]="";
                                                   ShelfData[7]="";
                                                   GaopinFlag=true;
                                               }
                                               if(whichdialog==12)
                                               {
                                                    m_control->m_smartshelf->m_gbox4->setTitle(trUtf8("4号货架：空"));//原版
                                                    m_control->m_smartshelf->m_label8->setText("");
                                                    m_control->m_smartshelf->m_label7->setPixmap(QPixmap(":/images/16.png"));
                                                }
                                          }
                                           if(s4=="05")
                                           {
                                               if(shelfInteface)
                                               {
                                                   ShelfData[8]="";
                                                   ShelfData[9]="";
                                                   GaopinFlag=true;
                                               }
                                               if(whichdialog==12)
                                               {
                                                    m_control->m_smartshelf->m_gbox5->setTitle(trUtf8("5号货架：空"));
                                                    m_control->m_smartshelf->m_label10->setText("");
                                                    m_control->m_smartshelf->m_label9->setPixmap(QPixmap(":/images/16.png"));
                                                }
                                           }
                                           if(s4=="06")
                                           {
                                               if(shelfInteface)
                                               {
                                                   ShelfData[10]="";
                                                   ShelfData[11]="";
                                                   GaopinFlag=true;
                                               }
                                               if(whichdialog==12)
                                               {
                                                    m_control->m_smartshelf->m_gbox6->setTitle(trUtf8("6号货架：空"));//原版
                                                    m_control->m_smartshelf->m_label12->setText("");
                                                    m_control->m_smartshelf->m_label11->setPixmap(QPixmap(":/images/16.png"));
                                                }
                                           }
                                       }
                                       else
                                       {
                                           qDebug()<<QString::number(ishelveslength);
//                                           QMessageBox::warning(this,trUtf8("提示"),"ishelveslength="+QString::number(ishelveslength));
                                           for(int ival=0;ival<ishelveslength;ival++)
                                           {
                                               if(QString::compare(s1,m_shevlesstruct[ival].rfidnum)==0)
                                               {
                                                   if(s3=="01")
                                                   {
                                                       if(shelfInteface)
                                                       {
                                                           ShelfData[0]=m_shevlesstruct[ival].rfidnum;
                                                           ShelfData[1]=m_shevlesstruct[ival].name;
                                                           GaopinFlag=true;
//                                                           QMessageBox::warning(this,trUtf8("1号货架"),m_shevlesstruct[ival].rfidnum+m_shevlesstruct[ival].name);
                                                       }
                                                       if(whichdialog==12)
                                                       {
                                                            m_control->m_smartshelf->m_gbox1->setTitle(trUtf8("1号货架：")+m_shevlesstruct[ival].name);
                                                            m_control->m_smartshelf->m_label2->setText(trUtf8("卡：")+m_shevlesstruct[ival].rfidnum);
                                                            m_control->m_smartshelf->m_label1->setPixmap(QPixmap(":/images/15.png"));
                                                       }
                                                   }
                                                   if(s3=="02")
                                                   {
                                                       if(shelfInteface)
                                                       {
                                                           ShelfData[2]=m_shevlesstruct[ival].rfidnum;
                                                           ShelfData[3]=m_shevlesstruct[ival].name;
                                                           GaopinFlag=true;
//                                                           QMessageBox::warning(this,trUtf8("2号货架"),m_shevlesstruct[ival].rfidnum+m_shevlesstruct[ival].name);
                                                       }
                                                       if(whichdialog==12)
                                                       {
                                                            m_control->m_smartshelf->m_gbox2->setTitle(trUtf8("2号货架：")+m_shevlesstruct[ival].name);
                                                            m_control->m_smartshelf->m_label4->setText(trUtf8("卡：")+m_shevlesstruct[ival].rfidnum);
                                                            m_control->m_smartshelf->m_label3->setPixmap(QPixmap(":/images/15.png"));
                                                        }
                                                   }
                                                   if(s3=="03")
                                                   {
                                                       if(shelfInteface)
                                                       {
                                                           ShelfData[4]=m_shevlesstruct[ival].rfidnum;
                                                           ShelfData[5]=m_shevlesstruct[ival].name;
                                                           GaopinFlag=true;
                                                       }
                                                       if(whichdialog==12)
                                                       {
                                                            m_control->m_smartshelf->m_gbox3->setTitle(trUtf8("3号货架：")+m_shevlesstruct[ival].name);
                                                            m_control->m_smartshelf->m_label6->setText(trUtf8("卡：")+m_shevlesstruct[ival].rfidnum);
                                                            m_control->m_smartshelf->m_label5->setPixmap(QPixmap(":/images/15.png"));
                                                        }
                                                   }
                                                   if(s3=="04")
                                                   {
                                                       if(shelfInteface)
                                                       {
                                                           ShelfData[6]=m_shevlesstruct[ival].rfidnum;
                                                           ShelfData[7]=m_shevlesstruct[ival].name;
                                                           GaopinFlag=true;
                                                       }
                                                       if(whichdialog==12)
                                                       {
                                                            m_control->m_smartshelf->m_gbox4->setTitle(trUtf8("4号货架：")+m_shevlesstruct[ival].name);
                                                            m_control->m_smartshelf->m_label8->setText(trUtf8("卡：")+m_shevlesstruct[ival].rfidnum);
                                                            m_control->m_smartshelf->m_label7->setPixmap(QPixmap(":/images/15.png"));
                                                        }
                                                   }
                                                   if(s3=="05")
                                                   {
                                                       if(shelfInteface)
                                                       {
                                                           ShelfData[8]=m_shevlesstruct[ival].rfidnum;
                                                           ShelfData[9]=m_shevlesstruct[ival].name;
                                                           GaopinFlag=true;
                                                       }
                                                       if(whichdialog==12)
                                                       {
                                                            m_control->m_smartshelf->m_gbox5->setTitle(trUtf8("5号货架：")+m_shevlesstruct[ival].name);
                                                            m_control->m_smartshelf->m_label10->setText(trUtf8("卡：")+m_shevlesstruct[ival].rfidnum);
                                                            m_control->m_smartshelf->m_label9->setPixmap(QPixmap(":/images/15.png"));
                                                        }
                                                   }
                                                   if(s3=="06")
                                                   {
                                                       if(shelfInteface)
                                                       {
                                                           ShelfData[10]=m_shevlesstruct[ival].rfidnum;
                                                           ShelfData[11]=m_shevlesstruct[ival].name;
                                                           GaopinFlag=true;
                                                       }
                                                       if(whichdialog==12)
                                                       {
                                                            m_control->m_smartshelf->m_gbox6->setTitle(trUtf8("6号货架：")+m_shevlesstruct[ival].name);
                                                            m_control->m_smartshelf->m_label12->setText(trUtf8("卡：")+m_shevlesstruct[ival].rfidnum);
                                                            m_control->m_smartshelf->m_label11->setPixmap(QPixmap(":/images/15.png"));
                                                       }
                                                   }
                                               }
                                           }
                                       }
                                   }
                                   else
                                   {
                                       QString s1="";QString s2="";
                                       for(int ival=8;ival<26;ival++)
                                       {
                                           s1=CharToStr(5,cData[ival],0x00);
                                           s2=s2+s1;
                                       }
                                       ui->label->setText(s2);
                                   }
                               }
                               else
                               {
                                   ui->label->setText(trUtf8("您未添加此节点"));
                               }
                           }

                         break;
                      }
                      case 0x12://门锁     K
                      {
                        if(cData[7]==0xAA&&cData[8]==0xAA&&cData[9]==0xAA)
                        {
                          if(whichdialog==1&&iaddtype==8)
                          {
                              if(JudgeAddrIsTheSame(whichdialog,sLAddr)==false)
                              {
                                (m_set->m_add->m_table)->setRowCount((m_set->m_add->m_table)->rowCount()+1);
                                (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),0,new QTableWidgetItem(trUtf8("门锁")));
                                (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),1,new QTableWidgetItem(str));
                                (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),2,new QTableWidgetItem(sLAddr));
                                (m_set->m_add->m_table)->setRowHeight(((m_set->m_add->m_table)->rowCount()-1),50);

                              }
                              m_set->m_add->label1->setText(trUtf8("确认添加"));
                           }
                           else if(JudgeIsAddTable(sLAddr)==true)
                           {
                                 ui->label->setText(trUtf8("确认添加"));
                           }
                           else
                           {
                                 ui->label->setText(trUtf8("您未添加此设备"));
                           }
                        }
                        if(cData[7]==0xBB&&cData[8]==0xBB&&cData[9]==0xBB)
                        {
                            if(whichdialog==1&&iaddtype==8)
                            {
                                m_set->m_add->label1->setText(trUtf8("门锁确认控制接收"));
                            }
                            else if(JudgeIsAddTable(sLAddr)==true)
                            {
                                ui->label->setText(trUtf8("门锁确认控制接收"));
                            }
                            else
                            {
                                ui->label->setText(trUtf8("您未添加此设备"));
                            }
                        }
                          break;
                      }
                      case 0x23://指纹  J
                      {
                         if(cData[7]==0xAA&&cData[8]==0xAA&&cData[9]==0xAA)
                          {
                             if(whichdialog==18)
                             {
                                 if(JudgeAddrIsTheSame(4,sLAddr)==false)
                                 {
                                   (m_set->m_add->m_zhiwen->m_table)->setRowCount((m_set->m_add->m_zhiwen->m_table)->rowCount()+1);
                                   (m_set->m_add->m_zhiwen->m_table)->setItem(((m_set->m_add->m_zhiwen->m_table)->rowCount()-1),0,new QTableWidgetItem(trUtf8("指纹")));
                                   (m_set->m_add->m_zhiwen->m_table)->setItem(((m_set->m_add->m_zhiwen->m_table)->rowCount()-1),1,new QTableWidgetItem(str));
                                   (m_set->m_add->m_zhiwen->m_table)->setItem(((m_set->m_add->m_zhiwen->m_table)->rowCount()-1),2,new QTableWidgetItem(sLAddr));
                                   (m_set->m_add->m_zhiwen->m_table)->setRowHeight(((m_set->m_add->m_zhiwen->m_table)->rowCount()-1),50);
                                 }
                                 m_set->m_add->m_zhiwen->m_label->setText(trUtf8("确认添加"));
                             }
                             else if(JudgeIsAddTable(sLAddr)==true)
                             {
                                 ui->label->setText(trUtf8("指纹确认添加接收"));
                             }
                             else
                             {
                                 ui->label->setText(trUtf8("您未添加此设备"));
                             }

                          }
                         if(cData[7]==0xBB)
                          {
                             if(whichdialog==18)
                             {
                                m_set->m_add->m_zhiwen->m_label->setText(trUtf8("搜索到ID：")+QString::number(cData[9]));
                             }
                             else
                              {
                                ui->label->setText(trUtf8("搜索到ID：")+QString::number(cData[9]));



                                for(int ii=0;ii<ui->tableWidget->rowCount();ii++)
                                {
                                    QTableWidgetItem *item = ui->tableWidget->item(ii, 0);
                                    if(item->text().contains(trUtf8("门锁"))==true)
                                    {
                                         item = ui->tableWidget->item(ii, 2);
                                         QTableWidgetItem *item1 = ui->tableWidget->item(ii, 3);
                                         MenSuo_ON(item->text(),item1->text());
                                    }
                                }
                              }
                          }
                         if(cData[7]==0xAA&&cData[8]==0x00)
                          {
                             if(whichdialog==18)
                             {
                                  m_set->m_add->m_zhiwen->m_label->setText(trUtf8("录入成功"));
                             }
                             else
                             {
                                   ui->label->setText(trUtf8("录入成功"));
                             }
                          }
                         if(cData[7]==0xCC)
                          {
                             if(whichdialog==18)
                             {
                                  m_set->m_add->m_zhiwen->m_label->setText(trUtf8("擦除成功"));
                             }
                             else
                             {
                                   ui->label->setText(trUtf8("擦除成功"));
                             }
                          }
                          break;
                      }
                      case 0x11://氧气     J
                      {
                           if(whichdialog==1&&iaddtype==6)
                           {
                               if(JudgeAddrIsTheSame(whichdialog,sLAddr)==false)
                               {
                                   (m_set->m_add->m_table)->setRowCount((m_set->m_add->m_table)->rowCount()+1);
                                   (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),0,new QTableWidgetItem(trUtf8("氧气")));
                                   (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),1,new QTableWidgetItem(str));
                                   (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),2,new QTableWidgetItem(sLAddr));
                                   (m_set->m_add->m_table)->setRowHeight(((m_set->m_add->m_table)->rowCount()-1),50);

                               }
                           }
                           else
                           {
                               if(JudgeIsAddTable(sLAddr)==true)
                               {
                                   changeData4=true;
                                  DeleteSensorDataTableToNull();
                                   ui->label->setText(trUtf8("当前氧气值:")+CharToStr(4,cData[7],0x00));
                                   yangqiNow=CharToStr(4,cData[7],0x00);
                                  // QString s1=CharToStr(2,cData[4],cData[5]);
                                   AddSensorDataTable(trUtf8("氧气"),str,sLAddr,RetDirByMacAddr(sLAddr),CharToStr(4,cData[7],0x00),"NULL");
                                //=================UDPSending==========================================

                                   ithreadsendtype=12;
                                   sthreadlongaddr=sLAddr;
                                  // SendDataToServerByUdpWenDu(RetDirByMacAddr(sLAddr),0x01);
                                   qDebug()<<"yangqi udp";
                               }
                               else
                               {
                                 ui->label->setText(trUtf8("您未添加此设备"));
                               }
                           }
                          break;
                      }
                      case 0x0F://水位
                      {
                         if(whichdialog==1&&iaddtype==6)
                         {
                             if(JudgeAddrIsTheSame(whichdialog,sLAddr)==false)
                             {
                                 (m_set->m_add->m_table)->setRowCount((m_set->m_add->m_table)->rowCount()+1);
                                 (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),0,new QTableWidgetItem(trUtf8("水位")));
                                 (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),1,new QTableWidgetItem(str));
                                 (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),2,new QTableWidgetItem(sLAddr));
                                 (m_set->m_add->m_table)->setRowHeight(((m_set->m_add->m_table)->rowCount()-1),50);

                             }
                         }
                        else
                        {
                            if(JudgeIsAddTable(sLAddr)==true)
                            {
                                changeData4=true;
                                 DeleteSensorDataTableToNull();
                                ui->label->setText(trUtf8("当前水位值:")+CharToStr(4,cData[7],0x01)+"cm");
                                shuiweiNow=CharToStr(4,cData[7],0x01)+"cm";

                                //QString s1=CharToStr(2,cData[4],cData[5]);
                                AddSensorDataTable(trUtf8("水位"),str,sLAddr,RetDirByMacAddr(sLAddr),CharToStr(4,cData[7],0x00),"NULL");
                              //  qDebug()<<"shuiwei xieshujuku";
                                //=======================================================================================
                                ithreadsendtype=13;
                                sthreadlongaddr=sLAddr;
                               // SendDataToServerByUdpWenDu(RetDirByMacAddr(sLAddr),0x02);
                                qDebug()<<"shuiwei udp";
                            }
                             else
                            {
                                 ui->label->setText(trUtf8("您未添加此设备"));
                            }

                        }
                        break;
                      }
                      case 0x22://二氧化碳  J
                    {
                       JDSecond[13]=0;
                       JDFlag[13]=true;
                         if(whichdialog==1&&iaddtype==6)
                         {
                             if(JudgeAddrIsTheSame(whichdialog,sLAddr)==false)
                             {
                                 (m_set->m_add->m_table)->setRowCount((m_set->m_add->m_table)->rowCount()+1);
                                 (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),0,new QTableWidgetItem(trUtf8("二氧化碳")));
                                 (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),1,new QTableWidgetItem(str));
                                 (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),2,new QTableWidgetItem(sLAddr));
                                 (m_set->m_add->m_table)->setRowHeight(((m_set->m_add->m_table)->rowCount()-1),50);
                             }
                         }
                         else
                         {
                             if(JudgeIsAddTable(sLAddr)==true)
                             {
                                 changeData3=true;
                                 changeData4=true;
                                 switch(cData[7])
                                 {
                                     case 0x00://no
                                     {
                                        DeleteSensorDataTableToNull();
                                        ui->label->setText(trUtf8("监测到二氧化碳正常"));
                                        AddSensorDataTable(trUtf8("二氧化碳"),str,sLAddr,RetDirByMacAddr(sLAddr),CharToStr(4,cData[7],0x00),"NULL");
                                        co2Now=trUtf8("正常");
                                        //=======================================================================================
                                        ithreadsendtype=14;
                                        sthreadlongaddr=sLAddr;

                                      //  SendDataToServerByUdpWenDu(RetDirByMacAddr(sLAddr),0x03);
                                        break;
                                     }
                                     case 0x01://y
                                     {
                                        DeleteSensorDataTableToNull();
                                        ui->label->setText(trUtf8("监测到二氧化碳异常，超标"));
                                        co2Now=trUtf8("异常,超标");
                                        AddSensorDataTable(trUtf8("二氧化碳"),str,sLAddr,RetDirByMacAddr(sLAddr),CharToStr(4,cData[7],0x00),"NULL");
                                        //=======================================================================================
                                        ithreadsendtype=14;
                                        sthreadlongaddr=sLAddr;

                                        //  SendDataToServerByUdpWenDu(RetDirByMacAddr(sLAddr),0x03);
                                        break;
                                     }
                                 }
                             }
                             else
                             {
                                 ui->label->setText(trUtf8("您未添加此设备"));
                             }
                         }
                         break;
                    }
                      case 0x14://PH    J
                      {
                         if(whichdialog==1&&iaddtype==6)
                         {
                             if(JudgeAddrIsTheSame(whichdialog,sLAddr)==false)
                             {
                               (m_set->m_add->m_table)->setRowCount((m_set->m_add->m_table)->rowCount()+1);
                               (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),0,new QTableWidgetItem(trUtf8("PH")));
                               (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),1,new QTableWidgetItem(str));
                               (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),2,new QTableWidgetItem(sLAddr));
                               (m_set->m_add->m_table)->setRowHeight(((m_set->m_add->m_table)->rowCount()-1),50);
                             }
                         }
                         else
                         {
                            if(JudgeIsAddTable(sLAddr)==true)
                            {
                               if(cData[7]==0xCC)
                               {
                                   changeData4=true;
                                   DeleteSensorDataTableToNull();
                                   QString s1="";
                                   s1=CharToStr(3,cData[8],cData[9]);
                                   ui->label->setText(trUtf8("当前PH值: ")+s1);
                                   AddSensorDataTable(trUtf8("PH"),s1,sLAddr,RetDirByMacAddr(sLAddr),CharToStr(4,cData[8],0x00),CharToStr(4,cData[9],0x00));
                                   //=======================================================================================
                                   ithreadsendtype=15;
                                   sthreadlongaddr=sLAddr;


                                   //SendDataToServerByUdpWenDu(RetDirByMacAddr(sLAddr),0x04);
                               }
                            }
                            else
                            {
                               ui->label->setText(trUtf8("您未添加此设备"));
                            }
                          }
                          break;
                        }
                      case 'L'://光敏
                     {
                       JDSecond[8]=0;
                       JDFlag[8]=true;
                         if(whichdialog==1&&iaddtype==6)
                         {
                             if(JudgeAddrIsTheSame(whichdialog,sLAddr)==false)
                             {
                                 (m_set->m_add->m_table)->setRowCount((m_set->m_add->m_table)->rowCount()+1);
                                 (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),0,new QTableWidgetItem(trUtf8("光敏")));
                                 (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),1,new QTableWidgetItem(str));
                                 (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),2,new QTableWidgetItem(sLAddr));
                                 (m_set->m_add->m_table)->setRowHeight(((m_set->m_add->m_table)->rowCount()-1),50);
                            }
                        }
                        else
                        {
                            if(JudgeIsAddTable(sLAddr)==true)
                            {
                                changeData4=true;
                                switch(cData[7])
                                {
                                    case 0x00://no
                                    {
                                       DeleteSensorDataTableToNull();
                                       ui->label->setText(trUtf8("光敏：检测到无光"));
                                       guangminNow=trUtf8("检测到无光");
                                       QString s2=CharToStr(4,cData[7],0x00);
                                       AddSensorDataTable(trUtf8("光敏"),str,sLAddr,RetDirByMacAddr(sLAddr),s2,"NULL");
                                       break;
                                    }
                                    case 0x01://y
                                    {
                                       DeleteSensorDataTableToNull();
                                       ui->label->setText(trUtf8("光敏：检测到有光"));
                                       guangminNow=trUtf8("检测到有光");
                                       QString s2=CharToStr(4,cData[7],0x00);
                                       AddSensorDataTable(trUtf8("光敏"),str,sLAddr,RetDirByMacAddr(sLAddr),s2,"NULL");
                                       break;
                                    }
                                    default:
                                    {
                                       break;
                                    }
                                 }
                             }
                             else
                             {
                                ui->label->setText(trUtf8("您未添加此设备"));
                             }
                        }
                         break;
                   }
                   case 'M':  //结露
                   {
                       JDSecond[6]=0;
                       JDFlag[6]=true;
                       if(whichdialog==1&&iaddtype==6)
                       {
                           if(JudgeAddrIsTheSame(whichdialog,sLAddr)==false)
                           {
                               (m_set->m_add->m_table)->setRowCount((m_set->m_add->m_table)->rowCount()+1);
                               (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),0,new QTableWidgetItem(trUtf8("结露")));
                               (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),1,new QTableWidgetItem(str));
                               (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),2,new QTableWidgetItem(sLAddr));
                               (m_set->m_add->m_table)->setRowHeight(((m_set->m_add->m_table)->rowCount()-1),50);
                          }
                        }
                        else
                        {
                            if(JudgeIsAddTable(sLAddr)==true)
                            {
                                changeData1=true;
                                changeData4=true;
                                switch(cData[7])
                                {
                                    case 0x00://no
                                    {
                                        DeleteSensorDataTableToNull();
                                        ui->label->setText(trUtf8("结露：检测到有结露"));
                                        jieluNow=trUtf8("检测到有结露");
                                        QString s2=CharToStr(4,cData[7],0x00);
                                        AddSensorDataTable(trUtf8("结露"),str,sLAddr,RetDirByMacAddr(sLAddr),s2,"NULL");
                                        break;
                                     }
                                    case 0x01://y
                                    {
                                        DeleteSensorDataTableToNull();
                                        ui->label->setText(trUtf8("结露：检测到正常"));
                                        jieluNow=trUtf8("检测到正常");
                                        QString s2=CharToStr(4,cData[7],0x00);
                                        AddSensorDataTable(trUtf8("结露"),str,sLAddr,RetDirByMacAddr(sLAddr),s2,"NULL");
                                        break;
                                    }
                                    default:
                                   {
                                      break;
                                   }
                                }
                        }
                        else
                        {
                            ui->label->setText(trUtf8("您未添加此设备"));
                        }
                     }
                       break;
                   }
                   case 'B'://三轴加速度
                   {
                       JDSecond[0]=0;
                       JDFlag[0]=true;
                      if(whichdialog==1&&iaddtype==6)
                      {
                          if(JudgeAddrIsTheSame(whichdialog,sLAddr)==false)
                          {
                            (m_set->m_add->m_table)->setRowCount((m_set->m_add->m_table)->rowCount()+1);
                              (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),0,new QTableWidgetItem(trUtf8("三轴加速度")));
                            (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),1,new QTableWidgetItem(str));
                            (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),2,new QTableWidgetItem(sLAddr));
                            (m_set->m_add->m_table)->setRowHeight(((m_set->m_add->m_table)->rowCount()-1),50);
                          }
                      }
                      else
                      {
                          if(JudgeIsAddTable(sLAddr)==true)
                          {
                              changeData4=true;
                               QString s2=CharToStr(1,cData[7],0x00);
                               QString s3=CharToStr(1,cData[8],0x00);
                               QString s4=CharToStr(1,cData[9],0x00);
                               ui->label->setText(trUtf8("三轴加速度")+" x:"+s2+" y:"+s3+" z:"+s4);
                               sanzhouNow=" x:"+s2+" y:"+s3+" z:"+s4;
                               DeleteSensorDataTableToNull();
                               AddSensorDataTable(trUtf8("三轴加速度"),str,sLAddr,RetDirByMacAddr(sLAddr),s2,"NULL");
                          }
                           else
                           {
                              ui->label->setText(trUtf8("您未添加此设备"));
                           }
                      }
                      break;
                   }
                   case 'D'://颜色
                   {
                       JDSecond[1]=0;
                       JDFlag[1]=true;
                      if(whichdialog==1&&iaddtype==6)
                      {
                          if(JudgeAddrIsTheSame(whichdialog,sLAddr)==false)
                          {
                            (m_set->m_add->m_table)->setRowCount((m_set->m_add->m_table)->rowCount()+1);
                            (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),0,new QTableWidgetItem(trUtf8("颜色")));
                            (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),1,new QTableWidgetItem(str));
                            (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),2,new QTableWidgetItem(sLAddr));
                            (m_set->m_add->m_table)->setRowHeight(((m_set->m_add->m_table)->rowCount()-1),50);
                          }
                      }
                      else
                      {
                          if(JudgeIsAddTable(sLAddr)==true)
                          {
                              changeData4=true;
                               QString s2=CharToStr(1,cData[7],0x00);
                               QString s3=CharToStr(1,cData[8],0x00);
                               QString s4=CharToStr(1,cData[9],0x00);
                               ui->label->setText(trUtf8("颜色")+" R:"+s2+" G:"+s3+" B:"+s4);
                               colorNow=" R:"+s2+" G:"+s3+" B:"+s4;
                               DeleteSensorDataTableToNull();
                               AddSensorDataTable(trUtf8("颜色"),str,sLAddr,RetDirByMacAddr(sLAddr),s2,"NULL");
                          }
                           else
                           {
                              ui->label->setText(trUtf8("您未添加此设备"));
                           }
                      }
                      break;
                   }
                   case 0x15://语音播报
                   {
                         if(whichdialog==1&&iaddtype==6)
                         {
                               if(JudgeAddrIsTheSame(whichdialog,sLAddr)==false)
                               {
                                      (m_set->m_add->m_table)->setRowCount((m_set->m_add->m_table)->rowCount()+1);
                                      (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),0,new QTableWidgetItem(trUtf8("语音播报")));
                                      (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),1,new QTableWidgetItem(str));
                                      (m_set->m_add->m_table)->setItem(((m_set->m_add->m_table)->rowCount()-1),2,new QTableWidgetItem(sLAddr));
                                      (m_set->m_add->m_table)->setRowHeight(((m_set->m_add->m_table)->rowCount()-1),50);
                                }
                         }
                         else
                         {
                              if(JudgeIsAddTable(sLAddr)==true)
                              {

                              }
                              else
                              {
                                    ui->label->setText(trUtf8("您未添加此设备"));
                              }
                         }
                         break;
                  }


                  default:
                  {
                     break;
                  }
                   }
            }
            else
            {
                   if(cData[0]==0xCC&&cData[1]==0xEE&&cData[2]==0xEE&&cData[3]==0xDD)
                   {
                       if(whichdialog==-1)
                       {
                           ui->label->setText(trUtf8("组网初始化成功"));
                           QMessageBox *m_messagebox=new QMessageBox();
                           m_messagebox->setText(trUtf8("组网初始化成功"));
                           m_messagebox->setStyleSheet("background-color: rgb(255,255,255,0);");
                           m_messagebox->setStyleSheet("color:rgb(10, 200, 100);");
                           m_messagebox->setFont(QFont("tt",60));
                           m_messagebox->exec();
                           delete m_messagebox;
                           return;
                       }
                   }
                   if(cData[0]==0xCC&&cData[2]==0xBB&&cData[5]==0xDD)
                   {
                       if(whichdialog==-1)
                       {
                           ui->label->setText(trUtf8("获取信道PANID接收成功"));
                           QString s2="";QString s1="";
                           s1.sprintf("%02x",cData[3]);
                           s2.sprintf("%02x",cData[4]);
                           s1=s1+s2;
                           s2.sprintf("%02d",cData[1]);
                           ui->label->setText(trUtf8("信道:")+s2+trUtf8("  PANID：")+s1);
                           QMessageBox *m_messagebox=new QMessageBox();
                           m_messagebox->setText(trUtf8("信道:")+s2+trUtf8("   PANID：")+s1);
                           m_messagebox->setStyleSheet("background-color: rgb(255,255,255,0);");
                           m_messagebox->setStyleSheet("color:rgb(10, 200, 100);");
                           m_messagebox->setFont(QFont("tt",60));
                           m_messagebox->exec();
                           delete m_messagebox;
                           return;
                       }
                   }
            }
        }
     }
    memset(cData,0,sizeof(cData)); //  清空cData
}

//void AutoControl_V2::ShowComIsRecv()
//{


//  m_CheckIsRecv->stop();
//  bcheckisrecv=false;
//  All_OFF();
//  DeleteSensorDataTableToNull();

//}

//void AutoControl_V2::TimerFunForKG()
//{
////  m_TimerFun->stop();
////  bistimerfunopen=false;
////  KG_OFF(m_control->btimerfunaddr,btimerfunmacaddr);
////  btimerfunaddr="";

//    if(bistimerfunopen==true)
//    {
//        switch(itimerfuntype)
//        {
//           case 1:
//          {
//              YanShi_DianJi_ZhengZhuan(FindShortAddrWhile(trUtf8("演示板"),trUtf8("大棚")),FindLongAddrWhile(trUtf8("演示板"),trUtf8("大棚")));

//              m_TimerFun->stop();
//              bistimerfunopen=false;
//              itimerfuntype=-1;
//              break;
//          }
//          case 2:
//          {
//              YanShi_DianJi_ZhengZhuan(FindShortAddrWhile(trUtf8("演示板"),trUtf8("加工厂")),FindLongAddrWhile(trUtf8("演示板"),trUtf8("加工厂")));
//              m_TimerFun->stop();
//              bistimerfunopen=false;
//              itimerfuntype=-1;
//              break;

//          }
//          case 3:
//          {
//              SendWenDuOrderToCar(telnumber,maccaraddr);
//              m_TimerFun->stop();
//              bistimerfunopen=false;
//              itimerfuntype=-1;
//             break;

//          }
//          default:
//          {
//            m_TimerFun->stop();
//            bistimerfunopen=false;
//            itimerfuntype=-1;
//              break;
//          }
//        }

//    }
//}

void AutoControl_V2::ReadDatabase()//open add dialog
{
    yanshibanID=0;
    yanshibanID2=0;
    DeleteNullForTable();

    QSqlQuery m_query(m_sql);
    QString str="";
    m_query.prepare("SELECT * FROM SensorTable");
    if (m_query.exec())
    {
        int Row = 0;str="";
        isensorlength=0;
        while (m_query.next())
        {
            ui->tableWidget->setRowCount(Row + 1);
            ui->tableWidget->setItem(Row, 0,new QTableWidgetItem(m_query.value(1).toString()));
            ui->tableWidget->setItem(Row, 1,new QTableWidgetItem(m_query.value(4).toString()));
            ui->tableWidget->setItem(Row, 2,new QTableWidgetItem(m_query.value(2).toString()));
            ui->tableWidget->setItem(Row, 3,new QTableWidgetItem(m_query.value(3).toString()));
            ui->tableWidget->setItem(Row, 4,new QTableWidgetItem(m_query.value(5).toString()));

            ui->tableWidget->setRowHeight(Row,50);
            m_sensorstruct[isensorlength].id=m_query.value(0).toInt();
            m_sensorstruct[isensorlength].name=m_query.value(1).toString();
            m_sensorstruct[isensorlength].shortaddr=m_query.value(2).toString();
            m_sensorstruct[isensorlength].longaddr=m_query.value(3).toString();
            m_sensorstruct[isensorlength].dir=m_query.value(4).toString();
            m_sensorstruct[isensorlength].status=m_query.value(5).toString();
            if(m_sensorstruct[isensorlength].name==trUtf8("演示板") && m_sensorstruct[isensorlength].dir==trUtf8("智能家居"))
            {
               yanshibanID=m_sensorstruct[isensorlength].id;
            }
            else if(m_sensorstruct[isensorlength].name==trUtf8("演示板") && m_sensorstruct[isensorlength].dir==trUtf8("智慧农业"))
            {
                yanshibanID2=m_sensorstruct[isensorlength].id;
            }
            isensorlength++;
            Row++;
        }
    }
    m_query.prepare("SELECT * FROM IRHWTable");
    if (m_query.exec())
    {
        int i=ui->tableWidget->rowCount();
        iirtructlength=0;
        str="";
        while (m_query.next())
        {
            ui->tableWidget->setRowCount(i + 1);
            ui->tableWidget->setItem(i, 0,new QTableWidgetItem(m_query.value(0).toString()));//name
            ui->tableWidget->setItem(i, 1,new QTableWidgetItem(m_query.value(5).toString()));//cname
            ui->tableWidget->setItem(i, 2,new QTableWidgetItem(m_query.value(1).toString()));//addr
            ui->tableWidget->setItem(i, 3,new QTableWidgetItem(m_query.value(2).toString()));//addr
            ui->tableWidget->setRowHeight(i,50);
            m_irstruct[iirtructlength].name=m_query.value(0).toString();
            m_irstruct[iirtructlength].shortaddr=m_query.value(1).toString();
            m_irstruct[iirtructlength].longaddr=m_query.value(2).toString();
            m_irstruct[iirtructlength].dir=m_query.value(3).toString();
            m_irstruct[iirtructlength].code=m_query.value(4).toString();
            m_irstruct[iirtructlength].function=m_query.value(5).toString();
            i++;
            iirtructlength++;
        }
    }
    m_query.prepare("SELECT * FROM ThreeFiveDevTable");
    if (m_query.exec())
    {
        int i=ui->tableWidget->rowCount();
        ithreefivestructlength=0;
        str="";
        while (m_query.next())
        {
            ui->tableWidget->setRowCount(i + 1);
            ui->tableWidget->setItem(i, 0,new QTableWidgetItem(m_query.value(0).toString()));//name
            ui->tableWidget->setItem(i, 1,new QTableWidgetItem(m_query.value(3).toString()));//
            ui->tableWidget->setItem(i, 2,new QTableWidgetItem(m_query.value(1).toString()));//addr
            ui->tableWidget->setItem(i, 3,new QTableWidgetItem(m_query.value(2).toString()));//addr
            ui->tableWidget->setRowHeight(i,50);
            m_threefivestruct[ithreefivestructlength].name=m_query.value(0).toString();
            m_threefivestruct[ithreefivestructlength].shortaddr=m_query.value(1).toString();
            m_threefivestruct[ithreefivestructlength].longaddr=m_query.value(2).toString();
            m_threefivestruct[ithreefivestructlength].dir=m_query.value(3).toString();
            m_threefivestruct[ithreefivestructlength].code=m_query.value(4).toString();
            i++;
            ithreefivestructlength++;
        }
    }
    m_query.prepare("SELECT * FROM ZhiWenTable");
    if (m_query.exec())
    {
        int j=0;
        int i=ui->tableWidget->rowCount();
        izhiwenstructlen=0;
        str="";
        while (m_query.next())
        {
            if(j!=0)
            {
                 QTableWidgetItem *item = ui->tableWidget->item((i-1), 3);
                if(QString::compare(m_query.value(2).toString(),item->text())!=0)
                {
                    ui->tableWidget->setRowCount(i + 1);
                    ui->tableWidget->setItem(i, 0,new QTableWidgetItem(m_query.value(0).toString()));//name
                    ui->tableWidget->setItem(i, 1,new QTableWidgetItem(m_query.value(3).toString()));//
                    ui->tableWidget->setItem(i, 2,new QTableWidgetItem(m_query.value(1).toString()));//addr
                    ui->tableWidget->setItem(i, 3,new QTableWidgetItem(m_query.value(2).toString()));//addr
                    ui->tableWidget->setRowHeight(i,50);
                }
            }
            else
            {
                ui->tableWidget->setRowCount(i + 1);
                ui->tableWidget->setItem(i, 0,new QTableWidgetItem(m_query.value(0).toString()));//name
                ui->tableWidget->setItem(i, 1,new QTableWidgetItem(m_query.value(3).toString()));//
                ui->tableWidget->setItem(i, 2,new QTableWidgetItem(m_query.value(1).toString()));//addr
                ui->tableWidget->setItem(i, 3,new QTableWidgetItem(m_query.value(2).toString()));//addr
                ui->tableWidget->setRowHeight(i,50);
            }

            m_zhiwenstruct[izhiwenstructlen].name=m_query.value(0).toString();
            m_zhiwenstruct[izhiwenstructlen].shortaddr=m_query.value(1).toString();
            m_zhiwenstruct[izhiwenstructlen].longaddr=m_query.value(2).toString();
            m_zhiwenstruct[izhiwenstructlen].dir=m_query.value(3).toString();
            m_zhiwenstruct[izhiwenstructlen].code=m_query.value(4).toString();
            i++;
            ++j;
            izhiwenstructlen++;



        }
    }
//-----------------测试------------
//    ReadSensorValTable();
//------------------------------------
}

void AutoControl_V2::ReadControlTable()
{
    QSqlQuery m_query(m_sql);
    m_query.prepare("SELECT * FROM GuanXianTable");
    if (m_query.exec())
    {
        iguangxianstructlength=0;
        while (m_query.next())
        {
            m_guangxianstruct[iguangxianstructlength].name=m_query.value(0).toString();
            m_guangxianstruct[iguangxianstructlength].shortaddr=m_query.value(1).toString();
            m_guangxianstruct[iguangxianstructlength].longaddr=m_query.value(2).toString();
            m_guangxianstruct[iguangxianstructlength].dir=m_query.value(3).toString();
            m_guangxianstruct[iguangxianstructlength].val=m_query.value(4).toString();
            m_guangxianstruct[iguangxianstructlength].cname=m_query.value(5).toString();
            m_guangxianstruct[iguangxianstructlength].cshortaddr=m_query.value(6).toString();
            m_guangxianstruct[iguangxianstructlength].clongaddr=m_query.value(7).toString();
            m_guangxianstruct[iguangxianstructlength].cdir=m_query.value(8).toString();
            m_guangxianstruct[iguangxianstructlength].cfun=m_query.value(9).toString();
            m_guangxianstruct[iguangxianstructlength].truefun=m_query.value(10).toString();
            iguangxianstructlength++;

        }
    }
    m_query.prepare("SELECT * FROM QiTiTable");
    if (m_query.exec())
    {
       iqitistructlength=0;
        while (m_query.next())
        {
            m_qitistruct[iqitistructlength].name=m_query.value(0).toString();
            m_qitistruct[iqitistructlength].shortaddr=m_query.value(1).toString();
            m_qitistruct[iqitistructlength].longaddr=m_query.value(2).toString();
            m_qitistruct[iqitistructlength].dir=m_query.value(3).toString();
            m_qitistruct[iqitistructlength].cname=m_query.value(4).toString();
            m_qitistruct[iqitistructlength].cshortaddr=m_query.value(5).toString();
            m_qitistruct[iqitistructlength].clongaddr=m_query.value(6).toString();
            m_qitistruct[iqitistructlength].cdir=m_query.value(7).toString();
            m_qitistruct[iqitistructlength].cfun=m_query.value(8).toString();
            m_qitistruct[iqitistructlength].truefun=m_query.value(9).toString();
            iqitistructlength++;
        }
    }
    m_query.prepare("SELECT * FROM SmogTable");
    if (m_query.exec())
    {
       ismogstructlength=0;
        while (m_query.next())
        {
            m_smogstruct[ismogstructlength].name=m_query.value(0).toString();
            m_smogstruct[ismogstructlength].shortaddr=m_query.value(1).toString();
            m_smogstruct[ismogstructlength].longaddr=m_query.value(2).toString();
            m_smogstruct[ismogstructlength].dir=m_query.value(3).toString();
            m_smogstruct[ismogstructlength].cname=m_query.value(4).toString();
            m_smogstruct[ismogstructlength].cshortaddr=m_query.value(5).toString();
            m_smogstruct[ismogstructlength].clongaddr=m_query.value(6).toString();
            m_smogstruct[ismogstructlength].cdir=m_query.value(7).toString();
            m_smogstruct[ismogstructlength].cfun=m_query.value(8).toString();
            m_smogstruct[ismogstructlength].truefun=m_query.value(9).toString();
            ismogstructlength++;
        }
    }
    m_query.prepare("SELECT * FROM RainTable");
    if (m_query.exec())
    {
       irainstructlength=0;
        while (m_query.next())
        {
            m_rainstruct[irainstructlength].name=m_query.value(0).toString();
            m_rainstruct[irainstructlength].shortaddr=m_query.value(1).toString();
            m_rainstruct[irainstructlength].longaddr=m_query.value(2).toString();
            m_rainstruct[irainstructlength].dir=m_query.value(3).toString();
            m_rainstruct[irainstructlength].cname=m_query.value(4).toString();
            m_rainstruct[irainstructlength].cshortaddr=m_query.value(5).toString();
            m_rainstruct[irainstructlength].clongaddr=m_query.value(6).toString();
            m_rainstruct[irainstructlength].cdir=m_query.value(7).toString();
            m_rainstruct[irainstructlength].cfun=m_query.value(8).toString();
            m_rainstruct[irainstructlength].truefun=m_query.value(9).toString();
            irainstructlength++;
        }
    }
    m_query.prepare("SELECT * FROM KeyTable");
    if (m_query.exec())
    {
       ikeystructlength=0;
        while (m_query.next())
        {
            m_keystruct[ikeystructlength].name=m_query.value(0).toString();
            m_keystruct[ikeystructlength].shortaddr=m_query.value(1).toString();
            m_keystruct[ikeystructlength].longaddr=m_query.value(2).toString();
            m_keystruct[ikeystructlength].dir=m_query.value(3).toString();
            m_keystruct[ikeystructlength].val=m_query.value(4).toString();
            m_keystruct[ikeystructlength].cname=m_query.value(5).toString();
            m_keystruct[ikeystructlength].cshortaddr=m_query.value(6).toString();
            m_keystruct[ikeystructlength].clongaddr=m_query.value(7).toString();
            m_keystruct[ikeystructlength].cdir=m_query.value(8).toString();
            m_keystruct[ikeystructlength].cfun=m_query.value(9).toString();
            m_keystruct[ikeystructlength].truefun=m_query.value(10).toString();
            ikeystructlength++;
        }
    }
    m_query.prepare("SELECT * FROM WenShiduTable");
    if (m_query.exec())
    {
       iwenshidustructlength=0;
        while (m_query.next())
        {
            m_wenshidustruct[iwenshidustructlength].name=m_query.value(0).toString();
            m_wenshidustruct[iwenshidustructlength].shortaddr=m_query.value(1).toString();
            m_wenshidustruct[iwenshidustructlength].longaddr=m_query.value(2).toString();
            m_wenshidustruct[iwenshidustructlength].dir=m_query.value(3).toString();
            m_wenshidustruct[iwenshidustructlength].wenduval=m_query.value(4).toString();
            m_wenshidustruct[iwenshidustructlength].shiduval=m_query.value(5).toString();
            m_wenshidustruct[iwenshidustructlength].cname=m_query.value(6).toString();
            m_wenshidustruct[iwenshidustructlength].cshortaddr=m_query.value(7).toString();
            m_wenshidustruct[iwenshidustructlength].clongaddr=m_query.value(8).toString();
            m_wenshidustruct[iwenshidustructlength].cdir=m_query.value(9).toString();
            m_wenshidustruct[iwenshidustructlength].cfun=m_query.value(10).toString();
            m_wenshidustruct[iwenshidustructlength].truefun=m_query.value(11).toString();
            iwenshidustructlength++;
        }
    }
    m_query.prepare("SELECT * FROM KongQiTable");
    if (m_query.exec())
    {
       ikongqistructlength=0;
        while (m_query.next())
        {
            m_kongqistruct[ikongqistructlength].name=m_query.value(0).toString();
            m_kongqistruct[ikongqistructlength].shortaddr=m_query.value(1).toString();
            m_kongqistruct[ikongqistructlength].longaddr=m_query.value(2).toString();
            m_kongqistruct[ikongqistructlength].dir=m_query.value(3).toString();
            m_kongqistruct[ikongqistructlength].cname=m_query.value(4).toString();
            m_kongqistruct[ikongqistructlength].cshortaddr=m_query.value(5).toString();
            m_kongqistruct[ikongqistructlength].clongaddr=m_query.value(6).toString();
            m_kongqistruct[ikongqistructlength].cdir=m_query.value(7).toString();
            m_kongqistruct[ikongqistructlength].cfun=m_query.value(8).toString();
            m_kongqistruct[ikongqistructlength].truefun=m_query.value(9).toString();
            ikongqistructlength++;
        }
    }
}

void AutoControl_V2::ReadTelNumber()
{
    QSqlQuery m_query(m_sql);
    m_query.prepare("SELECT * FROM TelNumTable");
    if (m_query.exec())
    {
      //  itelephonelength=0;
         while (m_query.next())
         {
//            m_telstruct[iduanxinsetlength].telephone=m_query.value(0).toString();
//            qDebug()<<"EE"+m_telstruct[iduanxinsetlength].telephone;
//            itelephonelength++;
            telnumber=m_query.value(0).toString();

         }
     }


}

void AutoControl_V2::ReadSensorValTable()
{
    QString str[19]={trUtf8("雨滴"),trUtf8("温度"),trUtf8("湿度"),trUtf8("气压"),trUtf8("按键"),trUtf8("火焰"),trUtf8("电子称"),trUtf8("震动"),trUtf8("噪声"),trUtf8("光线"),trUtf8("空气质量"),trUtf8("二氧化碳"),trUtf8("气体"),trUtf8("烟雾"),trUtf8("人体"),trUtf8("门磁"),trUtf8("氧气"),trUtf8("水位"),trUtf8("PH")};
    QSqlQuery m_query(m_sql);

    m_query.prepare("SELECT * FROM SensorDataTable WHERE name=?");
    int i=0;int row=0;
    while(i<19)
    {
         row=0;
         m_query.addBindValue(str[i]);
         if (m_query.exec())
         {
            while (m_query.next())
            {
                row++;
                m_sensorvalstruct[i].name=m_query.value(0).toString();
                m_sensorvalstruct[i].shortaddr=m_query.value(1).toString();
                m_sensorvalstruct[i].longaddr=m_query.value(2).toString();
                m_sensorvalstruct[i].dir=m_query.value(3).toString();
                m_sensorvalstruct[i].highval=m_query.value(4).toString();
                m_sensorvalstruct[i].lowval=m_query.value(5).toString();


            }
         }
         if(row==0)
         {
             m_sensorvalstruct[i].name=str[i];
             m_sensorvalstruct[i].shortaddr="NULL";
             m_sensorvalstruct[i].longaddr="NULL";
             m_sensorvalstruct[i].dir="NULL";//NULL
             m_sensorvalstruct[i].highval="NULL";//NULL
             m_sensorvalstruct[i].lowval="NULL";//NULL

         }
         ++i;
    }

}

void AutoControl_V2::ReadShevlesTable()
{
    QSqlQuery m_query(m_sql);
    m_query.prepare("SELECT * FROM ShelvesMessTable");
    if (m_query.exec())
    {
        ishelveslength=0;
         while (m_query.next())
         {
            m_shevlesstruct[ishelveslength].name=m_query.value(0).toString();
            m_shevlesstruct[ishelveslength].rfidnum=m_query.value(1).toString();
            ishelveslength++;
         }
     }
}

void AutoControl_V2::AddSensorDataTable(QString name,QString shortaddr,QString longaddr,QString dir,QString valhigh,QString vallow)
{
    QSqlQuery m_query(m_sql);
    m_query.prepare("insert into SensorDataTable(name,shortaddr,longaddr,dir,valhigh,vallow) values(:name,:shortaddr,:longaddr,:dir,:valhigh,:vallow)");

    m_query.bindValue(":name",name);
    m_query.bindValue(":shortaddr", shortaddr);
    m_query.bindValue(":longaddr", longaddr);
    m_query.bindValue(":dir", dir);
    m_query.bindValue(":valhigh", valhigh);
    m_query.bindValue(":vallow", vallow);

    bool ok=m_query.exec();
    if(ok==false)
    {
        ui->label->setText(trUtf8("添加表3错误。。"));
        return;
    }
}

void AutoControl_V2::DeleteSensorDataTableToNull()
{
    QSqlQuery m_query(m_sql);
    m_query.prepare("DELETE FROM SensorDataTable");
    bool ok=false;
    ok=m_query.exec();
    if(ok==false)
    {
       ui->label->setText(trUtf8("删除值错误"));
       return;
    }
}

void AutoControl_V2::DeleteNullForTable()
{
    //rowcount得到行数
    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        ui->tableWidget->removeRow(i);//移除第i列
    }
}

void AutoControl_V2::SendUpdate()//fasong shuaxin
{
    bool ok=1;QString str1="";
    QByteArray ba;
    for(int i=0;i<(22+8);i++)
    {
        ba[i]=0x00;
    }
    ba[0]=0xFB;ba[21+8]=0xFE;
   for(int i=0;i<isensorlength;i++)
    {
       if(m_sensorstruct[i].name.contains(trUtf8("通风扇"))==true)
       {
           ba[4]=0x28;

           qcharaddr=m_sensorstruct[i].shortaddr.toInt(&ok,16);
           ba[2]=(qcharaddr.unicode())/256;
           ba[3]=(qcharaddr.unicode())%256;

           str1=CutMACString(1,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[21]=(qcharaddr.unicode())/256;
           ba[22]=(qcharaddr.unicode())%256;
           str1=CutMACString(2,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[23]=(qcharaddr.unicode())/256;
           ba[24]=(qcharaddr.unicode())%256;
           str1=CutMACString(3,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[25]=(qcharaddr.unicode())/256;
           ba[26]=(qcharaddr.unicode())%256;
           str1=CutMACString(4,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[27]=(qcharaddr.unicode())/256;
           ba[28]=(qcharaddr.unicode())%256;
       }
       if(m_sensorstruct[i].name.contains(trUtf8("调光"))==true)
       {
           ba[4]=0x24;
           qcharaddr=m_sensorstruct[i].shortaddr.toInt(&ok,16);
           ba[2]=(qcharaddr.unicode())/256;
           ba[3]=(qcharaddr.unicode())%256;

           str1=CutMACString(1,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[21]=(qcharaddr.unicode())/256;
           ba[22]=(qcharaddr.unicode())%256;
           str1=CutMACString(2,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[23]=(qcharaddr.unicode())/256;
           ba[24]=(qcharaddr.unicode())%256;
           str1=CutMACString(3,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[25]=(qcharaddr.unicode())/256;
           ba[26]=(qcharaddr.unicode())%256;
           str1=CutMACString(4,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[27]=(qcharaddr.unicode())/256;
           ba[28]=(qcharaddr.unicode())%256;
       }
       if(m_sensorstruct[i].name.contains(trUtf8("窗帘"))==true)
       {
           ba[4]=0x25;
           qcharaddr=m_sensorstruct[i].shortaddr.toInt(&ok,16);
           ba[2]=(qcharaddr.unicode())/256;
           ba[3]=(qcharaddr.unicode())%256;

           str1=CutMACString(1,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[21]=(qcharaddr.unicode())/256;
           ba[22]=(qcharaddr.unicode())%256;
           str1=CutMACString(2,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[23]=(qcharaddr.unicode())/256;
           ba[24]=(qcharaddr.unicode())%256;
           str1=CutMACString(3,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[25]=(qcharaddr.unicode())/256;
           ba[26]=(qcharaddr.unicode())%256;
           str1=CutMACString(4,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[27]=(qcharaddr.unicode())/256;
           ba[28]=(qcharaddr.unicode())%256;
       }
        if(QString::compare(m_sensorstruct[i].name,trUtf8("温度"))==0)
       {
           ba[4]=0x05;
           qcharaddr=m_sensorstruct[i].shortaddr.toInt(&ok,16);
           ba[2]=(qcharaddr.unicode())/256;
           ba[3]=(qcharaddr.unicode())%256;

           str1=CutMACString(1,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[21]=(qcharaddr.unicode())/256;
           ba[22]=(qcharaddr.unicode())%256;
           str1=CutMACString(2,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[23]=(qcharaddr.unicode())/256;
           ba[24]=(qcharaddr.unicode())%256;
           str1=CutMACString(3,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[25]=(qcharaddr.unicode())/256;
           ba[26]=(qcharaddr.unicode())%256;
           str1=CutMACString(4,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[27]=(qcharaddr.unicode())/256;
           ba[28]=(qcharaddr.unicode())%256;
       }
       if(QString::compare(m_sensorstruct[i].name,trUtf8("温湿度"))==0)
       {
           ba[4]=0x06;
           qcharaddr=m_sensorstruct[i].shortaddr.toInt(&ok,16);
           ba[2]=(qcharaddr.unicode())/256;
           ba[3]=(qcharaddr.unicode())%256;

           str1=CutMACString(1,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[21]=(qcharaddr.unicode())/256;
           ba[22]=(qcharaddr.unicode())%256;
           str1=CutMACString(2,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[23]=(qcharaddr.unicode())/256;
           ba[24]=(qcharaddr.unicode())%256;
           str1=CutMACString(3,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[25]=(qcharaddr.unicode())/256;
           ba[26]=(qcharaddr.unicode())%256;
           str1=CutMACString(4,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[27]=(qcharaddr.unicode())/256;
           ba[28]=(qcharaddr.unicode())%256;
       }
       if(m_sensorstruct[i].name.contains(trUtf8("光线"))==true)
       {
           ba[4]=0x20;
           qcharaddr=m_sensorstruct[i].shortaddr.toInt(&ok,16);
           ba[2]=(qcharaddr.unicode())/256;
           ba[3]=(qcharaddr.unicode())%256;

           str1=CutMACString(1,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[21]=(qcharaddr.unicode())/256;
           ba[22]=(qcharaddr.unicode())%256;
           str1=CutMACString(2,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[23]=(qcharaddr.unicode())/256;
           ba[24]=(qcharaddr.unicode())%256;
           str1=CutMACString(3,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[25]=(qcharaddr.unicode())/256;
           ba[26]=(qcharaddr.unicode())%256;
           str1=CutMACString(4,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[27]=(qcharaddr.unicode())/256;
           ba[28]=(qcharaddr.unicode())%256;
       }
      if(m_sensorstruct[i].name.contains(trUtf8("电子称"))==true)
       {
           ba[4]=0x13;
           qcharaddr=m_sensorstruct[i].shortaddr.toInt(&ok,16);
           ba[2]=(qcharaddr.unicode())/256;
           ba[3]=(qcharaddr.unicode())%256;

           str1=CutMACString(1,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[21]=(qcharaddr.unicode())/256;
           ba[22]=(qcharaddr.unicode())%256;
           str1=CutMACString(2,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[23]=(qcharaddr.unicode())/256;
           ba[24]=(qcharaddr.unicode())%256;
           str1=CutMACString(3,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[25]=(qcharaddr.unicode())/256;
           ba[26]=(qcharaddr.unicode())%256;
           str1=CutMACString(4,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[27]=(qcharaddr.unicode())/256;
           ba[28]=(qcharaddr.unicode())%256;
       }
       if(m_sensorstruct[i].name.contains(trUtf8("浇花"))==true)
       {
           ba[4]=0x31;
           qcharaddr=m_sensorstruct[i].shortaddr.toInt(&ok,16);
           ba[2]=(qcharaddr.unicode())/256;
           ba[3]=(qcharaddr.unicode())%256;

           str1=CutMACString(1,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[21]=(qcharaddr.unicode())/256;
           ba[22]=(qcharaddr.unicode())%256;
           str1=CutMACString(2,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[23]=(qcharaddr.unicode())/256;
           ba[24]=(qcharaddr.unicode())%256;
           str1=CutMACString(3,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[25]=(qcharaddr.unicode())/256;
           ba[26]=(qcharaddr.unicode())%256;
           str1=CutMACString(4,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[27]=(qcharaddr.unicode())/256;
           ba[28]=(qcharaddr.unicode())%256;
       }
       if(m_sensorstruct[i].name.contains(trUtf8("电饭煲"))==true)
       {
           ba[4]=0x30;
           qcharaddr=m_sensorstruct[i].shortaddr.toInt(&ok,16);
           ba[2]=(qcharaddr.unicode())/256;
           ba[3]=(qcharaddr.unicode())%256;

           str1=CutMACString(1,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[21]=(qcharaddr.unicode())/256;
           ba[22]=(qcharaddr.unicode())%256;
           str1=CutMACString(2,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[23]=(qcharaddr.unicode())/256;
           ba[24]=(qcharaddr.unicode())%256;
           str1=CutMACString(3,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[25]=(qcharaddr.unicode())/256;
           ba[26]=(qcharaddr.unicode())%256;
           str1=CutMACString(4,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[27]=(qcharaddr.unicode())/256;
           ba[28]=(qcharaddr.unicode())%256;
       }
       if(m_sensorstruct[i].name.contains(trUtf8("加湿器"))==true)
       {
           ba[4]=0x33;
           qcharaddr=m_sensorstruct[i].shortaddr.toInt(&ok,16);
           ba[2]=(qcharaddr.unicode())/256;
           ba[3]=(qcharaddr.unicode())%256;

           str1=CutMACString(1,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[21]=(qcharaddr.unicode())/256;
           ba[22]=(qcharaddr.unicode())%256;
           str1=CutMACString(2,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[23]=(qcharaddr.unicode())/256;
           ba[24]=(qcharaddr.unicode())%256;
           str1=CutMACString(3,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[25]=(qcharaddr.unicode())/256;
           ba[26]=(qcharaddr.unicode())%256;
           str1=CutMACString(4,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[27]=(qcharaddr.unicode())/256;
           ba[28]=(qcharaddr.unicode())%256;
       }
       if(m_sensorstruct[i].name.contains(trUtf8("饮水机"))==true)
       {
           ba[4]=0x40;
           qcharaddr=m_sensorstruct[i].shortaddr.toInt(&ok,16);
           ba[2]=(qcharaddr.unicode())/256;
           ba[3]=(qcharaddr.unicode())%256;

           str1=CutMACString(1,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[21]=(qcharaddr.unicode())/256;
           ba[22]=(qcharaddr.unicode())%256;
           str1=CutMACString(2,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[23]=(qcharaddr.unicode())/256;
           ba[24]=(qcharaddr.unicode())%256;
           str1=CutMACString(3,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[25]=(qcharaddr.unicode())/256;
           ba[26]=(qcharaddr.unicode())%256;
           str1=CutMACString(4,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[27]=(qcharaddr.unicode())/256;
           ba[28]=(qcharaddr.unicode())%256;
       }
       if(QString::compare(m_sensorstruct[i].name,trUtf8("雨蓬"))==0)
       {
           ba[4]=0x26;
           qcharaddr=m_sensorstruct[i].shortaddr.toInt(&ok,16);
           ba[2]=(qcharaddr.unicode())/256;
           ba[3]=(qcharaddr.unicode())%256;

           str1=CutMACString(1,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[21]=(qcharaddr.unicode())/256;
           ba[22]=(qcharaddr.unicode())%256;
           str1=CutMACString(2,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[23]=(qcharaddr.unicode())/256;
           ba[24]=(qcharaddr.unicode())%256;
           str1=CutMACString(3,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[25]=(qcharaddr.unicode())/256;
           ba[26]=(qcharaddr.unicode())%256;
           str1=CutMACString(4,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[27]=(qcharaddr.unicode())/256;
           ba[28]=(qcharaddr.unicode())%256;
       }
       if(m_sensorstruct[i].name.contains(trUtf8("净化器"))==true)
       {
           ba[4]=0x41;
           qcharaddr=m_sensorstruct[i].shortaddr.toInt(&ok,16);
           ba[2]=(qcharaddr.unicode())/256;
           ba[3]=(qcharaddr.unicode())%256;

           str1=CutMACString(1,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[21]=(qcharaddr.unicode())/256;
           ba[22]=(qcharaddr.unicode())%256;
           str1=CutMACString(2,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[23]=(qcharaddr.unicode())/256;
           ba[24]=(qcharaddr.unicode())%256;
           str1=CutMACString(3,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[25]=(qcharaddr.unicode())/256;
           ba[26]=(qcharaddr.unicode())%256;
           str1=CutMACString(4,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[27]=(qcharaddr.unicode())/256;
           ba[28]=(qcharaddr.unicode())%256;
       }
       if(m_sensorstruct[i].name.contains(trUtf8("电源"))==true)
       {
           ba[4]=0x42;
           qcharaddr=m_sensorstruct[i].shortaddr.toInt(&ok,16);
           ba[2]=(qcharaddr.unicode())/256;
           ba[3]=(qcharaddr.unicode())%256;

           str1=CutMACString(1,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[21]=(qcharaddr.unicode())/256;
           ba[22]=(qcharaddr.unicode())%256;
           str1=CutMACString(2,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[23]=(qcharaddr.unicode())/256;
           ba[24]=(qcharaddr.unicode())%256;
           str1=CutMACString(3,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[25]=(qcharaddr.unicode())/256;
           ba[26]=(qcharaddr.unicode())%256;
           str1=CutMACString(4,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[27]=(qcharaddr.unicode())/256;
           ba[28]=(qcharaddr.unicode())%256;
       }
       if(QString::compare(m_sensorstruct[i].name,trUtf8("换气扇"))==0)
       {
           ba[4]=0x29;
           qcharaddr=m_sensorstruct[i].shortaddr.toInt(&ok,16);
           ba[2]=(qcharaddr.unicode())/256;
           ba[3]=(qcharaddr.unicode())%256;

           str1=CutMACString(1,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[21]=(qcharaddr.unicode())/256;
           ba[22]=(qcharaddr.unicode())%256;
           str1=CutMACString(2,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[23]=(qcharaddr.unicode())/256;
           ba[24]=(qcharaddr.unicode())%256;
           str1=CutMACString(3,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[25]=(qcharaddr.unicode())/256;
           ba[26]=(qcharaddr.unicode())%256;
           str1=CutMACString(4,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[27]=(qcharaddr.unicode())/256;
           ba[28]=(qcharaddr.unicode())%256;
       }
       if(QString::compare(m_sensorstruct[i].name,trUtf8("喷淋"))==0)
       {
           ba[4]=0x32;
           qcharaddr=m_sensorstruct[i].shortaddr.toInt(&ok,16);
           ba[2]=(qcharaddr.unicode())/256;
           ba[3]=(qcharaddr.unicode())%256;

           str1=CutMACString(1,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[21]=(qcharaddr.unicode())/256;
           ba[22]=(qcharaddr.unicode())%256;
           str1=CutMACString(2,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[23]=(qcharaddr.unicode())/256;
           ba[24]=(qcharaddr.unicode())%256;
           str1=CutMACString(3,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[25]=(qcharaddr.unicode())/256;
           ba[26]=(qcharaddr.unicode())%256;
           str1=CutMACString(4,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[27]=(qcharaddr.unicode())/256;
           ba[28]=(qcharaddr.unicode())%256;
       }
       if(QString::compare(m_sensorstruct[i].name,trUtf8("雨滴"))==0)
       {
           ba[4]=0x01;
           qcharaddr=m_sensorstruct[i].shortaddr.toInt(&ok,16);
           ba[2]=(qcharaddr.unicode())/256;
           ba[3]=(qcharaddr.unicode())%256;

           str1=CutMACString(1,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[21]=(qcharaddr.unicode())/256;
           ba[22]=(qcharaddr.unicode())%256;
           str1=CutMACString(2,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[23]=(qcharaddr.unicode())/256;
           ba[24]=(qcharaddr.unicode())%256;
           str1=CutMACString(3,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[25]=(qcharaddr.unicode())/256;
           ba[26]=(qcharaddr.unicode())%256;
           str1=CutMACString(4,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[27]=(qcharaddr.unicode())/256;
           ba[28]=(qcharaddr.unicode())%256;
       }
       if(QString::compare(m_sensorstruct[i].name,trUtf8("气压"))==0)
       {
           ba[4]=0x07;
           qcharaddr=m_sensorstruct[i].shortaddr.toInt(&ok,16);
           ba[2]=(qcharaddr.unicode())/256;
           ba[3]=(qcharaddr.unicode())%256;

           str1=CutMACString(1,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[21]=(qcharaddr.unicode())/256;
           ba[22]=(qcharaddr.unicode())%256;
           str1=CutMACString(2,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[23]=(qcharaddr.unicode())/256;
           ba[24]=(qcharaddr.unicode())%256;
           str1=CutMACString(3,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[25]=(qcharaddr.unicode())/256;
           ba[26]=(qcharaddr.unicode())%256;
           str1=CutMACString(4,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[27]=(qcharaddr.unicode())/256;
           ba[28]=(qcharaddr.unicode())%256;
       }
       if(QString::compare(m_sensorstruct[i].name,trUtf8("空气质量"))==0)
       {
           ba[4]=0x22;
           qcharaddr=m_sensorstruct[i].shortaddr.toInt(&ok,16);
           ba[2]=(qcharaddr.unicode())/256;
           ba[3]=(qcharaddr.unicode())%256;

           str1=CutMACString(1,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[21]=(qcharaddr.unicode())/256;
           ba[22]=(qcharaddr.unicode())%256;
           str1=CutMACString(2,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[23]=(qcharaddr.unicode())/256;
           ba[24]=(qcharaddr.unicode())%256;
           str1=CutMACString(3,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[25]=(qcharaddr.unicode())/256;
           ba[26]=(qcharaddr.unicode())%256;
           str1=CutMACString(4,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[27]=(qcharaddr.unicode())/256;
           ba[28]=(qcharaddr.unicode())%256;
       }
       if(m_sensorstruct[i].name.contains(trUtf8("噪声")))
       {
           ba[4]=0x19;
           qcharaddr=m_sensorstruct[i].shortaddr.toInt(&ok,16);
           ba[2]=(qcharaddr.unicode())/256;
           ba[3]=(qcharaddr.unicode())%256;

           str1=CutMACString(1,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[21]=(qcharaddr.unicode())/256;
           ba[22]=(qcharaddr.unicode())%256;
           str1=CutMACString(2,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[23]=(qcharaddr.unicode())/256;
           ba[24]=(qcharaddr.unicode())%256;
           str1=CutMACString(3,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[25]=(qcharaddr.unicode())/256;
           ba[26]=(qcharaddr.unicode())%256;
           str1=CutMACString(4,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[27]=(qcharaddr.unicode())/256;
           ba[28]=(qcharaddr.unicode())%256;
       }
       if(m_sensorstruct[i].name.contains(trUtf8("震动")))
       {
           ba[4]=0x15;
           qcharaddr=m_sensorstruct[i].shortaddr.toInt(&ok,16);
           ba[2]=(qcharaddr.unicode())/256;
           ba[3]=(qcharaddr.unicode())%256;

           str1=CutMACString(1,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[21]=(qcharaddr.unicode())/256;
           ba[22]=(qcharaddr.unicode())%256;
           str1=CutMACString(2,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[23]=(qcharaddr.unicode())/256;
           ba[24]=(qcharaddr.unicode())%256;
           str1=CutMACString(3,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[25]=(qcharaddr.unicode())/256;
           ba[26]=(qcharaddr.unicode())%256;
           str1=CutMACString(4,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[27]=(qcharaddr.unicode())/256;
           ba[28]=(qcharaddr.unicode())%256;
       }
       if(m_sensorstruct[i].name.contains(trUtf8("小车")))
       {
           ba[4]=0x27;
           qcharaddr=m_sensorstruct[i].shortaddr.toInt(&ok,16);
           ba[2]=(qcharaddr.unicode())/256;
           ba[3]=(qcharaddr.unicode())%256;

           str1=CutMACString(1,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[21]=(qcharaddr.unicode())/256;
           ba[22]=(qcharaddr.unicode())%256;
           str1=CutMACString(2,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[23]=(qcharaddr.unicode())/256;
           ba[24]=(qcharaddr.unicode())%256;
           str1=CutMACString(3,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[25]=(qcharaddr.unicode())/256;
           ba[26]=(qcharaddr.unicode())%256;
           str1=CutMACString(4,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[27]=(qcharaddr.unicode())/256;
           ba[28]=(qcharaddr.unicode())%256;
       }
       if(QString::compare(m_sensorstruct[i].name,trUtf8("喷雾器"))==0)
       {
           ba[4]=0x44;
           qcharaddr=m_sensorstruct[i].shortaddr.toInt(&ok,16);
           ba[2]=(qcharaddr.unicode())/256;
           ba[3]=(qcharaddr.unicode())%256;

           str1=CutMACString(1,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[21]=(qcharaddr.unicode())/256;
           ba[22]=(qcharaddr.unicode())%256;
           str1=CutMACString(2,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[23]=(qcharaddr.unicode())/256;
           ba[24]=(qcharaddr.unicode())%256;
           str1=CutMACString(3,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[25]=(qcharaddr.unicode())/256;
           ba[26]=(qcharaddr.unicode())%256;
           str1=CutMACString(4,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[27]=(qcharaddr.unicode())/256;
           ba[28]=(qcharaddr.unicode())%256;
       }
       if(QString::compare(m_sensorstruct[i].name,trUtf8("高频"))==0)
       {
           ba[4]=0x18;
           qcharaddr=m_sensorstruct[i].shortaddr.toInt(&ok,16);
           ba[2]=(qcharaddr.unicode())/256;
           ba[3]=(qcharaddr.unicode())%256;

           str1=CutMACString(1,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[21]=(qcharaddr.unicode())/256;
           ba[22]=(qcharaddr.unicode())%256;
           str1=CutMACString(2,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[23]=(qcharaddr.unicode())/256;
           ba[24]=(qcharaddr.unicode())%256;
           str1=CutMACString(3,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[25]=(qcharaddr.unicode())/256;
           ba[26]=(qcharaddr.unicode())%256;
           str1=CutMACString(4,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[27]=(qcharaddr.unicode())/256;
           ba[28]=(qcharaddr.unicode())%256;
       }
       if(QString::compare(m_sensorstruct[i].name,trUtf8("超高频"))==0)
       {
           ba[4]=0x16;
           qcharaddr=m_sensorstruct[i].shortaddr.toInt(&ok,16);
           ba[2]=(qcharaddr.unicode())/256;
           ba[3]=(qcharaddr.unicode())%256;

           str1=CutMACString(1,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[21]=(qcharaddr.unicode())/256;
           ba[22]=(qcharaddr.unicode())%256;
           str1=CutMACString(2,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[23]=(qcharaddr.unicode())/256;
           ba[24]=(qcharaddr.unicode())%256;
           str1=CutMACString(3,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[25]=(qcharaddr.unicode())/256;
           ba[26]=(qcharaddr.unicode())%256;
           str1=CutMACString(4,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[27]=(qcharaddr.unicode())/256;
           ba[28]=(qcharaddr.unicode())%256;
       }
       if(QString::compare(m_sensorstruct[i].name,trUtf8("门锁"))==0)
       {
           ba[4]=0x45;
           qcharaddr=m_sensorstruct[i].shortaddr.toInt(&ok,16);
           ba[2]=(qcharaddr.unicode())/256;
           ba[3]=(qcharaddr.unicode())%256;

           str1=CutMACString(1,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[21]=(qcharaddr.unicode())/256;
           ba[22]=(qcharaddr.unicode())%256;
           str1=CutMACString(2,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[23]=(qcharaddr.unicode())/256;
           ba[24]=(qcharaddr.unicode())%256;
           str1=CutMACString(3,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[25]=(qcharaddr.unicode())/256;
           ba[26]=(qcharaddr.unicode())%256;
           str1=CutMACString(4,m_sensorstruct[i].longaddr);
           qcharaddr=str1.toInt(&ok,16);
           ba[27]=(qcharaddr.unicode())/256;
           ba[28]=(qcharaddr.unicode())%256;
       }
       clientConnection->write(ba);

    }

    for(int i=0;i<iirtructlength;i++)
    {
        if(QString::compare(trUtf8("空调"),m_irstruct[i].name)==0)
        {
            ba[4]=0x38;
            qcharaddr=m_irstruct[i].shortaddr.toInt(&ok,16);
            ba[2]=(qcharaddr.unicode())/256;
            ba[3]=(qcharaddr.unicode())%256;
            if(QString::compare(trUtf8("开"),m_irstruct[i].function)==0)
            {
                ba[20]=0xF1;
            }
            if(QString::compare(trUtf8("关"),m_irstruct[i].function)==0)
            {
                ba[20]=0xF0;
            }
            if(QString::compare(trUtf8("风向"),m_irstruct[i].function)==0)
            {
                ba[20]=0x5F;
            }
            if(QString::compare(trUtf8("风速"),m_irstruct[i].function)==0)
            {
                ba[20]=0x6F;
            }
            if(QString::compare(trUtf8("预设温度"),m_irstruct[i].function)==0)
            {
                ba[20]=0x7F;
            }
            str1=CutMACString(1,m_irstruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[21]=(qcharaddr.unicode())/256;
            ba[22]=(qcharaddr.unicode())%256;
            str1=CutMACString(2,m_irstruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[23]=(qcharaddr.unicode())/256;
            ba[24]=(qcharaddr.unicode())%256;
            str1=CutMACString(3,m_irstruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[25]=(qcharaddr.unicode())/256;
            ba[26]=(qcharaddr.unicode())%256;
            str1=CutMACString(4,m_irstruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[27]=(qcharaddr.unicode())/256;
            ba[28]=(qcharaddr.unicode())%256;
        }
        if(QString::compare(trUtf8("空调扇"),m_irstruct[i].name)==0)
        {
            ba[4]=0x39;
            qcharaddr=m_irstruct[i].shortaddr.toInt(&ok,16);
            ba[2]=(qcharaddr.unicode())/256;
            ba[3]=(qcharaddr.unicode())%256;
            if(QString::compare(trUtf8("开"),m_irstruct[i].function)==0)
            {
                ba[20]=0xF1;
            }
            if(QString::compare(trUtf8("关"),m_irstruct[i].function)==0)
            {
                ba[20]=0xF0;
            }
            if(QString::compare(trUtf8("风向"),m_irstruct[i].function)==0)
            {
                ba[20]=0x5F;
            }
            if(QString::compare(trUtf8("风速"),m_irstruct[i].function)==0)
            {
                ba[20]=0x6F;
            }
            if(QString::compare(trUtf8("预设温度"),m_irstruct[i].function)==0)
            {
                ba[20]=0x7F;
            }
            str1=CutMACString(1,m_irstruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[21]=(qcharaddr.unicode())/256;
            ba[22]=(qcharaddr.unicode())%256;
            str1=CutMACString(2,m_irstruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[23]=(qcharaddr.unicode())/256;
            ba[24]=(qcharaddr.unicode())%256;
            str1=CutMACString(3,m_irstruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[25]=(qcharaddr.unicode())/256;
            ba[26]=(qcharaddr.unicode())%256;
            str1=CutMACString(4,m_irstruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[27]=(qcharaddr.unicode())/256;
            ba[28]=(qcharaddr.unicode())%256;
        }
        if(QString::compare(trUtf8("音箱"),m_irstruct[i].name)==0)
        {
            ba[4]=0x37;
            qcharaddr=m_irstruct[i].shortaddr.toInt(&ok,16);
            ba[2]=(qcharaddr.unicode())/256;
            ba[3]=(qcharaddr.unicode())%256;
            if(QString::compare(trUtf8("开"),m_irstruct[i].function)==0)
            {
                ba[20]=0xF1;
            }
            if(QString::compare(trUtf8("关"),m_irstruct[i].function)==0)
            {
                ba[20]=0xF0;
            }
            if(QString::compare(trUtf8("音量+"),m_irstruct[i].function)==0)
            {
                ba[20]=0x0F;
            }
            if(QString::compare(trUtf8("音量-"),m_irstruct[i].function)==0)
            {
                ba[20]=0x1F;
            }
            str1=CutMACString(1,m_irstruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[21]=(qcharaddr.unicode())/256;
            ba[22]=(qcharaddr.unicode())%256;
            str1=CutMACString(2,m_irstruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[23]=(qcharaddr.unicode())/256;
            ba[24]=(qcharaddr.unicode())%256;
            str1=CutMACString(3,m_irstruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[25]=(qcharaddr.unicode())/256;
            ba[26]=(qcharaddr.unicode())%256;
            str1=CutMACString(4,m_irstruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[27]=(qcharaddr.unicode())/256;
            ba[28]=(qcharaddr.unicode())%256;
        }
        if(QString::compare(trUtf8("投影机"),m_irstruct[i].name)==0)
        {
            ba[4]=0x35;
            qcharaddr=m_irstruct[i].shortaddr.toInt(&ok,16);
            ba[2]=(qcharaddr.unicode())/256;
            ba[3]=(qcharaddr.unicode())%256;
            if(QString::compare(trUtf8("开"),m_irstruct[i].function)==0)
            {
                ba[20]=0xF1;
            }
            if(QString::compare(trUtf8("关"),m_irstruct[i].function)==0)
            {
                ba[20]=0xF0;
            }
            str1=CutMACString(1,m_irstruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[21]=(qcharaddr.unicode())/256;
            ba[22]=(qcharaddr.unicode())%256;
            str1=CutMACString(2,m_irstruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[23]=(qcharaddr.unicode())/256;
            ba[24]=(qcharaddr.unicode())%256;
            str1=CutMACString(3,m_irstruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[25]=(qcharaddr.unicode())/256;
            ba[26]=(qcharaddr.unicode())%256;
            str1=CutMACString(4,m_irstruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[27]=(qcharaddr.unicode())/256;
            ba[28]=(qcharaddr.unicode())%256;
        }
        if(QString::compare(trUtf8("电视机"),m_irstruct[i].name)==0)
        {
            ba[4]=0x36;
            qcharaddr=m_irstruct[i].shortaddr.toInt(&ok,16);
            ba[2]=(qcharaddr.unicode())/256;
            ba[3]=(qcharaddr.unicode())%256;
            if(QString::compare(trUtf8("开"),m_irstruct[i].function)==0)
            {
                ba[20]=0xF1;
            }
            if(QString::compare(trUtf8("关"),m_irstruct[i].function)==0)
            {
                ba[20]=0xF0;
            }
            if(QString::compare(trUtf8("音量+"),m_irstruct[i].function)==0)
            {
                ba[20]=0x0F;
            }
            if(QString::compare(trUtf8("音量-"),m_irstruct[i].function)==0)
            {
                ba[20]=0x1F;
            }
            if(QString::compare(trUtf8("频道+"),m_irstruct[i].function)==0)
            {
                ba[20]=0x2F;
            }
            if(QString::compare(trUtf8("频道-"),m_irstruct[i].function)==0)
            {
                ba[20]=0x3F;
            }
            if(QString::compare(trUtf8("AV模式"),m_irstruct[i].function)==0)
            {
                ba[20]=0x4F;
            }
            str1=CutMACString(1,m_irstruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[21]=(qcharaddr.unicode())/256;
            ba[22]=(qcharaddr.unicode())%256;
            str1=CutMACString(2,m_irstruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[23]=(qcharaddr.unicode())/256;
            ba[24]=(qcharaddr.unicode())%256;
            str1=CutMACString(3,m_irstruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[25]=(qcharaddr.unicode())/256;
            ba[26]=(qcharaddr.unicode())%256;
            str1=CutMACString(4,m_irstruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[27]=(qcharaddr.unicode())/256;
            ba[28]=(qcharaddr.unicode())%256;
        }
        if(QString::compare(trUtf8("DVD"),m_irstruct[i].name)==0)
        {
            ba[4]=0x46;
            qcharaddr=m_irstruct[i].shortaddr.toInt(&ok,16);
            ba[2]=(qcharaddr.unicode())/256;
            ba[3]=(qcharaddr.unicode())%256;
            if(QString::compare(trUtf8("开/关"),m_irstruct[i].function)==0)
            {
                ba[20]=0xF1;
            }
            if(QString::compare(trUtf8("音量+"),m_irstruct[i].function)==0)
            {
                ba[20]=0x0F;
            }
            if(QString::compare(trUtf8("音量-"),m_irstruct[i].function)==0)
            {
                ba[20]=0x1F;
            }
            if(QString::compare(trUtf8("进/出仓"),m_irstruct[i].function)==0)
            {
                ba[20]=0x8F;
            }
            if(QString::compare(trUtf8("播放/暂停"),m_irstruct[i].function)==0)
            {
                ba[20]=0x9F;
            }
            if(QString::compare(trUtf8("快进"),m_irstruct[i].function)==0)
            {
                ba[20]=0xAF;
            }
            if(QString::compare(trUtf8("快退"),m_irstruct[i].function)==0)
            {
                ba[20]=0xBF;
            }
            str1=CutMACString(1,m_irstruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[21]=(qcharaddr.unicode())/256;
            ba[22]=(qcharaddr.unicode())%256;
            str1=CutMACString(2,m_irstruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[23]=(qcharaddr.unicode())/256;
            ba[24]=(qcharaddr.unicode())%256;
            str1=CutMACString(3,m_irstruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[25]=(qcharaddr.unicode())/256;
            ba[26]=(qcharaddr.unicode())%256;
            str1=CutMACString(4,m_irstruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[27]=(qcharaddr.unicode())/256;
            ba[28]=(qcharaddr.unicode())%256;
        }
        clientConnection->write(ba);

    }

    for(int i=0;i<ithreefivestructlength;i++)
    {
        if(QString::compare(trUtf8("烟雾"),m_threefivestruct[i].name)==0)
        {
            ba[4]=0x21;
            qcharaddr=m_threefivestruct[i].shortaddr.toInt(&ok,16);
            ba[2]=(qcharaddr.unicode())/256;
            ba[3]=(qcharaddr.unicode())%256;
            ba[20]=(char)m_threefivestruct[i].code.toInt(&ok,16);

            str1=CutMACString(1,m_threefivestruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[21]=(qcharaddr.unicode())/256;
            ba[22]=(qcharaddr.unicode())%256;
            str1=CutMACString(2,m_threefivestruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[23]=(qcharaddr.unicode())/256;
            ba[24]=(qcharaddr.unicode())%256;
            str1=CutMACString(3,m_threefivestruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[25]=(qcharaddr.unicode())/256;
            ba[26]=(qcharaddr.unicode())%256;
            str1=CutMACString(4,m_threefivestruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[27]=(qcharaddr.unicode())/256;
            ba[28]=(qcharaddr.unicode())%256;
        }
        if(QString::compare(trUtf8("气体"),m_threefivestruct[i].name)==0)
        {
            ba[4]=0x09;
            qcharaddr=m_threefivestruct[i].shortaddr.toInt(&ok,16);
            ba[2]=(qcharaddr.unicode())/256;
            ba[3]=(qcharaddr.unicode())%256;
            ba[20]=(char)m_threefivestruct[i].code.toInt(&ok,16);

            str1=CutMACString(1,m_threefivestruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[21]=(qcharaddr.unicode())/256;
            ba[22]=(qcharaddr.unicode())%256;
            str1=CutMACString(2,m_threefivestruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[23]=(qcharaddr.unicode())/256;
            ba[24]=(qcharaddr.unicode())%256;
            str1=CutMACString(3,m_threefivestruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[25]=(qcharaddr.unicode())/256;
            ba[26]=(qcharaddr.unicode())%256;
            str1=CutMACString(4,m_threefivestruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[27]=(qcharaddr.unicode())/256;
            ba[28]=(qcharaddr.unicode())%256;
        }
        if(QString::compare(trUtf8("人体"),m_threefivestruct[i].name)==0)
        {
            ba[4]=0x14;
            qcharaddr=m_threefivestruct[i].shortaddr.toInt(&ok,16);
            ba[2]=(qcharaddr.unicode())/256;
            ba[3]=(qcharaddr.unicode())%256;
            ba[20]=(char)m_threefivestruct[i].code.toInt(&ok,16);

            str1=CutMACString(1,m_threefivestruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[21]=(qcharaddr.unicode())/256;
            ba[22]=(qcharaddr.unicode())%256;
            str1=CutMACString(2,m_threefivestruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[23]=(qcharaddr.unicode())/256;
            ba[24]=(qcharaddr.unicode())%256;
            str1=CutMACString(3,m_threefivestruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[25]=(qcharaddr.unicode())/256;
            ba[26]=(qcharaddr.unicode())%256;
            str1=CutMACString(4,m_threefivestruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[27]=(qcharaddr.unicode())/256;
            ba[28]=(qcharaddr.unicode())%256;
        }
        if(QString::compare(trUtf8("门磁"),m_threefivestruct[i].name)==0)
        {
            ba[4]=0x43;
            qcharaddr=m_threefivestruct[i].shortaddr.toInt(&ok,16);
            ba[2]=(qcharaddr.unicode())/256;
            ba[3]=(qcharaddr.unicode())%256;
            ba[20]=(char)m_threefivestruct[i].code.toInt(&ok,16);

            str1=CutMACString(1,m_threefivestruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[21]=(qcharaddr.unicode())/256;
            ba[22]=(qcharaddr.unicode())%256;
            str1=CutMACString(2,m_threefivestruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[23]=(qcharaddr.unicode())/256;
            ba[24]=(qcharaddr.unicode())%256;
            str1=CutMACString(3,m_threefivestruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[25]=(qcharaddr.unicode())/256;
            ba[26]=(qcharaddr.unicode())%256;
            str1=CutMACString(4,m_threefivestruct[i].longaddr);
            qcharaddr=str1.toInt(&ok,16);
            ba[27]=(qcharaddr.unicode())/256;
            ba[28]=(qcharaddr.unicode())%256;
        }
        clientConnection->write(ba);

    }
}

void AutoControl_V2::SendUpDateEnd()
{
    QByteArray ba;
    for(int i=0;i<(22+8);i++)
    {
        ba[i]=0x00;
    }
    ba[0]=0xFB;
    ba[20]=0xED;
    ba[21+8]=0xFE;
    clientConnection->write(ba);

}

void AutoControl_V2::SendDataClient(char ctype)//fasong shuzhi chuanganqi
{
    ReadSensorValTable();
    bool ok;QString str1="";
    QByteArray ba;
    for(int i=0;i<(22+8);i++)
    {
        ba[i]=0x00;
    }
    ba[0]=0xFB;ba[21+8]=0xFE;
    switch(ctype)
    {
        case 0x01://yudi
       {
          ba[4]=0x01;
          if((QString::compare(m_sensorvalstruct[0].shortaddr,"NULL")!=0)&&(QString::compare(m_sensorvalstruct[0].longaddr,"NULL")!=0)&&(QString::compare(m_sensorvalstruct[0].highval,"NULL")!=0))
          {
              ba[1]=0x01;
              qcharaddr=m_sensorvalstruct[0].longaddr.toInt(&ok,16);
              ba[2]=(qcharaddr.unicode())/256;
              ba[3]=(qcharaddr.unicode())%256;
              int i=m_sensorvalstruct[0].highval.toInt(&ok,10);
              if(i==0)
              {
                  ba[20]=0x00;
              }
              if(i==1)
              {
                  ba[20]=0x01;
              }
              str1=CutMACString(1,m_sensorvalstruct[0].longaddr);
              qcharaddr=str1.toInt(&ok,16);
              ba[21]=(qcharaddr.unicode())/256;
              ba[22]=(qcharaddr.unicode())%256;
              str1=CutMACString(2,m_sensorvalstruct[0].longaddr);
              qcharaddr=str1.toInt(&ok,16);
              ba[23]=(qcharaddr.unicode())/256;
              ba[24]=(qcharaddr.unicode())%256;
              str1=CutMACString(3,m_sensorvalstruct[0].longaddr);
              qcharaddr=str1.toInt(&ok,16);
              ba[25]=(qcharaddr.unicode())/256;
              ba[26]=(qcharaddr.unicode())%256;
              str1=CutMACString(4,m_sensorvalstruct[0].longaddr);
              qcharaddr=str1.toInt(&ok,16);
              ba[27]=(qcharaddr.unicode())/256;
              ba[28]=(qcharaddr.unicode())%256;
          }
          break;
       }
        case 0x05://wendu
        {
            ba[4]=0x05;
            if((QString::compare(m_sensorvalstruct[1].longaddr,"NULL")!=0)&&(QString::compare(m_sensorvalstruct[1].highval,"NULL")!=0)&&(QString::compare(m_sensorvalstruct[1].lowval,"NULL")!=0))
            {
               ba[1]=0x02;
               qcharaddr=m_sensorvalstruct[1].longaddr.toInt(&ok,16);
               ba[2]=(qcharaddr.unicode())/256;
               ba[3]=(qcharaddr.unicode())%256;
               char i=(char)m_sensorvalstruct[1].highval.toInt(&ok,10);
               ba[19]=i;
               i=(char)m_sensorvalstruct[1].lowval.toInt(&ok,10);
               ba[20]=i;

               str1=CutMACString(1,m_sensorvalstruct[1].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[21]=(qcharaddr.unicode())/256;
               ba[22]=(qcharaddr.unicode())%256;
               str1=CutMACString(2,m_sensorvalstruct[1].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[23]=(qcharaddr.unicode())/256;
               ba[24]=(qcharaddr.unicode())%256;
               str1=CutMACString(3,m_sensorvalstruct[1].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[25]=(qcharaddr.unicode())/256;
               ba[26]=(qcharaddr.unicode())%256;
               str1=CutMACString(4,m_sensorvalstruct[1].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[27]=(qcharaddr.unicode())/256;
               ba[28]=(qcharaddr.unicode())%256;
            }
           break;
        }
        case 0x06://shidu
        {
            ba[4]=0x06;
            if((QString::compare(m_sensorvalstruct[2].longaddr,"NULL")!=0)&&(QString::compare(m_sensorvalstruct[2].highval,"NULL")!=0)&&(QString::compare(m_sensorvalstruct[2].lowval,"NULL")!=0))
            {
               ba[1]=0x02;
               qcharaddr=m_sensorvalstruct[2].longaddr.toInt(&ok,16);
               ba[2]=(qcharaddr.unicode())/256;
               ba[3]=(qcharaddr.unicode())%256;
               char i=(char)m_sensorvalstruct[2].highval.toInt(&ok,10);
               ba[19]=i;
               i=(char)m_sensorvalstruct[2].lowval.toInt(&ok,10);
               ba[20]=i;

               str1=CutMACString(1,m_sensorvalstruct[2].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[21]=(qcharaddr.unicode())/256;
               ba[22]=(qcharaddr.unicode())%256;
               str1=CutMACString(2,m_sensorvalstruct[2].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[23]=(qcharaddr.unicode())/256;
               ba[24]=(qcharaddr.unicode())%256;
               str1=CutMACString(3,m_sensorvalstruct[2].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[25]=(qcharaddr.unicode())/256;
               ba[26]=(qcharaddr.unicode())%256;
               str1=CutMACString(4,m_sensorvalstruct[2].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[27]=(qcharaddr.unicode())/256;
               ba[28]=(qcharaddr.unicode())%256;
            }
           break;
        }
        case 0x07://qiya
        {
            ba[4]=0x07;
            if((QString::compare(m_sensorvalstruct[3].longaddr,"NULL")!=0)&&(QString::compare(m_sensorvalstruct[3].highval,"NULL")!=0)&&(QString::compare(m_sensorvalstruct[3].lowval,"NULL")!=0))
            {
               ba[1]=0x02;
               qcharaddr=m_sensorvalstruct[3].longaddr.toInt(&ok,16);
               ba[2]=(qcharaddr.unicode())/256;
               ba[3]=(qcharaddr.unicode())%256;
               char i=(char)m_sensorvalstruct[3].highval.toInt(&ok,10);
               ba[19]=i;
               i=(char)m_sensorvalstruct[3].lowval.toInt(&ok,10);
               ba[20]=i;

               str1=CutMACString(1,m_sensorvalstruct[3].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[21]=(qcharaddr.unicode())/256;
               ba[22]=(qcharaddr.unicode())%256;
               str1=CutMACString(2,m_sensorvalstruct[3].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[23]=(qcharaddr.unicode())/256;
               ba[24]=(qcharaddr.unicode())%256;
               str1=CutMACString(3,m_sensorvalstruct[3].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[25]=(qcharaddr.unicode())/256;
               ba[26]=(qcharaddr.unicode())%256;
               str1=CutMACString(4,m_sensorvalstruct[3].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[27]=(qcharaddr.unicode())/256;
               ba[28]=(qcharaddr.unicode())%256;
            }
           break;
        }
        case 0x08://key
        {
            ba[4]=0x08;
            if((QString::compare(m_sensorvalstruct[4].longaddr,"NULL")!=0)&&(QString::compare(m_sensorvalstruct[4].shortaddr,"NULL")!=0)&&(QString::compare(m_sensorvalstruct[4].highval,"NULL")!=0))
            {
               ba[1]=0x01;
               qcharaddr=m_sensorvalstruct[4].longaddr.toInt(&ok,16);
               ba[2]=(qcharaddr.unicode())/256;
               ba[3]=(qcharaddr.unicode())%256;
               char i=(char)m_sensorvalstruct[4].highval.toInt(&ok,10);
               ba[20]=i;

               str1=CutMACString(1,m_sensorvalstruct[4].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[21]=(qcharaddr.unicode())/256;
               ba[22]=(qcharaddr.unicode())%256;
               str1=CutMACString(2,m_sensorvalstruct[4].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[23]=(qcharaddr.unicode())/256;
               ba[24]=(qcharaddr.unicode())%256;
               str1=CutMACString(3,m_sensorvalstruct[4].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[25]=(qcharaddr.unicode())/256;
               ba[26]=(qcharaddr.unicode())%256;
               str1=CutMACString(4,m_sensorvalstruct[4].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[27]=(qcharaddr.unicode())/256;
               ba[28]=(qcharaddr.unicode())%256;
            }
           break;
        }
        case 0x12://fire
        {
            ba[4]=0x12;
            if((QString::compare(m_sensorvalstruct[5].longaddr,"NULL")!=0)&&(QString::compare(m_sensorvalstruct[5].highval,"NULL")!=0))
            {
               ba[1]=0x01;
               qcharaddr=m_sensorvalstruct[5].longaddr.toInt(&ok,16);
               ba[2]=(qcharaddr.unicode())/256;
               ba[3]=(qcharaddr.unicode())%256;
               int i=(char)m_sensorvalstruct[5].highval.toInt(&ok,10);
               if(i==0)
               {
                   ba[20]=0x00;
               }
               if(i==1)
               {
                   ba[20]=0x01;
               }
               str1=CutMACString(1,m_sensorvalstruct[5].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[21]=(qcharaddr.unicode())/256;
               ba[22]=(qcharaddr.unicode())%256;
               str1=CutMACString(2,m_sensorvalstruct[5].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[23]=(qcharaddr.unicode())/256;
               ba[24]=(qcharaddr.unicode())%256;
               str1=CutMACString(3,m_sensorvalstruct[5].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[25]=(qcharaddr.unicode())/256;
               ba[26]=(qcharaddr.unicode())%256;
               str1=CutMACString(4,m_sensorvalstruct[5].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[27]=(qcharaddr.unicode())/256;
               ba[28]=(qcharaddr.unicode())%256;
            }
           break;
        }
        case 0x13://dianzichen
        {
            ba[4]=0x13;
            if((QString::compare(m_sensorvalstruct[6].longaddr,"NULL")!=0)&&(QString::compare(m_sensorvalstruct[6].highval,"NULL")!=0))
            {
               ba[1]=0x01;
               qcharaddr=m_sensorvalstruct[6].longaddr.toInt(&ok,16);
               ba[2]=(qcharaddr.unicode())/256;
               ba[3]=(qcharaddr.unicode())%256;
               char i=(char)m_sensorvalstruct[6].highval.toInt(&ok,10);
               ba[20]=i;

               str1=CutMACString(1,m_sensorvalstruct[6].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[21]=(qcharaddr.unicode())/256;
               ba[22]=(qcharaddr.unicode())%256;
               str1=CutMACString(2,m_sensorvalstruct[6].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[23]=(qcharaddr.unicode())/256;
               ba[24]=(qcharaddr.unicode())%256;
               str1=CutMACString(3,m_sensorvalstruct[6].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[25]=(qcharaddr.unicode())/256;
               ba[26]=(qcharaddr.unicode())%256;
               str1=CutMACString(4,m_sensorvalstruct[6].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[27]=(qcharaddr.unicode())/256;
               ba[28]=(qcharaddr.unicode())%256;
            }

           break;
        }
        case 0x15://zhendong
        {
            ba[4]=0x15;
            if((QString::compare(m_sensorvalstruct[7].longaddr,"NULL")!=0)&&(QString::compare(m_sensorvalstruct[7].highval,"NULL")!=0))
            {
               ba[1]=0x01;
               qcharaddr=m_sensorvalstruct[7].longaddr.toInt(&ok,16);
               ba[2]=(qcharaddr.unicode())/256;
               ba[3]=(qcharaddr.unicode())%256;
               int i=m_sensorvalstruct[7].highval.toInt(&ok,10);
               if(i==0)
               {
                   ba[20]=0x00;
               }
               if(i==1)
               {
                   ba[20]=0x01;
               }
               str1=CutMACString(1,m_sensorvalstruct[7].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[21]=(qcharaddr.unicode())/256;
               ba[22]=(qcharaddr.unicode())%256;
               str1=CutMACString(2,m_sensorvalstruct[7].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[23]=(qcharaddr.unicode())/256;
               ba[24]=(qcharaddr.unicode())%256;
               str1=CutMACString(3,m_sensorvalstruct[7].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[25]=(qcharaddr.unicode())/256;
               ba[26]=(qcharaddr.unicode())%256;
               str1=CutMACString(4,m_sensorvalstruct[7].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[27]=(qcharaddr.unicode())/256;
               ba[28]=(qcharaddr.unicode())%256;
            }
           break;
        }
        case 0x19://zaosheng
        {
            ba[4]=0x19;
            if((QString::compare(m_sensorvalstruct[8].longaddr,"NULL")!=0)&&(QString::compare(m_sensorvalstruct[8].highval,"NULL")!=0)&&(QString::compare(m_sensorvalstruct[8].lowval,"NULL")!=0))
            {
               ba[1]=0x01;
               qcharaddr=m_sensorvalstruct[8].longaddr.toInt(&ok,16);
               ba[2]=(qcharaddr.unicode())/256;
               ba[3]=(qcharaddr.unicode())%256;
               char i=(char)m_sensorvalstruct[8].highval.toInt(&ok,10);
               ba[19]=i;
               i=(char)m_sensorvalstruct[8].lowval.toInt(&ok,10);
               ba[20]=i;
               str1=CutMACString(1,m_sensorvalstruct[8].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[21]=(qcharaddr.unicode())/256;
               ba[22]=(qcharaddr.unicode())%256;
               str1=CutMACString(2,m_sensorvalstruct[8].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[23]=(qcharaddr.unicode())/256;
               ba[24]=(qcharaddr.unicode())%256;
               str1=CutMACString(3,m_sensorvalstruct[8].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[25]=(qcharaddr.unicode())/256;
               ba[26]=(qcharaddr.unicode())%256;
               str1=CutMACString(4,m_sensorvalstruct[8].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[27]=(qcharaddr.unicode())/256;
               ba[28]=(qcharaddr.unicode())%256;
            }
           break;
        }
        case 0x20://guangxian
        {
            ba[4]=0x20;

            if((QString::compare(m_sensorvalstruct[9].longaddr,"NULL")!=0)&&(QString::compare(m_sensorvalstruct[9].highval,"NULL")!=0))
            {
               ba[1]=0x01;
               qcharaddr=m_sensorvalstruct[9].longaddr.toInt(&ok,16);
               ba[2]=(qcharaddr.unicode())/256;
               ba[3]=(qcharaddr.unicode())%256;
               char i=(char)m_sensorvalstruct[9].highval.toInt(&ok,10);
               ba[20]=i;
               str1=CutMACString(1,m_sensorvalstruct[9].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[21]=(qcharaddr.unicode())/256;
               ba[22]=(qcharaddr.unicode())%256;
               str1=CutMACString(2,m_sensorvalstruct[9].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[23]=(qcharaddr.unicode())/256;
               ba[24]=(qcharaddr.unicode())%256;
               str1=CutMACString(3,m_sensorvalstruct[9].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[25]=(qcharaddr.unicode())/256;
               ba[26]=(qcharaddr.unicode())%256;
               str1=CutMACString(4,m_sensorvalstruct[9].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[27]=(qcharaddr.unicode())/256;
               ba[28]=(qcharaddr.unicode())%256;

            }
           break;
        }
        case 0x22://kongqizhiliang
        {
            ba[4]=0x22;
            if((QString::compare(m_sensorvalstruct[10].longaddr,"NULL")!=0)&&(QString::compare(m_sensorvalstruct[10].highval,"NULL")!=0))
            {
               ba[1]=0x01;
               qcharaddr=m_sensorvalstruct[10].longaddr.toInt(&ok,16);
               ba[2]=(qcharaddr.unicode())/256;
               ba[3]=(qcharaddr.unicode())%256;
               int i=m_sensorvalstruct[10].highval.toInt(&ok,10);
               if(i==0)
               {
                   ba[20]=0x01;
               }
               if(i==1)
               {
                   ba[20]=0x00;
               }
               str1=CutMACString(1,m_sensorvalstruct[10].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[21]=(qcharaddr.unicode())/256;
               ba[22]=(qcharaddr.unicode())%256;
               str1=CutMACString(2,m_sensorvalstruct[10].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[23]=(qcharaddr.unicode())/256;
               ba[24]=(qcharaddr.unicode())%256;
               str1=CutMACString(3,m_sensorvalstruct[10].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[25]=(qcharaddr.unicode())/256;
               ba[26]=(qcharaddr.unicode())%256;
               str1=CutMACString(4,m_sensorvalstruct[10].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[27]=(qcharaddr.unicode())/256;
               ba[28]=(qcharaddr.unicode())%256;
            }
           break;
        }
        case 0x23://eryanghuatan
        {
            ba[4]=0x23;
            if((QString::compare(m_sensorvalstruct[11].longaddr,"NULL")!=0)&&(QString::compare(m_sensorvalstruct[11].highval,"NULL")!=0))
            {
               ba[1]=0x01;
               qcharaddr=m_sensorvalstruct[11].longaddr.toInt(&ok,16);
               ba[2]=(qcharaddr.unicode())/256;
               ba[3]=(qcharaddr.unicode())%256;
               char i=(char)m_sensorvalstruct[11].highval.toInt(&ok,16);
               if(i==0)
               {
                   ba[20]=i;
               }
               if(i==1)
               {
                   ba[20]=i;
               }
               str1=CutMACString(1,m_sensorvalstruct[11].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[21]=(qcharaddr.unicode())/256;
               ba[22]=(qcharaddr.unicode())%256;
               str1=CutMACString(2,m_sensorvalstruct[11].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[23]=(qcharaddr.unicode())/256;
               ba[24]=(qcharaddr.unicode())%256;
               str1=CutMACString(3,m_sensorvalstruct[11].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[25]=(qcharaddr.unicode())/256;
               ba[26]=(qcharaddr.unicode())%256;
               str1=CutMACString(4,m_sensorvalstruct[11].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[27]=(qcharaddr.unicode())/256;
               ba[28]=(qcharaddr.unicode())%256;
            }
           break;
        }
        case 0x09://qiti
        {
            ba[4]=0x09;
            if((QString::compare(m_sensorvalstruct[12].longaddr,"NULL")!=0)&&(QString::compare(m_sensorvalstruct[12].highval,"NULL")!=0))
            {
               ba[1]=0x01;
               qcharaddr=m_sensorvalstruct[12].longaddr.toInt(&ok,16);
               ba[2]=(qcharaddr.unicode())/256;
               ba[3]=(qcharaddr.unicode())%256;
               int i=m_sensorvalstruct[12].highval.toInt(&ok,10);
               if(i==0)
               {
                   ba[20]=0x00;
               }
               if(i==1)
               {
                   ba[20]=0x01;
               }
               str1=CutMACString(1,m_sensorvalstruct[12].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[21]=(qcharaddr.unicode())/256;
               ba[22]=(qcharaddr.unicode())%256;
               str1=CutMACString(2,m_sensorvalstruct[12].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[23]=(qcharaddr.unicode())/256;
               ba[24]=(qcharaddr.unicode())%256;
               str1=CutMACString(3,m_sensorvalstruct[12].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[25]=(qcharaddr.unicode())/256;
               ba[26]=(qcharaddr.unicode())%256;
               str1=CutMACString(4,m_sensorvalstruct[12].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[27]=(qcharaddr.unicode())/256;
               ba[28]=(qcharaddr.unicode())%256;
              }
           break;
        }
        case 0x21://yanwu
        {
            ba[4]=0x21;
            if((QString::compare(m_sensorvalstruct[13].longaddr,"NULL")!=0)&&(QString::compare(m_sensorvalstruct[13].highval,"NULL")!=0))
            {
               ba[1]=0x01;
               qcharaddr=m_sensorvalstruct[13].longaddr.toInt(&ok,16);
               ba[2]=(qcharaddr.unicode())/256;
               ba[3]=(qcharaddr.unicode())%256;
               int i=m_sensorvalstruct[13].highval.toInt(&ok,10);
               if(i==0)
               {
                   ba[20]=0x00;
               }
               if(i==1)
               {
                   ba[20]=0x01;
               }
               str1=CutMACString(1,m_sensorvalstruct[13].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[21]=(qcharaddr.unicode())/256;
               ba[22]=(qcharaddr.unicode())%256;
               str1=CutMACString(2,m_sensorvalstruct[13].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[23]=(qcharaddr.unicode())/256;
               ba[24]=(qcharaddr.unicode())%256;
               str1=CutMACString(3,m_sensorvalstruct[13].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[25]=(qcharaddr.unicode())/256;
               ba[26]=(qcharaddr.unicode())%256;
               str1=CutMACString(4,m_sensorvalstruct[13].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[27]=(qcharaddr.unicode())/256;
               ba[28]=(qcharaddr.unicode())%256;
              }
        break;
        }
        case 0x14://renti
        {
            ba[4]=0x14;
            if((QString::compare(m_sensorvalstruct[14].longaddr,"NULL")!=0)&&(QString::compare(m_sensorvalstruct[14].highval,"NULL")!=0))
            {
               ba[1]=0x01;
               qcharaddr=m_sensorvalstruct[14].longaddr.toInt(&ok,16);
               ba[2]=(qcharaddr.unicode())/256;
               ba[3]=(qcharaddr.unicode())%256;
               int i=m_sensorvalstruct[14].highval.toInt(&ok,10);
               if(i==0)
               {
                   ba[20]=0x00;
               }
               if(i==1)
               {
                   ba[20]=0x01;
               }
               str1=CutMACString(1,m_sensorvalstruct[14].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[21]=(qcharaddr.unicode())/256;
               ba[22]=(qcharaddr.unicode())%256;
               str1=CutMACString(2,m_sensorvalstruct[14].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[23]=(qcharaddr.unicode())/256;
               ba[24]=(qcharaddr.unicode())%256;
               str1=CutMACString(3,m_sensorvalstruct[14].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[25]=(qcharaddr.unicode())/256;
               ba[26]=(qcharaddr.unicode())%256;
               str1=CutMACString(4,m_sensorvalstruct[14].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[27]=(qcharaddr.unicode())/256;
               ba[28]=(qcharaddr.unicode())%256;
               break;
            }
        }
        case 0x43://menci
        {
            ba[4]=0x43;
            if((QString::compare(m_sensorvalstruct[15].longaddr,"NULL")!=0)&&(QString::compare(m_sensorvalstruct[15].highval,"NULL")!=0))
            {
               ba[1]=0x01;
               qcharaddr=m_sensorvalstruct[15].longaddr.toInt(&ok,16);
               ba[2]=(qcharaddr.unicode())/256;
               ba[3]=(qcharaddr.unicode())%256;
               int i=m_sensorvalstruct[15].highval.toInt(&ok,10);
               if(i==0)
               {
                   ba[20]=0x00;
               }
               if(i==1)
               {
                   ba[20]=0x01;
               }
               str1=CutMACString(1,m_sensorvalstruct[15].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[21]=(qcharaddr.unicode())/256;
               ba[22]=(qcharaddr.unicode())%256;
               str1=CutMACString(2,m_sensorvalstruct[15].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[23]=(qcharaddr.unicode())/256;
               ba[24]=(qcharaddr.unicode())%256;
               str1=CutMACString(3,m_sensorvalstruct[15].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[25]=(qcharaddr.unicode())/256;
               ba[26]=(qcharaddr.unicode())%256;
               str1=CutMACString(4,m_sensorvalstruct[15].longaddr);
               qcharaddr=str1.toInt(&ok,16);
               ba[27]=(qcharaddr.unicode())/256;
               ba[28]=(qcharaddr.unicode())%256;
            }
        break;
        }
    }
    clientConnection->write(ba);

}

void AutoControl_V2::HexIntToNetwork( bool is64, char *str, char *result)
{
    short tmps;
    int num,index;
    if( is64 == true )
    {
        memset(result,0,8);
        num = 8;
        index=0;
    }
    else
    {
        memset(result,0,4);
        num = 4;
        index = 4;
    }
    for(int i=0;i<num;i++)
    {

        short hchar=str[i*2],lchar=str[i*2+1];

        if( hchar<'A' )
            hchar = hchar-48;
        else if(hchar>'Z')
            hchar = hchar-'a'+10;
        else
            hchar = hchar-'A'+10;

        if( lchar<'A' )
            lchar = lchar-48;
        else if(lchar>'Z')
            lchar = lchar-'a'+10;
        else
            lchar = lchar-'A'+10;

        tmps = ( (hchar<<4) | lchar);
        result[index] = tmps;


        index++;
    }
}

QString AutoControl_V2::CutMacAddrStr(QString str,int itype)
{

    QString sval="";
    switch(itype)
    {
      case 1:
      {
          sval=str.mid(0,2);
          break;
      }
      case 2:
      {
          sval=str.mid(3,2);
          break;
      }
      case 3:
      {
          sval=str.mid(6,2);
          break;
      }
      case 4:
      {
          sval=str.mid(9,2);
          break;
      }
      case 5:
      {
         sval=str.mid(12,2);
          break;
      }
      case 6:
      {
         sval=str.mid(15,2);
         break;
      }
      default:
      {
         sval=str;
          break;
      }
    }
    return sval;
}

char AutoControl_V2::strtohex(QString str)
{
    unsigned char cdata=0x00;
    bool ok=1;
    cdata=(unsigned char)str.toInt(&ok,16);
}

QString AutoControl_V2::CharToStr(int itype,char cval1,char cval2)//
{
    QString str="";QString str1="";
    switch(itype)
    {
        case 1:
       {
          str.sprintf("%02x",cval1);
          break;
       }
       case 2:
       {
         str.sprintf("%02x",cval1);
         str1.sprintf("%02x",cval2);
         str=str+str1;
         break;
       }
       case 3:
       {

        str.sprintf("%02d",cval1);
        str1.sprintf(".%02d",cval2);
        str=str+str1;
        break;
       }
       case 4:
       {
          str.sprintf("%d",cval1);
          break;
       }
       case 5:
       {
          str.sprintf("%c",cval1);
          break;
       }
    }
    return str;
}

QString AutoControl_V2::FindMacAddrByNameNoDir(QString str,QString dir)//
{
    for(int j=0;j<ui->tableWidget->rowCount();j++)
    {
        QTableWidgetItem *item = ui->tableWidget->item(j,0);
        QTableWidgetItem *item2 = ui->tableWidget->item(j,1);
        if((QString::compare(str,item->text())==0)&&(QString::compare(dir,item2->text())!=0))
        {
            QTableWidgetItem *item1 = ui->tableWidget->item(j,3);
            return item1->text();
        }
    }
    return "NULL";
}

bool AutoControl_V2::JudgeAddrIsTheSame(int itype,QString str)//
{
    switch(itype)
    {
       case 1:
       {
        for(int j=0;j<(m_set->m_add->m_table)->rowCount();j++)
        {
            QTableWidgetItem *item = (m_set->m_add->m_table)->item(j,2);

            if(QString::compare(str,item->text())==0)
            {
                return true;
            }
        }
        break;
       }
       case 2:
       {
          for(int j=0;j<(m_set->m_add->m_irdev->m_table)->rowCount();j++)
          {
            QTableWidgetItem *item = (m_set->m_add->m_irdev->m_table)->item(j,2);
            if(QString::compare(str,item->text())==0)
            {
                return true;
            }
         }
          break;
       }
       case 3:
       {
        for(int j=0;j<(m_set->m_add->m_threefive->m_table)->rowCount();j++)
        {
          QTableWidgetItem *item = (m_set->m_add->m_threefive->m_table)->item(j,2);
          if(QString::compare(str,item->text())==0)
          {
              return true;
          }
        }
          break;
       }
        case 4:
        {
         for(int j=0;j<(m_set->m_add->m_zhiwen->m_table)->rowCount();j++)
         {
           QTableWidgetItem *item = (m_set->m_add->m_zhiwen->m_table)->item(j,2);
           if(QString::compare(str,item->text())==0)
           {
               return true;
           }
         }
           break;
        }
    }
    return false;
}

QString AutoControl_V2::FindMacAddrByName(QString str)//
{
    for(int j=0;j<ui->tableWidget->rowCount();j++)
    {
        QTableWidgetItem *item = ui->tableWidget->item(j,0);
        if(QString::compare(str,item->text())==0)
        {
            QTableWidgetItem *item1 = ui->tableWidget->item(j,3);
            return item1->text();
        }
    }
    return "";
}

bool AutoControl_V2::JudgeIsAddTable(QString str)//
{
    for(int j=0;j<ui->tableWidget->rowCount();j++)
    {
        QTableWidgetItem *item = ui->tableWidget->item(j,3);
        if(QString::compare(str,item->text())==0)
        {
            return true;
        }
    }
    return false;
}

QString AutoControl_V2::RetDirByMacAddr(QString addr)
{
    for(int j=0;j<ui->tableWidget->rowCount();j++)
    {
        QTableWidgetItem *item = ui->tableWidget->item(j,3);
        if(QString::compare(addr,item->text())==0)
        {
            item = ui->tableWidget->item(j,1);
            return item->text();
        }
    }
    return "NULL";
}

void AutoControl_V2::on_pushButton_clicked()//add
{
//    m_control->whichdialog=1;

    this->hide();
    this->m_set = new Set();
    this->m_set->show();
    this->m_set->parent = this;
    return;
}

void AutoControl_V2::on_pushButton_2_clicked()//on
{
    if(tablerow>=0)
    {
       QTableWidgetItem *item = ui->tableWidget->item(tablerow, 0);
       if(item->text().contains(trUtf8("设备1"))||item->text().contains(trUtf8("设备2"))||item->text().contains(trUtf8("喷水"))||item->text().contains(trUtf8("灯"))||item->text().contains(trUtf8("喷雾"))||item->text().contains(trUtf8("地热"))||item->text().contains(trUtf8("滴灌"))||item->text().contains(trUtf8("通风扇"))||item->text().contains(trUtf8("喷雾器"))||item->text().contains(trUtf8("电饭煲"))||item->text().contains(trUtf8("净化器"))||item->text().contains(trUtf8("电源"))||item->text().contains(trUtf8("换气扇"))||item->text().contains(trUtf8("喷淋"))||item->text().contains(trUtf8("浇花"))||item->text().contains(trUtf8("加湿器"))||item->text().contains(trUtf8("饮水机")))
       {

           QTableWidgetItem *item1 = ui->tableWidget->item(tablerow, 2);
           QTableWidgetItem *item2 = ui->tableWidget->item(tablerow, 3);

           KG_ON(item1->text(),item2->text());
           return;
       }
       if(item->text().contains(trUtf8("窗帘")))
       {
           QTableWidgetItem *item1 = ui->tableWidget->item(tablerow, 2);
           QTableWidgetItem *item2 = ui->tableWidget->item(tablerow, 3);

           CUR_ON(item1->text(),item2->text());
           return;
       }
       if(item->text().contains(trUtf8("调光")))
       {
           QTableWidgetItem *item1 = ui->tableWidget->item(tablerow, 2);
           QTableWidgetItem *item2 = ui->tableWidget->item(tablerow, 3);
           if(initval<0x75)
           {
              initval=initval+0x10;
           }
           if(initval>=0x75)
           {
              initval=0x75;
           }
           SUN_ON(item1->text(),item2->text(),initval);
           return;
       }
       if(item->text().contains(trUtf8("雨蓬")))
       {
           QTableWidgetItem *item1 = ui->tableWidget->item(tablerow, 2);
           QTableWidgetItem *item2 = ui->tableWidget->item(tablerow, 3);
           YuPengOn(item1->text(),item2->text());
           return;
       }
    }
    else
    {
        ui->label->setText(trUtf8("您未选择节点名称"));

    }

}

void AutoControl_V2::on_pushButton_3_clicked()//off
{
    if(tablerow>=0)
    {
        QTableWidgetItem *item = ui->tableWidget->item(tablerow, 0);
        if(item->text().contains(trUtf8("窗帘")))
        {
            QTableWidgetItem *item1 = ui->tableWidget->item(tablerow, 2);
            QTableWidgetItem *item2 = ui->tableWidget->item(tablerow, 3);

            CUR_OFF(item1->text(),item2->text());
            return;
        }
        if(item->text().contains(trUtf8("调光")))
        {
            QTableWidgetItem *item1 = ui->tableWidget->item(tablerow, 2);
            QTableWidgetItem *item2 = ui->tableWidget->item(tablerow, 3);
            if(initval>0x00)
            {
               initval=initval-0x10;
            }
            if(initval<=0x00)
            {
               initval=0x00;
            }

            SUN_OFF(item1->text(),item2->text(),initval);
            return;
        }
        if(item->text().contains(trUtf8("雨蓬")))
        {
            QTableWidgetItem *item1 = ui->tableWidget->item(tablerow, 2);
            QTableWidgetItem *item2 = ui->tableWidget->item(tablerow, 3);

            YuPengStop(item1->text(),item2->text());
            return;
        }
        if(item->text().contains(trUtf8("投影机"))||item->text().contains(trUtf8("电视"))||item->text().contains(trUtf8("空调"))||item->text().contains(trUtf8("空调扇"))||item->text().contains(trUtf8("音箱"))||item->text().contains(trUtf8("DVD")))
        {
           QTableWidgetItem *item1 = ui->tableWidget->item(tablerow, 1);
           for(int i=0;i<iirtructlength;i++)
           {
               if(QString::compare(item->text(),m_irstruct[i].name)==0&&QString::compare(item1->text(),m_irstruct[i].function)==0)
               {
                  Ir_Send(m_irstruct[i].shortaddr,m_irstruct[i].longaddr,m_irstruct[i].code);
                  return;
               }
           }
        }
        if(item->text().contains(trUtf8("设备1"))||item->text().contains(trUtf8("设备2"))||item->text().contains(trUtf8("喷水"))||item->text().contains(trUtf8("灯"))||item->text().contains(trUtf8("喷雾"))||item->text().contains(trUtf8("地热"))||item->text().contains(trUtf8("滴灌"))||item->text().contains(trUtf8("通风扇"))||item->text().contains(trUtf8("喷雾器"))||item->text().contains(trUtf8("电饭煲"))||item->text().contains(trUtf8("净化器"))||item->text().contains(trUtf8("电源"))||item->text().contains(trUtf8("换气扇"))||item->text().contains(trUtf8("喷淋"))||item->text().contains(trUtf8("浇花"))||item->text().contains(trUtf8("加湿器"))||item->text().contains(trUtf8("饮水机")))
        {
            QTableWidgetItem *item1 = ui->tableWidget->item(tablerow, 2);
            QTableWidgetItem *item2 = ui->tableWidget->item(tablerow, 3);
            KG_OFF(item1->text(),item2->text());
            return;
        }
        if(item->text().contains(trUtf8("门锁")))
        {
            QTableWidgetItem *item1 = ui->tableWidget->item(tablerow, 2);
            QTableWidgetItem *item2 = ui->tableWidget->item(tablerow, 3);

            MenSuo_ON(item1->text(),item2->text());
            return;
        }
        if(item->text().contains(trUtf8("指纹")))
        {
            QTableWidgetItem *item1 = ui->tableWidget->item(tablerow, 2);
            QTableWidgetItem *item2 = ui->tableWidget->item(tablerow, 3);
            ZhiWen_Sousuo(item1->text(),item2->text());
            return;
        }
        if(item->text().contains(trUtf8("PH"))==true)
        {
            QTableWidgetItem *item1 = ui->tableWidget->item(tablerow, 2);
            QTableWidgetItem *item2 = ui->tableWidget->item(tablerow, 3);
            Send_PHZhi(item1->text(),item2->text());
            return;

        }
    }
    else
    {
        ui->label->setText(trUtf8("您未选择设备号"));
    }
}

void AutoControl_V2::on_pushButton_4_clicked()//ting
{
    QTableWidgetItem *item = ui->tableWidget->item(tablerow, 0);
    if(item->text().contains(trUtf8("雨蓬")))
    {
       QTableWidgetItem *item1 = ui->tableWidget->item(tablerow, 2);
       QTableWidgetItem *item2 = ui->tableWidget->item(tablerow, 3);

       YuPengBettween(item1->text(),item2->text());
       return;
    }
}

void AutoControl_V2::on_tableWidget_cellClicked(int row, int column)
{
    ui->label->setText("");
    tablerow=row;
    ui->pushButton_2->setText(trUtf8("打开"));
    ui->pushButton_3->setText(trUtf8("关闭"));
    ui->pushButton_2->setVisible(true);
    ui->pushButton_3->setVisible(true);
    ui->pushButton_4->setVisible(false);
    QTableWidgetItem *item = ui->tableWidget->item(tablerow, 0);
    if(item->text().contains(trUtf8("二氧化碳"))==true||item->text().contains(trUtf8("高频"))==true||item->text().contains(trUtf8("超高频"))==true||item->text().contains(trUtf8("氧气"))==true||item->text().contains(trUtf8("按键"))==true||item->text().contains(trUtf8("烟雾"))==true||item->text().contains(trUtf8("门磁"))==true||item->text().contains(trUtf8("人体"))==true||item->text().contains(trUtf8("气体"))==true||item->text().contains(trUtf8("温度"))==true||item->text().contains(trUtf8("温湿度"))==true||item->text().contains(trUtf8("光照"))==true||item->text().contains(trUtf8("电子称"))==true||item->text().contains(trUtf8("噪声"))==true||item->text().contains(trUtf8("震动"))==true||item->text().contains(trUtf8("雨滴"))==true||item->text().contains(trUtf8("光线"))==true||item->text().contains(trUtf8("气压"))==true||item->text().contains(trUtf8("气体"))==true||item->text().contains(trUtf8("空气质量"))==true)
    {
        ui->pushButton_2->setVisible(false);
        ui->pushButton_3->setVisible(false);
        ui->pushButton_4->setVisible(false);
        return;
    }
    if(item->text().contains(trUtf8("投影机"))==true||item->text().contains(trUtf8("电视"))==true||item->text().contains(trUtf8("空调"))==true||item->text().contains(trUtf8("空调扇"))==true||item->text().contains(trUtf8("音箱"))==true||item->text().contains(trUtf8("DVD"))==true)
    {
        ui->pushButton_2->setVisible(false);
        ui->pushButton_3->setVisible(true);
        ui->pushButton_4->setVisible(false);
        ui->pushButton_3->setText(trUtf8("发送"));
        return;
    }
    if(item->text().contains(trUtf8("雨蓬"))==true)
    {
        ui->pushButton_2->setText(trUtf8("雨蓬打开"));
        ui->pushButton_3->setText(trUtf8("雨蓬关闭"));
        ui->pushButton_4->setVisible(true);
        ui->pushButton_4->setText(trUtf8("雨蓬停"));
        return;
    }
    if(item->text().contains(trUtf8("调光"))==true)
    {
        ui->pushButton_2->setText(trUtf8("渐亮"));
        ui->pushButton_3->setText(trUtf8("渐暗"));
        ui->pushButton_4->setVisible(false);
        return;
    }
    if(item->text().contains(trUtf8("小车"))==true)
    {
       QTableWidgetItem *item1 = ui->tableWidget->item(tablerow, 2);
       mcaraddr=item1->text();
       item1 = ui->tableWidget->item(tablerow, 3);
       maccaraddr=item1->text();
       this->hide();
       this->m_car = new SmartCar();
       this->m_car->show();
       this->m_car->parent = this;
       return;
    }
    if(item->text().contains(trUtf8("演示板"))==true)
    {
        QTableWidgetItem *item1 = ui->tableWidget->item(tablerow, 2);
        stryanshibanaddr=item1->text();
        item1 = ui->tableWidget->item(tablerow, 3);
        stryanshibanmacaddr=item1->text();
        this->hide();
        this->m_yanshiban = new YanShiBan();
        this->m_yanshiban->show();
        this->m_yanshiban->parent = this;
       return;
    }
    if(item->text().contains(trUtf8("智能货架"))==true)
    {
       whichdialog=12;
       ui->pushButton_2->setVisible(false);
       ui->pushButton_3->setVisible(false);
       ui->pushButton_4->setVisible(false);
       this->hide();
       this->m_smartshelf = new smartshelf();
       this->m_smartshelf->show();
       this->m_smartshelf->parent = this;
       return;
    }
    if(item->text().contains(trUtf8("门锁"))==true)
    {
        ui->pushButton_2->setVisible(false);
        ui->pushButton_3->setVisible(true);
        ui->pushButton_4->setVisible(false);
        ui->pushButton_3->setText(trUtf8("打开"));
        return;
    }
    if(item->text().contains(trUtf8("指纹"))==true)
    {
        ui->pushButton_2->setVisible(false);
        ui->pushButton_3->setVisible(true);
        ui->pushButton_4->setVisible(false);
        ui->pushButton_3->setText(trUtf8("搜索"));
        return;

    }
    if(item->text().contains(trUtf8("PH"))==true)
    {
        ui->pushButton_2->setVisible(false);
        ui->pushButton_3->setVisible(true);
        ui->pushButton_4->setVisible(false);
        ui->pushButton_3->setText(trUtf8("采集PH值"));
        return;
    }
}

QString AutoControl_V2::CutMACString(int itype,QString str)  //取MAC地址数据函数
{
    QString sret="";

    if(str.length()==16)
    {
        switch(itype)
        {
           case 1:
           {
               sret=str.mid(0,4);
               break;
           }
           case 2:
           {
               sret=str.mid(4,4);
               break;
           }
           case 3:
           {
               sret=str.mid(8,4);
               break;
           }
           case 4:
           {
               sret=str.mid(12,4);
               break;
           }
        }

    }
    return sret;

}

void AutoControl_V2::KG_ON(QString addr,QString macaddr)//（短地址 ，MAC节点地址）
{
     bool ok=1;
     QString str1="";
     qcharaddr=addr.toInt(&ok,16);
     send[2]=(qcharaddr.unicode())/256;
     send[3]=(qcharaddr.unicode())%256;
     send[6]='K';
     send[7]=(qcharaddr.unicode())/256;
     send[8]=(qcharaddr.unicode())%256;
     send[9]=0xDD;
     send[10]=0x01;
     send[11]=0xAA;
     str1=CutMACString(1,macaddr);
     qcharaddr=str1.toInt(&ok,16);
     send[13]=(qcharaddr.unicode())/256;
     send[14]=(qcharaddr.unicode())%256;
     str1=CutMACString(2,macaddr);
     qcharaddr=str1.toInt(&ok,16);
     send[15]=(qcharaddr.unicode())/256;
     send[16]=(qcharaddr.unicode())%256;
     str1=CutMACString(3,macaddr);
     qcharaddr=str1.toInt(&ok,16);
     send[17]=(qcharaddr.unicode())/256;
     send[18]=(qcharaddr.unicode())%256;
     str1=CutMACString(4,macaddr);
     qcharaddr=str1.toInt(&ok,16);
     send[19]=(qcharaddr.unicode())/256;
     send[20]=(qcharaddr.unicode())%256;
     m_Com->write(send,21);
     ui->label->setText(trUtf8("继电器开发送了"));
}

void AutoControl_V2::KG_OFF(QString addr,QString macaddr)
{
    bool ok=1;QString str1="";
    qcharaddr=addr.toInt(&ok,16);
    send[2]=(qcharaddr.unicode())/256;
    send[3]=(qcharaddr.unicode())%256;
    send[6]='K';
    send[7]=(qcharaddr.unicode())/256;
    send[8]=(qcharaddr.unicode())%256;
    send[9]=0xDD;
    send[10]=0x01;
    send[11]=0xBB;
    str1=CutMACString(1,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[13]=(qcharaddr.unicode())/256;
    send[14]=(qcharaddr.unicode())%256;
    str1=CutMACString(2,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[15]=(qcharaddr.unicode())/256;
    send[16]=(qcharaddr.unicode())%256;
    str1=CutMACString(3,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[17]=(qcharaddr.unicode())/256;
    send[18]=(qcharaddr.unicode())%256;
    str1=CutMACString(4,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[19]=(qcharaddr.unicode())/256;
    send[20]=(qcharaddr.unicode())%256;
    m_Com->write(send,21);
    ui->label->setText(trUtf8("继电器关发送了"));


}

void AutoControl_V2::CUR_ON(QString addr, QString macaddr)
{
   bool ok=1;QString str1="";
   qcharaddr=addr.toInt(&ok,16);
   send[2]=(qcharaddr.unicode())/256;
   send[3]=(qcharaddr.unicode())%256;
   send[6]='H';
   send[7]=(qcharaddr.unicode())/256;
   send[8]=(qcharaddr.unicode())%256;
   send[9]=0xDD;
   send[10]=0xC0;
   send[11]=0xAA;
   str1=CutMACString(1,macaddr);
   qcharaddr=str1.toInt(&ok,16);
   send[13]=(qcharaddr.unicode())/256;
   send[14]=(qcharaddr.unicode())%256;
   str1=CutMACString(2,macaddr);
   qcharaddr=str1.toInt(&ok,16);
   send[15]=(qcharaddr.unicode())/256;
   send[16]=(qcharaddr.unicode())%256;
   str1=CutMACString(3,macaddr);
   qcharaddr=str1.toInt(&ok,16);
   send[17]=(qcharaddr.unicode())/256;
   send[18]=(qcharaddr.unicode())%256;
   str1=CutMACString(4,macaddr);
   qcharaddr=str1.toInt(&ok,16);
   send[19]=(qcharaddr.unicode())/256;
   send[20]=(qcharaddr.unicode())%256;
   m_Com->write(send,21);
   ui->label->setText(trUtf8("窗帘开发送了"));

}

void AutoControl_V2::CUR_OFF(QString addr, QString macaddr)
{
    bool ok=1;QString str1="";
    qcharaddr=addr.toInt(&ok,16);
    send[2]=(qcharaddr.unicode())/256;
    send[3]=(qcharaddr.unicode())%256;
    send[6]='H';
    send[7]=(qcharaddr.unicode())/256;
    send[8]=(qcharaddr.unicode())%256;
    send[9]=0xDD;
    send[10]=0xC0;
    send[11]=0xBB;
    str1=CutMACString(1,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[13]=(qcharaddr.unicode())/256;
    send[14]=(qcharaddr.unicode())%256;
    str1=CutMACString(2,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[15]=(qcharaddr.unicode())/256;
    send[16]=(qcharaddr.unicode())%256;
    str1=CutMACString(3,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[17]=(qcharaddr.unicode())/256;
    send[18]=(qcharaddr.unicode())%256;
    str1=CutMACString(4,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[19]=(qcharaddr.unicode())/256;
    send[20]=(qcharaddr.unicode())%256;
    m_Com->write(send,21);
    ui->label->setText(trUtf8("窗帘关发送了"));

}

void AutoControl_V2::SUN_ON(QString addr, QString macaddr,char initval)
{
       bool ok=1;QString str1="";
       qcharaddr=addr.toInt(&ok,16);
       send[2]=(qcharaddr.unicode())/256;
       send[3]=(qcharaddr.unicode())%256;
       send[6]='S';
       send[7]=(qcharaddr.unicode())/256;
       send[8]=(qcharaddr.unicode())%256;
       send[9]=0xAB;
       send[10]=0xB2;
       send[11]=initval;
       str1=CutMACString(1,macaddr);
       qcharaddr=str1.toInt(&ok,16);
       send[13]=(qcharaddr.unicode())/256;
       send[14]=(qcharaddr.unicode())%256;
       str1=CutMACString(2,macaddr);
       qcharaddr=str1.toInt(&ok,16);
       send[15]=(qcharaddr.unicode())/256;
       send[16]=(qcharaddr.unicode())%256;
       str1=CutMACString(3,macaddr);
       qcharaddr=str1.toInt(&ok,16);
       send[17]=(qcharaddr.unicode())/256;
       send[18]=(qcharaddr.unicode())%256;
       str1=CutMACString(4,macaddr);
       qcharaddr=str1.toInt(&ok,16);
       send[19]=(qcharaddr.unicode())/256;
       send[20]=(qcharaddr.unicode())%256;
       m_Com->write(send,21);
       ui->label->setText(trUtf8("调光亮发送了"));
       if(initval==0x75)
       {
           ui->label->setText(trUtf8("灯都最亮了，您不能在点亮了啊"));
           return;
       }

}

void AutoControl_V2::SUN_OFF(QString addr, QString macaddr,char initval)
{
       bool ok=1;QString str1="";
       qcharaddr=addr.toInt(&ok,16);
       send[2]=(qcharaddr.unicode())/256;
       send[3]=(qcharaddr.unicode())%256;
       send[6]='S';
       send[7]=(qcharaddr.unicode())/256;
       send[8]=(qcharaddr.unicode())%256;
       send[9]=0xAB;
       send[10]=0xB2;
       send[11]=initval;
       str1=CutMACString(1,macaddr);
       qcharaddr=str1.toInt(&ok,16);
       send[13]=(qcharaddr.unicode())/256;
       send[14]=(qcharaddr.unicode())%256;
       str1=CutMACString(2,macaddr);
       qcharaddr=str1.toInt(&ok,16);
       send[15]=(qcharaddr.unicode())/256;
       send[16]=(qcharaddr.unicode())%256;
       str1=CutMACString(3,macaddr);
       qcharaddr=str1.toInt(&ok,16);
       send[17]=(qcharaddr.unicode())/256;
       send[18]=(qcharaddr.unicode())%256;
       str1=CutMACString(4,macaddr);
       qcharaddr=str1.toInt(&ok,16);
       send[19]=(qcharaddr.unicode())/256;
       send[20]=(qcharaddr.unicode())%256;
       m_Com->write(send,21);
       ui->label->setText(trUtf8("调光暗发送了"));
       if(initval==0x00)
       {
           ui->label->setText(trUtf8("灯都关了，您不能在点暗了啊"));
           return;
       }



}

void AutoControl_V2::Ir_Send(QString addr,QString macaddr,QString code)//hongwai fasong
{
   bool ok=1;QString str1="";
   qcharaddr=addr.toInt(&ok,16);
   sendir[2]=(qcharaddr.unicode())/256;
   sendir[3]=(qcharaddr.unicode())%256;
   sendir[6]='P';
   sendir[7]=(qcharaddr.unicode())/256;
   sendir[8]=(qcharaddr.unicode())%256;
   sendir[9]=0x81;
   sendir[10]=code.toInt(&ok,16);
   str1=CutMACString(1,macaddr);
   qcharaddr=str1.toInt(&ok,16);
   sendir[13]=(qcharaddr.unicode())/256;
   sendir[14]=(qcharaddr.unicode())%256;
   str1=CutMACString(2,macaddr);
   qcharaddr=str1.toInt(&ok,16);
   sendir[15]=(qcharaddr.unicode())/256;
   sendir[16]=(qcharaddr.unicode())%256;
   str1=CutMACString(3,macaddr);
   qcharaddr=str1.toInt(&ok,16);
   sendir[17]=(qcharaddr.unicode())/256;
   sendir[18]=(qcharaddr.unicode())%256;
   str1=CutMACString(4,macaddr);
   qcharaddr=str1.toInt(&ok,16);
   sendir[19]=(qcharaddr.unicode())/256;
   sendir[20]=(qcharaddr.unicode())%256;
   m_Com->write(sendir,21);

   ui->label->setText(trUtf8("红外发送了...."));

}

void AutoControl_V2::Car_AutoXun(QString caraddr,QString macaddr)
{
    bool ok=1;QString str1="";
    qcharaddr=caraddr.toInt(&ok,16);
    send[2]=(qcharaddr.unicode())/256;
    send[3]=(qcharaddr.unicode())%256;
    send[6]=0x06;
    send[7]=(qcharaddr.unicode())/256;
    send[8]=(qcharaddr.unicode())%256;
    send[9]=0xDD;
    send[10]=0x01;
    send[11]=0x00;
    str1=CutMACString(1,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[13]=(qcharaddr.unicode())/256;
    send[14]=(qcharaddr.unicode())%256;
    str1=CutMACString(2,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[15]=(qcharaddr.unicode())/256;
    send[16]=(qcharaddr.unicode())%256;
    str1=CutMACString(3,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[17]=(qcharaddr.unicode())/256;
    send[18]=(qcharaddr.unicode())%256;
    str1=CutMACString(4,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[19]=(qcharaddr.unicode())/256;
    send[20]=(qcharaddr.unicode())%256;
    m_Com->write(send,21);
    ui->label->setText(trUtf8("小车自动寻迹"));


}

void AutoControl_V2::Car_Stop(QString caraddr,QString macaddr)
{
    bool ok=1;QString str1="";
    qcharaddr=caraddr.toInt(&ok,16);
    send[2]=(qcharaddr.unicode())/256;
    send[3]=(qcharaddr.unicode())%256;
    send[6]=0x06;
    send[7]=(qcharaddr.unicode())/256;
    send[8]=(qcharaddr.unicode())%256;
    send[9]=0xDD;
    send[10]=0x00;
    send[11]=0x00;
    str1=CutMACString(1,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[13]=(qcharaddr.unicode())/256;
    send[14]=(qcharaddr.unicode())%256;
    str1=CutMACString(2,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[15]=(qcharaddr.unicode())/256;
    send[16]=(qcharaddr.unicode())%256;
    str1=CutMACString(3,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[17]=(qcharaddr.unicode())/256;
    send[18]=(qcharaddr.unicode())%256;
    str1=CutMACString(4,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[19]=(qcharaddr.unicode())/256;
    send[20]=(qcharaddr.unicode())%256;
    m_Com->write(send,21);

    ui->label->setText(trUtf8("小车停止"));

}

void AutoControl_V2::Car_Go(QString caraddr,QString macaddr)
{
    bool ok=1;QString str1="";
    qcharaddr=caraddr.toInt(&ok,16);
    send[2]=(qcharaddr.unicode())/256;
    send[3]=(qcharaddr.unicode())%256;
    send[6]=0x06;
    send[7]=(qcharaddr.unicode())/256;
    send[8]=(qcharaddr.unicode())%256;
    send[9]=0xDD;
    send[10]=0x02;
    send[11]=0x00;
    str1=CutMACString(1,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[13]=(qcharaddr.unicode())/256;
    send[14]=(qcharaddr.unicode())%256;
    str1=CutMACString(2,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[15]=(qcharaddr.unicode())/256;
    send[16]=(qcharaddr.unicode())%256;
    str1=CutMACString(3,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[17]=(qcharaddr.unicode())/256;
    send[18]=(qcharaddr.unicode())%256;
    str1=CutMACString(4,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[19]=(qcharaddr.unicode())/256;
    send[20]=(qcharaddr.unicode())%256;
    m_Com->write(send,21);
    ui->label->setText(trUtf8("小车前进"));

}

void AutoControl_V2::Car_Back(QString caraddr,QString macaddr)
{
    bool ok=1;QString str1="";
    qcharaddr=caraddr.toInt(&ok,16);
    send[2]=(qcharaddr.unicode())/256;
    send[3]=(qcharaddr.unicode())%256;
    send[6]=0x06;
    send[7]=(qcharaddr.unicode())/256;
    send[8]=(qcharaddr.unicode())%256;
    send[9]=0xDD;
    send[10]=0x05;
    send[11]=0x00;
    str1=CutMACString(1,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[13]=(qcharaddr.unicode())/256;
    send[14]=(qcharaddr.unicode())%256;
    str1=CutMACString(2,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[15]=(qcharaddr.unicode())/256;
    send[16]=(qcharaddr.unicode())%256;
    str1=CutMACString(3,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[17]=(qcharaddr.unicode())/256;
    send[18]=(qcharaddr.unicode())%256;
    str1=CutMACString(4,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[19]=(qcharaddr.unicode())/256;
    send[20]=(qcharaddr.unicode())%256;
    m_Com->write(send,21);
    ui->label->setText(trUtf8("小车后退"));

}

void AutoControl_V2::Car_Left(QString caraddr,QString macaddr)
{
    bool ok=1;QString str1="";
    qcharaddr=caraddr.toInt(&ok,16);
    send[2]=(qcharaddr.unicode())/256;
    send[3]=(qcharaddr.unicode())%256;
    send[6]=0x06;
    send[7]=(qcharaddr.unicode())/256;
    send[8]=(qcharaddr.unicode())%256;
    send[9]=0xDD;
    send[10]=0x03;
    send[11]=0x00;
    str1=CutMACString(1,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[13]=(qcharaddr.unicode())/256;
    send[14]=(qcharaddr.unicode())%256;
    str1=CutMACString(2,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[15]=(qcharaddr.unicode())/256;
    send[16]=(qcharaddr.unicode())%256;
    str1=CutMACString(3,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[17]=(qcharaddr.unicode())/256;
    send[18]=(qcharaddr.unicode())%256;
    str1=CutMACString(4,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[19]=(qcharaddr.unicode())/256;
    send[20]=(qcharaddr.unicode())%256;
    m_Com->write(send,21);
    ui->label->setText(trUtf8("小车左转"));

}

void AutoControl_V2::Car_Right(QString caraddr,QString macaddr)
{
    bool ok=1;QString str1="";
    qcharaddr=caraddr.toInt(&ok,16);
    send[2]=(qcharaddr.unicode())/256;
    send[3]=(qcharaddr.unicode())%256;
    send[6]=0x06;
    send[7]=(qcharaddr.unicode())/256;
    send[8]=(qcharaddr.unicode())%256;
    send[9]=0xDD;
    send[10]=0x04;
    send[11]=0x00;
    str1=CutMACString(1,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[13]=(qcharaddr.unicode())/256;
    send[14]=(qcharaddr.unicode())%256;
    str1=CutMACString(2,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[15]=(qcharaddr.unicode())/256;
    send[16]=(qcharaddr.unicode())%256;
    str1=CutMACString(3,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[17]=(qcharaddr.unicode())/256;
    send[18]=(qcharaddr.unicode())%256;
    str1=CutMACString(4,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[19]=(qcharaddr.unicode())/256;
    send[20]=(qcharaddr.unicode())%256;
    m_Com->write(send,21);
    ui->label->setText(trUtf8("小车右转"));

}

void AutoControl_V2::YuPengOn(QString yupengaddr,QString macaddr)
{
    bool ok=1;QString str1="";
    qcharaddr=yupengaddr.toInt(&ok,16);
    send[2]=(qcharaddr.unicode())/256;
    send[3]=(qcharaddr.unicode())%256;
    send[6]=0x05;
    send[7]=(qcharaddr.unicode())/256;
    send[8]=(qcharaddr.unicode())%256;
    send[9]=0xDD;
    send[10]=0xA3;
    send[11]=0xBB;
    str1=CutMACString(1,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[13]=(qcharaddr.unicode())/256;
    send[14]=(qcharaddr.unicode())%256;
    str1=CutMACString(2,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[15]=(qcharaddr.unicode())/256;
    send[16]=(qcharaddr.unicode())%256;
    str1=CutMACString(3,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[17]=(qcharaddr.unicode())/256;
    send[18]=(qcharaddr.unicode())%256;
    str1=CutMACString(4,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[19]=(qcharaddr.unicode())/256;
    send[20]=(qcharaddr.unicode())%256;
    m_Com->write(send,21);
    ui->label->setText(trUtf8("雨蓬开"));


}

void AutoControl_V2::YuPengStop(QString yupengaddr,QString macaddr)
{
    bool ok=1;QString str1="";
    qcharaddr=yupengaddr.toInt(&ok,16);
    send[2]=(qcharaddr.unicode())/256;
    send[3]=(qcharaddr.unicode())%256;
    send[6]=0x05;
    send[7]=(qcharaddr.unicode())/256;
    send[8]=(qcharaddr.unicode())%256;
    send[9]=0xDD;
    send[10]=0xA3;
    send[11]=0xAA;
    str1=CutMACString(1,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[13]=(qcharaddr.unicode())/256;
    send[14]=(qcharaddr.unicode())%256;
    str1=CutMACString(2,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[15]=(qcharaddr.unicode())/256;
    send[16]=(qcharaddr.unicode())%256;
    str1=CutMACString(3,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[17]=(qcharaddr.unicode())/256;
    send[18]=(qcharaddr.unicode())%256;
    str1=CutMACString(4,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[19]=(qcharaddr.unicode())/256;
    send[20]=(qcharaddr.unicode())%256;
    m_Com->write(send,21);
    ui->label->setText(trUtf8("雨蓬关闭"));


}

void AutoControl_V2::YuPengBettween(QString yupengaddr,QString macaddr)
{
    bool ok=1;QString str1="";
    qcharaddr=yupengaddr.toInt(&ok,16);
    send[2]=(qcharaddr.unicode())/256;
    send[3]=(qcharaddr.unicode())%256;
    send[6]=0x05;
    send[7]=(qcharaddr.unicode())/256;
    send[8]=(qcharaddr.unicode())%256;
    send[9]=0xDD;
    send[10]=0xA3;
    send[11]=0xCC;
    str1=CutMACString(1,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[13]=(qcharaddr.unicode())/256;
    send[14]=(qcharaddr.unicode())%256;
    str1=CutMACString(2,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[15]=(qcharaddr.unicode())/256;
    send[16]=(qcharaddr.unicode())%256;
    str1=CutMACString(3,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[17]=(qcharaddr.unicode())/256;
    send[18]=(qcharaddr.unicode())%256;
    str1=CutMACString(4,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[19]=(qcharaddr.unicode())/256;
    send[20]=(qcharaddr.unicode())%256;
    m_Com->write(send,21);
    ui->label->setText(trUtf8("雨蓬停"));


}

void AutoControl_V2::DaPengUp(QString yupengaddr,QString macaddr)
{
    bool ok=1;QString str1="";
    qcharaddr=yupengaddr.toInt(&ok,16);
    send[2]=(qcharaddr.unicode())/256;
    send[3]=(qcharaddr.unicode())%256;
    send[6]=0x4B;
    send[7]=(qcharaddr.unicode())/256;
    send[8]=(qcharaddr.unicode())%256;
    send[9]=0xDD;
    send[10]=0x01;
    send[11]=0xFF;
    str1=CutMACString(1,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[13]=(qcharaddr.unicode())/256;
    send[14]=(qcharaddr.unicode())%256;
    str1=CutMACString(2,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[15]=(qcharaddr.unicode())/256;
    send[16]=(qcharaddr.unicode())%256;
    str1=CutMACString(3,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[17]=(qcharaddr.unicode())/256;
    send[18]=(qcharaddr.unicode())%256;
    str1=CutMACString(4,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[19]=(qcharaddr.unicode())/256;
    send[20]=(qcharaddr.unicode())%256;
    m_Com->write(send,21);
    ui->label->setText(trUtf8("大棚上"));


}

void AutoControl_V2::DaPengStop(QString yupengaddr,QString macaddr)
{
    bool ok=1;QString str1="";
    qcharaddr=yupengaddr.toInt(&ok,16);
    send[2]=(qcharaddr.unicode())/256;
    send[3]=(qcharaddr.unicode())%256;
    send[6]=0x4B;
    send[7]=(qcharaddr.unicode())/256;
    send[8]=(qcharaddr.unicode())%256;
    send[9]=0xDD;
    send[10]=0x01;
    send[11]=0xDD;
    str1=CutMACString(1,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[13]=(qcharaddr.unicode())/256;
    send[14]=(qcharaddr.unicode())%256;
    str1=CutMACString(2,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[15]=(qcharaddr.unicode())/256;
    send[16]=(qcharaddr.unicode())%256;
    str1=CutMACString(3,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[17]=(qcharaddr.unicode())/256;
    send[18]=(qcharaddr.unicode())%256;
    str1=CutMACString(4,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[19]=(qcharaddr.unicode())/256;
    send[20]=(qcharaddr.unicode())%256;
    m_Com->write(send,21);
    ui->label->setText(trUtf8("大棚停"));


}

void AutoControl_V2::DaPengDown(QString yupengaddr,QString macaddr)
{
    bool ok=1;QString str1="";
    qcharaddr=yupengaddr.toInt(&ok,16);
    send[2]=(qcharaddr.unicode())/256;
    send[3]=(qcharaddr.unicode())%256;
    send[6]=0x4B;
    send[7]=(qcharaddr.unicode())/256;
    send[8]=(qcharaddr.unicode())%256;
    send[9]=0xDD;
    send[10]=0x01;
    send[11]=0xEE;
    str1=CutMACString(1,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[13]=(qcharaddr.unicode())/256;
    send[14]=(qcharaddr.unicode())%256;
    str1=CutMACString(2,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[15]=(qcharaddr.unicode())/256;
    send[16]=(qcharaddr.unicode())%256;
    str1=CutMACString(3,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[17]=(qcharaddr.unicode())/256;
    send[18]=(qcharaddr.unicode())%256;
    str1=CutMACString(4,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[19]=(qcharaddr.unicode())/256;
    send[20]=(qcharaddr.unicode())%256;
    m_Com->write(send,21);
    ui->label->setText(trUtf8("大棚下"));


}

void AutoControl_V2::YanShi_DianCiFa_ON(QString addr, QString macaddr)
{
    bool ok=1;QString str1="";
    qcharaddr=addr.toInt(&ok,16);
    send[2]=(qcharaddr.unicode())/256;
    send[3]=(qcharaddr.unicode())%256;
    send[6]=0x09;
    send[7]=(qcharaddr.unicode())/256;
    send[8]=(qcharaddr.unicode())%256;
    send[9]=0xDD;
    send[10]=0x0A;
    send[11]=0xAA;
    str1=CutMACString(1,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[13]=(qcharaddr.unicode())/256;
    send[14]=(qcharaddr.unicode())%256;
    str1=CutMACString(2,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[15]=(qcharaddr.unicode())/256;
    send[16]=(qcharaddr.unicode())%256;
    str1=CutMACString(3,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[17]=(qcharaddr.unicode())/256;
    send[18]=(qcharaddr.unicode())%256;
    str1=CutMACString(4,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[19]=(qcharaddr.unicode())/256;
    send[20]=(qcharaddr.unicode())%256;
    m_Com->write(send,21);
    ui->label->setText(trUtf8("演示-电磁阀-开发送"));


}

void AutoControl_V2::YanShi_DianCiFa_OFF(QString addr, QString macaddr)
{
    bool ok=1;QString str1="";
    qcharaddr=addr.toInt(&ok,16);
    send[2]=(qcharaddr.unicode())/256;
    send[3]=(qcharaddr.unicode())%256;
    send[6]=0x09;
    send[7]=(qcharaddr.unicode())/256;
    send[8]=(qcharaddr.unicode())%256;
    send[9]=0xDD;
    send[10]=0x0A;
    send[11]=0xBB;
    str1=CutMACString(1,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[13]=(qcharaddr.unicode())/256;
    send[14]=(qcharaddr.unicode())%256;
    str1=CutMACString(2,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[15]=(qcharaddr.unicode())/256;
    send[16]=(qcharaddr.unicode())%256;
    str1=CutMACString(3,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[17]=(qcharaddr.unicode())/256;
    send[18]=(qcharaddr.unicode())%256;
    str1=CutMACString(4,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[19]=(qcharaddr.unicode())/256;
    send[20]=(qcharaddr.unicode())%256;
    m_Com->write(send,21);
    ui->label->setText(trUtf8("演示-电磁阀-关发送"));

}

void AutoControl_V2::YanShi_FengShan_ON(QString addr, QString macaddr)
{
    bool ok=1;QString str1="";
    qcharaddr=addr.toInt(&ok,16);
    send[2]=(qcharaddr.unicode())/256;
    send[3]=(qcharaddr.unicode())%256;
    send[6]=0x09;
    send[7]=(qcharaddr.unicode())/256;
    send[8]=(qcharaddr.unicode())%256;
    send[9]=0xDD;
    send[10]=0x0B;
    send[11]=0xAA;
    str1=CutMACString(1,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[13]=(qcharaddr.unicode())/256;
    send[14]=(qcharaddr.unicode())%256;
    str1=CutMACString(2,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[15]=(qcharaddr.unicode())/256;
    send[16]=(qcharaddr.unicode())%256;
    str1=CutMACString(3,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[17]=(qcharaddr.unicode())/256;
    send[18]=(qcharaddr.unicode())%256;
    str1=CutMACString(4,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[19]=(qcharaddr.unicode())/256;
    send[20]=(qcharaddr.unicode())%256;
    m_Com->write(send,21);
    ui->label->setText(trUtf8("演示-风扇-开发送"));


}

void AutoControl_V2::YanShi_FengShan_OFF(QString addr, QString macaddr)
{
    bool ok=1;QString str1="";
    qcharaddr=addr.toInt(&ok,16);
    send[2]=(qcharaddr.unicode())/256;
    send[3]=(qcharaddr.unicode())%256;
    send[6]=0x09;
    send[7]=(qcharaddr.unicode())/256;
    send[8]=(qcharaddr.unicode())%256;
    send[9]=0xDD;
    send[10]=0x0B;
    send[11]=0xBB;
    str1=CutMACString(1,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[13]=(qcharaddr.unicode())/256;
    send[14]=(qcharaddr.unicode())%256;
    str1=CutMACString(2,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[15]=(qcharaddr.unicode())/256;
    send[16]=(qcharaddr.unicode())%256;
    str1=CutMACString(3,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[17]=(qcharaddr.unicode())/256;
    send[18]=(qcharaddr.unicode())%256;
    str1=CutMACString(4,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[19]=(qcharaddr.unicode())/256;
    send[20]=(qcharaddr.unicode())%256;
    m_Com->write(send,21);
    ui->label->setText(trUtf8("演示-分扇-关发送"));


}

void AutoControl_V2::YanShi_BuGuangDeng_ON(QString addr, QString macaddr)
{
    bool ok=1;QString str1="";
    qcharaddr=addr.toInt(&ok,16);
    send[2]=(qcharaddr.unicode())/256;
    send[3]=(qcharaddr.unicode())%256;
    send[6]=0x09;
    send[7]=(qcharaddr.unicode())/256;
    send[8]=(qcharaddr.unicode())%256;
    send[9]=0xDD;
    send[10]=0x0C;
    send[11]=0xAA;
    str1=CutMACString(1,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[13]=(qcharaddr.unicode())/256;
    send[14]=(qcharaddr.unicode())%256;
    str1=CutMACString(2,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[15]=(qcharaddr.unicode())/256;
    send[16]=(qcharaddr.unicode())%256;
    str1=CutMACString(3,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[17]=(qcharaddr.unicode())/256;
    send[18]=(qcharaddr.unicode())%256;
    str1=CutMACString(4,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[19]=(qcharaddr.unicode())/256;
    send[20]=(qcharaddr.unicode())%256;
    m_Com->write(send,21);
    ui->label->setText(trUtf8("演示-补光灯-开发送"));


}

void AutoControl_V2::YanShi_BuGuangDeng_OFF(QString addr, QString macaddr)
{
    bool ok=1;QString str1="";
    qcharaddr=addr.toInt(&ok,16);
    send[2]=(qcharaddr.unicode())/256;
    send[3]=(qcharaddr.unicode())%256;
    send[6]=0x09;
    send[7]=(qcharaddr.unicode())/256;
    send[8]=(qcharaddr.unicode())%256;
    send[9]=0xDD;
    send[10]=0x0C;
    send[11]=0xBB;
    str1=CutMACString(1,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[13]=(qcharaddr.unicode())/256;
    send[14]=(qcharaddr.unicode())%256;
    str1=CutMACString(2,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[15]=(qcharaddr.unicode())/256;
    send[16]=(qcharaddr.unicode())%256;
    str1=CutMACString(3,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[17]=(qcharaddr.unicode())/256;
    send[18]=(qcharaddr.unicode())%256;
    str1=CutMACString(4,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[19]=(qcharaddr.unicode())/256;
    send[20]=(qcharaddr.unicode())%256;
    m_Com->write(send,21);
    ui->label->setText(trUtf8("演示-补光灯-关发送"));


}

void AutoControl_V2::YanShi_ShuMaGuan(QString addr, QString macaddr,char cVal)//shumaguan
{
    bool ok=1;QString str1="";
    qcharaddr=addr.toInt(&ok,16);
    send[2]=(qcharaddr.unicode())/256;
    send[3]=(qcharaddr.unicode())%256;
    send[6]=0x09;
    send[7]=(qcharaddr.unicode())/256;
    send[8]=(qcharaddr.unicode())%256;
    send[9]=0xEA;
    send[10]=cVal;
    send[11]=0xAA;
    str1=CutMACString(1,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[13]=(qcharaddr.unicode())/256;
    send[14]=(qcharaddr.unicode())%256;
    str1=CutMACString(2,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[15]=(qcharaddr.unicode())/256;
    send[16]=(qcharaddr.unicode())%256;
    str1=CutMACString(3,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[17]=(qcharaddr.unicode())/256;
    send[18]=(qcharaddr.unicode())%256;
    str1=CutMACString(4,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[19]=(qcharaddr.unicode())/256;
    send[20]=(qcharaddr.unicode())%256;
    m_Com->write(send,21);
    ui->label->setText(trUtf8("演示-数码管-发送"));
}

void AutoControl_V2::YanShi_DianJi_ZhengZhuan(QString addr, QString macaddr)//电机正转
{

    bool ok=1;QString str1="";
    qcharaddr=addr.toInt(&ok,16);
    send[2]=(qcharaddr.unicode())/256;
    send[3]=(qcharaddr.unicode())%256;
    send[6]=0x09;
    send[7]=(qcharaddr.unicode())/256;
    send[8]=(qcharaddr.unicode())%256;
    send[9]=0xEB;
    send[10]=0xAB;
    send[11]=0xAA;
    str1=CutMACString(1,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[13]=(qcharaddr.unicode())/256;
    send[14]=(qcharaddr.unicode())%256;
    str1=CutMACString(2,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[15]=(qcharaddr.unicode())/256;
    send[16]=(qcharaddr.unicode())%256;
    str1=CutMACString(3,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[17]=(qcharaddr.unicode())/256;
    send[18]=(qcharaddr.unicode())%256;
    str1=CutMACString(4,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[19]=(qcharaddr.unicode())/256;
    send[20]=(qcharaddr.unicode())%256;
    m_Com->write(send,21);
    ui->label->setText(trUtf8("演示-电机正转-发送"));

}

void AutoControl_V2::YanShi_DianJi_FanZhuan(QString addr, QString macaddr)//电机反转
{
    bool ok=1;QString str1="";
    qcharaddr=addr.toInt(&ok,16);
    send[2]=(qcharaddr.unicode())/256;
    send[3]=(qcharaddr.unicode())%256;
    send[6]=0x09;
    send[7]=(qcharaddr.unicode())/256;
    send[8]=(qcharaddr.unicode())%256;
    send[9]=0xEB;
    send[10]=0xBA;
    send[11]=0xAA;
    str1=CutMACString(1,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[13]=(qcharaddr.unicode())/256;
    send[14]=(qcharaddr.unicode())%256;
    str1=CutMACString(2,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[15]=(qcharaddr.unicode())/256;
    send[16]=(qcharaddr.unicode())%256;
    str1=CutMACString(3,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[17]=(qcharaddr.unicode())/256;
    send[18]=(qcharaddr.unicode())%256;
    str1=CutMACString(4,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[19]=(qcharaddr.unicode())/256;
    send[20]=(qcharaddr.unicode())%256;
    m_Com->write(send,21);
    ui->label->setText(trUtf8("演示-电机反转-发送"));


}

void AutoControl_V2::YanShi_DianJi_Ting(QString addr,QString macaddr)//dianj
{
    bool ok=1;QString str1="";
    qcharaddr=addr.toInt(&ok,16);
    send[2]=(qcharaddr.unicode())/256;
    send[3]=(qcharaddr.unicode())%256;
    send[6]=0x09;
    send[7]=(qcharaddr.unicode())/256;
    send[8]=(qcharaddr.unicode())%256;
    send[9]=0xEB;
    send[10]=0x00;
    send[11]=0xAA;
    str1=CutMACString(1,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[13]=(qcharaddr.unicode())/256;
    send[14]=(qcharaddr.unicode())%256;
    str1=CutMACString(2,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[15]=(qcharaddr.unicode())/256;
    send[16]=(qcharaddr.unicode())%256;
    str1=CutMACString(3,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[17]=(qcharaddr.unicode())/256;
    send[18]=(qcharaddr.unicode())%256;
    str1=CutMACString(4,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[19]=(qcharaddr.unicode())/256;
    send[20]=(qcharaddr.unicode())%256;
    m_Com->write(send,21);
    ui->label->setText(trUtf8("演示-电机停-发送"));

}

void AutoControl_V2::MenSuo_ON(QString addr,QString macaddr)
{
    bool ok=1;QString str1="";
    qcharaddr=addr.toInt(&ok,16);
    send[2]=(qcharaddr.unicode())/256;
    send[3]=(qcharaddr.unicode())%256;
    send[6]=0x12;
    send[7]=(qcharaddr.unicode())/256;
    send[8]=(qcharaddr.unicode())%256;
    send[9]=0xDD;
    send[10]=0x01;
    send[11]=0xAA;
    str1=CutMACString(1,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[13]=(qcharaddr.unicode())/256;
    send[14]=(qcharaddr.unicode())%256;
    str1=CutMACString(2,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[15]=(qcharaddr.unicode())/256;
    send[16]=(qcharaddr.unicode())%256;
    str1=CutMACString(3,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[17]=(qcharaddr.unicode())/256;
    send[18]=(qcharaddr.unicode())%256;
    str1=CutMACString(4,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[19]=(qcharaddr.unicode())/256;
    send[20]=(qcharaddr.unicode())%256;
    m_Com->write(send,21);
    ui->label->setText(trUtf8("门锁-发送"));


}

void AutoControl_V2::ZhiWen_Sousuo(QString addr,QString longaddr)
{
    QString str1="";
    bool ok=1;
    qcharaddr=addr.toInt(&ok,16);
    send[2]=(qcharaddr.unicode())/256;
    send[3]=(qcharaddr.unicode())%256;
    send[6]=0x23;
    send[7]=(qcharaddr.unicode())/256;
    send[8]=(qcharaddr.unicode())%256;
    send[9]=0xBB;
    send[10]=0x00;
    send[11]=0x00;
    str1=CutMACString(1,longaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[13]=(qcharaddr.unicode())/256;
    send[14]=(qcharaddr.unicode())%256;
    str1=CutMACString(2,longaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[15]=(qcharaddr.unicode())/256;
    send[16]=(qcharaddr.unicode())%256;
    str1=CutMACString(3,longaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[17]=(qcharaddr.unicode())/256;
    send[18]=(qcharaddr.unicode())%256;
    str1=CutMACString(4,longaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[19]=(qcharaddr.unicode())/256;
    send[20]=(qcharaddr.unicode())%256;
    QString s33="";
    for(int i=0;i<21;i++)
    {
        s33.sprintf("%02x",send[i]);
        qDebug()<<s33;
    }
    m_Com->write(send,21);
    ui->label->setText(trUtf8("指纹搜索发送类"));

}

void AutoControl_V2::Send_PHZhi(QString addr,QString longaddr)
{
    QString str1="";
    bool ok=1;
    qcharaddr=addr.toInt(&ok,16);
    send[2]=(qcharaddr.unicode())/256;
    send[3]=(qcharaddr.unicode())%256;
    send[6]=0x14;
    send[7]=(qcharaddr.unicode())/256;
    send[8]=(qcharaddr.unicode())%256;
    send[9]=0x01;
    send[10]=0x03;
    send[11]=0x0C;
    str1=CutMACString(1,longaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[13]=(qcharaddr.unicode())/256;
    send[14]=(qcharaddr.unicode())%256;
    str1=CutMACString(2,longaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[15]=(qcharaddr.unicode())/256;
    send[16]=(qcharaddr.unicode())%256;
    str1=CutMACString(3,longaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[17]=(qcharaddr.unicode())/256;
    send[18]=(qcharaddr.unicode())%256;
    str1=CutMACString(4,longaddr);
    qcharaddr=str1.toInt(&ok,16);
    send[19]=(qcharaddr.unicode())/256;
    send[20]=(qcharaddr.unicode())%256;
    m_Com->write(send,21);
    ui->label->setText(trUtf8("PH发送类"));

}

void AutoControl_V2::Send_Sound(QString addr,QString longaddr,char itype)
{
        QString str1="";
        bool ok=1;
        qcharaddr=addr.toInt(&ok,16);
        send[2]=(qcharaddr.unicode())/256;
        send[3]=(qcharaddr.unicode())%256;
        send[6]=0x15;
        send[7]=(qcharaddr.unicode())/256;
        send[8]=(qcharaddr.unicode())%256;
        send[9]=0xDD;
        send[10]=itype;
        send[11]=0x00;
        str1=CutMACString(1,longaddr);
        qcharaddr=str1.toInt(&ok,16);
        send[13]=(qcharaddr.unicode())/256;
        send[14]=(qcharaddr.unicode())%256;
        str1=CutMACString(2,longaddr);
        qcharaddr=str1.toInt(&ok,16);
        send[15]=(qcharaddr.unicode())/256;
        send[16]=(qcharaddr.unicode())%256;
        str1=CutMACString(3,longaddr);
        qcharaddr=str1.toInt(&ok,16);
        send[17]=(qcharaddr.unicode())/256;
        send[18]=(qcharaddr.unicode())%256;
        str1=CutMACString(4,longaddr);
        qcharaddr=str1.toInt(&ok,16);
        send[19]=(qcharaddr.unicode())/256;
        send[20]=(qcharaddr.unicode())%256;
        m_Com->write(send,21);
        ui->label->setText(trUtf8("语音播报发送类"));
}

void AutoControl_V2::All_OFF()
{
    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        QTableWidgetItem *item = ui->tableWidget->item(tablerow, 0);
        if((QString::compare(trUtf8("通风扇"),item->text())==0)||(QString::compare(trUtf8("浇花"),item->text())==0)||(QString::compare(trUtf8("电源"),item->text())==0)||(QString::compare(trUtf8("喷淋"),item->text())==0)||(QString::compare(trUtf8("电饭煲"),item->text())==0)||(QString::compare(trUtf8("加湿器"),item->text())==0)||(QString::compare(trUtf8("换气扇"),item->text())==0)||(QString::compare(trUtf8("净化器"),item->text())==0)||(QString::compare(trUtf8("饮水机"),item->text())==0)||(QString::compare(trUtf8("喷雾器"),item->text())==0))
        {
            QTableWidgetItem *item1 = ui->tableWidget->item(tablerow, 2);
            QTableWidgetItem *item2 = ui->tableWidget->item(tablerow, 3);
            KG_OFF(item1->text(),item2->text());
        }
        if((QString::compare(trUtf8("雨蓬"),item->text())==0))
        {
            QTableWidgetItem *item1 = ui->tableWidget->item(tablerow, 2);
            QTableWidgetItem *item2 = ui->tableWidget->item(tablerow, 3);

            YuPengStop(item1->text(),item2->text());
        }
        if((QString::compare(trUtf8("窗帘"),item->text())==0))
        {
            QTableWidgetItem *item1 = ui->tableWidget->item(tablerow, 2);
            QTableWidgetItem *item2 = ui->tableWidget->item(tablerow, 3);
            CUR_OFF(item1->text(),item2->text());
        }
        if((QString::compare(trUtf8("调光"),item->text())==0))
        {
            QTableWidgetItem *item1 = ui->tableWidget->item(tablerow, 2);
            QTableWidgetItem *item2 = ui->tableWidget->item(tablerow, 3);
            SUN_OFF(item1->text(),item2->text(),initval);
        }
        if((QString::compare(trUtf8("空调"),item->text())==0)||(QString::compare(trUtf8("空调扇"),item->text())==0)||(QString::compare(trUtf8("电视"),item->text())==0)||(QString::compare(trUtf8("音箱"),item->text())==0)||(QString::compare(trUtf8("DVD"),item->text())==0))
        {

            QTableWidgetItem *item1 = ui->tableWidget->item(tablerow, 1);
            QTableWidgetItem *item2 = ui->tableWidget->item(tablerow, 2);
            QTableWidgetItem *item3 = ui->tableWidget->item(tablerow, 3);
            if(item1->text()==trUtf8("关"))
            {
                Ir_Send(item2->text(),item3->text(),RetIRCodeByFun(item1->text()));
            }
        }
    }
}

bool AutoControl_V2::isKGType(QString addr)
{
    for(int i=0;i<isensorlength;i++)
    {
        if(QString::compare(addr,m_sensorstruct[i].longaddr)==0)
        {
            if(m_sensorstruct[i].name.contains(trUtf8("通风扇"))==0||m_sensorstruct[i].name.contains(trUtf8("喷雾器"))==0||m_sensorstruct[i].name.contains(trUtf8("电饭煲"))==0||m_sensorstruct[i].name.contains(trUtf8("净化器"))==0||m_sensorstruct[i].name.contains(trUtf8("电源"))==0||m_sensorstruct[i].name.contains(trUtf8("换气扇"))==0||m_sensorstruct[i].name.contains(trUtf8("喷淋"))==0||m_sensorstruct[i].name.contains(trUtf8("浇花"))==0||m_sensorstruct[i].name.contains(trUtf8("加湿器"))==0||m_sensorstruct[i].name.contains(trUtf8("饮水机"))==0)
            {
                 return true;
            }
        }
    }
    return false;
}

bool AutoControl_V2::isCurType(QString addr)
{
    for(int i=0;i<isensorlength;i++)
    {
        if(QString::compare(addr,m_sensorstruct[i].longaddr)==0)
        {
            if(m_sensorstruct[i].name.contains(trUtf8("窗帘")))
            {
                 return true;
            }
        }
    }
    return false;
}

bool AutoControl_V2::isSunType(QString addr)
{
    for(int i=0;i<isensorlength;i++)
    {
        if(QString::compare(addr,m_sensorstruct[i].longaddr)==0)
        {
            if(m_sensorstruct[i].name.contains(trUtf8("调光")))
            {
                 return true;
            }
        }
    }
    return false;
}

bool AutoControl_V2::isIrType(QString addr)  //判断红外节点是否存在
{
     for(int i=0;i<iirtructlength;i++)
     {
         if(QString::compare(addr,m_irstruct[i].longaddr)==0)
         {
             if(m_irstruct[i].name.contains(trUtf8("电视"))||m_irstruct[i].name.contains(trUtf8("空调"))||m_irstruct[i].name.contains(trUtf8("空调扇"))||m_irstruct[i].name.contains(trUtf8("投影机"))||m_irstruct[i].name.contains(trUtf8("音箱")))
             {
                return true;
             }
         }
     }
     return false;
}

bool AutoControl_V2::isThreeFiveType(QString addr)
{
    for(int i=0;i<ithreefivestructlength;i++)
    {
        if(QString::compare(addr,m_threefivestruct[i].longaddr)==0)
        {
            if(m_threefivestruct[i].name.contains(trUtf8("烟雾"))||m_threefivestruct[i].name.contains(trUtf8("人体"))||m_threefivestruct[i].name.contains(trUtf8("门磁"))||m_threefivestruct[i].name.contains(trUtf8("气体")))
            {
               return true;
            }
        }
    }
    return false;
}

bool AutoControl_V2::isYuPengType(QString addr)
{
    for(int i=0;i<isensorlength;i++)
    {
        if(QString::compare(addr,m_sensorstruct[i].longaddr)==0)
        {
            if(m_sensorstruct[i].name.contains(trUtf8("雨蓬")))
            {
                 return true;
            }
        }
    }
    return false;

}

bool AutoControl_V2::JudgeLianDongTheSameAddr(int itype,QString macaddr)
{
    switch(itype)
    {
       case 1://guangxian
       {
            for(int i=0;i<iguangxianstructlength;i++)
            {
                if(QString::compare(macaddr,m_guangxianstruct[i].longaddr)==0)
                {
                    return true;
                }

            }
            break;
       }
       case 2://qiti
       {
           for(int i=0;i<iqitistructlength;i++)
           {
              if(QString::compare(macaddr,m_qitistruct[i].longaddr)==0)
              {
                 return true;
              }
           }
            break;
       }
        case 3://smog
        {
            for(int i=0;i<ismogstructlength;i++)
            {
               if(QString::compare(macaddr,m_smogstruct[i].longaddr)==0)
               {
                  return true;
               }
            }
             break;
        }
        case 4://rain
        {
            for(int i=0;i<irainstructlength;i++)
            {
               if(QString::compare(macaddr,m_rainstruct[i].longaddr)==0)
               {
                  return true;
               }
            }
             break;
        }
        case 5://key
        {
            for(int i=0;i<ikeystructlength;i++)
            {
               if(QString::compare(macaddr,m_keystruct[i].longaddr)==0)
               {
                  return true;
               }
            }
             break;
        }
        case 6://wenshidu
        {
            for(int i=0;i<iwenshidustructlength;i++)
            {
               if(QString::compare(macaddr,m_wenshidustruct[i].longaddr)==0)
               {
                  return true;
               }
            }
             break;
        }
        case 7://kongqi
        {
            for(int i=0;i<ikongqistructlength;i++)
            {
               if(QString::compare(macaddr,m_kongqistruct[i].longaddr)==0)
               {
                  return true;
               }
            }
             break;
        }
    }
    return false;

}

QString AutoControl_V2::RetIRCode(QString addr)
{
    for(int i=0;i<iirtructlength;i++)
    {
        if(QString::compare(m_irstruct[i].longaddr,addr)==0)
        {
            return m_irstruct[i].code;
        }
    }
    return "NULL";
}

QString AutoControl_V2::RetIRCodeByFun(QString fun)
{
    for(int i=0;i<iirtructlength;i++)
    {
        if(QString::compare(m_irstruct[i].function,fun)==0)
        {
            return m_irstruct[i].code;
        }
    }
    return "NULL";
}

void AutoControl_V2::TrueControl(int itype,QString addr,QString macaddr,QString fval)
{
    bool ok=1;
    float ffval=0.00;
    ffval=fval.toDouble(&ok);

    switch(itype)
    {
        case 1://guangxian
       {
            for(int i=0;i<iguangxianstructlength;i++)
            {
                if(QString::compare(macaddr,m_guangxianstruct[i].longaddr)==0)
                {

                    if(isKGType(m_guangxianstruct[i].clongaddr)==true)
                    {
                        if(ffval>=m_guangxianstruct[i].val.toFloat(&ok))
                        {
                            if(QString::compare(trUtf8("关"),m_guangxianstruct[i].truefun)==0)
                            {
                               KG_OFF(m_guangxianstruct[i].cshortaddr,m_guangxianstruct[i].clongaddr);
                            }
                            if(QString::compare(trUtf8("开"),m_guangxianstruct[i].truefun)==0)
                            {
                               KG_ON(m_guangxianstruct[i].cshortaddr,m_guangxianstruct[i].clongaddr);
                            }
                        }
                        else
                        {
                            if(QString::compare(trUtf8("关"),m_guangxianstruct[i].truefun)==0)
                            {
                               KG_ON(m_guangxianstruct[i].cshortaddr,m_guangxianstruct[i].clongaddr);
                            }
                            if(QString::compare(trUtf8("开"),m_guangxianstruct[i].truefun)==0)
                            {
                               KG_OFF(m_guangxianstruct[i].cshortaddr,m_guangxianstruct[i].clongaddr);
                            }
                        }
                    }
                    if(isCurType(m_guangxianstruct[i].clongaddr)==true)
                    {
                        if(ffval>=m_guangxianstruct[i].val.toFloat(&ok))
                        {
                            if(QString::compare(trUtf8("关"),m_guangxianstruct[i].truefun)==0)
                            {
                               CUR_OFF(m_guangxianstruct[i].cshortaddr,m_guangxianstruct[i].clongaddr);

                            }
                            if(QString::compare(trUtf8("开"),m_guangxianstruct[i].truefun)==0)
                            {
                               CUR_ON(m_guangxianstruct[i].cshortaddr,m_guangxianstruct[i].clongaddr);

                            }
                        }
                        else
                        {
                            if(QString::compare(trUtf8("关"),m_guangxianstruct[i].truefun)==0)
                            {
                               CUR_ON(m_guangxianstruct[i].cshortaddr,m_guangxianstruct[i].clongaddr);

                            }
                            if(QString::compare(trUtf8("开"),m_guangxianstruct[i].truefun)==0)
                            {
                               CUR_OFF(m_guangxianstruct[i].cshortaddr,m_guangxianstruct[i].clongaddr);

                            }
                        }
                    }
                    if(isSunType(m_guangxianstruct[i].clongaddr)==true)
                    {
                        if(ffval>=m_guangxianstruct[i].val.toFloat(&ok))
                        {
                            if(QString::compare(trUtf8("关"),m_guangxianstruct[i].truefun)==0)
                            {
                               SUN_OFF(m_guangxianstruct[i].cshortaddr,m_guangxianstruct[i].clongaddr,0x00);

                            }
                            if(QString::compare(trUtf8("开"),m_guangxianstruct[i].truefun)==0)
                            {
                               SUN_ON(m_guangxianstruct[i].cshortaddr,m_guangxianstruct[i].clongaddr,0x75);

                            }

                        }
                        else
                        {
                            if(QString::compare(trUtf8("关"),m_guangxianstruct[i].truefun)==0)
                            {
                               SUN_ON(m_guangxianstruct[i].cshortaddr,m_guangxianstruct[i].clongaddr,0x75);

                            }
                            if(QString::compare(trUtf8("开"),m_guangxianstruct[i].truefun)==0)
                            {
                               SUN_OFF(m_guangxianstruct[i].cshortaddr,m_guangxianstruct[i].clongaddr,0x00);

                            }
                        }
                    }
                    if(isYuPengType(m_guangxianstruct[i].clongaddr)==true)
                    {
                        if(ffval>=m_guangxianstruct[i].val.toFloat(&ok))
                        {
                            if(QString::compare(trUtf8("关"),m_guangxianstruct[i].truefun)==0)
                            {
                               YuPengStop(m_guangxianstruct[i].cshortaddr,m_guangxianstruct[i].clongaddr);
                            }
                            if(QString::compare(trUtf8("开"),m_guangxianstruct[i].truefun)==0)
                            {
                               YuPengOn(m_guangxianstruct[i].cshortaddr,m_guangxianstruct[i].clongaddr);
                            }

                        }
                        else
                        {
                            if(QString::compare(trUtf8("关"),m_guangxianstruct[i].truefun)==0)
                            {
                                YuPengOn(m_guangxianstruct[i].cshortaddr,m_guangxianstruct[i].clongaddr);
                            }
                            if(QString::compare(trUtf8("开"),m_guangxianstruct[i].truefun)==0)
                            {
                                YuPengStop(m_guangxianstruct[i].cshortaddr,m_guangxianstruct[i].clongaddr);
                            }

                        }
                    }
                    if(isIrType(m_guangxianstruct[i].clongaddr)==true)
                    {
                        if(QString::compare(m_guangxianstruct[i].truefun,m_guangxianstruct[i].cfun)==0)
                        {
                            if(ffval>=m_guangxianstruct[i].val.toFloat(&ok))
                            {
                                   Ir_Send(m_guangxianstruct[i].cshortaddr,m_guangxianstruct[i].clongaddr,RetIRCode(m_guangxianstruct[i].clongaddr));

                            }
                        }
                    }
                    if(iguangxianstructlength>1)
                    {
                       sleep(1);

                    }
                }

            }
            break;
       }
        case 2://qiti
       {
           for(int i=0;i<iqitistructlength;i++)
           {
              if(QString::compare(macaddr,m_qitistruct[i].longaddr)==0)
              {
                  if(isKGType(m_qitistruct[i].clongaddr)==true)
                  {
                      if(QString::compare(trUtf8("关"),m_qitistruct[i].truefun)==0)
                      {
                          KG_OFF(m_qitistruct[i].cshortaddr,m_qitistruct[i].clongaddr);
                      }
                      if(QString::compare(trUtf8("开"),m_qitistruct[i].truefun)==0)
                      {
                         KG_ON(m_qitistruct[i].cshortaddr,m_qitistruct[i].clongaddr);
                      }
                  }
                  if(isCurType(m_qitistruct[i].clongaddr)==true)
                  {
                      if(QString::compare(trUtf8("关"),m_qitistruct[i].truefun)==0)
                      {
                         CUR_OFF(m_qitistruct[i].cshortaddr,m_qitistruct[i].clongaddr);
                      }
                      if(QString::compare(trUtf8("开"),m_qitistruct[i].truefun)==0)
                      {
                         CUR_ON(m_qitistruct[i].cshortaddr,m_qitistruct[i].clongaddr);
                      }

                  }
                  if(isSunType(m_qitistruct[i].clongaddr)==true)
                  {
                      if(QString::compare(trUtf8("关"),m_qitistruct[i].truefun)==0)
                      {
                         SUN_OFF(m_qitistruct[i].cshortaddr,m_qitistruct[i].clongaddr,0x00);
                      }
                      if(QString::compare(trUtf8("开"),m_qitistruct[i].truefun)==0)
                      {
                         SUN_ON(m_qitistruct[i].cshortaddr,m_qitistruct[i].clongaddr,0x75);
                      }
                  }
                  if(isYuPengType(m_qitistruct[i].clongaddr)==true)
                  {
                      if(QString::compare(trUtf8("关"),m_qitistruct[i].truefun)==0)
                      {
                         YuPengStop(m_qitistruct[i].cshortaddr,m_qitistruct[i].clongaddr);
                      }
                      if(QString::compare(trUtf8("开"),m_qitistruct[i].truefun)==0)
                      {
                         YuPengOn(m_qitistruct[i].cshortaddr,m_qitistruct[i].clongaddr);
                      }
                  }
                  if(isIrType(m_qitistruct[i].clongaddr)==true)
                  {
                      if(QString::compare(m_qitistruct[i].truefun,m_qitistruct[i].cfun)==0)
                      {
                         Ir_Send(m_qitistruct[i].cshortaddr,m_qitistruct[i].clongaddr,RetIRCode(m_qitistruct[i].clongaddr));

                      }
                  }
              }
           }
            break;
       }
        case 3://smog
        {
            for(int i=0;i<ismogstructlength;i++)
            {
               if(QString::compare(macaddr,m_smogstruct[i].longaddr)==0)
               {
                   if(isKGType(m_smogstruct[i].clongaddr)==true)
                   {
                       if(QString::compare(trUtf8("关"),m_smogstruct[i].truefun)==0)
                       {
                          KG_OFF(m_smogstruct[i].cshortaddr,m_smogstruct[i].clongaddr);
                       }
                       if(QString::compare(trUtf8("开"),m_smogstruct[i].truefun)==0)
                       {
                          KG_ON(m_smogstruct[i].cshortaddr,m_smogstruct[i].clongaddr);
                       }
                   }
                   if(isCurType(m_smogstruct[i].clongaddr)==true)
                   {
                       if(QString::compare(trUtf8("关"),m_smogstruct[i].truefun)==0)
                       {
                          CUR_OFF(m_smogstruct[i].cshortaddr,m_smogstruct[i].clongaddr);
                       }
                       if(QString::compare(trUtf8("开"),m_smogstruct[i].truefun)==0)
                       {
                          CUR_ON(m_smogstruct[i].cshortaddr,m_smogstruct[i].clongaddr);
                       }

                   }
                   if(isSunType(m_smogstruct[i].clongaddr)==true)
                   {
                       if(QString::compare(trUtf8("关"),m_smogstruct[i].truefun)==0)
                       {
                          SUN_OFF(m_smogstruct[i].cshortaddr,m_smogstruct[i].clongaddr,0x00);
                       }
                       if(QString::compare(trUtf8("开"),m_smogstruct[i].truefun)==0)
                       {
                          SUN_ON(m_smogstruct[i].cshortaddr,m_smogstruct[i].clongaddr,0x75);
                       }
                   }
                   if(isYuPengType(m_smogstruct[i].clongaddr)==true)
                   {
                       if(QString::compare(trUtf8("关"),m_smogstruct[i].truefun)==0)
                       {
                          YuPengStop(m_smogstruct[i].cshortaddr,m_smogstruct[i].clongaddr);
                       }
                       if(QString::compare(trUtf8("开"),m_smogstruct[i].truefun)==0)
                       {
                          YuPengOn(m_smogstruct[i].cshortaddr,m_smogstruct[i].clongaddr);
                       }
                   }
                   if(isIrType(m_smogstruct[i].clongaddr)==true)
                   {
                       if(QString::compare(m_smogstruct[i].truefun,m_smogstruct[i].cfun)==0)
                       {
                          Ir_Send(m_smogstruct[i].cshortaddr,m_smogstruct[i].clongaddr,RetIRCode(m_smogstruct[i].clongaddr));

                       }
                   }
               }
            }
             break;
        }
        case 4://rain
        {
            for(int i=0;i<irainstructlength;i++)
            {
               if(QString::compare(macaddr,m_rainstruct[i].longaddr)==0)
               {
                   if(isKGType(m_rainstruct[i].clongaddr)==true)
                   {
                       if(QString::compare(trUtf8("关"),m_rainstruct[i].truefun)==0)
                       {
                          KG_OFF(m_rainstruct[i].cshortaddr,m_rainstruct[i].clongaddr);
                       }
                       if(QString::compare(trUtf8("开"),m_rainstruct[i].truefun)==0)
                       {
                          KG_ON(m_rainstruct[i].cshortaddr,m_rainstruct[i].clongaddr);
                       }
                   }
                   if(isCurType(m_rainstruct[i].clongaddr)==true)
                   {
                       if(QString::compare(trUtf8("关"),m_rainstruct[i].truefun)==0)
                       {
                          CUR_OFF(m_rainstruct[i].cshortaddr,m_rainstruct[i].clongaddr);
                       }
                       if(QString::compare(trUtf8("开"),m_rainstruct[i].truefun)==0)
                       {
                          CUR_ON(m_rainstruct[i].cshortaddr,m_rainstruct[i].clongaddr);
                       }

                   }
                   if(isSunType(m_rainstruct[i].clongaddr)==true)
                   {
                       if(QString::compare(trUtf8("关"),m_rainstruct[i].truefun)==0)
                       {
                          SUN_OFF(m_rainstruct[i].cshortaddr,m_rainstruct[i].clongaddr,0x00);
                       }
                       if(QString::compare(trUtf8("开"),m_rainstruct[i].truefun)==0)
                       {
                          SUN_ON(m_rainstruct[i].cshortaddr,m_rainstruct[i].clongaddr,0x75);
                       }
                   }
                   if(isYuPengType(m_rainstruct[i].clongaddr)==true)
                   {
                       if(QString::compare(trUtf8("关"),m_rainstruct[i].truefun)==0)
                       {
                          YuPengStop(m_rainstruct[i].cshortaddr,m_rainstruct[i].clongaddr);
                       }
                       if(QString::compare(trUtf8("开"),m_rainstruct[i].truefun)==0)
                       {
                          YuPengOn(m_rainstruct[i].cshortaddr,m_rainstruct[i].clongaddr);
                       }
                   }
                   if(isIrType(m_rainstruct[i].clongaddr)==true)
                   {
                       if(QString::compare(m_rainstruct[i].truefun,m_rainstruct[i].cfun)==0)
                       {
                          Ir_Send(m_rainstruct[i].cshortaddr,m_rainstruct[i].clongaddr,RetIRCode(m_rainstruct[i].clongaddr));


                       }
                   }
               }
            }
             break;
        }
        case 5://rain no
        {
            for(int i=0;i<irainstructlength;i++)
            {
               if(QString::compare(macaddr,m_rainstruct[i].longaddr)==0)
               {
                   if(isKGType(m_rainstruct[i].clongaddr)==true)
                   {
                       if(QString::compare(trUtf8("关"),m_rainstruct[i].truefun)==0)
                       {
                          KG_ON(m_rainstruct[i].cshortaddr,m_rainstruct[i].clongaddr);
                       }
                       if(QString::compare(trUtf8("开"),m_rainstruct[i].truefun)==0)
                       {
                          KG_OFF(m_rainstruct[i].cshortaddr,m_rainstruct[i].clongaddr);
                       }
                   }
                   if(isCurType(m_rainstruct[i].clongaddr)==true)
                   {
                       if(QString::compare(trUtf8("关"),m_rainstruct[i].truefun)==0)
                       {
                          CUR_ON(m_rainstruct[i].cshortaddr,m_rainstruct[i].clongaddr);
                       }
                       if(QString::compare(trUtf8("开"),m_rainstruct[i].truefun)==0)
                       {
                          CUR_OFF(m_rainstruct[i].cshortaddr,m_rainstruct[i].clongaddr);
                       }

                   }
                   if(isSunType(m_rainstruct[i].clongaddr)==true)
                   {
                       if(QString::compare(trUtf8("关"),m_rainstruct[i].truefun)==0)
                       {
                          SUN_ON(m_rainstruct[i].cshortaddr,m_rainstruct[i].clongaddr,0x00);
                       }
                       if(QString::compare(trUtf8("开"),m_rainstruct[i].truefun)==0)
                       {
                          SUN_OFF(m_rainstruct[i].cshortaddr,m_rainstruct[i].clongaddr,0x75);
                       }
                   }
                   if(isYuPengType(m_rainstruct[i].clongaddr)==true)
                   {
                       if(QString::compare(trUtf8("关"),m_rainstruct[i].truefun)==0)
                       {
                          YuPengOn(m_rainstruct[i].cshortaddr,m_rainstruct[i].clongaddr);
                       }
                       if(QString::compare(trUtf8("开"),m_rainstruct[i].truefun)==0)
                       {
                          YuPengStop(m_rainstruct[i].cshortaddr,m_rainstruct[i].clongaddr);
                       }
                   }
                   if(isIrType(m_rainstruct[i].clongaddr)==true)
                   {
                       if(QString::compare(m_rainstruct[i].truefun,m_rainstruct[i].cfun)==0)
                       {
                          Ir_Send(m_rainstruct[i].cshortaddr,m_rainstruct[i].clongaddr,RetIRCode(m_rainstruct[i].clongaddr));


                       }
                   }
               }
            }
             break;
        }
        case 6://key
        {
            for(int i=0;i<ikeystructlength;i++)
            {
               if(QString::compare(macaddr,m_keystruct[i].longaddr)==0)
               {
                   if(isKGType(m_keystruct[i].clongaddr)==true)
                   {
                       if(m_keystruct[i].val==fval)
                       {
                           if(QString::compare(trUtf8("开"),m_keystruct[i].truefun)==0)
                           {
                               KG_ON(m_keystruct[i].cshortaddr,m_keystruct[i].clongaddr);
                           }
                           if(QString::compare(trUtf8("关"),m_keystruct[i].truefun)==0)
                           {
                               KG_OFF(m_keystruct[i].cshortaddr,m_keystruct[i].clongaddr);
                           }

                       }
                   }
                   if(isCurType(m_smogstruct[i].clongaddr)==true)
                   {
                       if(m_keystruct[i].val==fval)
                       {
                           if(QString::compare(trUtf8("开"),m_keystruct[i].truefun))
                           {
                               CUR_ON(m_keystruct[i].cshortaddr,m_keystruct[i].clongaddr);
                           }
                           if(QString::compare(trUtf8("关"),m_keystruct[i].truefun))
                           {
                               CUR_OFF(m_keystruct[i].cshortaddr,m_keystruct[i].clongaddr);
                           }

                       }
                   }
                   if(isSunType(m_keystruct[i].clongaddr)==true)
                   {
                       if(m_keystruct[i].val==fval)
                       {
                           if(QString::compare(trUtf8("开"),m_keystruct[i].truefun))
                           {
                               SUN_ON(m_keystruct[i].cshortaddr,m_keystruct[i].clongaddr,0x75);
                           }
                           if(QString::compare(trUtf8("关"),m_keystruct[i].truefun))
                           {
                               SUN_OFF(m_keystruct[i].cshortaddr,m_keystruct[i].clongaddr,0x00);
                           }

                       }
                   }
                   if(isYuPengType(m_keystruct[i].clongaddr)==true)
                   {
                       if(m_keystruct[i].val==fval)
                       {
                           if(QString::compare(trUtf8("开"),m_keystruct[i].truefun))
                           {
                               YuPengOn(m_keystruct[i].cshortaddr,m_keystruct[i].clongaddr);
                           }
                           if(QString::compare(trUtf8("关"),m_keystruct[i].truefun))
                           {
                               YuPengStop(m_keystruct[i].cshortaddr,m_keystruct[i].clongaddr);
                           }

                       }
                   }
                   if(isIrType(m_keystruct[i].clongaddr)==true)
                   {
                       if(QString::compare(m_keystruct[i].truefun,m_keystruct[i].cfun)==0)
                       {
                          Ir_Send(m_keystruct[i].cshortaddr,m_keystruct[i].clongaddr,RetIRCode(m_keystruct[i].clongaddr));

                       }
                   }
               }
            }
             break;
        }
        case 7://wendu
        {
            for(int i=0;i<iwenshidustructlength;i++)
            {
               if(QString::compare(macaddr,m_wenshidustruct[i].longaddr)==0)
               {
                   if(m_wenshidustruct[i].wenduval!="")
                   {


                       if(isKGType(m_wenshidustruct[i].clongaddr)==true)
                       {
                           if(ffval>=m_wenshidustruct[i].wenduval.toFloat(&ok))
                           {
                               if(QString::compare(trUtf8("关"),m_wenshidustruct[i].truefun)==0)
                               {
                                   KG_OFF(m_wenshidustruct[i].cshortaddr,m_wenshidustruct[i].clongaddr);
                               }
                               if(QString::compare(trUtf8("开"),m_wenshidustruct[i].truefun)==0)
                               {
                                  KG_ON(m_wenshidustruct[i].cshortaddr,m_wenshidustruct[i].clongaddr);
                               }

                           }
                           else
                           {
                               if(QString::compare(trUtf8("关"),m_wenshidustruct[i].truefun)==0)
                               {
                                  KG_ON(m_wenshidustruct[i].cshortaddr,m_wenshidustruct[i].clongaddr);
                               }
                               if(QString::compare(trUtf8("开"),m_wenshidustruct[i].truefun)==0)
                               {
                                  KG_OFF(m_wenshidustruct[i].cshortaddr,m_wenshidustruct[i].clongaddr);
                               }

                           }
                       }
                       if(isSunType(m_wenshidustruct[i].clongaddr)==true)
                       {

                               if(ffval>=m_wenshidustruct[i].wenduval.toFloat(&ok))
                               {
                                   if(QString::compare(trUtf8("关"),m_wenshidustruct[i].truefun)==0)
                                   {
                                      SUN_OFF(m_wenshidustruct[i].cshortaddr,m_wenshidustruct[i].clongaddr,0x00);
                                   }
                                   if(QString::compare(trUtf8("开"),m_wenshidustruct[i].truefun)==0)
                                   {
                                      SUN_ON(m_wenshidustruct[i].cshortaddr,m_wenshidustruct[i].clongaddr,0x75);
                                   }

                               }
                               else
                               {
                                   if(QString::compare(trUtf8("关"),m_wenshidustruct[i].truefun)==0)
                                   {
                                      SUN_ON(m_wenshidustruct[i].cshortaddr,m_wenshidustruct[i].clongaddr,0x75);
                                   }
                                   if(QString::compare(trUtf8("开"),m_wenshidustruct[i].truefun)==0)
                                   {
                                      SUN_OFF(m_wenshidustruct[i].cshortaddr,m_wenshidustruct[i].clongaddr,0x00);
                                   }
                               }

                       }
                       if(isCurType(m_wenshidustruct[i].clongaddr)==true)
                       {
                          if(ffval>=m_wenshidustruct[i].wenduval.toFloat(&ok))
                               {
                                   if(QString::compare(trUtf8("关"),m_wenshidustruct[i].truefun)==0)
                                   {
                                      CUR_OFF(m_wenshidustruct[i].cshortaddr,m_wenshidustruct[i].clongaddr);
                                   }
                                   if(QString::compare(trUtf8("开"),m_wenshidustruct[i].truefun)==0)
                                   {
                                      CUR_ON(m_wenshidustruct[i].cshortaddr,m_wenshidustruct[i].clongaddr);
                                   }

                               }
                               else
                               {
                                   if(QString::compare(trUtf8("关"),m_wenshidustruct[i].truefun)==0)
                                   {
                                      CUR_ON(m_wenshidustruct[i].cshortaddr,m_wenshidustruct[i].clongaddr);
                                   }
                                   if(QString::compare(trUtf8("开"),m_wenshidustruct[i].truefun)==0)
                                   {
                                      CUR_OFF(m_wenshidustruct[i].cshortaddr,m_wenshidustruct[i].clongaddr);
                                   }
                               }
                       }
                       if(isYuPengType(m_wenshidustruct[i].clongaddr)==true)
                       {
                           if(ffval>=m_wenshidustruct[i].wenduval.toFloat(&ok))
                           {
                                   if(QString::compare(trUtf8("关"),m_wenshidustruct[i].truefun)==0)
                                   {
                                      YuPengStop(m_wenshidustruct[i].cshortaddr,m_wenshidustruct[i].clongaddr);
                                   }
                                   if(QString::compare(trUtf8("开"),m_wenshidustruct[i].truefun)==0)
                                   {
                                      YuPengOn(m_wenshidustruct[i].cshortaddr,m_wenshidustruct[i].clongaddr);
                                   }

                            }
                            else
                            {
                                 if(QString::compare(trUtf8("关"),m_wenshidustruct[i].truefun)==0)
                                 {
                                     YuPengOn(m_wenshidustruct[i].cshortaddr,m_wenshidustruct[i].clongaddr);
                                 }
                                 if(QString::compare(trUtf8("开"),m_wenshidustruct[i].truefun)==0)
                                 {
                                     YuPengStop(m_wenshidustruct[i].cshortaddr,m_wenshidustruct[i].clongaddr);
                                 }
                             }
                       }
                       if(isIrType(m_wenshidustruct[i].clongaddr)==true)
                       {
                           if(QString::compare(m_wenshidustruct[i].truefun,m_wenshidustruct[i].cfun)==0)
                           {
                               if(ffval>=m_wenshidustruct[i].wenduval.toFloat(&ok))
                               {
                                  Ir_Send(m_wenshidustruct[i].cshortaddr,m_wenshidustruct[i].clongaddr,RetIRCode(m_wenshidustruct[i].clongaddr));

                               }
                           }
                       }
                   }
               }
            }
            break;
        }
        case 8://shidu
       {
            for(int i=0;i<iwenshidustructlength;i++)
            {
               if(QString::compare(macaddr,m_wenshidustruct[i].longaddr)==0)
               {

                   if(isKGType(m_wenshidustruct[i].clongaddr)==true)
                   {
                       if(m_wenshidustruct[i].shiduval!="")
                       {
                           if(ffval>=m_wenshidustruct[i].shiduval.toFloat(&ok))
                           {
                               if(QString::compare(trUtf8("关"),m_wenshidustruct[i].truefun)==0)
                               {
                                  KG_OFF(m_wenshidustruct[i].cshortaddr,m_wenshidustruct[i].clongaddr);
                               }
                               if(QString::compare(trUtf8("开"),m_wenshidustruct[i].truefun)==0)
                               {
                                  KG_ON(m_wenshidustruct[i].cshortaddr,m_wenshidustruct[i].clongaddr);
                               }

                           }
                           else
                           {
                               if(QString::compare(trUtf8("关"),m_wenshidustruct[i].truefun)==0)
                               {
                                  KG_ON(m_wenshidustruct[i].cshortaddr,m_wenshidustruct[i].clongaddr);
                               }
                               if(QString::compare(trUtf8("开"),m_wenshidustruct[i].truefun)==0)
                               {
                                  KG_OFF(m_wenshidustruct[i].cshortaddr,m_wenshidustruct[i].clongaddr);
                               }
                           }
                       }

                   }
                   if(isSunType(m_wenshidustruct[i].clongaddr)==true)
                   {
                       if(m_wenshidustruct[i].shiduval!="")
                       {
                           if(ffval>=m_wenshidustruct[i].shiduval.toFloat(&ok))
                           {
                               if(QString::compare(trUtf8("关"),m_wenshidustruct[i].truefun)==0)
                               {
                                  SUN_OFF(m_wenshidustruct[i].cshortaddr,m_wenshidustruct[i].clongaddr,0x00);
                               }
                               if(QString::compare(trUtf8("开"),m_wenshidustruct[i].truefun)==0)
                               {
                                  SUN_ON(m_wenshidustruct[i].cshortaddr,m_wenshidustruct[i].clongaddr,0x75);
                               }

                           }
                           else
                           {
                               if(QString::compare(trUtf8("关"),m_wenshidustruct[i].truefun)==0)
                               {
                                  SUN_ON(m_wenshidustruct[i].cshortaddr,m_wenshidustruct[i].clongaddr,0x75);
                               }
                               if(QString::compare(trUtf8("开"),m_wenshidustruct[i].truefun)==0)
                               {
                                  SUN_OFF(m_wenshidustruct[i].cshortaddr,m_wenshidustruct[i].clongaddr,0x00);
                               }
                           }
                       }
                   }

                   if(isCurType(m_wenshidustruct[i].clongaddr)==true)
                   {
                       if(m_wenshidustruct[i].shiduval!="")
                       {
                           if(ffval>=m_wenshidustruct[i].shiduval.toFloat(&ok))
                           {
                               if(QString::compare(trUtf8("关"),m_wenshidustruct[i].truefun)==0)
                               {
                                  CUR_OFF(m_wenshidustruct[i].cshortaddr,m_wenshidustruct[i].clongaddr);
                               }
                               if(QString::compare(trUtf8("开"),m_wenshidustruct[i].truefun)==0)
                               {
                                  CUR_ON(m_wenshidustruct[i].cshortaddr,m_wenshidustruct[i].clongaddr);
                               }

                           }
                           else
                           {
                               if(QString::compare(trUtf8("关"),m_wenshidustruct[i].truefun)==0)
                               {
                                  CUR_ON(m_wenshidustruct[i].cshortaddr,m_wenshidustruct[i].clongaddr);
                               }
                               if(QString::compare(trUtf8("开"),m_wenshidustruct[i].truefun)==0)
                               {
                                  CUR_OFF(m_wenshidustruct[i].cshortaddr,m_wenshidustruct[i].clongaddr);
                               }
                           }
                       }
                   }

                   if(isYuPengType(m_wenshidustruct[i].clongaddr)==true)
                   {
                       if(m_wenshidustruct[i].shiduval!="")
                       {
                           if(ffval>=m_wenshidustruct[i].shiduval.toFloat(&ok))
                           {
                               if(QString::compare(trUtf8("关"),m_wenshidustruct[i].truefun)==0)
                               {
                                  YuPengStop(m_wenshidustruct[i].cshortaddr,m_wenshidustruct[i].clongaddr);
                               }
                               if(QString::compare(trUtf8("开"),m_wenshidustruct[i].truefun)==0)
                               {
                                  YuPengOn(m_wenshidustruct[i].cshortaddr,m_wenshidustruct[i].clongaddr);
                               }

                           }
                           else
                           {
                               if(QString::compare(trUtf8("关"),m_wenshidustruct[i].truefun)==0)
                               {
                                  YuPengOn(m_wenshidustruct[i].cshortaddr,m_wenshidustruct[i].clongaddr);
                               }
                               if(QString::compare(trUtf8("开"),m_wenshidustruct[i].truefun)==0)
                               {
                                  YuPengStop(m_wenshidustruct[i].cshortaddr,m_wenshidustruct[i].clongaddr);
                               }
                           }
                       }
                   }
                   if(isIrType(m_wenshidustruct[i].clongaddr)==true)
                   {
                       if(m_wenshidustruct[i].shiduval!="")
                       {
                           if(QString::compare(m_wenshidustruct[i].truefun,m_wenshidustruct[i].cfun)==0)
                           {
                               if(ffval>=m_wenshidustruct[i].shiduval.toFloat(&ok))
                               {
                                  Ir_Send(m_wenshidustruct[i].cshortaddr,m_wenshidustruct[i].clongaddr,RetIRCode(m_wenshidustruct[i].clongaddr));

                               }
                           }
                       }

                   }
               }
            }
             break;
       }
        case 9://kongqi yichang
        {
            for(int i=0;i<ikongqistructlength;i++)
            {
               if(QString::compare(macaddr,m_kongqistruct[i].longaddr)==0)
               {
                   if(isKGType(m_kongqistruct[i].clongaddr)==true)
                   {
                       if(QString::compare(trUtf8("关"),m_kongqistruct[i].truefun)==0)
                       {
                          KG_OFF(m_kongqistruct[i].cshortaddr,m_kongqistruct[i].clongaddr);
                       }
                       if(QString::compare(trUtf8("开"),m_kongqistruct[i].truefun)==0)
                       {
                          KG_ON(m_kongqistruct[i].cshortaddr,m_kongqistruct[i].clongaddr);
                       }
                   }
                   if(isCurType(m_kongqistruct[i].clongaddr)==true)
                   {
                       if(QString::compare(trUtf8("关"),m_kongqistruct[i].truefun)==0)
                       {
                          CUR_OFF(m_kongqistruct[i].cshortaddr,m_kongqistruct[i].clongaddr);
                       }
                       if(QString::compare(trUtf8("开"),m_kongqistruct[i].truefun)==0)
                       {
                          CUR_ON(m_kongqistruct[i].cshortaddr,m_kongqistruct[i].clongaddr);
                       }

                   }
                   if(isSunType(m_kongqistruct[i].clongaddr)==true)
                   {
                       if(QString::compare(trUtf8("关"),m_kongqistruct[i].truefun)==0)
                       {
                          SUN_OFF(m_kongqistruct[i].cshortaddr,m_kongqistruct[i].clongaddr,0x00);
                       }
                       if(QString::compare(trUtf8("开"),m_kongqistruct[i].truefun)==0)
                       {
                          SUN_ON(m_kongqistruct[i].cshortaddr,m_kongqistruct[i].clongaddr,0x75);
                       }
                   }
                   if(isYuPengType(m_kongqistruct[i].clongaddr)==true)
                   {
                       if(QString::compare(trUtf8("关"),m_kongqistruct[i].truefun)==0)
                       {
                          YuPengStop(m_kongqistruct[i].cshortaddr,m_kongqistruct[i].clongaddr);
                       }
                       if(QString::compare(trUtf8("开"),m_kongqistruct[i].truefun)==0)
                       {
                          YuPengOn(m_kongqistruct[i].cshortaddr,m_kongqistruct[i].clongaddr);
                       }
                   }
               }
            }
             break;
        }
        case 10://kongqi zhengchang
        {
            for(int i=0;i<ikongqistructlength;i++)
            {
               if(QString::compare(macaddr,m_kongqistruct[i].longaddr)==0)
               {
                   if(isKGType(m_kongqistruct[i].clongaddr)==true)
                   {
                       if(QString::compare(trUtf8("关"),m_kongqistruct[i].truefun)==0)
                       {
                          KG_ON(m_kongqistruct[i].cshortaddr,m_kongqistruct[i].clongaddr);
                       }
                       if(QString::compare(trUtf8("开"),m_kongqistruct[i].truefun)==0)
                       {
                          KG_OFF(m_kongqistruct[i].cshortaddr,m_kongqistruct[i].clongaddr);
                       }
                   }
                   if(isCurType(m_kongqistruct[i].clongaddr)==true)
                   {
                       if(QString::compare(trUtf8("关"),m_kongqistruct[i].truefun)==0)
                       {
                          CUR_ON(m_kongqistruct[i].cshortaddr,m_kongqistruct[i].clongaddr);
                       }
                       if(QString::compare(trUtf8("开"),m_kongqistruct[i].truefun)==0)
                       {
                          CUR_OFF(m_kongqistruct[i].cshortaddr,m_kongqistruct[i].clongaddr);
                       }

                   }
                   if(isSunType(m_kongqistruct[i].clongaddr)==true)
                   {
                       if(QString::compare(trUtf8("关"),m_kongqistruct[i].truefun)==0)
                       {
                          SUN_ON(m_kongqistruct[i].cshortaddr,m_kongqistruct[i].clongaddr,0x00);
                       }
                       if(QString::compare(trUtf8("开"),m_kongqistruct[i].truefun)==0)
                       {
                          SUN_OFF(m_kongqistruct[i].cshortaddr,m_kongqistruct[i].clongaddr,0x75);
                       }
                   }
                   if(isYuPengType(m_kongqistruct[i].clongaddr)==true)
                   {
                       if(QString::compare(trUtf8("关"),m_kongqistruct[i].truefun)==0)
                       {
                          YuPengOn(m_kongqistruct[i].cshortaddr,m_kongqistruct[i].clongaddr);
                       }
                       if(QString::compare(trUtf8("开"),m_kongqistruct[i].truefun)==0)
                       {
                          YuPengStop(m_kongqistruct[i].cshortaddr,m_kongqistruct[i].clongaddr);
                       }
                   }
               }
            }
             break;
        }
    }
}

void AutoControl_V2::SendDataToServerByUdpWenDu(QString dir,char ctype)
{
    ReadSensorValTable();
    bool ok;
    QString str1="";
    QByteArray ba;
    for(int i=0;i<62;i++)
    {
        ba[i]=0x00;
    }
    if(QString::compare(dir,trUtf8("大棚"))==0)
    {
        ba[0]=0x1400/256;
        ba[1]=0x1400%256;
    }
    if(QString::compare(dir,trUtf8("加工厂"))==0)
    {
        ba[0]=0x1500/256;
        ba[1]=0x1500%256;
    }
    if(QString::compare(dir,trUtf8("冷链"))==0)
    {
        ba[0]=0x1600/256;
        ba[1]=0x1600%256;
    }
    if(QString::compare(dir,trUtf8("仓储"))==0)
    {
        ba[0]=0x1700/256;
        ba[1]=0x1700%256;
    }
    if(QString::compare(dir,trUtf8("鱼塘"))==0)
    {
        ba[0]=0x1800/256;
        ba[1]=0x1800%256;
    }
    if(QString::compare(dir,trUtf8("养殖场"))==0)
    {
        ba[0]=0x1900/256;
        ba[1]=0x1900%256;
    }
    if(QString::compare(dir,trUtf8("加油站"))==0)
    {
        ba[0]=0x2100/256;
        ba[1]=0x2100%256;
    }
    if(QString::compare(dir,trUtf8("超市"))==0)
    {
        ba[0]=0x2200/256;
        ba[1]=0x2200%256;
    }
    if(QString::compare(dir,trUtf8("交易所"))==0)
    {
        ba[0]=0x2300/256;
        ba[1]=0x2300%256;
    }
    ba[8]=strtohex(CutMacAddrStr(m_MacAddr,1));
    ba[9]=strtohex(CutMacAddrStr(m_MacAddr,2));
    ba[10]=strtohex(CutMacAddrStr(m_MacAddr,3));
    ba[11]=strtohex(CutMacAddrStr(m_MacAddr,4));
    ba[12]=strtohex(CutMacAddrStr(m_MacAddr,5));
    ba[13]=strtohex(CutMacAddrStr(m_MacAddr,6));//
    switch(ctype)
    {
        case 0x05://wendu
        {
            if((QString::compare(m_sensorvalstruct[1].longaddr,"NULL")!=0)&&(QString::compare(m_sensorvalstruct[1].highval,"NULL")!=0)&&(QString::compare(m_sensorvalstruct[1].lowval,"NULL")!=0))
            {
                str1=CutMACString(1,m_sensorvalstruct[1].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[18]=(qcharaddr.unicode())/256;
                ba[19]=(qcharaddr.unicode())%256;
                str1=CutMACString(2,m_sensorvalstruct[1].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[20]=(qcharaddr.unicode())/256;
                ba[21]=(qcharaddr.unicode())%256;
                str1=CutMACString(3,m_sensorvalstruct[1].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[22]=(qcharaddr.unicode())/256;
                ba[23]=(qcharaddr.unicode())%256;
                str1=CutMACString(4,m_sensorvalstruct[1].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[24]=(qcharaddr.unicode())/256;
                ba[25]=(qcharaddr.unicode())%256;
//               qcharaddr=m_sensorvalstruct[1].longaddr.toInt(&ok,16);
//               ba[24]=(qcharaddr.unicode())/256;
//               ba[25]=(qcharaddr.unicode())%256;
               ba[27]=(char)m_sensorvalstruct[1].highval.toInt(&ok,10);

               ba[28]=(char)m_sensorvalstruct[1].lowval.toInt(&ok,10);
               ba[26]=0x01;
            }
           break;
        }
        case 0x06://shidu
        {
            if((QString::compare(m_sensorvalstruct[2].longaddr,"NULL")!=0)&&(QString::compare(m_sensorvalstruct[2].highval,"NULL")!=0)&&(QString::compare(m_sensorvalstruct[2].lowval,"NULL")!=0))
            {
                str1=CutMACString(1,m_sensorvalstruct[2].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[18]=(qcharaddr.unicode())/256;
                ba[19]=(qcharaddr.unicode())%256;
                str1=CutMACString(2,m_sensorvalstruct[2].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[20]=(qcharaddr.unicode())/256;
                ba[21]=(qcharaddr.unicode())%256;
                str1=CutMACString(3,m_sensorvalstruct[2].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[22]=(qcharaddr.unicode())/256;
                ba[23]=(qcharaddr.unicode())%256;
                str1=CutMACString(4,m_sensorvalstruct[2].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[24]=(qcharaddr.unicode())/256;
                ba[25]=(qcharaddr.unicode())%256;
//               qcharaddr=m_sensorvalstruct[2].addr.toInt(&ok,16);
//               ba[24]=(qcharaddr.unicode())/256;
//               ba[25]=(qcharaddr.unicode())%256;
               ba[30]=(char)m_sensorvalstruct[2].highval.toInt(&ok,10);
               ba[31]=(char)m_sensorvalstruct[2].lowval.toInt(&ok,10);
               ba[29]=0x01;
            }
           break;
        }
        case 0x20://guangxian
        {
            if((QString::compare(m_sensorvalstruct[9].longaddr,"NULL")!=0)&&(QString::compare(m_sensorvalstruct[9].highval,"NULL")!=0))
            {
                str1=CutMACString(1,m_sensorvalstruct[9].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[18]=(qcharaddr.unicode())/256;
                ba[19]=(qcharaddr.unicode())%256;
                str1=CutMACString(2,m_sensorvalstruct[9].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[20]=(qcharaddr.unicode())/256;
                ba[21]=(qcharaddr.unicode())%256;
                str1=CutMACString(3,m_sensorvalstruct[9].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[22]=(qcharaddr.unicode())/256;
                ba[23]=(qcharaddr.unicode())%256;
                str1=CutMACString(4,m_sensorvalstruct[9].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[24]=(qcharaddr.unicode())/256;
                ba[25]=(qcharaddr.unicode())%256;
//               qcharaddr=m_sensorvalstruct[9].addr.toInt(&ok,16);
//               ba[24]=(qcharaddr.unicode())/256;
//               ba[25]=(qcharaddr.unicode())%256;
               ba[36]=(char)m_sensorvalstruct[9].highval.toInt(&ok,10);
               ba[32]=0x01;
            }
           break;
        }
        case 0x22://kongqizhiliang
        {
            if((QString::compare(m_sensorvalstruct[10].longaddr,"NULL")!=0)&&(QString::compare(m_sensorvalstruct[10].highval,"NULL")!=0))
            {
                str1=CutMACString(1,m_sensorvalstruct[10].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[18]=(qcharaddr.unicode())/256;
                ba[19]=(qcharaddr.unicode())%256;
                str1=CutMACString(2,m_sensorvalstruct[10].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[20]=(qcharaddr.unicode())/256;
                ba[21]=(qcharaddr.unicode())%256;
                str1=CutMACString(3,m_sensorvalstruct[10].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[22]=(qcharaddr.unicode())/256;
                ba[23]=(qcharaddr.unicode())%256;
                str1=CutMACString(4,m_sensorvalstruct[10].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[24]=(qcharaddr.unicode())/256;
                ba[25]=(qcharaddr.unicode())%256;
//               qcharaddr=m_sensorvalstruct[10].addr.toInt(&ok,16);
//               ba[24]=(qcharaddr.unicode())/256;
//               ba[25]=(qcharaddr.unicode())%256;
               int i=m_sensorvalstruct[10].highval.toInt(&ok,10);
               if(i==0)
               {
                   ba[46]=0x00;
               }
               if(i==1)
               {
                   ba[46]=0x01;
               }
               ba[45]=0x01;
            }
           break;
        }
        case 0x03://eryanghuatan
        {
            if((QString::compare(m_sensorvalstruct[11].longaddr,"NULL")!=0)&&(QString::compare(m_sensorvalstruct[12].highval,"NULL")!=0))
            {
                str1=CutMACString(1,m_sensorvalstruct[11].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[18]=(qcharaddr.unicode())/256;
                ba[19]=(qcharaddr.unicode())%256;
                str1=CutMACString(2,m_sensorvalstruct[11].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[20]=(qcharaddr.unicode())/256;
                ba[21]=(qcharaddr.unicode())%256;
                str1=CutMACString(3,m_sensorvalstruct[11].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[22]=(qcharaddr.unicode())/256;
                ba[23]=(qcharaddr.unicode())%256;
                str1=CutMACString(4,m_sensorvalstruct[11].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[24]=(qcharaddr.unicode())/256;
                ba[25]=(qcharaddr.unicode())%256;
    //               qcharaddr=m_sensorvalstruct[12].addr.toInt(&ok,16);
    //               ba[24]=(qcharaddr.unicode())/256;
    //               ba[25]=(qcharaddr.unicode())%256;
               int i=m_sensorvalstruct[11].highval.toInt(&ok,10);
               if(i==0)
               {
                   ba[58]=0x00;
               }
               if(i==1)
               {
                   ba[58]=0x01;
               }
               ba[57]=0x01;

              }
           break;
        }
        case 0x09://qiti
        {
            if((QString::compare(m_sensorvalstruct[12].longaddr,"NULL")!=0)&&(QString::compare(m_sensorvalstruct[12].highval,"NULL")!=0))
            {
                str1=CutMACString(1,m_sensorvalstruct[12].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[18]=(qcharaddr.unicode())/256;
                ba[19]=(qcharaddr.unicode())%256;
                str1=CutMACString(2,m_sensorvalstruct[12].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[20]=(qcharaddr.unicode())/256;
                ba[21]=(qcharaddr.unicode())%256;
                str1=CutMACString(3,m_sensorvalstruct[12].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[22]=(qcharaddr.unicode())/256;
                ba[23]=(qcharaddr.unicode())%256;
                str1=CutMACString(4,m_sensorvalstruct[12].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[24]=(qcharaddr.unicode())/256;
                ba[25]=(qcharaddr.unicode())%256;
//               qcharaddr=m_sensorvalstruct[12].addr.toInt(&ok,16);
//               ba[24]=(qcharaddr.unicode())/256;
//               ba[25]=(qcharaddr.unicode())%256;
               int i=m_sensorvalstruct[12].highval.toInt(&ok,10);
               if(i==0)
               {
                   ba[44]=0x00;
               }
               if(i==1)
               {
                   ba[44]=0x01;
               }
               ba[43]=0x01;

              }
           break;
        }
        case 0x21://yanwu
        {
            if((QString::compare(m_sensorvalstruct[13].longaddr,"NULL")!=0)&&(QString::compare(m_sensorvalstruct[13].highval,"NULL")!=0))
            {
                str1=CutMACString(1,m_sensorvalstruct[13].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[18]=(qcharaddr.unicode())/256;
                ba[19]=(qcharaddr.unicode())%256;
                str1=CutMACString(2,m_sensorvalstruct[13].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[20]=(qcharaddr.unicode())/256;
                ba[21]=(qcharaddr.unicode())%256;
                str1=CutMACString(3,m_sensorvalstruct[13].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[22]=(qcharaddr.unicode())/256;
                ba[23]=(qcharaddr.unicode())%256;
                str1=CutMACString(4,m_sensorvalstruct[13].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[24]=(qcharaddr.unicode())/256;
                ba[25]=(qcharaddr.unicode())%256;
//               qcharaddr=m_sensorvalstruct[13].addr.toInt(&ok,16);
//               ba[24]=(qcharaddr.unicode())/256;
//               ba[25]=(qcharaddr.unicode())%256;
               int i=m_sensorvalstruct[13].highval.toInt(&ok,10);
               if(i==0)
               {
                   ba[38]=0x00;
               }
               if(i==1)
               {
                   ba[38]=0x01;
               }
               ba[37]=0x01;

              }
        break;
        }
        case 0x14://renti
        {
            if((QString::compare(m_sensorvalstruct[14].longaddr,"NULL")!=0)&&(QString::compare(m_sensorvalstruct[14].highval,"NULL")!=0))
            {
                str1=CutMACString(1,m_sensorvalstruct[14].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[18]=(qcharaddr.unicode())/256;
                ba[19]=(qcharaddr.unicode())%256;
                str1=CutMACString(2,m_sensorvalstruct[14].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[20]=(qcharaddr.unicode())/256;
                ba[21]=(qcharaddr.unicode())%256;
                str1=CutMACString(3,m_sensorvalstruct[14].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[22]=(qcharaddr.unicode())/256;
                ba[23]=(qcharaddr.unicode())%256;
                str1=CutMACString(4,m_sensorvalstruct[14].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[24]=(qcharaddr.unicode())/256;
                ba[25]=(qcharaddr.unicode())%256;
//               qcharaddr=m_sensorvalstruct[14].addr.toInt(&ok,16);
//               ba[24]=(qcharaddr.unicode())/256;
//               ba[25]=(qcharaddr.unicode())%256;
               int i=m_sensorvalstruct[14].highval.toInt(&ok,10);
               if(i==0)
               {
                   ba[40]=0x00;
               }
               if(i==1)
               {
                   ba[40]=0x01;
               }
               ba[39]=0x01;
               break;
            }
        }
        case 0x43://menci
        {

            if((QString::compare(m_sensorvalstruct[15].longaddr,"NULL")!=0)&&(QString::compare(m_sensorvalstruct[15].highval,"NULL")!=0))
            {
                str1=CutMACString(1,m_sensorvalstruct[15].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[18]=(qcharaddr.unicode())/256;
                ba[19]=(qcharaddr.unicode())%256;
                str1=CutMACString(2,m_sensorvalstruct[15].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[20]=(qcharaddr.unicode())/256;
                ba[21]=(qcharaddr.unicode())%256;
                str1=CutMACString(3,m_sensorvalstruct[15].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[22]=(qcharaddr.unicode())/256;
                ba[23]=(qcharaddr.unicode())%256;
                str1=CutMACString(4,m_sensorvalstruct[15].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[24]=(qcharaddr.unicode())/256;
                ba[25]=(qcharaddr.unicode())%256;
//               qcharaddr=m_sensorvalstruct[15].addr.toInt(&ok,16);
//               ba[24]=(qcharaddr.unicode())/256;
//               ba[25]=(qcharaddr.unicode())%256;
               int i=m_sensorvalstruct[15].highval.toInt(&ok,10);
               if(i==0)
               {
                   ba[42]=0x00;
               }
               if(i==1)
               {
                   ba[42]=0x01;
               }
               ba[41]=0x01;
            }
        break;
        }
        case 0x01://氧气
        {
            if((QString::compare(m_sensorvalstruct[16].longaddr,"NULL")!=0)&&(QString::compare(m_sensorvalstruct[16].highval,"NULL")!=0))
            {
                str1=CutMACString(1,m_sensorvalstruct[16].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[18]=(qcharaddr.unicode())/256;
                ba[19]=(qcharaddr.unicode())%256;
                str1=CutMACString(2,m_sensorvalstruct[16].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[20]=(qcharaddr.unicode())/256;
                ba[21]=(qcharaddr.unicode())%256;
                str1=CutMACString(3,m_sensorvalstruct[16].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[22]=(qcharaddr.unicode())/256;
                ba[23]=(qcharaddr.unicode())%256;
                str1=CutMACString(4,m_sensorvalstruct[16].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[24]=(qcharaddr.unicode())/256;
                ba[25]=(qcharaddr.unicode())%256;
    //               qcharaddr=m_sensorvalstruct[1].longaddr.toInt(&ok,16);
    //               ba[24]=(qcharaddr.unicode())/256;
    //               ba[25]=(qcharaddr.unicode())%256;
               ba[51]=(char)m_sensorvalstruct[16].highval.toInt(&ok,10);
               ba[47]=0x01;
            }
           break;
        }
        case 0x02://水位
        {
            if((QString::compare(m_sensorvalstruct[17].longaddr,"NULL")!=0)&&(QString::compare(m_sensorvalstruct[17].highval,"NULL")!=0))
            {
                str1=CutMACString(1,m_sensorvalstruct[17].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[18]=(qcharaddr.unicode())/256;
                ba[19]=(qcharaddr.unicode())%256;
                str1=CutMACString(2,m_sensorvalstruct[17].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[20]=(qcharaddr.unicode())/256;
                ba[21]=(qcharaddr.unicode())%256;
                str1=CutMACString(3,m_sensorvalstruct[17].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[22]=(qcharaddr.unicode())/256;
                ba[23]=(qcharaddr.unicode())%256;
                str1=CutMACString(4,m_sensorvalstruct[17].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[24]=(qcharaddr.unicode())/256;
                ba[25]=(qcharaddr.unicode())%256;
    //               qcharaddr=m_sensorvalstruct[1].longaddr.toInt(&ok,16);
    //               ba[24]=(qcharaddr.unicode())/256;
    //               ba[25]=(qcharaddr.unicode())%256;
               ba[56]=(char)m_sensorvalstruct[17].highval.toInt(&ok,10);
               ba[52]=0x01;
            }
           break;
        }
        case 0x04://PH
        {
            if((QString::compare(m_sensorvalstruct[18].longaddr,"NULL")!=0)&&(QString::compare(m_sensorvalstruct[18].highval,"NULL")!=0))
            {
                str1=CutMACString(1,m_sensorvalstruct[18].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[18]=(qcharaddr.unicode())/256;
                ba[19]=(qcharaddr.unicode())%256;
                str1=CutMACString(2,m_sensorvalstruct[18].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[20]=(qcharaddr.unicode())/256;
                ba[21]=(qcharaddr.unicode())%256;
                str1=CutMACString(3,m_sensorvalstruct[18].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[22]=(qcharaddr.unicode())/256;
                ba[23]=(qcharaddr.unicode())%256;
                str1=CutMACString(4,m_sensorvalstruct[18].longaddr);
                qcharaddr=str1.toInt(&ok,16);
                ba[24]=(qcharaddr.unicode())/256;
                ba[25]=(qcharaddr.unicode())%256;
    //               qcharaddr=m_sensorvalstruct[1].longaddr.toInt(&ok,16);
    //               ba[24]=(qcharaddr.unicode())/256;
    //               ba[25]=(qcharaddr.unicode())%256;
               ba[60]=(char)m_sensorvalstruct[18].highval.toInt(&ok,10);
               ba[61]=(char)m_sensorvalstruct[18].lowval.toInt(&ok,10);
               ba[59]=0x01;
            }
           break;
        }
    }
    ba[5]=(char)ba.size();
    int ret= m_udp->writeDatagram(ba.data(),ba.size(),QHostAddress::Broadcast,16889);//19892008
    //int ret= m_udp->writeDatagram(ba.data(),ba.size(),QHostAddress::LocalHost,16889);//19892008
    if(ret==-1)
    {
        ui->label->setText("sender error");
    }
}

void AutoControl_V2::SendDataToServeByCar(QString dir,QString macaddr,char tempval)
{
    bool ok;
    QString str1="";
    QByteArray ba;
    for(int i=0;i<28;i++)
    {
        ba[i]=0x00;
    }
    if(QString::compare(dir,trUtf8("大棚"))==0)
    {
        ba[0]=0x1408/256;
        ba[1]=0x1408%256;
    }
    if(QString::compare(dir,trUtf8("加工厂"))==0)
    {
        ba[0]=0x1508/256;
        ba[1]=0x1508%256;
    }
    if(QString::compare(dir,trUtf8("冷链"))==0)
    {
        ba[0]=0x1608/256;
        ba[1]=0x1608%256;
    }
    if(QString::compare(dir,trUtf8("仓储"))==0)
    {
        ba[0]=0x1708/256;
        ba[1]=0x1708%256;
    }
    if(QString::compare(dir,trUtf8("鱼塘"))==0)
    {
        ba[0]=0x1808/256;
        ba[1]=0x1808%256;
    }
    if(QString::compare(dir,trUtf8("养殖场"))==0)
    {
        ba[0]=0x1908/256;
        ba[1]=0x1908%256;
    }
    if(QString::compare(dir,trUtf8("加油站"))==0)
    {
        ba[0]=0x2108/256;
        ba[1]=0x2108%256;
    }
    if(QString::compare(dir,trUtf8("超市"))==0)
    {
        ba[0]=0x2208/256;
        ba[1]=0x2208%256;
    }
    if(QString::compare(dir,trUtf8("交易所"))==0)
    {
        ba[0]=0x2308/256;
        ba[1]=0x2308%256;
    }
    ba[8]=strtohex(CutMacAddrStr(m_MacAddr,1));
    ba[9]=strtohex(CutMacAddrStr(m_MacAddr,2));
    ba[10]=strtohex(CutMacAddrStr(m_MacAddr,3));
    ba[11]=strtohex(CutMacAddrStr(m_MacAddr,4));
    ba[12]=strtohex(CutMacAddrStr(m_MacAddr,5));
    ba[13]=strtohex(CutMacAddrStr(m_MacAddr,6));

    str1=CutMACString(1,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    ba[18]=(qcharaddr.unicode())/256;
    ba[19]=(qcharaddr.unicode())%256;
    str1=CutMACString(2,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    ba[20]=(qcharaddr.unicode())/256;
    ba[21]=(qcharaddr.unicode())%256;
    str1=CutMACString(3,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    ba[22]=(qcharaddr.unicode())/256;
    ba[23]=(qcharaddr.unicode())%256;
    str1=CutMACString(4,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    ba[24]=(qcharaddr.unicode())/256;
    ba[25]=(qcharaddr.unicode())%256;
    ba[27]=(char)tempval;
    ba[26]=0x01;
    ba[5]=(char)ba.size();
    int ret= m_udp->writeDatagram(ba.data(),ba.size(),QHostAddress::Broadcast,16889);//19892008
    if(ret==-1)
    {
        ui->label->setText("sender error");
    }
}





QString AutoControl_V2::FindShortAddrByName(QString str)//
{
    for(int j=0;j<ui->tableWidget->rowCount();j++)
    {
        QTableWidgetItem *item = ui->tableWidget->item(j,0);
        if(QString::compare(str,item->text())==0)
        {
            QTableWidgetItem *item1 = ui->tableWidget->item(j,2);
            return item1->text();
        }
    }
    return "";
}

QString AutoControl_V2::FindLongAddrByName(QString str)//
{
    for(int j=0;j<ui->tableWidget->rowCount();j++)
    {
        QTableWidgetItem *item = ui->tableWidget->item(j,0);
        if(QString::compare(str,item->text())==0)
        {
           QTableWidgetItem *item1 = ui->tableWidget->item(j,3);
           return item1->text();
        }
    }
    return "";
}

QString AutoControl_V2::FindShortAddrWhile(QString name,QString dir)
{
   for(int i=0;i<ui->tableWidget->rowCount();i++)
   {
      QTableWidgetItem *item = ui->tableWidget->item(i,0);
      QTableWidgetItem *item1 = ui->tableWidget->item(i,1);
      if((QString::compare(item->text(),name)==0)&&(QString::compare(item1->text(),dir)==0))
      {
        item1 = ui->tableWidget->item(i,2);
        return item1->text();
      }
   }
   return "NULL";
}

QString AutoControl_V2::FindLongAddrWhile(QString name,QString dir)
{
    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
       QTableWidgetItem *item = ui->tableWidget->item(i,0);
       QTableWidgetItem *item1 = ui->tableWidget->item(i,1);
       if((QString::compare(item->text(),name)==0)&&(QString::compare(item1->text(),dir)==0))
       {
          item1 = ui->tableWidget->item(i,3);
          return item1->text();
       }
    }
    return "NULL";
}

QString AutoControl_V2::GetMacAddr()
{
    //QList为Qt提供链表
    QList<QNetworkInterface> list=QNetworkInterface::allInterfaces();//获取所有网络接口的列表
    foreach(QNetworkInterface m_macaddr,list)
    {
        qDebug()<<m_macaddr.hardwareAddress();//输出硬件地址
        m_MacAddr=m_macaddr.hardwareAddress();

    }
    return m_MacAddr;
}

QString AutoControl_V2::CutTelnumber(int itype,QString telnum)
{
    QString str="";
    switch(itype)
    {
        case 1:
        {
           str=telnum.mid(0,1);

           break;
        }
        case 2:
        {
           str=telnum.mid(1,1);

           break;
        }
        case 3:
        {
           str=telnum.mid(2,1);

           break;
        }
        case 4:
        {
           str=telnum.mid(3,1);

           break;
        }
        case 5:
        {
           str=telnum.mid(4,1);

           break;
        }
        case 6:
        {
           str=telnum.mid(5,1);

           break;
        }
        case 7:
        {
           str=telnum.mid(6,1);

           break;
        }
        case 8:
        {
           str=telnum.mid(7,1);

           break;
        }
        case 9:
        {
           str=telnum.mid(8,1);

           break;
        }
        case 10:
        {
           str=telnum.mid(9,1);

           break;
        }
        case 11:
        {
           str=telnum.mid(10,1);

           break;
        }
        default:
        {
           break;
        }
    }
    return str;
}

void AutoControl_V2::SendWenDuOrderToCar(QString TelNum,QString macaddr)
{

    QString str1="";bool ok=1;
    str1=CutTelnumber(1,TelNum);
    sendcar[12]=str1.toInt(&ok,10)+48;
    str1=CutTelnumber(2,TelNum);
    sendcar[13]=str1.toInt(&ok,10)+48;
    str1=CutTelnumber(3,TelNum);
    sendcar[14]=str1.toInt(&ok,10)+48;
    str1=CutTelnumber(4,TelNum);
    sendcar[15]=str1.toInt(&ok,10)+48;
    str1=CutTelnumber(5,TelNum);
    sendcar[16]=str1.toInt(&ok,10)+48;
    str1=CutTelnumber(6,TelNum);
    sendcar[17]=str1.toInt(&ok,10)+48;
    str1=CutTelnumber(7,TelNum);
    sendcar[18]=str1.toInt(&ok,10)+48;
    str1=CutTelnumber(8,TelNum);
    sendcar[19]=str1.toInt(&ok,10)+48;
    str1=CutTelnumber(9,TelNum);
    sendcar[20]=str1.toInt(&ok,10)+48;
    str1=CutTelnumber(10,TelNum);
    sendcar[21]=str1.toInt(&ok,10)+48;
    str1=CutTelnumber(11,TelNum);
    sendcar[22]=str1.toInt(&ok,10)+48;

    str1=CutMACString(1,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    sendcar[24]=(qcharaddr.unicode())/256;
    sendcar[25]=(qcharaddr.unicode())%256;
    str1=CutMACString(2,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    sendcar[26]=(qcharaddr.unicode())/256;
    sendcar[27]=(qcharaddr.unicode())%256;
    str1=CutMACString(3,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    sendcar[28]=(qcharaddr.unicode())/256;
    sendcar[29]=(qcharaddr.unicode())%256;
    str1=CutMACString(4,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    sendcar[30]=(qcharaddr.unicode())/256;
    sendcar[31]=(qcharaddr.unicode())%256;
    sendcar[1]=0x1A;
    m_Com->write(sendcar,32);

    //qDebug()<<"car wendu fa";
}

void AutoControl_V2::SendWenDuOrderToCarNoDuanXin(QString macaddr)
{
    bool ok=1;
    QString str1="";
    str1=CutMACString(1,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    sendcarnoduanxin[13]=(qcharaddr.unicode())/256;
    sendcarnoduanxin[14]=(qcharaddr.unicode())%256;
    str1=CutMACString(2,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    sendcarnoduanxin[15]=(qcharaddr.unicode())/256;
    sendcarnoduanxin[16]=(qcharaddr.unicode())%256;
    str1=CutMACString(3,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    sendcarnoduanxin[17]=(qcharaddr.unicode())/256;
    sendcarnoduanxin[18]=(qcharaddr.unicode())%256;
    str1=CutMACString(4,macaddr);
    qcharaddr=str1.toInt(&ok,16);
    sendcarnoduanxin[19]=(qcharaddr.unicode())/256;
    sendcarnoduanxin[20]=(qcharaddr.unicode())%256;
    m_Com->write(sendcarnoduanxin,21);

    //qDebug()<<"car wendu fa";
}

//void AutoControl_V2::DeleteSensorDataTableToNull()
//{
//    QSqlQuery m_query(m_sql);
//    m_query.prepare("delete FROM SensorDataTable");
//    bool ok=m_query.exec();
//    if(ok==false)
//    {
//       qDebug("shanchu wenshidu cuowu");
//       return;
//    }
//}

//--------------------------


//基础测试界面
void AutoControl_V2::on_BackPB_clicked()
{
    this->hide();
    this->ISTparent->show();
}

void AutoControl_V2::SensorFun()
{
    for(int i=0;i<17;i++)
    {
        if(rownum[i]>0)
        {
            JDSecond[i]++;
            if(JDSecond[i]== 20)
            {
                JDFlag[i]=false;
            }
        }
    }
}
