#include "intehomefurn.h"
#include "ui_intehomefurn.h"
//#include <QTimer>

InteHomeFurn::InteHomeFurn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InteHomeFurn)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);

    QPixmap pixmap;
    pixmap.load(":/images/intehomefurn/1.png");
    QPalette p(palette());
    p.setBrush(QPalette::Window,QBrush(pixmap));
    setPalette(p);

    pixmap1.load(":/images/inteagri/30.png");
    pixmap2.load(":/images/inteagri/31.png");

    pixmap.load(":/images/intehomefurn/01.png");
    ui->toolButton->setIcon(pixmap);
    ui->toolButton->setIconSize(pixmap.size());
    ui->toolButton->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/intehomefurn/02.png");
    ui->toolButton_2->setIcon(pixmap);
    ui->toolButton_2->setIconSize(pixmap.size());
    ui->toolButton_2->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/intehomefurn/03.png");
    ui->toolButton_3->setIcon(pixmap);
    ui->toolButton_3->setIconSize(pixmap.size());
    ui->toolButton_3->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/intehomefurn/04.png");
    ui->toolButton_4->setIcon(pixmap);
    ui->toolButton_4->setIconSize(pixmap.size());
    ui->toolButton_4->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/intehomefurn/05.png");
    ui->toolButton_5->setIcon(pixmap);
    ui->toolButton_5->setIconSize(pixmap.size());
    ui->toolButton_5->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/intehomefurn/06.png");
    ui->toolButton_6->setIcon(pixmap);
    ui->toolButton_6->setIconSize(pixmap.size());
    ui->toolButton_6->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/intehomefurn/07.png");
    ui->toolButton_7->setIcon(pixmap);
    ui->toolButton_7->setIconSize(pixmap.size());
    ui->toolButton_7->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/intehomefurn/08.png");
    ui->toolButton_9->setIcon(pixmap);
    ui->toolButton_9->setIconSize(pixmap.size());
    ui->toolButton_9->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/0010.png");
    ui->toolButton_8->setIcon(pixmap);
    ui->toolButton_8->setIconSize(pixmap.size());
    ui->toolButton_8->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/011.png");
    ui->P1_openTB->setIcon(pixmap);
    ui->P1_openTB->setIconSize(pixmap.size());
    ui->P1_openTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/012.png");
    ui->P1_closeTB->setIcon(pixmap);
    ui->P1_closeTB->setIconSize(pixmap.size());
    ui->P1_closeTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/021.png");
    ui->P2_openTB->setIcon(pixmap);
    ui->P2_openTB->setIconSize(pixmap.size());
    ui->P2_openTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/022.png");
    ui->P2_closeTB->setIcon(pixmap);
    ui->P2_closeTB->setIconSize(pixmap.size());
    ui->P2_closeTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/023.png");
    ui->P2_addsoundTB->setIcon(pixmap);
    ui->P2_addsoundTB->setIconSize(pixmap.size());
    ui->P2_addsoundTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/024.png");
    ui->P2_redusoundTB->setIcon(pixmap);
    ui->P2_redusoundTB->setIconSize(pixmap.size());
    ui->P2_redusoundTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/025.png");
    ui->P2_AVtypeTB->setIcon(pixmap);
    ui->P2_AVtypeTB->setIconSize(pixmap.size());
    ui->P2_AVtypeTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/026.png");
    ui->P2_addchannelTB->setIcon(pixmap);
    ui->P2_addchannelTB->setIconSize(pixmap.size());
    ui->P2_addchannelTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/027.png");
    ui->P2_reduchannelTB->setIcon(pixmap);
    ui->P2_reduchannelTB->setIconSize(pixmap.size());
    ui->P2_reduchannelTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/031.png");
    ui->P3_openTB->setIcon(pixmap);
    ui->P3_openTB->setIconSize(pixmap.size());
    ui->P3_openTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/032.png");
    ui->P3_closeTB->setIcon(pixmap);
    ui->P3_closeTB->setIconSize(pixmap.size());
    ui->P3_closeTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/033.png");
    ui->P3_windspeedTB->setIcon(pixmap);
    ui->P3_windspeedTB->setIconSize(pixmap.size());
    ui->P3_windspeedTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/034.png");
    ui->P3_winddireTB->setIcon(pixmap);
    ui->P3_winddireTB->setIconSize(pixmap.size());
    ui->P3_winddireTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/041.png");
    ui->P4_openTB->setIcon(pixmap);
    ui->P4_openTB->setIconSize(pixmap.size());
    ui->P4_openTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/042.png");
    ui->P4_closeTB->setIcon(pixmap);
    ui->P4_closeTB->setIconSize(pixmap.size());
    ui->P4_closeTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/043.png");
    ui->P4_presetTB->setIcon(pixmap);
    ui->P4_presetTB->setIconSize(pixmap.size());
    ui->P4_presetTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/044.png");
    ui->P4_windspeedTB->setIcon(pixmap);
    ui->P4_windspeedTB->setIconSize(pixmap.size());
    ui->P4_windspeedTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/045.png");
    ui->P4_winddireTB->setIcon(pixmap);
    ui->P4_winddireTB->setIconSize(pixmap.size());
    ui->P4_winddireTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/051.png");
    ui->P5_openTB->setIcon(pixmap);
    ui->P5_openTB->setIconSize(pixmap.size());
    ui->P5_openTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/052.png");
    ui->P5_closeTB->setIcon(pixmap);
    ui->P5_closeTB->setIconSize(pixmap.size());
    ui->P5_closeTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/053.png");
    ui->P5_addsoundTB->setIcon(pixmap);
    ui->P5_addsoundTB->setIconSize(pixmap.size());
    ui->P5_addsoundTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/054.png");
    ui->P5_redusoundTB->setIcon(pixmap);
    ui->P5_redusoundTB->setIconSize(pixmap.size());
    ui->P5_redusoundTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/061.png");
    ui->P6_oporclTB->setIcon(pixmap);
    ui->P6_oporclTB->setIconSize(pixmap.size());
    ui->P6_oporclTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/062.png");
    ui->P6_addsoundTB->setIcon(pixmap);
    ui->P6_addsoundTB->setIconSize(pixmap.size());
    ui->P6_addsoundTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/063.png");
    ui->P6_redusoundTB->setIcon(pixmap);
    ui->P6_redusoundTB->setIconSize(pixmap.size());
    ui->P6_redusoundTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/064.png");
    ui->P6_intooroutTB->setIcon(pixmap);
    ui->P6_intooroutTB->setIconSize(pixmap.size());
    ui->P6_intooroutTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/065.png");
    ui->P6_playorpauseTB->setIcon(pixmap);
    ui->P6_playorpauseTB->setIconSize(pixmap.size());
    ui->P6_playorpauseTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/066.png");
    ui->P6_fastforwardTB->setIcon(pixmap);
    ui->P6_fastforwardTB->setIconSize(pixmap.size());
    ui->P6_fastforwardTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/067.png");
    ui->P6_rewindTB->setIcon(pixmap);
    ui->P6_rewindTB->setIconSize(pixmap.size());
    ui->P6_rewindTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/0004.png");
    ui->equipopenTB->setIcon(pixmap);
    ui->equipopenTB->setIconSize(pixmap.size());
    ui->equipopenTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/0005.png");
    ui->equipcloseTB->setIcon(pixmap);
    ui->equipcloseTB->setIconSize(pixmap.size());
    ui->equipcloseTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/0006.png");
    ui->equipstopTB->setIcon(pixmap);
    ui->equipstopTB->setIconSize(pixmap.size());
    ui->equipstopTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/007.png");
    ui->addlightTB->setIcon(pixmap);
    ui->addlightTB->setIconSize(pixmap.size());
    ui->addlightTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/008.png");
    ui->redulightTB->setIcon(pixmap);
    ui->redulightTB->setIconSize(pixmap.size());
    ui->redulightTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/1001.png");
    ui->powerOpenTB1->setIcon(pixmap);
    ui->powerOpenTB1->setIconSize(pixmap.size());
    ui->powerOpenTB1->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    ui->powerOpenTB2->setIcon(pixmap);
    ui->powerOpenTB2->setIconSize(pixmap.size());
    ui->powerOpenTB2->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/1002.png");
    ui->powerCloseTB1->setIcon(pixmap);
    ui->powerCloseTB1->setIconSize(pixmap.size());
    ui->powerCloseTB1->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    ui->powerCloseTB2->setIcon(pixmap);
    ui->powerCloseTB2->setIconSize(pixmap.size());
    ui->powerCloseTB2->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/intehomefurn/2.png");
    ui->label_7->setPixmap(pixmap);
    pixmap.load(":/images/intehomefurn/3.png");
    ui->label_8->setPixmap(pixmap);
    pixmap.load(":/images/intehomefurn/4.png");
    ui->label_9->setPixmap(pixmap);
    pixmap.load(":/images/intehomefurn/5.png");
    ui->label_10->setPixmap(pixmap);
    pixmap.load(":/images/intehomefurn/6.png");
    ui->label_11->setPixmap(pixmap);
    pixmap.load(":/images/intehomefurn/7.png");
    ui->label_12->setPixmap(pixmap);

    fengshanStatus=false;
    yuyinStatus=false;

    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);

    pixmap.load(":/images/inteagri/30.png");
    ui->pix1Label->setScaledContents(true);
    ui->pix1Label->setPixmap(pixmap);
    ui->pix2Label->setScaledContents(true);
    ui->pix2Label->setPixmap(pixmap);
    ui->pix3Label->setScaledContents(true);
    ui->pix3Label->setPixmap(pixmap);
    ui->pix4Label->setScaledContents(true);
    ui->pix4Label->setPixmap(pixmap);
    ui->pix5Label->setScaledContents(true);
    ui->pix5Label->setPixmap(pixmap);
    ui->pix6Label->setScaledContents(true);
    ui->pix6Label->setPixmap(pixmap);
    ui->pix7Label->setScaledContents(true);
    ui->pix7Label->setPixmap(pixmap);
    ui->pix8Label->setScaledContents(true);
    ui->pix8Label->setPixmap(pixmap);
    ui->pix9Label->setScaledContents(true);
    ui->pix9Label->setPixmap(pixmap);
    ui->pix10Label->setScaledContents(true);
    ui->pix10Label->setPixmap(pixmap);
    ui->pix11Label->setScaledContents(true);
    ui->pix11Label->setPixmap(pixmap);
    ui->pix12Label->setScaledContents(true);
    ui->pix12Label->setPixmap(pixmap);
    ui->pix13Label->setScaledContents(true);
    ui->pix13Label->setPixmap(pixmap);
    ui->pix14Label->setScaledContents(true);
    ui->pix14Label->setPixmap(pixmap);
    ui->pix15Label->setScaledContents(true);
    ui->pix15Label->setPixmap(pixmap);
    ui->pix16Label->setScaledContents(true);
    ui->pix16Label->setPixmap(pixmap);
    ui->pix17Label->setScaledContents(true);
    ui->pix17Label->setPixmap(pixmap);
    ui->pix18Label->setScaledContents(true);
    ui->pix18Label->setPixmap(pixmap);

    pixmap.load(":/images/intehomefurn/off.png");
    ui->fengshanLabel->setScaledContents(true);
    ui->fengshanLabel->setPixmap(pixmap);

    ui->yuyinLabel->setScaledContents(true);
    ui->yuyinLabel->setPixmap(pixmap);

    ui->sunLineEdit->setReadOnly(true);
    ui->sunLineEdit->setAlignment(Qt::AlignRight);
    ui->sunLineEdit->setMaxLength(15);

    ui->tempLineEdit->setReadOnly(true);
    ui->tempLineEdit->setAlignment(Qt::AlignRight);
    ui->tempLineEdit->setMaxLength(15);

    ui->humLineEdit->setReadOnly(true);
    ui->humLineEdit->setAlignment(Qt::AlignRight);
    ui->humLineEdit->setMaxLength(15);

    ui->sunLineEdit->setText("0");
    ui->tempLineEdit->setText("0");
    ui->humLineEdit->setText("0");

    for(int i=0;i<3;i++)
        changeNum[i]=false;

    for(int i=0;i<4;i++)
        countNum[i]=0;

    initval=0x40;
    countSMG=0;

    FsunPreVal=20;
    FtempPreVal=20;
    FhumPreVal=20;

    LEDStatus=false;
    SMGStatus=false;
    power1Status=false;
    power2Status=false;

    ui->pagelabel1->setVisible(false);
    ui->pagelabel2->setVisible(false);
    ui->pagelabel3->setVisible(false);
    ui->pagelabel4->setVisible(false);
    ui->pagelabel5->setVisible(false);
    ui->pagelabel6->setVisible(false);

    ui->sunValLabel1->setText(QString::number(FsunPreVal));
    ui->tempValLabel1->setText(QString::number(FtempPreVal));
    ui->humValLabel1->setText(QString::number(FhumPreVal));
    ui->sunValLabel6->setText(QString::number(FsunPreVal));
    ui->tempValLabel6->setText(QString::number(FtempPreVal));
    ui->humValLabel6->setText(QString::number(FhumPreVal));

    connect(ui->sunLineEdit,SIGNAL(selectionChanged()),this,SLOT(lineClick1()));
    connect(ui->tempLineEdit,SIGNAL(selectionChanged()),this,SLOT(lineClick2()));
    connect(ui->humLineEdit,SIGNAL(selectionChanged()),this,SLOT(lineClick3()));

    m_timer=new QTimer(this);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(readInfo()));
//    m_timer->start(2000);
    
    vKey=new VKey(this);
    ui->stackedWidget->setCurrentIndex(0);

    fan_pix[0].load(":/images/fan/f1.png");
    fan_pix[1].load(":/images/fan/f2.png");
    fan_pix[2].load(":/images/fan/f3.png");
    fan_pix[3].load(":/images/fan/f4.png");
    fan_pix[4].load(":/images/fan/f5.png");
    fan_pix[5].load(":/images/fan/f6.png");
    fan_pix[6].load(":/images/fan/f7.png");
    fan_pix[7].load(":/images/fan/f8.png");
    ui->fengshanLabel->setPixmap(fan_pix[0]);
    fan_timer =  new QTimer(this);
    connect(fan_timer,SIGNAL(timeout()),this,SLOT(runFan()));
//    fan_timer->start(250);
    fan_count=-1;
}

InteHomeFurn::~InteHomeFurn()
{
    delete ui;

    m_timer->stop();
    delete m_timer;

    fan_timer->stop();
    delete fan_timer;
}

void InteHomeFurn::on_toolButton_7_clicked()
{
    this->m_timer->stop();
    this->fan_timer->stop();
    this->parent->show();
    this->close();
}

void InteHomeFurn::on_toolButton_8_clicked()
{
    this->hide();
    m_control->show();
    m_control->ISTparent=this;
}

void InteHomeFurn::on_toolButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->toolButton->setFocus();
}

void InteHomeFurn::on_toolButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->toolButton_2->setFocus();
}

void InteHomeFurn::on_toolButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->toolButton_3->setFocus();
}


void InteHomeFurn::on_toolButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->toolButton_4->setFocus();
}

void InteHomeFurn::on_toolButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    ui->toolButton_5->setFocus();
}

void InteHomeFurn::on_toolButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->toolButton_6->setFocus();
}

void InteHomeFurn::mousePressEvent(QMouseEvent *event)
{
    if (event->pos().x() > 360 && event->pos().x() < 490)
    {
        if(event->pos().y() > 160 && event->pos().y() < 215)
        {
            if(ui->stackedWidget->currentIndex()==2)
            {
                if(m_control->yanshibanID<0)
                {
                    QMessageBox::warning(0,trUtf8("提示"),trUtf8("未添加演示板设备"));
                    return;
                }
                fanControl();
            }
        }
    }

    if (event->pos().x() > 360 && event->pos().x() < 490)
    {
        if(event->pos().y() > 310 && event->pos().y() < 365)
        {
            if(ui->stackedWidget->currentIndex()==2)
            {
                if(yuyinStatus==false)
                {
                    ui->yuyinLabel->setPixmap(QPixmap(":/images/intehomefurn/on.png"));
                    yuyinStatus=true;
                }
                else
                {
                    ui->yuyinLabel->setPixmap(QPixmap(":/images/intehomefurn/off.png"));
                    yuyinStatus=false;
                }
            }
        }
    }
}
//通风扇的控制
void InteHomeFurn::fanControl()
{
    if(fengshanStatus==false)
    {
//        ui->fengshanLabel->setPixmap(QPixmap(":/images/intehomefurn/on.png"));
        ui->pix6Label->setPixmap(pixmap2);
        fan_timer->start(250);
        if(m_control->yanshibanID)
            m_control->YanShi_FengShan_ON(m_control->stryanshibanaddr,m_control->stryanshibanmacaddr);
        fengshanStatus=true;
        return;
    }
    else
    {
//        ui->fengshanLabel->setPixmap(QPixmap(":/images/intehomefurn/off.png"));
        ui->pix6Label->setPixmap(pixmap1);
        fan_timer->stop();
        if(m_control->yanshibanID)
            m_control->YanShi_FengShan_OFF(m_control->stryanshibanaddr,m_control->stryanshibanmacaddr);
        fengshanStatus=false;
        return;
    }
}


void InteHomeFurn::lineClick1()
{
    changeNum[0]=true;
    disconnect(vKey,0,0,0);
    connect(vKey,SIGNAL(setvalue(const QString &)),ui->sunLineEdit,SLOT(setText(const QString &)));
    vKey->show();
//        vKey->raise();
//        vKey->activateWindow();
}


void InteHomeFurn::lineClick2()
{
    changeNum[1]=true;
    disconnect(vKey,0,0,0);
    connect(vKey,SIGNAL(setvalue(const QString &)),ui->tempLineEdit,SLOT(setText(const QString &)));
    vKey->show();
//        vKey->raise();
//        vKey->activateWindow();
}

void InteHomeFurn::lineClick3()
{
    changeNum[2]=true;
    disconnect(vKey,0,0,0);
    connect(vKey,SIGNAL(setvalue(const QString &)),ui->humLineEdit,SLOT(setText(const QString &)));
    vKey->show();
//        vKey->raise();
//        vKey->activateWindow();
}
//确认修改 按钮
void InteHomeFurn::on_toolButton_9_clicked()
{
    if(changeNum[0])
    {
        FsunPreVal=ui->sunLineEdit->text().toFloat();
        ui->sunValLabel1->setText(QString::number(FsunPreVal));
        ui->sunValLabel6->setText(QString::number(FsunPreVal));
        changeNum[0]=false;
    }
    if(changeNum[1])
    {
        FtempPreVal=ui->tempLineEdit->text().toFloat();
        ui->tempValLabel1->setText(QString::number(FtempPreVal));
        ui->tempValLabel6->setText(QString::number(FtempPreVal));
        changeNum[1]=false;
    }
    if(changeNum[2])
    {
        FhumPreVal=ui->humLineEdit->text().toFloat();
        ui->humValLabel1->setText(QString::number(FhumPreVal));
        ui->humValLabel6->setText(QString::number(FhumPreVal));
        changeNum[2]=false;
    }
}


void InteHomeFurn::readInfo()
{
    if(m_control->changeData1)
    {
        if(m_control->rownum[6]>0)
        {
            ui->rainLabel->setText("<font color=green>"+m_control->jieluNow+"</font>");
        }
        if(m_control->rownum[8]>0)
        {
            ui->sunLabel->setText("<font color=green>"+m_control->guangminNow+"</font>");
        }
        if(m_control->rownum[2]>0)
        {
            ui->tempLabel->setText("<font color=green>"+m_control->tempNow+"</font>");
            ui->humLabel->setText("<font color=green>"+m_control->humNow+"</font>");
        }
        if(m_control->rownum[3]>0)
        {
            ui->fireLabel->setText("<font color=green>"+m_control->huoyanNow+"</font>");
        }
        if(m_control->rownum[4]>0)
        {
            ui->airLabel->setText("<font color=green>"+m_control->airNow+"</font>");
        }
        if(m_control->rownum[5]>0)
        {
            ui->paLabel->setText("<font color=green>"+m_control->qiyaNow+"</font>");
        }

        if(m_control->ithreefivestructlength>0)
        {
            //315设备
            if(m_control->threefiveNow.contains(trUtf8("烟雾"))==true)
            {
                ui->gasLabel->setText("<font color=red>"+trUtf8("有警情")+"</font>");
                fengshanStatus=false;
                fanControl();
                countNum[0]=0;

            }
            else if(m_control->threefiveNow.contains(trUtf8("气体"))==true)
            {
                ui->smogLabel->setText("<font color=red>"+trUtf8("有警情")+"</font>");
                fengshanStatus=false;
                fanControl();
                countNum[1]=0;
            }
            else if(m_control->threefiveNow.contains(trUtf8("人体"))==true)
            {
                ui->manLabel->setText("<font color=red>"+trUtf8("有警情")+"</font>");
                countNum[2]=0;
            }
            else if(m_control->threefiveNow.contains(trUtf8("门磁"))==true)
            {
                ui->doorLabel->setText("<font color=red>"+trUtf8("有警情")+"</font>");
                countNum[3]=0;
            }

            for(int i=0;i<4;i++)
            {
                if(countNum[i]==11) continue;
                countNum[i]++;
            }
            if(countNum[0]==10)
            {
                fengshanStatus=true;
                fanControl();
                ui->gasLabel->setText("<font color=green>"+trUtf8("正常")+"</font>");
            }
            if(countNum[1]==10)
            {
                fengshanStatus=true;
                fanControl();
                ui->smogLabel->setText("<font color=green>"+trUtf8("正常")+"</font>");
            }

            if(countNum[2]==10)
            {
                ui->manLabel->setText("<font color=green>"+trUtf8("正常")+"</font>");
            }
            if(countNum[3]==10)
            {
                ui->doorLabel->setText("<font color=green>"+trUtf8("正常")+"</font>");
            }
            for(int i=0;i<m_control->ithreefivestructlength;i++)
            {
                if(m_control->m_threefivestruct[i].name==trUtf8("烟雾"))
                    ui->pix4Label->setPixmap(pixmap2);
                else
                    ui->pix4Label->setPixmap(pixmap1);
                if(m_control->m_threefivestruct[i].name==trUtf8("气体"))
                    ui->pix13Label->setPixmap(pixmap2);
                else
                    ui->pix13Label->setPixmap(pixmap1);
                if(m_control->m_threefivestruct[i].name==trUtf8("人体"))
                    ui->pix15Label->setPixmap(pixmap2);
                else
                    ui->pix15Label->setPixmap(pixmap1);
                if(m_control->m_threefivestruct[i].name==trUtf8("门磁"))
                    ui->pix2Label->setPixmap(pixmap2);
                else
                    ui->pix2Label->setPixmap(pixmap1);
            }
        }
        m_control->changeData1=false;
    }
//强电设备1
    if(m_control->powerID1 || m_control->powerID2)
    {
        ui->pix18Label->setPixmap(pixmap2);
    }
    else
    {
        ui->pix18Label->setPixmap(pixmap1);
    }

    if(m_control->changeHomeDB)
    {
        for(int i=0;i<m_control->isensorlength;i++)
        {
            if(m_control->m_sensorstruct[i].name==trUtf8("光敏"))
            {
                if(m_control->m_sensorstruct[i].status==trUtf8("在线"))
                {
                    ui->pix1Label->setPixmap(pixmap2);
                }
                else
                {
                    ui->sunLabel->setText("");
                    ui->pix1Label->setPixmap(pixmap1);
                }
            }

            if(m_control->m_sensorstruct[i].name==trUtf8("火焰") && m_control->m_sensorstruct[i].dir==trUtf8("智能家居"))
            {
                if(m_control->m_sensorstruct[i].status==trUtf8("在线"))
                {
                    ui->pix3Label->setPixmap(pixmap2);
                }
                else
                {
                    ui->pix3Label->setPixmap(pixmap1);
                }
            }

            if(m_control->m_sensorstruct[i].name==trUtf8("空气质量"))
            {
                if(m_control->m_sensorstruct[i].status==trUtf8("在线"))
                {
                    ui->pix5Label->setPixmap(pixmap2);
                }
                else
                {
                    ui->airLabel->setText("");
                    ui->pix5Label->setPixmap(pixmap1);
                }
            }

            if(m_control->m_sensorstruct[i].name==trUtf8("温湿度") && m_control->m_sensorstruct[i].dir==trUtf8("智能家居"))
            {
                if(m_control->m_sensorstruct[i].status==trUtf8("在线"))
                {
                    ui->pix7Label->setPixmap(pixmap2);
                }
                else
                {
                    ui->tempLabel->setText("");
                    ui->humLabel->setText("");
                    ui->pix7Label->setPixmap(pixmap1);
                }
            }

            if(m_control->m_sensorstruct[i].name==trUtf8("气压"))
            {
                if(m_control->m_sensorstruct[i].status==trUtf8("在线"))
                {
                    ui->pix9Label->setPixmap(pixmap2);
                }
                else
                {
                    ui->paLabel->setText("");
                    ui->pix9Label->setPixmap(pixmap1);
                }
            }

            if(m_control->m_sensorstruct[i].name==trUtf8("结露"))
            {
                if(m_control->m_sensorstruct[i].status==trUtf8("在线"))
                {
                    ui->pix11Label->setPixmap(pixmap2);
                }
                else
                {
                    ui->rainLabel->setText("");
                    ui->pix11Label->setPixmap(pixmap1);
                }
            }

            if(m_control->m_sensorstruct[i].name==trUtf8("调光"))
            {
                ui->pix17Label->setPixmap(pixmap2);
            }
            else
            {
                ui->pix17Label->setPixmap(pixmap1);
            }
        }
    }

    if(m_control->yanshibanID)
    {
        if(m_control->rownum[2]>0)
        {
            countSMG++;
            if(countSMG==10)
            {
                if(SMGStatus==false)
                {
                    ui->pix10Label->setPixmap(pixmap2);
                }
                float fnum=m_control->tempNow.toFloat();
                int inum=(int)fnum;
                unsigned char abb=(unsigned char)inum;
                m_control->YanShi_ShuMaGuan(m_control->stryanshibanaddr,m_control->stryanshibanmacaddr,abb);
                countSMG=0;
            }
        }
        else
        {
            if(SMGStatus)
            {
                ui->pix10Label->setPixmap(pixmap1);
                countSMG=0;
            }
        }

//     LED
//        if(m_control->rownum[8] )
//        {
//            if(LEDStatus==false)
//                ui->pix16Label->setPixmap(pixmap2);
//        }
//        else
//        {
//            if(LEDStatus)
//                ui->pix16Label->setPixmap(pixmap1);
//        }
    }
//    else
//    {
//        if(LEDStatus)
//            ui->pix10Label->setPixmap(pixmap1);
//    }
    //按键
    if(m_control->rownum[7])
        ui->pix14Label->setPixmap(pixmap2);
    else
        ui->pix14Label->setPixmap(pixmap1);
    //红外
    if(m_control->iirtructlength)
        ui->pix12Label->setPixmap(pixmap2);
    else
        ui->pix12Label->setPixmap(pixmap1);
}

void InteHomeFurn::on_addlightTB_clicked()
{
    for(int i=0;i<m_control->isensorlength;i++)
    {
         if(QString::compare(trUtf8("调光"),m_control->m_sensorstruct[i].name)==0)
         {
             if( initval<0x75)
             {
                initval=initval+0x10;
                ui->pix17Label->setPixmap(pixmap2);
             }
             if(initval>=0x75)
             {
                initval=0x75;
             }
             m_control->SUN_ON(m_control->m_sensorstruct[i].shortaddr,m_control->m_sensorstruct[i].longaddr,initval);
             return;
         }
    }
}

void InteHomeFurn::on_redulightTB_clicked()
{
    for(int i=0;i<m_control->isensorlength;i++)
    {
         if(QString::compare(trUtf8("调光"),m_control->m_sensorstruct[i].name)==0)
         {
             if( initval>0x00)
             {
                initval=initval-0x10;
                if(initval==0x00)
                    ui->pix17Label->setPixmap(pixmap1);
             }
             if(initval<0x00)
             {
                initval=0x00;
             }
             m_control->SUN_OFF(m_control->m_sensorstruct[i].shortaddr,m_control->m_sensorstruct[i].longaddr,initval);
             return;
         }
    }
}

void InteHomeFurn::on_powerOpenTB1_clicked()
{
    bool flag=false;
    for(int i=0;i<m_control->isensorlength;i++)
    {
        if(m_control->m_sensorstruct[i].name==trUtf8("设备1"))
        {
             m_control->KG_ON(m_control->m_sensorstruct[i].shortaddr,m_control->m_sensorstruct[i].longaddr);
             ui->powerLabel1->setText(trUtf8("强电设备1打开命令已经发送."));
            flag=true;
            break;
        }
    }
    if(!flag)
    {
        ui->powerLabel1->setText(trUtf8("未添加强电设备1."));
    }
}

void InteHomeFurn::on_powerCloseTB1_clicked()
{
    bool flag=false;
    for(int i=0;i<m_control->isensorlength;i++)
    {
        if(m_control->m_sensorstruct[i].name==trUtf8("设备1"))
        {
             m_control->KG_OFF(m_control->m_sensorstruct[i].shortaddr,m_control->m_sensorstruct[i].longaddr);
             ui->powerLabel1->setText(trUtf8("强电设备1关闭命令已经发送."));
            flag=true;
            break;
        }
    }
    if(!flag)
    {
        ui->powerLabel1->setText(trUtf8("未添加强电设备1."));
    }
}

void InteHomeFurn::on_powerOpenTB2_clicked()
{
    bool flag=false;
    for(int i=0;i<m_control->isensorlength;i++)
    {
        if(m_control->m_sensorstruct[i].name==trUtf8("设备2"))
        {
             m_control->KG_ON(m_control->m_sensorstruct[i].shortaddr,m_control->m_sensorstruct[i].longaddr);
             ui->powerLabel2->setText(trUtf8("强电设备2打开命令已经发送."));
            flag=true;
            break;
        }
    }
    if(!flag)
    {
        ui->powerLabel2->setText(trUtf8("未添加强电设备2."));
    }
}

void InteHomeFurn::on_powerCloseTB2_clicked()
{
    bool flag=false;
    for(int i=0;i<m_control->isensorlength;i++)
    {
        if(m_control->m_sensorstruct[i].name==trUtf8("设备2"))
        {
             m_control->KG_OFF(m_control->m_sensorstruct[i].shortaddr,m_control->m_sensorstruct[i].longaddr);
             ui->powerLabel2->setText(trUtf8("强电设备2关闭命令已经发送."));
            flag=true;
            break;
        }
    }
    if(!flag)
    {
        ui->powerLabel2->setText(trUtf8("未添加强电设备2."));
    }
}
//
void InteHomeFurn::on_equipopenTB_clicked()
{
    if(m_control->yanshibanID)
    {
        ui->pix8Label->setPixmap(pixmap2);
        ui->curtainLabel->setText(trUtf8("窗帘打开命令已经发送."));
        m_control->YanShi_DianJi_ZhengZhuan(m_control->stryanshibanaddr,m_control->stryanshibanmacaddr);  
    }
    else
    {
        ui->curtainLabel->setText(trUtf8("未添加演示板设备."));
        return;
    }
}

void InteHomeFurn::on_equipcloseTB_clicked()
{
    if(m_control->yanshibanID)
    {
        ui->pix8Label->setPixmap(pixmap2);
        ui->curtainLabel->setText(trUtf8("窗帘关闭命令已经发送."));
        m_control->YanShi_DianJi_FanZhuan(m_control->stryanshibanaddr,m_control->stryanshibanmacaddr);
    }
    else
    {
        ui->curtainLabel->setText(trUtf8("未添加演示板设备."));
        return;
    }
}

void InteHomeFurn::on_equipstopTB_clicked()
{
    if(m_control->yanshibanID)
    {
        ui->pix8Label->setPixmap(pixmap1);
        ui->curtainLabel->setText(trUtf8("窗帘停止命令已经发送."));
        m_control->YanShi_DianJi_Ting(m_control->stryanshibanaddr,m_control->stryanshibanmacaddr);
    }
    else
    {
        ui->curtainLabel->setText(trUtf8("未添加演示板设备."));
        return;
    }
}

//红外控制
void InteHomeFurn::on_P3_openTB_clicked()
{
    QString str1=trUtf8("空调扇");
    QString str2=trUtf8("开");
    InfraredControlFun(str1,str2);
}

void InteHomeFurn::on_P3_closeTB_clicked()
{
    QString str1=trUtf8("空调扇");
    QString str2=trUtf8("关");
    InfraredControlFun(str1,str2);
}

void InteHomeFurn::on_P3_windspeedTB_clicked()
{
    QString str1=trUtf8("空调扇");
    QString str2=trUtf8("风速");
    InfraredControlFun(str1,str2);
}

void InteHomeFurn::on_P3_winddireTB_clicked()
{
    QString str1=trUtf8("空调扇");
    QString str2=trUtf8("风向");
    InfraredControlFun(str1,str2);
}

void InteHomeFurn::on_P1_openTB_clicked()
{
    QString str1=trUtf8("投影机");
    QString str2=trUtf8("开");
    InfraredControlFun(str1,str2);
}

void InteHomeFurn::on_P1_closeTB_clicked()
{
    QString str1=trUtf8("投影机");
    QString str2=trUtf8("关");
    InfraredControlFun(str1,str2);
}

void InteHomeFurn::on_P2_openTB_clicked()
{
    QString str1=trUtf8("电视机");
    QString str2=trUtf8("开");
    InfraredControlFun(str1,str2);
}

void InteHomeFurn::on_P2_closeTB_clicked()
{
    QString str1=trUtf8("电视机");
    QString str2=trUtf8("关");
    InfraredControlFun(str1,str2);
}

void InteHomeFurn::on_P2_addsoundTB_clicked()
{
    QString str1=trUtf8("电视机");
    QString str2=trUtf8("音量+");
    InfraredControlFun(str1,str2);
}

void InteHomeFurn::on_P2_redusoundTB_clicked()
{
    QString str1=trUtf8("电视机");
    QString str2=trUtf8("音量-");
    InfraredControlFun(str1,str2);
}

void InteHomeFurn::on_P2_AVtypeTB_clicked()
{
    QString str1=trUtf8("电视机");
    QString str2=trUtf8("AV模式");
    InfraredControlFun(str1,str2);
}

void InteHomeFurn::on_P2_addchannelTB_clicked()
{
    QString str1=trUtf8("电视机");
    QString str2=trUtf8("频道+");
    InfraredControlFun(str1,str2);
}

void InteHomeFurn::on_P2_reduchannelTB_clicked()
{
    QString str1=trUtf8("电视机");
    QString str2=trUtf8("频道-");
    InfraredControlFun(str1,str2);
}

void InteHomeFurn::on_P4_openTB_clicked()
{
    QString str1=trUtf8("空调");
    QString str2=trUtf8("开");
    InfraredControlFun(str1,str2);
}

void InteHomeFurn::on_P4_closeTB_clicked()
{
    QString str1=trUtf8("空调");
    QString str2=trUtf8("关");
    InfraredControlFun(str1,str2);
}

void InteHomeFurn::on_P4_presetTB_clicked()
{
    QString str1=trUtf8("空调");
    QString str2=trUtf8("预设温度");
    InfraredControlFun(str1,str2);
}

void InteHomeFurn::on_P4_windspeedTB_clicked()
{
    QString str1=trUtf8("空调");
    QString str2=trUtf8("风速");
    InfraredControlFun(str1,str2);
}

void InteHomeFurn::on_P4_winddireTB_clicked()
{
    QString str1=trUtf8("空调");
    QString str2=trUtf8("风向");
    InfraredControlFun(str1,str2);
}

void InteHomeFurn::on_P5_openTB_clicked()
{
    QString str1=trUtf8("音箱");
    QString str2=trUtf8("开");
    InfraredControlFun(str1,str2);
}

void InteHomeFurn::on_P5_closeTB_clicked()
{
    QString str1=trUtf8("音箱");
    QString str2=trUtf8("关");
    InfraredControlFun(str1,str2);
}

void InteHomeFurn::on_P5_addsoundTB_clicked()
{
    QString str1=trUtf8("音箱");
    QString str2=trUtf8("音量+");
    InfraredControlFun(str1,str2);
}

void InteHomeFurn::on_P5_redusoundTB_clicked()
{
    QString str1=trUtf8("音箱");
    QString str2=trUtf8("音量-");
    InfraredControlFun(str1,str2);
}

void InteHomeFurn::on_P6_oporclTB_clicked()
{
    QString str1=trUtf8("DVD");
    QString str2=trUtf8("开/关");
    InfraredControlFun(str1,str2);
}


void InteHomeFurn::on_P6_addsoundTB_clicked()
{
    QString str1=trUtf8("DVD");
    QString str2=trUtf8("音量+");
    InfraredControlFun(str1,str2);
}

void InteHomeFurn::on_P6_redusoundTB_clicked()
{
    QString str1=trUtf8("DVD");
    QString str2=trUtf8("音量-");
    InfraredControlFun(str1,str2);
}

void InteHomeFurn::on_P6_intooroutTB_clicked()
{
    QString str1=trUtf8("DVD");
    QString str2=trUtf8("进/出仓");
    InfraredControlFun(str1,str2);
}

void InteHomeFurn::on_P6_playorpauseTB_clicked()
{
    QString str1=trUtf8("DVD");
    QString str2=trUtf8("播放/暂停");
    InfraredControlFun(str1,str2);
}

void InteHomeFurn::on_P6_fastforwardTB_clicked()
{
    QString str1=trUtf8("DVD");
    QString str2=trUtf8("快进");
    InfraredControlFun(str1,str2);
}

void InteHomeFurn::on_P6_rewindTB_clicked()
{
    QString str1=trUtf8("DVD");
    QString str2=trUtf8("快退");
    InfraredControlFun(str1,str2);
}

void InteHomeFurn::InfraredControlFun(QString str1, QString str2)
{
    for(int i=0;i<m_control->iirtructlength;i++)
    {
         if(QString::compare(str1,m_control->m_irstruct[i].name)==0&&QString::compare(str2,m_control->m_irstruct[i].function)==0)
         {
              m_control->Ir_Send(m_control->m_irstruct[i].shortaddr,m_control->m_irstruct[i].longaddr,m_control->m_irstruct[i].code);
              return;
         }
    }
}

void InteHomeFurn::on_projectorRB_clicked()
{
    ui->stackedWidget_2->setVisible(true);
    ui->stackedWidget_2->setCurrentIndex(0);
}

void InteHomeFurn::on_televisionRB_clicked()
{
    ui->stackedWidget_2->setVisible(true);
    ui->stackedWidget_2->setCurrentIndex(1);
}

void InteHomeFurn::on_aircondfanRB_clicked()
{
    ui->stackedWidget_2->setVisible(true);
    ui->stackedWidget_2->setCurrentIndex(2);
}

void InteHomeFurn::on_aircondRB_clicked()
{
    ui->stackedWidget_2->setVisible(true);
    ui->stackedWidget_2->setCurrentIndex(3);
}

void InteHomeFurn::on_speakerRB_clicked()
{
    ui->stackedWidget_2->setVisible(true);
    ui->stackedWidget_2->setCurrentIndex(4);
}

void InteHomeFurn::on_DVDplayerRB_clicked()
{
    ui->stackedWidget_2->setVisible(true);
    ui->stackedWidget_2->setCurrentIndex(5);
}

void InteHomeFurn::runFan()
{
    fan_count++;
    ui->fengshanLabel->setPixmap(fan_pix[fan_count]);
    if(fan_count==7) fan_count=-1;
}
