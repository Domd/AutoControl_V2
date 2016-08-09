#include "inteagricul.h"
#include "ui_inteagricul.h"

InteAgricul::InteAgricul(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InteAgricul)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    QPixmap pixmap;
    pixmap.load(":/images/inteagri/302.png");
    QPalette p(palette());
    p.setBrush(QPalette::Window,QBrush(pixmap));
    setPalette(p);

    pixmap1.load(":/images/intehomefurn/on.png");
    pixmap2.load(":/images/intehomefurn/off.png");
    pix1.load(":/images/inteagri/30.png");
    pix2.load(":/images/inteagri/31.png");

    for(int i=0;i<5;i++)
    {
        changeNum[i]=false;
    }

    pixmap.load(":/images/inteagri/1.png");
    ui->toolButton->setIcon(pixmap);
    ui->toolButton->setIconSize(pixmap.size());
    ui->toolButton->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/inteagri/2.png");
    ui->toolButton_2->setIcon(pixmap);
    ui->toolButton_2->setIconSize(pixmap.size());
    ui->toolButton_2->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/inteagri/3.png");
    ui->toolButton_3->setIcon(pixmap);
    ui->toolButton_3->setIconSize(pixmap.size());
    ui->toolButton_3->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/inteagri/4.png");
    ui->toolButton_4->setIcon(pixmap);
    ui->toolButton_4->setIconSize(pixmap.size());
    ui->toolButton_4->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/inteagri/5.png");
    ui->toolButton_5->setIcon(pixmap);
    ui->toolButton_5->setIconSize(pixmap.size());
    ui->toolButton_5->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/inteagri/6.png");
    ui->toolButton_6->setIcon(pixmap);
    ui->toolButton_6->setIconSize(pixmap.size());
    ui->toolButton_6->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/inteagri/7.png");
    ui->toolButton_7->setIcon(pixmap);
    ui->toolButton_7->setIconSize(pixmap.size());
    ui->toolButton_7->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/inteagri/8.png");
    ui->sureTB->setIcon(pixmap);
    ui->sureTB->setIconSize(pixmap.size());
    ui->sureTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/inteagri/20.png");
    ui->toolButton_8->setIcon(pixmap);
    ui->toolButton_8->setIconSize(pixmap.size());
    ui->toolButton_8->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");



    ui->stackedWidget->setCurrentIndex(0);
    ui->mainfaceLabel->setPixmap(QPixmap(":/images/inteagri/10.png"));

    ui->p2Label->setPixmap(QPixmap(":/images/inteagri/11.png"));
    ui->p3Label->setPixmap(QPixmap(":/images/inteagri/12.png"));
    ui->p4Label->setPixmap(QPixmap(":/images/inteagri/13.png"));
    ui->p5Label->setPixmap(QPixmap(":/images/inteagri/14.png"));
    ui->p6Label->setPixmap(QPixmap(":/images/inteagri/15.png"));

    pixmap.load(":/images/inteagri/30.png");
    ui->s1Label->setPixmap(pixmap);
    ui->s1Label->setScaledContents(true);
    ui->s2Label->setPixmap(pixmap);
    ui->s2Label->setScaledContents(true);
    ui->s3Label->setPixmap(pixmap);
    ui->s3Label->setScaledContents(true);
    ui->s4Label->setPixmap(pixmap);
    ui->s4Label->setScaledContents(true);
    ui->s5Label->setPixmap(pixmap);
    ui->s5Label->setScaledContents(true);
    ui->s6Label->setPixmap(pixmap);
    ui->s6Label->setScaledContents(true);
    ui->s7Label->setPixmap(pixmap);
    ui->s7Label->setScaledContents(true);
    ui->s8Label->setPixmap(pixmap);
    ui->s8Label->setScaledContents(true);
    ui->s9Label->setPixmap(pixmap);
    ui->s9Label->setScaledContents(true);
    ui->s0Label->setPixmap(pixmap);
    ui->s0Label->setScaledContents(true);

    ui->diguanPix->setPixmap(pix1);
    ui->diguanPix->setScaledContents(true);
    ui->LEDPix->setPixmap(QPixmap(":/images/light/light1.png"));
    ui->LEDPix->setScaledContents(true);
//    ui->tongfengPix->setPixmap(QPixmap(":/images/fan/f1.png"));
//    ui->tongfengPix->setScaledContents(true);

    m_timer=new QTimer(this);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(readInfo()));
//    m_timer->start(2000);

    ui->sunLine->setReadOnly(true);
    ui->sunLine->setAlignment(Qt::AlignRight);
    ui->sunLine->setMaxLength(15);

    ui->tempLine->setReadOnly(true);
    ui->tempLine->setAlignment(Qt::AlignRight);
    ui->tempLine->setMaxLength(15);

    ui->humLine->setReadOnly(true);
    ui->humLine->setAlignment(Qt::AlignRight);
    ui->humLine->setMaxLength(15);

    ui->soiltempLine->setReadOnly(true);
    ui->soiltempLine->setAlignment(Qt::AlignRight);
    ui->soiltempLine->setMaxLength(15);

    ui->soilhumLine->setReadOnly(true);
    ui->soilhumLine->setAlignment(Qt::AlignRight);
    ui->soilhumLine->setMaxLength(15);

    ui->sunLine->setText("0");
    ui->tempLine->setText("0");
    ui->humLine->setText("0");
    ui->soiltempLine->setText("0");
    ui->soilhumLine->setText("0");

    FsunPreVal=20;
    FtempPreVal=20;
    FhumPreVal=20;
    FsoiltempPreVal=20;
    FsoilhumPreVal=20;
//演示板的器件的状态
    fengshanStatus=false;
    ledStatus=false;
    diguanStatus=false;

    countSMG=0;  //给数码管发送数据时间计数
    controlMode=false;//初始化为手动

    ui->sunvalLabel4->setText(QString::number(FsunPreVal));
    ui->sunvalLabel6->setText(QString::number(FsunPreVal));
    ui->tempvalLabel4->setText(QString::number(FtempPreVal));
    ui->tempvalLabel6->setText(QString::number(FtempPreVal));
    ui->humvalLabel4->setText(QString::number(FhumPreVal));
    ui->humvalLabel6->setText(QString::number(FhumPreVal));
    ui->soiltempvalLabel4->setText(QString::number(FsoiltempPreVal));
    ui->soiltempvalLabel6->setText(QString::number(FsoiltempPreVal));
    ui->soilhumvalLabel4->setText(QString::number(FsoilhumPreVal));
    ui->soilhumvalLabel6->setText(QString::number(FsoilhumPreVal));

    connect(ui->sunLine,SIGNAL(selectionChanged()),this,SLOT(lineClick1()));
    connect(ui->tempLine,SIGNAL(selectionChanged()),this,SLOT(lineClick2()));
    connect(ui->humLine,SIGNAL(selectionChanged()),this,SLOT(lineClick3()));
    connect(ui->soiltempLine,SIGNAL(selectionChanged()),this,SLOT(lineClick4()));
    connect(ui->soilhumLine,SIGNAL(selectionChanged()),this,SLOT(lineClick5()));

    vKey=new VKey(this);

    fan_pix[0].load(":/images/fan/f1.png");
    fan_pix[1].load(":/images/fan/f2.png");
    fan_pix[2].load(":/images/fan/f3.png");
    fan_pix[3].load(":/images/fan/f4.png");
    fan_pix[4].load(":/images/fan/f5.png");
    fan_pix[5].load(":/images/fan/f6.png");
    fan_pix[6].load(":/images/fan/f7.png");
    fan_pix[7].load(":/images/fan/f8.png");

    ui->tongfengPix->setPixmap(fan_pix[0]);
    fan_timer =  new QTimer(this);
    connect(fan_timer,SIGNAL(timeout()),this,SLOT(runFan()));
//    fan_timer->start(250);
    fan_count=-1;
}

InteAgricul::~InteAgricul()
{
    delete ui;

    fan_timer->stop();
    delete fan_timer;

    m_timer->stop();
    delete m_timer;
    delete vKey;
}
//系统主页
void InteAgricul::on_toolButton_7_clicked()
{
    this->m_timer->stop();
    this->parent->show();
    this->close();
}

void InteAgricul::on_toolButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->toolButton->setFocus();
}

void InteAgricul::on_toolButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->toolButton_2->setFocus();
}


void InteAgricul::on_toolButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->toolButton_3->setFocus();
}

void InteAgricul::on_toolButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->toolButton_4->setFocus();
}

void InteAgricul::on_toolButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    ui->toolButton_5->setFocus();
}

void InteAgricul::on_toolButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->toolButton_6->setFocus();
}



void InteAgricul::readInfo()
{
     if(m_control->changeData3)
     {
       if(m_control->rownum[11]>0)
       {
            ui->tempLabel->setText("<font color=green>"+m_control->tempNow+'C'+"</font>");
            ui->tempLabel4->setText("<font color=green>"+m_control->tempNow+"%RH"+"</font>");
            ui->humLabel->setText("<font color=green>"+m_control->humNow+'C'+"</font>");
            ui->humLabel4->setText("<font color=green>"+m_control->humNow+"%RH"+"</font>");
       }
       if(m_control->rownum[12]>0)
       {
            ui->soiltempLabel->setText("<font color=green>"+m_control->soiltempNow+'C'+"</font>");
            ui->soilhumLabel->setText("<font color=green>"+m_control->soilhumNow+"%RH"+"</font>");
            ui->soiltempLabel4->setText("<font color=green>"+m_control->soiltempNow+'C'+"</font>");
            ui->soilhumLabel4->setText("<font color=green>"+m_control->soilhumNow+"%RH"+"</font>");
       }
       if(m_control->rownum[10]>0)
       {
            ui->sunLabel->setText("<font color=green>"+m_control->guangxianNow+"</font>");
            ui->sunLabel4->setText("<font color=green>"+m_control->guangxianNow+"</font>");
        }
        if(m_control->rownum[13]>0)
        {
            ui->co2Label->setText("<font color=green>"+m_control->co2Now+"</font>");
            ui->co2Label4->setText("<font color=green>"+m_control->co2Now+"</font>");
         }
         if(m_control->rownum[14]>0)
            ui->fireLabel4->setText("<font color=green>"+m_control->huoyanNow+"</font>");

         m_control->changeData3=false;
     }
//节点的状态
     if(m_control->changeAgriDB)
     {
         for(int i=0;i<m_control->isensorlength;i++)
         {
             if(m_control->rownum[10]>0)
             {
                 if(m_control->m_sensorstruct[i].name==trUtf8("光线"))
                {
                    if(m_control->m_sensorstruct[i].status==trUtf8("在线"))
                        ui->s1Label->setPixmap(pix2);
                    else
                    {
                        m_control->guangxianNow="0";
                        ui->sunLabel->setText("");
                        ui->sunLabel4->setText("");
                        ui->s1Label->setPixmap(pix1);
                    }
                }
             }
             else
             {
                 m_control->guangxianNow="0";
                 ui->sunLabel->setText("");
                 ui->sunLabel4->setText("");
                 ui->s1Label->setPixmap(pix1);
             }

             if(m_control->rownum[13]>0)
             {
                if(m_control->m_sensorstruct[i].name==trUtf8("二氧化碳"))
                {
                    if(m_control->m_sensorstruct[i].status==trUtf8("在线"))
                        ui->s3Label->setPixmap(pix2);
                    else
                    {
                        m_control->co2Now="";
                        ui->co2Label->setText("");
                        ui->co2Label4->setText("");
                        ui->s3Label->setPixmap(pix1);
                    }
                }
             }
             else
             {
                 m_control->co2Now="";
                 ui->co2Label->setText("");
                 ui->co2Label4->setText("");
                 ui->s3Label->setPixmap(pix1);
             }
             if(m_control->rownum[12]>0)
             {
                if(m_control->m_sensorstruct[i].name==trUtf8("土壤温湿度"))
                {
                    if(m_control->m_sensorstruct[i].status==trUtf8("在线"))
                        ui->s7Label->setPixmap(pix2);
                    else
                    {
                        m_control->soiltempNow="0";
                        m_control->soilhumNow="0";
                        ui->soiltempLabel->setText("");
                        ui->soilhumLabel->setText("");
                        ui->soiltempLabel4->setText("");
                        ui->soilhumLabel4->setText("");
                        ui->s7Label->setPixmap(pix1);
                    }
                }
             }
             else
             {
                 m_control->soiltempNow="0";
                 m_control->soilhumNow="0";
                 ui->soiltempLabel->setText("");
                 ui->soilhumLabel->setText("");
                 ui->soiltempLabel4->setText("");
                 ui->soilhumLabel4->setText("");
                 ui->s7Label->setPixmap(pix1);
              }
             if(m_control->rownum[11]>0)
             {
                if(m_control->m_sensorstruct[i].name==trUtf8("温湿度"))
                {
                    if(m_control->m_sensorstruct[i].status==trUtf8("在线"))
                        ui->s5Label->setPixmap(pix2);
                    else
                    {
                        m_control->tempNow="0";
                        m_control->humNow="0";
                        ui->tempLabel->setText("");
                        ui->humLabel->setText("");
                        ui->tempLabel4->setText("");
                        ui->humLabel4->setText("");
                        ui->s5Label->setPixmap(pix1);
                    }
                }
             }
             else
             {
                 m_control->tempNow="0";
                 m_control->humNow="0";
                 ui->tempLabel->setText("");
                 ui->humLabel->setText("");
                 ui->tempLabel4->setText("");
                 ui->humLabel4->setText("");
                 ui->s5Label->setPixmap(pix1);
             }

             if(m_control->rownum[14]>0)
             {
                if(m_control->m_sensorstruct[i].name==trUtf8("火焰"))
                {
                    if(m_control->m_sensorstruct[i].status==trUtf8("在线"))
                        ui->s9Label->setPixmap(pix2);
                    else
                    {
                        m_control->huoyanNow="0";
                        ui->fireLabel4->setText("");
                        ui->s9Label->setPixmap(pix1);
                     }
                }
             }
             else
             {
                 m_control->huoyanNow="0";
                 ui->fireLabel4->setText("");
                 ui->s9Label->setPixmap(pix1);
             }
            m_control->changeAgriDB=false;
         }
     }
//-----------------------------------------------------------------------------------------
     if(controlMode/*自动控制*/ )
     {
         //LED灯
         if(m_control->rownum[10]>0 && m_control->yanshibanID2>0)
         {
            if(m_control->guangxianNow.toFloat()<FsunPreVal  && m_control->guangxianNow.toFloat()>0)
            {
                if(ledStatus==false)
                {
                    m_control->YanShi_BuGuangDeng_ON(m_control->stryanshibanaddr2,m_control->stryanshibanmacaddr2);
                    ledStatus=true;
                }
                ui->s2Label->setPixmap(pix2);
                ui->LEDPix->setPixmap(QPixmap(":/images/light/light2.png"));
            }
            else
            {
                if(ledStatus==true)
                {
                    m_control->YanShi_BuGuangDeng_OFF(m_control->stryanshibanaddr2,m_control->stryanshibanmacaddr2);
                    ledStatus=false;
                }
                ui->s2Label->setPixmap(pix1);
                ui->LEDPix->setPixmap(QPixmap(":/images/light/light1.png"));
            }
         }
         else
         {
             if(ledStatus==true)
             {
                 m_control->YanShi_BuGuangDeng_OFF(m_control->stryanshibanaddr2,m_control->stryanshibanmacaddr2);
                 ledStatus=false;
             }
             ui->s2Label->setPixmap(pix1);
             ui->LEDPix->setPixmap(QPixmap(":/images/light/light1.png"));
         }

         //滴灌设备
         if(m_control->rownum[12]>0/*土壤温湿度节点*/&& m_control->yanshibanID2>0/*演示板添加上*/)
         {
            if((m_control->soiltempNow.toFloat() > FsoiltempPreVal || m_control->soilhumNow.toFloat() < FsoilhumPreVal ))
            {
                if(m_control->soiltempNow=="0" && m_control->soilhumNow=="0")
                {
                    if(diguanStatus==true)
                    {
                        m_control->YanShi_DianCiFa_OFF(m_control->stryanshibanaddr2,m_control->stryanshibanmacaddr2);
    //                    QMessageBox::warning(0,trUtf8("提示"),trUtf8("关闭滴灌"));
        //                messagebox=new QMessageBox(QMessageBox::Information,trUtf8("提示"),trUtf8("关闭滴灌"),QMessageBox::Close,this);
                        diguanStatus=false;
                    }
                    ui->s4Label->setPixmap(pix1);
                    ui->diguanPix->setPixmap(pix1);
                }
                else
                {
                    if(diguanStatus==false)
                    {
                        m_control->YanShi_DianCiFa_ON(m_control->stryanshibanaddr2,m_control->stryanshibanmacaddr2);
    //                  QMessageBox::warning(0,trUtf8("提示"),trUtf8("打开滴灌"));
    //                    messagebox=new QMessageBox(QMessageBox::Information,trUtf8("提示"),trUtf8("打开滴灌"),QMessageBox::Close,this);
                        diguanStatus=true;
                     }
                }
                ui->s4Label->setPixmap(pix2);
                ui->diguanPix->setPixmap(pix2);
            }
            else
            {
                if(diguanStatus==true)
                {
                    m_control->YanShi_DianCiFa_OFF(m_control->stryanshibanaddr2,m_control->stryanshibanmacaddr2);
    //                QMessageBox::warning(0,trUtf8("提示"),trUtf8("关闭滴灌"));
    //                messagebox=new QMessageBox(QMessageBox::Information,trUtf8("提示"),trUtf8("关闭滴灌"),QMessageBox::Close,this);
                    diguanStatus=false;
                }
                ui->s4Label->setPixmap(pix1);
                ui->diguanPix->setPixmap(pix1);
            }
         }
         else
         {
             if(diguanStatus==true)
             {
                 m_control->YanShi_DianCiFa_OFF(m_control->stryanshibanaddr2,m_control->stryanshibanmacaddr2);
    //             QMessageBox::warning(0,trUtf8("提示"),trUtf8("无法检测温湿度状况，关闭滴灌！！！"));
    //             messagebox=new QMessageBox(QMessageBox::Information,trUtf8("提示"),trUtf8("关闭滴灌"),QMessageBox::Close,this);
                 diguanStatus=false;
             }
             ui->s4Label->setPixmap(pix1);
             ui->diguanPix->setPixmap(pix1);
         }

         //风扇
         if( m_control->rownum[13]>0 && m_control->yanshibanID2>0)
         {
            if(m_control->co2Now==trUtf8("异常,超标") )
            {
                if(fengshanStatus==false)
                {
                    m_control->YanShi_FengShan_ON(m_control->stryanshibanaddr2,m_control->stryanshibanmacaddr2);
    //                QMessageBox::warning(this,trUtf8("提示"),trUtf8("打开通风扇"));
    //                messagebox=new QMessageBox(QMessageBox::Information,trUtf8("提示"),trUtf8("打开通风扇"),QMessageBox::Close,this);
                    fengshanStatus=true;
                }
                ui->s6Label->setPixmap(pix2);
                fan_timer->start(250);
            }
            else
            {
                if(fengshanStatus==true)
                {
                    m_control->YanShi_FengShan_OFF(m_control->stryanshibanaddr2,m_control->stryanshibanmacaddr2);
    //                QMessageBox::warning(this,trUtf8("提示"),trUtf8("关闭通风扇"));
    //                messagebox=new QMessageBox(QMessageBox::Information,trUtf8("提示"),trUtf8("关闭通风扇"),QMessageBox::Close,this);
                    fengshanStatus=false;
                }
                ui->s6Label->setPixmap(pix1);
                fan_timer->stop();
            }
         }
         else
         {
             if(fengshanStatus==true)
             {
                 m_control->YanShi_FengShan_OFF(m_control->stryanshibanaddr2,m_control->stryanshibanmacaddr2);
    //             QMessageBox::warning(this,trUtf8("提示"),trUtf8("无法检测二氧化碳状况，关闭通风扇！！！"));
    //             messagebox=new QMessageBox(QMessageBox::Information,trUtf8("提示"),trUtf8("关闭通风扇"),QMessageBox::Close,this);
                 fengshanStatus=false;
             }
             ui->s6Label->setPixmap(pix1);
    //         ui->tongfengPix->setPixmap(pix1);
             fan_timer->stop();
         }
     }

     //电机 //数码管
     if(m_control->yanshibanID2>0)
     {
         countSMG++;
         if(countSMG==10)
         {
            ui->s0Label->setPixmap(pix2);
            if(m_control->rownum[11]>0)
            {
                float fnum=m_control->tempNow.toFloat();
                int inum=(int)fnum;
                unsigned char abb=(unsigned char)inum;
//                QMessageBox::warning(0,"inum=",QString::number(inum));
//                QMessageBox::warning(0,"abb=",QString(abb));
                m_control->YanShi_ShuMaGuan(m_control->stryanshibanaddr2,m_control->stryanshibanmacaddr2,abb);
            }
            countSMG=0;
         }
     }
     else
     {
         ui->s8Label->setPixmap(pix1);
         ui->s0Label->setPixmap(pix1);
     }

}

void InteAgricul::lineClick1()
{
        changeNum[0]=true;
        disconnect(vKey,0,0,0);
        connect(vKey,SIGNAL(setvalue(const QString &)),ui->sunLine,SLOT(setText(const QString &)));
        vKey->show();
//        vKey->raise();
//        vKey->activateWindow();
}


void InteAgricul::lineClick2()
{
        changeNum[1]=true;
        disconnect(vKey,0,0,0);
        connect(vKey,SIGNAL(setvalue(const QString &)),ui->tempLine,SLOT(setText(const QString &)));
        vKey->show();
//        vKey->raise();
//        vKey->activateWindow();
}

void InteAgricul::lineClick3()
{
        changeNum[2]=true;
        disconnect(vKey,0,0,0);
        connect(vKey,SIGNAL(setvalue(const QString &)),ui->humLine,SLOT(setText(const QString &)));
        vKey->show();
//        vKey->raise();
//        vKey->activateWindow();
}

void InteAgricul::lineClick4()
{
        changeNum[3]=true;
        disconnect(vKey,0,0,0);
        connect(vKey,SIGNAL(setvalue(const QString &)),ui->soiltempLine,SLOT(setText(const QString &)));
        vKey->show();
//        vKey->raise();
//        vKey->activateWindow();
}

void InteAgricul::lineClick5()
{
        changeNum[4]=true;
        disconnect(vKey,0,0,0);
        connect(vKey,SIGNAL(setvalue(const QString &)),ui->soilhumLine,SLOT(setText(const QString &)));
        vKey->show();
//        vKey->raise();
//        vKey->activateWindow();
}
//确认修改 按钮
void InteAgricul::on_sureTB_clicked()
{
    if(changeNum[0])
    {
        FsunPreVal=ui->sunLine->text().toFloat();
        ui->sunvalLabel4->setText(QString::number(FsunPreVal));
        ui->sunvalLabel6->setText(QString::number(FsunPreVal));
        changeNum[0]=false;
    }
    if(changeNum[1])
    {
        FtempPreVal=ui->tempLine->text().toFloat();
        ui->tempvalLabel4->setText(QString::number(FtempPreVal));
        ui->tempvalLabel6->setText(QString::number(FtempPreVal));
        changeNum[1]=false;
    }
    if(changeNum[2])
    {
        FhumPreVal=ui->humLine->text().toFloat();
        ui->humvalLabel4->setText(QString::number(FhumPreVal));
        ui->humvalLabel6->setText(QString::number(FhumPreVal));
        changeNum[2]=false;
    }
    if(changeNum[3])
    {
        FsoiltempPreVal=ui->soiltempLine->text().toFloat();
        ui->soiltempvalLabel4->setText(QString::number(FsoiltempPreVal));
        ui->soiltempvalLabel6->setText(QString::number(FsoiltempPreVal));
        changeNum[3]=false;
    }
    if(changeNum[4])
    {
        FsoilhumPreVal=ui->soilhumLine->text().toFloat();
        ui->soilhumvalLabel4->setText(QString::number(FsoilhumPreVal));
        ui->soilhumvalLabel6->setText(QString::number(FsoilhumPreVal));
        changeNum[4]=false;
    }
}
//设置界面
void InteAgricul::on_toolButton_8_clicked()
{
    this->hide();
    m_control->show();
    m_control->ISTparent=this;

}



// 手动控制通风扇/滴灌/LED
void InteAgricul::on_Pb_OpenDG_clicked()
{
    ui->diguanPix->setPixmap(pix2);
    ui->s4Label->setPixmap(pix2);
    m_control->YanShi_DianCiFa_ON(m_control->stryanshibanaddr2,m_control->stryanshibanmacaddr2);
}

void InteAgricul::on_Pb_closeDG_clicked()
{
    ui->diguanPix->setPixmap(pix1);
    ui->s4Label->setPixmap(pix1);
    m_control->YanShi_DianCiFa_OFF(m_control->stryanshibanaddr2,m_control->stryanshibanmacaddr2);
}

void InteAgricul::on_Pb_OpenLED_clicked()
{
    ui->LEDPix->setPixmap(QPixmap(":/images/light/light2.png"));
    ui->s2Label->setPixmap(pix2);
    m_control->YanShi_BuGuangDeng_ON(m_control->stryanshibanaddr2,m_control->stryanshibanmacaddr2);
}

void InteAgricul::on_Pb_closeLED_clicked()
{
    ui->LEDPix->setPixmap(QPixmap(":/images/light/light1.png"));
    ui->s2Label->setPixmap(pix1);
    m_control->YanShi_BuGuangDeng_OFF(m_control->stryanshibanaddr2,m_control->stryanshibanmacaddr2);
}

void InteAgricul::on_Pb_OpenFan_clicked()
{
    fan_timer->start(250);
    ui->s6Label->setPixmap(pix2);
    m_control->YanShi_FengShan_ON(m_control->stryanshibanaddr2,m_control->stryanshibanmacaddr2);
}

void InteAgricul::on_Pb_closeFan_clicked()
{
    fan_timer->stop();
    ui->s6Label->setPixmap(pix1);
    m_control->YanShi_FengShan_OFF(m_control->stryanshibanaddr2,m_control->stryanshibanmacaddr2);
}
//。。。。。。。

void InteAgricul::runFan()
{
    fan_count++;
    ui->tongfengPix->setPixmap(fan_pix[fan_count]);
    if(fan_count==7) fan_count=-1;
}
//控制方式 PushButton
void InteAgricul::on_Pb_controlMode_clicked()
{
    if(!controlMode)
    {
        ui->Pb_controlMode->setText(trUtf8("自动控制"));
        controlMode=true;
        ui->Pb_OpenDG->setVisible(false);
        ui->Pb_closeDG->setVisible(false);
        ui->Pb_OpenLED->setVisible(false);
        ui->Pb_closeLED->setVisible(false);
        ui->Pb_OpenFan->setVisible(false);
        ui->Pb_closeFan->setVisible(false);
        m_control->YanShi_DianCiFa_OFF(m_control->stryanshibanaddr2,m_control->stryanshibanmacaddr2);
        m_control->YanShi_FengShan_OFF(m_control->stryanshibanaddr2,m_control->stryanshibanmacaddr2);
        m_control->YanShi_BuGuangDeng_OFF(m_control->stryanshibanaddr2,m_control->stryanshibanmacaddr2);
        ledStatus=false;diguanStatus=false;fengshanStatus=false;

        return;
    }
    else
    {
        ui->Pb_controlMode->setText(trUtf8("手动控制"));
        controlMode=false;
        ui->Pb_OpenDG->setVisible(true);
        ui->Pb_closeDG->setVisible(true);
        ui->Pb_OpenLED->setVisible(true);
        ui->Pb_closeLED->setVisible(true);
        ui->Pb_OpenFan->setVisible(true);
        ui->Pb_closeFan->setVisible(true);
        m_control->YanShi_DianCiFa_OFF(m_control->stryanshibanaddr2,m_control->stryanshibanmacaddr2);
        m_control->YanShi_FengShan_OFF(m_control->stryanshibanaddr2,m_control->stryanshibanmacaddr2);
        m_control->YanShi_BuGuangDeng_OFF(m_control->stryanshibanaddr2,m_control->stryanshibanmacaddr2);
        ui->s2Label->setPixmap(pix1);
        ui->s4Label->setPixmap(pix1);
        ui->s6Label->setPixmap(pix1);
        ui->s8Label->setPixmap(pix1);
        return;
    }
}
