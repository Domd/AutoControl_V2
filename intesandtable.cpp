#include "intesandtable.h"
#include "ui_intesandtable.h"
#include <QDebug>

InteSandTable::InteSandTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InteSandTable)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);

    QPixmap pixmap;
    pixmap.load(":/images/123.png");
    QPalette p(palette());
    p.setBrush(QPalette::Window,QBrush(pixmap));
    setPalette(p);

    pixmap.load(":/images/131.png");
    ui->toolButton2->setIcon(pixmap);
    ui->toolButton2->setIconSize(pixmap.size());
    ui->toolButton2->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/130.png");
    ui->toolButton3->setIcon(pixmap);
    ui->toolButton3->setIconSize(pixmap.size());
    ui->toolButton3->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/132.png");
    ui->toolButton4->setIcon(pixmap);
    ui->toolButton4->setIconSize(pixmap.size());
    ui->toolButton4->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/133.png");
    ui->toolButton1->setIcon(pixmap);
    ui->toolButton1->setIconSize(pixmap.size());
    ui->toolButton1->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/134.png");
    ui->toolButton5->setIcon(pixmap);
    ui->toolButton5->setIconSize(pixmap.size());
    ui->toolButton5->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/124.png");
    QPalette p2=ui->stackedWidget->palette();
    p2.setBrush(ui->stackedWidget->backgroundRole(),QBrush(pixmap));
    ui->stackedWidget->setPalette(p2);

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

    pixmap.load(":/images/button/0001.png");
    ui->gatelockTB->setIcon(pixmap);
    ui->gatelockTB->setIconSize(pixmap.size());
    ui->gatelockTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/0002.png");
    ui->PHvalueTB->setIcon(pixmap);
    ui->PHvalueTB->setIconSize(pixmap.size());
    ui->PHvalueTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/0003.png");
    ui->fingerprintTB->setIcon(pixmap);
    ui->fingerprintTB->setIconSize(pixmap.size());
    ui->fingerprintTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

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

    pixmap.load(":/images/button/0007.png");
    ui->carcontrolTB->setIcon(pixmap);
    ui->carcontrolTB->setIconSize(pixmap.size());
    ui->carcontrolTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/0008.png");
    ui->demoboradTB->setIcon(pixmap);
    ui->demoboradTB->setIconSize(pixmap.size());
    ui->demoboradTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/0009.png");
    ui->smartshelfTB->setIcon(pixmap);
    ui->smartshelfTB->setIconSize(pixmap.size());
    ui->smartshelfTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/0010.png");
    ui->toolButton->setIcon(pixmap);
    ui->toolButton->setIconSize(pixmap.size());
    ui->toolButton->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/007.png");
    ui->addlightTB->setIcon(pixmap);
    ui->addlightTB->setIconSize(pixmap.size());
    ui->addlightTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/008.png");
    ui->redulightTB->setIcon(pixmap);
    ui->redulightTB->setIconSize(pixmap.size());
    ui->redulightTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/1001.png");
    ui->qiangdianTB->setIcon(pixmap);
    ui->qiangdianTB->setIconSize(pixmap.size());
    ui->qiangdianTB->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    ui->qiangdianTB_2->setIcon(pixmap);
    ui->qiangdianTB_2->setIconSize(pixmap.size());
    ui->qiangdianTB_2->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/1002.png");
    ui->qiangdianTB2->setIcon(pixmap);
    ui->qiangdianTB2->setIconSize(pixmap.size());
    ui->qiangdianTB2->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    ui->qiangdianTB2_2->setIcon(pixmap);
    ui->qiangdianTB2_2->setIconSize(pixmap.size());
    ui->qiangdianTB2_2->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");


//    ui->lightForSlider->setRange(0,75);
//    connect(ui->lightForSlider,SIGNAL(valueChange(int)),this,SLOT(lightChangeValue()));

    ui->maininterfaceLB->setPixmap(QPixmap(":/images/136.png"));
    ui->maininterfaceLB->setVisible(true);

    initval=0x40;
    for(int k=0;k<30;k++)
    {
        aTob[k]=1;
        bToa[k]=3;
    }

    ui->equipopenTB->setEnabled(false);
    ui->equipcloseTB->setEnabled(false);
    ui->equipstopTB->setEnabled(false);

    timer=new QTimer(this);  //建立定时器
    timer->start(1000);
    connect(timer,SIGNAL(timeout()),this,SLOT(TimerOut()));
  //  resize(800,480);
    ui->stackedWidget->setVisible(false);
    ui->stackedWidget->setCurrentIndex(2);
    ui->stackedWidget_2->setVisible(false);

    //ui->sensorpictureLabel->setPixmap(QPixmap(":/images/Sensor/sensor1.png"));
//    ui->pagelabel1->setPixmap(QPixmap(":/images/button/001.png"));
//    ui->pagelabel2->setPixmap(QPixmap(":/images/button/002.png"));
//    ui->pagelabel3->setPixmap(QPixmap(":/images/button/003.png"));
//    ui->pagelabel4->setPixmap(QPixmap(":/images/button/004.png"));
//    ui->pagelabel5->setPixmap(QPixmap(":/images/button/005.png"));
//    ui->pagelabel6->setPixmap(QPixmap(":/images/button/006.png"));
    ui->label->setPixmap(QPixmap(":/images/141.png"));
    ui->label_2->setPixmap(QPixmap(":/images/140.png"));
    ui->sensorpictureLabel->setText(trUtf8("<font color=red>未选择节点</font>"));

    QStringList header;
    header<<trUtf8("序号")<<trUtf8("节点名称")<<trUtf8("节点位置")<<trUtf8("短地址")<<trUtf8("MAC节点地址")<<trUtf8("节点状态");
    ui->SersonStatusTW->setColumnCount(6);   //设置4列数据
    ui->SersonStatusTW->setColumnWidth(0,0);
    ui->SersonStatusTW->setColumnWidth(1,150);
    ui->SersonStatusTW->setColumnWidth(2,0);
    ui->SersonStatusTW->setColumnWidth(3, 0);
    ui->SersonStatusTW->setColumnWidth(4, 0);
    ui->SersonStatusTW->setColumnWidth(5,100);
    ui->SersonStatusTW->setHorizontalHeaderLabels(header);
    ui->SersonStatusTW->setSelectionBehavior(QAbstractItemView::SelectRows);  //设置选择行为 ，以行为单位
    ui->SersonStatusTW->verticalHeader()->setVisible(false);     //隐藏列表头
    ui->SersonStatusTW->horizontalHeader()->setVisible(false);  //隐藏行表头
//    ui->SersonStatusTW->setFrameShape(QFrame::Box);//QFrame在它的内容周围画一个框
    ui->SersonStatusTW->setFrameShape(QFrame::NoFrame);  //设置边框 (不画任何东西)


//    ui->Tb_jiaoping->setVisible(false);

    ReadDatabase();
}

InteSandTable::~InteSandTable()
{
    delete ui;

    timer->stop();
    delete timer;
}
void InteSandTable::TimerOut() //时间 和 节点状态
{
    //节点状态
    int j=0;
    while(j<17)
    {
        if(m_control->JDFlag[j])
        {
            aTob[j]=1;bToa[j]++;
        }
        else
        {
             aTob[j]++;bToa[j]=1;
        }
        j++;
    }
        //改变状态数据库
        addStatusDb();
         //加入节点后 读取数据库
        if(m_control->addChange==true)
        {
            ReadDatabase();
            m_control->addChange=false;
        }
        //添数据
        if(m_control->changeData4)
        {
            ui->jieluLabel->setText(trUtf8("结露:")+"<font color=red>"+m_control->jieluNow+"</font>");
            ui->guangminLabel->setText(trUtf8("光敏:")+"<font color=red>"+m_control->guangminNow+"</font>");
            ui->yudiLabel->setText(trUtf8("雨滴:")+"<font color=red>"+m_control->rainNow+"</font>");
            ui->wenshiduLabel->setText(trUtf8("温湿度:")+"<font color=red>"+m_control->tempNow+'C'+m_control->humNow+"%RH"+"</font>");
            ui->guangxianLabel->setText(trUtf8("光线:")+"<font color=red>"+m_control->guangxianNow+"</font>");
            ui->kongqiLabel->setText(trUtf8("空气质量:")+"<font color=red>"+m_control->airNow+"</font>");
            ui->qiyaLabel->setText(trUtf8("气压:")+"<font color=red>"+m_control->qiyaNow+"</font>");
            ui->huoyanLabel->setText(trUtf8("火焰:")+"<font color=red>"+m_control->huoyanNow+"</font>");
            ui->anjianLabel->setText(trUtf8("遥控按键:")+"<font color=red>"+m_control->anjianNow+"</font>");
            ui->threefiveLabel->setText(trUtf8("家庭安防:")+"<font color=red>"+m_control->threefiveNow+"</font>");
            ui->zhendongLabel->setText(trUtf8("震动:")+"<font color=red>"+m_control->zhendongNow+"</font>");
            ui->rfidchaogaopinLabel->setText(trUtf8("超高频:")+"<font color=red>"+m_control->chaogaopinNow+"</font>");
            ui->rfidgaopinLabel->setText(trUtf8("高频:")+"<font color=red>"+m_control->gaopinNow+"</font>");
            ui->rfiddipinLabel->setText(trUtf8("低频:")+"<font color=red>"+m_control->dipinNow+"</font>");
            ui->zaoshengLabel->setText(trUtf8("噪声:")+"<font color=red>"+m_control->zaoshengNow+"</font>");
            ui->yangqiLabel->setText(trUtf8("氧气:")+"<font color=red>"+m_control->yangqiNow+"</font>");
            ui->shuiweiLabel->setText(trUtf8("水位:")+"<font color=red>"+m_control->shuiweiNow+"</font>");
            ui->co2Label->setText(trUtf8("二氧化碳:")+"<font color=red>"+m_control->co2Now+"</font>");
            ui->soilwenshiduLabel->setText(trUtf8("土壤温湿度:")+"<font color=red>"+m_control->soiltempNow+'C'+m_control->soilhumNow+"%RH"+"</font>");
            ui->sanzhouLabel->setText(trUtf8("三轴加速度:")+"<font color=red>"+m_control->sanzhouNow+"</font>");
            ui->colorLabel->setText(trUtf8("颜色")+"<font color=red>"+m_control->colorNow+"</font>");

            m_control->changeData4=false;
        }
}

void InteSandTable::addStatusDb()
{
    for(int i=0;i<17;i++)
    {
        if(bToa[i]==2)
        {
            if(m_control->rownum[i]>0 )
            {

                if(i>=10 && i<=14) m_control->changeAgriDB=true;
                if(i>=2   &&  i<=8 ) m_control->changeHomeDB=true;
                InputDbOnline(m_control->rownum[i]);
                bToa[i]=3;
            }
        }
        else if(aTob[i]==2)
        {
            if( m_control->rownum[i]>0)
            {
                if(i>=10 && i<=14) m_control->changeAgriDB=true;
                if(i>=2   &&  i<=8 ) m_control->changeHomeDB=true;
                InputDbOffline(m_control->rownum[i]);
                aTob[i]=3;
            }
       }
    }
}


void InteSandTable::on_toolButton1_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->toolButton1->setFocus();
    ui->interfaceLabel->setText(trUtf8(""));
    ui->maininterfaceLB->setVisible(true);
    ui->stackedWidget->setVisible(false);
}

void InteSandTable::on_toolButton2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->toolButton2->setFocus();
    ui->interfaceLabel->setText(trUtf8("<font color=white>节点状态信息</font>"));
    ui->maininterfaceLB->setVisible(false);
    ui->stackedWidget->setVisible(true);
}

void InteSandTable::on_toolButton3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->toolButton3->setFocus();
    ui->interfaceLabel->setText(trUtf8("<font color=white>节点监测</font>"));
    ui->maininterfaceLB->setVisible(false);
    ui->stackedWidget->setVisible(true);
}

void InteSandTable::on_toolButton4_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->toolButton4->setFocus();
    ui->interfaceLabel->setText(trUtf8("<font color=white>节点控制</font>"));
    ui->maininterfaceLB->setVisible(false);
    ui->stackedWidget->setVisible(true);
}


void InteSandTable::ReadDatabase()
{
    DeleteNullForTable();
    //QSqlQuery
    QSqlQuery m_query(m_control->m_sql);
    QString str="";
    m_query.prepare("SELECT * FROM SensorTable");
    if(m_query.exec())
    {
        int Row=0;
        str="";
        m_control->isensorlength=0;
        while(m_query.next())
        {
            ui->SersonStatusTW->setRowCount(Row+1);
            ui->SersonStatusTW->setItem(Row,0,new QTableWidgetItem(m_query.value(0).toString()));
            ui->SersonStatusTW->setItem(Row,1,new QTableWidgetItem(m_query.value(1).toString()));
            ui->SersonStatusTW->setItem(Row,2,new QTableWidgetItem(m_query.value(4).toString()));
            ui->SersonStatusTW->setItem(Row,3,new QTableWidgetItem(m_query.value(2).toString()));
            ui->SersonStatusTW->setItem(Row,4,new QTableWidgetItem(m_query.value(3).toString()));
            ui->SersonStatusTW->setItem(Row,5,new QTableWidgetItem(m_query.value(5).toString()));
            ui->SersonStatusTW->setRowHeight(Row,50);
            //判断状态 设置字体颜色
            if(ui->SersonStatusTW->item(Row,5)->text()==trUtf8("在线"))
            {
                ui->SersonStatusTW->item(Row,5)->setTextColor(QColor(Qt::green));
            }
            if(ui->SersonStatusTW->item(Row,5)->text()==trUtf8("离线"))
            {
                ui->SersonStatusTW->item(Row,5)->setTextColor(QColor(Qt::red));
            }
            m_control->m_sensorstruct[m_control->isensorlength].id=m_query.value(0).toInt();
            m_control->m_sensorstruct[m_control->isensorlength].name=m_query.value(1).toString();
            m_control->m_sensorstruct[m_control->isensorlength].shortaddr=m_query.value(2).toString();
            m_control->m_sensorstruct[m_control->isensorlength].longaddr=m_query.value(3).toString();
            m_control->m_sensorstruct[m_control->isensorlength].dir=m_query.value(4).toString();
            m_control->m_sensorstruct[m_control->isensorlength].status=m_query.value(5).toString();            
            m_control->isensorlength++;
            Row++;
        }
    }  
}
void InteSandTable::DeleteNullForTable()
{
    for(int k=0;k<ui->SersonStatusTW->rowCount();k++)
    {
        ui->SersonStatusTW->removeRow(k);
    }
}

void InteSandTable::InputDbOnline(int row)
{
    QSqlQuery m_query;
    m_query.prepare(QString("UPDATE SensorTable SET status=? WHERE id=%1").arg(row));
    m_query.bindValue(0,trUtf8("在线"));
    if(!m_query.exec())
    {
        QMessageBox::warning(this,trUtf8("提示"),trUtf8("添加数据失败！"),QMessageBox::Ok);
        return;
    }
    ReadDatabase();
}
void InteSandTable::InputDbOffline(int row)
{
    QSqlQuery m_query;
    m_query.prepare(QString("UPDATE SensorTable SET status=? WHERE id=%1").arg(row));
    m_query.bindValue(0,trUtf8("离线"));
    if(!m_query.exec())
    {
        QMessageBox::warning(this,trUtf8("提示"),trUtf8("添加数据失败！"),QMessageBox::Ok);
        return;
    }
    ReadDatabase();
}
////数据库 （节点所在的行号）
//bool InteSandTable::JudgeDb(int row)
//{
// //    QMessageBox::warning(this,"tishi","JudgeDb",QMessageBox::Ok);
//    QSqlQuery m_query;
//    bool ok=m_query.exec(QString("SELECT * FROM SensorTable WHERE id=%1").arg(row));
//    if(ok)
//        return true;
//    else
//        return false;
//}
//小车控制 界面
void InteSandTable::on_carcontrolTB_clicked()
{
    this->hide();
    this->m_car = new SmartCar();
    this->m_car->show();
    this->m_car->parent = this;
}
//演示板 界面
void InteSandTable::on_demoboradTB_clicked()
{
    for(int i=0;i<m_control->isensorlength;i++)
    {
        if(QString::compare(trUtf8("演示板"),m_control->m_sensorstruct[i].name)==0)
        {
            m_control->stryanshibanaddr=m_control->m_sensorstruct[i].shortaddr;
            m_control->stryanshibanmacaddr=m_control->m_sensorstruct[i].longaddr;
        }
    }
    this->hide();
    this->m_yanshiban = new YanShiBan();
    this->m_yanshiban->show();
    this->m_yanshiban->parent = this;
}
//智能货架 界面
void InteSandTable::on_smartshelfTB_clicked()
{
    this->hide();
    this->m_smartshelf = new smartshelf();
    this->m_smartshelf->show();
    this->m_smartshelf->parent = this;
}


void InteSandTable::on_gatelockTB_clicked()
{
    if(m_control->rownum[23]>0)
    {
        for(int i=0;i<m_control->isensorlength;i++)
        {
            if(m_control->m_sensorstruct[i].name==trUtf8("门锁"))
            {
                m_control->MenSuo_ON(m_control->m_sensorstruct[i].shortaddr,m_control->m_sensorstruct[i].longaddr);
                ui->infoLabel->setText("门锁打开成功。。");
                return;
            }
        }
    }
    else
    {
        ui->infoLabel->setText(trUtf8("未添加门锁设备。。"));
    }
}

void InteSandTable::on_PHvalueTB_clicked()
{
    if(m_control->rownum[28]>0)
    {
        for(int i=0;i<m_control->isensorlength;i++)
        {
            if(m_control->m_sensorstruct[i].name==trUtf8("PH"))
            {
                m_control->MenSuo_ON(m_control->m_sensorstruct[i].shortaddr,m_control->m_sensorstruct[i].longaddr);
                ui->infoLabel->setText("发送PH成功。。");
                return;
            }
        }
    }
    else
    {
        ui->infoLabel->setText(trUtf8("未添加测试PH设备。。"));
    }
}

void InteSandTable::on_fingerprintTB_clicked()
{
    if(m_control->rownum[24]>0)
    {
        for(int i=0;i<m_control->isensorlength;i++)
        {
            if(m_control->m_sensorstruct[i].name==trUtf8("指纹"))
            {
                m_control->ZhiWen_Sousuo(m_control->m_sensorstruct[i].shortaddr,m_control->m_sensorstruct[i].longaddr);
                ui->infoLabel->setText("指纹搜索发送类");
                return;
            }
        }
    }
    else
    {
        ui->infoLabel->setText(trUtf8("未添加指纹识别类设备。。"));
    }
}

void InteSandTable::on_projectorRB_clicked()
{
    ui->stackedWidget_2->setVisible(true);
    ui->stackedWidget_2->setCurrentIndex(0);
}

void InteSandTable::on_televisionRB_clicked()
{
    ui->stackedWidget_2->setVisible(true);
    ui->stackedWidget_2->setCurrentIndex(1);
}

void InteSandTable::on_aircondfanRB_clicked()
{
    ui->stackedWidget_2->setVisible(true);
    ui->stackedWidget_2->setCurrentIndex(2);
}

void InteSandTable::on_aircondRB_clicked()
{
    ui->stackedWidget_2->setVisible(true);
    ui->stackedWidget_2->setCurrentIndex(3);
}

void InteSandTable::on_speakerRB_clicked()
{
    ui->stackedWidget_2->setVisible(true);
    ui->stackedWidget_2->setCurrentIndex(4);
}

void InteSandTable::on_DVDplayerRB_clicked()
{
    ui->stackedWidget_2->setVisible(true);
    ui->stackedWidget_2->setCurrentIndex(5);
}

void InteSandTable::on_P1_openTB_clicked()
{
    QString str1=trUtf8("投影机");
    QString str2=trUtf8("开");
    InfraredControlFun(str1,str2);
}

void InteSandTable::on_P1_closeTB_clicked()
{
    QString str1=trUtf8("投影机");
    QString str2=trUtf8("关");
    InfraredControlFun(str1,str2);
}

void InteSandTable::on_P2_openTB_clicked()
{
    QString str1=trUtf8("电视机");
    QString str2=trUtf8("开");
    InfraredControlFun(str1,str2);
}

void InteSandTable::on_P2_closeTB_clicked()
{
    QString str1=trUtf8("电视机");
    QString str2=trUtf8("关");
    InfraredControlFun(str1,str2);
}

void InteSandTable::on_P2_addsoundTB_clicked()
{
    QString str1=trUtf8("电视机");
    QString str2=trUtf8("音量+");
    InfraredControlFun(str1,str2);
}

void InteSandTable::on_P2_redusoundTB_clicked()
{
    QString str1=trUtf8("电视机");
    QString str2=trUtf8("音量-");
    InfraredControlFun(str1,str2);
}

void InteSandTable::on_P2_AVtypeTB_clicked()
{
    QString str1=trUtf8("电视机");
    QString str2=trUtf8("AV模式");
    InfraredControlFun(str1,str2);
}

void InteSandTable::on_P2_addchannelTB_clicked()
{
    QString str1=trUtf8("电视机");
    QString str2=trUtf8("频道+");
    InfraredControlFun(str1,str2);
}

void InteSandTable::on_P2_reduchannelTB_clicked()
{
    QString str1=trUtf8("电视机");
    QString str2=trUtf8("频道-");
    InfraredControlFun(str1,str2);
}

void InteSandTable::on_P3_openTB_clicked()
{
    QString str1=trUtf8("空调扇");
    QString str2=trUtf8("开");
    InfraredControlFun(str1,str2);
}

void InteSandTable::on_P3_closeTB_clicked()
{
    QString str1=trUtf8("空调扇");
    QString str2=trUtf8("关");
    InfraredControlFun(str1,str2);
}

void InteSandTable::on_P3_windspeedTB_clicked()
{
    QString str1=trUtf8("空调扇");
    QString str2=trUtf8("风速");
    InfraredControlFun(str1,str2);
}

void InteSandTable::on_P3_winddireTB_clicked()
{
    QString str1=trUtf8("空调扇");
    QString str2=trUtf8("风向");
    InfraredControlFun(str1,str2);
}

void InteSandTable::on_P4_openTB_clicked()
{
    QString str1=trUtf8("空调");
    QString str2=trUtf8("开");
    InfraredControlFun(str1,str2);
}

void InteSandTable::on_P4_closeTB_clicked()
{
    QString str1=trUtf8("空调");
    QString str2=trUtf8("关");
    InfraredControlFun(str1,str2);
}

void InteSandTable::on_P4_presetTB_clicked()
{
    QString str1=trUtf8("空调");
    QString str2=trUtf8("预设温度");
    InfraredControlFun(str1,str2);
}

void InteSandTable::on_P4_windspeedTB_clicked()
{
    QString str1=trUtf8("空调");
    QString str2=trUtf8("风速");
    InfraredControlFun(str1,str2);
}

void InteSandTable::on_P4_winddireTB_clicked()
{
    QString str1=trUtf8("空调");
    QString str2=trUtf8("风向");
    InfraredControlFun(str1,str2);
}

void InteSandTable::on_P5_openTB_clicked()
{
    QString str1=trUtf8("音箱");
    QString str2=trUtf8("开");
    InfraredControlFun(str1,str2);
}

void InteSandTable::on_P5_closeTB_clicked()
{
    QString str1=trUtf8("音箱");
    QString str2=trUtf8("关");
    InfraredControlFun(str1,str2);
}

void InteSandTable::on_P5_addsoundTB_clicked()
{
    QString str1=trUtf8("音箱");
    QString str2=trUtf8("音量+");
    InfraredControlFun(str1,str2);
}

void InteSandTable::on_P5_redusoundTB_clicked()
{
    QString str1=trUtf8("音箱");
    QString str2=trUtf8("音量-");
    InfraredControlFun(str1,str2);
}

void InteSandTable::on_P6_oporclTB_clicked()
{
    QString str1=trUtf8("DVD");
    QString str2=trUtf8("开/关");
    InfraredControlFun(str1,str2);
}


void InteSandTable::on_P6_addsoundTB_clicked()
{
    QString str1=trUtf8("DVD");
    QString str2=trUtf8("音量+");
    InfraredControlFun(str1,str2);
}

void InteSandTable::on_P6_redusoundTB_clicked()
{
    QString str1=trUtf8("DVD");
    QString str2=trUtf8("音量-");
    InfraredControlFun(str1,str2);
}

void InteSandTable::on_P6_intooroutTB_clicked()
{
    QString str1=trUtf8("DVD");
    QString str2=trUtf8("进/出仓");
    InfraredControlFun(str1,str2);
}

void InteSandTable::on_P6_playorpauseTB_clicked()
{
    QString str1=trUtf8("DVD");
    QString str2=trUtf8("播放/暂停");
    InfraredControlFun(str1,str2);
}

void InteSandTable::on_P6_fastforwardTB_clicked()
{
    QString str1=trUtf8("DVD");
    QString str2=trUtf8("快进");
    InfraredControlFun(str1,str2);
}

void InteSandTable::on_P6_rewindTB_clicked()
{
    QString str1=trUtf8("DVD");
    QString str2=trUtf8("快退");
    InfraredControlFun(str1,str2);
}

void InteSandTable::InfraredControlFun(QString str1, QString str2)
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

void InteSandTable::on_equipopenTB_clicked()
{
    if(ui->curtainsRB->isChecked()==true)
    {
        for(int i=0;i<m_control->isensorlength;i++)
        {
            if(QString::compare(trUtf8("窗帘"),m_control->m_sensorstruct[i].name)==0)
            {
                m_control->CUR_ON(m_control->m_sensorstruct[i].shortaddr,m_control->m_sensorstruct[i].longaddr);
                return;
            }
        }
    }
    if(ui->canopyRB->isChecked()==true)
    {
        for(int i=0;i<m_control->isensorlength;i++)
        {
            if(QString::compare(trUtf8("雨蓬"),m_control->m_sensorstruct[i].name)==0)
            {
                m_control->YuPengOn(m_control->m_sensorstruct[i].shortaddr,m_control->m_sensorstruct[i].longaddr);
                return;
            }
        }
    }
}

void InteSandTable::on_equipcloseTB_clicked()
{
    if(ui->curtainsRB->isChecked()==true)
    {
        for(int i=0;i<m_control->isensorlength;i++)
        {
            if(QString::compare(trUtf8("窗帘"),m_control->m_sensorstruct[i].name)==0)
            {
                m_control->CUR_OFF(m_control->m_sensorstruct[i].shortaddr,m_control->m_sensorstruct[i].longaddr);
                 return;
            }
        }
    }
    if(ui->canopyRB->isChecked()==true)
    {
        for(int i=0;i<m_control->isensorlength;i++)
        {
            if(QString::compare(trUtf8("雨蓬"),m_control->m_sensorstruct[i].name)==0)
            {
                m_control->YuPengStop(m_control->m_sensorstruct[i].shortaddr,m_control->m_sensorstruct[i].longaddr);
                return;
            }
        }
    }
}

void InteSandTable::on_equipstopTB_clicked()
{
    if(ui->canopyRB->isChecked()==true)
    {
        for(int i=0;i<m_control->isensorlength;i++)
        {
            if(QString::compare(trUtf8("雨蓬"),m_control->m_sensorstruct[i].name)==0)
            {
                m_control->YuPengBettween(m_control->m_sensorstruct[i].shortaddr,m_control->m_sensorstruct[i].longaddr);
                return;
            }
        }
    }
}

void InteSandTable::on_addlightTB_clicked()
{
    for(int i=0;i<m_control->isensorlength;i++)
    {
         if(QString::compare(trUtf8("调光"),m_control->m_sensorstruct[i].name)==0)
         {
             if( initval<0x75)
             {
                initval=initval+0x10;
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

void InteSandTable::on_redulightTB_clicked()
{
    for(int i=0;i<m_control->isensorlength;i++)
    {
         if(QString::compare(trUtf8("调光"),m_control->m_sensorstruct[i].name)==0)
         {
             if( initval>0x00)
             {
                initval=initval-0x10;
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

void InteSandTable::on_SersonStatusTW_cellClicked(int row, int column)
{
    QTableWidgetItem *item = ui->SersonStatusTW->item(row,1);
    if(item->text().contains("RFID")==true)
    {
        ui->sensorpictureLabel->setPixmap(QPixmap(":/images/Sensor/sensor1.png"));
        return;
    }
    else if(item->text().contains(trUtf8("超高频"))==true)
    {
        ui->sensorpictureLabel->setPixmap(QPixmap(":/images/Sensor/sensor2.jpg"));
        return;
    }
    else if(item->text().contains(trUtf8("超声波测距"))==true)
    {
        ui->sensorpictureLabel->setPixmap(QPixmap(":/images/Sensor/sensor3.jpg"));
        return;
    }
    else if(item->text().contains(trUtf8("调光"))==true)
    {
        ui->sensorpictureLabel->setPixmap(QPixmap(":/images/Sensor/sensor4.jpg"));
        return;
    }
    else if(item->text().contains(trUtf8("窗帘"))==true)
    {
        ui->sensorpictureLabel->setPixmap(QPixmap(":/images/Sensor/sensor5.jpg"));
        return;
    }
    else if(item->text().contains(trUtf8("低频"))==true)
    {
        ui->sensorpictureLabel->setPixmap(QPixmap(":/images/Sensor/sensor6.jpg"));
        return;
    }

    else if(item->text().contains(trUtf8("二氧化碳"))==true)
    {
        ui->sensorpictureLabel->setPixmap(QPixmap(":/images/Sensor/sensor7.jpg"));
        return;
    }
    else if(item->text().contains(trUtf8("高频"))==true)
    {
        ui->sensorpictureLabel->setPixmap(QPixmap(":/images/Sensor/sensor8.jpg"));
        return;
    }
    else if(item->text().contains(trUtf8("光敏"))==true)
    {
        ui->sensorpictureLabel->setPixmap(QPixmap(":/images/Sensor/sensor9.jpg"));
        return;
    }
    else if(item->text().contains(trUtf8("光线"))==true)
    {
        ui->sensorpictureLabel->setPixmap(QPixmap(":/images/Sensor/sensor10.png"));
        return;
    }
//    if(item->text().contains(trUtf8("光线"))==true)
//    {
//        ui->sensorpictureLabel->setPixmap(QPixmap(":/images/Sensor/sensor11.jpg"));
//        return;
//    }
    else if(item->text().contains(trUtf8("红外"))==true)
    {
        ui->sensorpictureLabel->setPixmap(QPixmap(":/images/Sensor/sensor12.png"));
        return;
    }
    else if(item->text().contains(trUtf8("火焰"))==true)
    {
        ui->sensorpictureLabel->setPixmap(QPixmap(":/images/Sensor/sensor13.png"));
        return;
    }
    else if(item->text().contains(trUtf8("灯"))==true)//继电器
    {
        ui->sensorpictureLabel->setPixmap(QPixmap(":/images/Sensor/sensor14.jpg"));
        return;
    }
    else if(item->text().contains(trUtf8("结露"))==true)
    {
        ui->sensorpictureLabel->setPixmap(QPixmap(":/images/Sensor/sensor15.jpg"));
        return;
    }
    else if(item->text().contains(trUtf8("可燃气体"))==true)
    {
        ui->sensorpictureLabel->setPixmap(QPixmap(":/images/Sensor/sensor16.jpg"));
        return;
    }
    else if(item->text().contains(trUtf8("空气质量"))==true)
    {
        ui->sensorpictureLabel->setPixmap(QPixmap(":/images/Sensor/sensor17.jpg"));
        return;
    }
    else if(item->text().contains(trUtf8("设备1"))||item->text().contains(trUtf8("设备2")))
    {
        ui->sensorpictureLabel->setPixmap(QPixmap(":/images/Sensor/sensor18.jpg"));
        return;
    }
    else if(item->text().contains(trUtf8("演示板"))==true)  //数码管
    {
        ui->sensorpictureLabel->setPixmap(QPixmap(":/images/Sensor/sensor19.jpg"));
        return;
    }
    else if(item->text().contains(trUtf8("气压"))==true)
    {
        ui->sensorpictureLabel->setPixmap(QPixmap(":/images/Sensor/sensor20.jpg"));
        return;
    }
    else if(item->text().contains(trUtf8("土壤温湿度"))==true)
    {
        ui->sensorpictureLabel->setPixmap(QPixmap(":/images/Sensor/sensor21.jpg"));
        return;
    }
    else if(item->text().contains(trUtf8("温湿度"))==true)
    {
        ui->sensorpictureLabel->setPixmap(QPixmap(":/images/Sensor/sensor22.jpg"));
        return;
    }
    else if(item->text().contains(trUtf8("颜色"))==true)
    {
        ui->sensorpictureLabel->setPixmap(QPixmap(":/images/Sensor/sensor23.jpg"));
        return;
    }
    else if(item->text().contains(trUtf8("遥控按键"))==true)
    {
        ui->sensorpictureLabel->setPixmap(QPixmap(":/images/Sensor/sensor24.jpg"));
        return;
    }
    else if(item->text().contains(trUtf8("雨滴"))==true)
    {
        ui->sensorpictureLabel->setPixmap(QPixmap(":/images/Sensor/sensor25.jpg"));
        return;
    }
    else if(item->text().contains(trUtf8("雨蓬"))==true)
    {
        ui->sensorpictureLabel->setPixmap(QPixmap(":/images/Sensor/sensor26.jpg"));
        return;
    }
    else if(item->text().contains(trUtf8("语音播报"))==true)
    {
        ui->sensorpictureLabel->setPixmap(QPixmap(":/images/Sensor/sensor27.jpg"));
        return;
    }
    else if(item->text().contains(trUtf8("震动"))==true)
    {
        ui->sensorpictureLabel->setPixmap(QPixmap(":/images/Sensor/sensor28.png"));
        return;
    }
    else if(item->text().contains(trUtf8("指纹"))==true)
    {
        ui->sensorpictureLabel->setPixmap(QPixmap(":/images/Sensor/sensor29.png"));
        return;
    }
    else if(item->text().contains(trUtf8("小车"))==true)
    {
        ui->sensorpictureLabel->setPixmap(QPixmap(":/images/Sensor/sensor30.jpg"));
        return;
    }
    else
    {
        ui->sensorpictureLabel->setText(trUtf8("未找到该节点示意图"));
    }
}

//系统主页
void InteSandTable::on_toolButton5_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    this->parent->show();
    this->close();
}

//设置界面
void InteSandTable::on_toolButton_clicked()
{
    this->hide();
    m_control->show();
    m_control->ISTparent=this;

}

void InteSandTable::on_curtainsRB_clicked()
{
    ui->equipopenTB->setEnabled(true);
    ui->equipcloseTB->setEnabled(true);
    ui->equipstopTB->setEnabled(false);
}

void InteSandTable::on_canopyRB_clicked()
{
    ui->equipopenTB->setEnabled(true);
    ui->equipcloseTB->setEnabled(true);
    ui->equipstopTB->setEnabled(true);
}


//void InteSandTable::lightChangeValue()
//{
//    for(int i=0;i<m_control->isensorlength;i++)
//    {
//         if(QString::compare(trUtf8("调光"),m_control->m_sensorstruct[i].name)==0)
//         {
//            initval=ui->lightForSlider->value();
//             m_control->SUN_OFF(m_control->m_sensorstruct[i].shortaddr,m_control->m_sensorstruct[i].longaddr,initval);
//             return;
//         }
//    }
//}


void InteSandTable::on_qiangdianTB_clicked()
{
    bool flag=false;
    for(int i=0;i<m_control->isensorlength;i++)
    {
        if(m_control->m_sensorstruct[i].name==trUtf8("设备1"))
        {
             m_control->KG_ON(m_control->m_sensorstruct[i].shortaddr,m_control->m_sensorstruct[i].longaddr);
             ui->qiangdianLabel->setText(trUtf8("强电设备1打开命令已经发送."));
            flag=true;
            break;
        }
    }
    if(!flag)
    {
        ui->qiangdianLabel->setText(trUtf8("未添加强电设备1."));
    }
}

void InteSandTable::on_qiangdianTB2_clicked()
{
    bool flag=false;
    for(int i=0;i<m_control->isensorlength;i++)
    {
        if(m_control->m_sensorstruct[i].name==trUtf8("设备1"))
        {
             m_control->KG_OFF(m_control->m_sensorstruct[i].shortaddr,m_control->m_sensorstruct[i].longaddr);
             ui->qiangdianLabel->setText(trUtf8("强电设备1关闭命令已经发送."));
            flag=true;
            break;
        }
    }
    if(!flag)
    {
        ui->qiangdianLabel->setText(trUtf8("未添加强电设备1."));
    }
}



void InteSandTable::on_qiangdianTB_2_clicked()
{
    bool flag=false;
    for(int i=0;i<m_control->isensorlength;i++)
    {
        if(m_control->m_sensorstruct[i].name==trUtf8("设备2"))
        {
             m_control->KG_ON(m_control->m_sensorstruct[i].shortaddr,m_control->m_sensorstruct[i].longaddr);
             ui->qiangdianLabel->setText(trUtf8("强电设备2打开命令已经发送."));
            flag=true;
            break;
        }
    }
    if(!flag)
    {
        ui->qiangdianLabel->setText(trUtf8("未添加强电设备2."));
    }
}

void InteSandTable::on_qiangdianTB2_2_clicked()
{
    bool flag=false;
    for(int i=0;i<m_control->isensorlength;i++)
    {
        if(m_control->m_sensorstruct[i].name==trUtf8("设备2"))
        {
             m_control->KG_OFF(m_control->m_sensorstruct[i].shortaddr,m_control->m_sensorstruct[i].longaddr);
             ui->qiangdianLabel->setText(trUtf8("强电设备2关闭命令已经发送."));
            flag=true;
            break;
        }
    }
    if(!flag)
    {
        ui->qiangdianLabel->setText(trUtf8("未添加强电设备2."));
    }
}


//void InteSandTable::on_Tb_jiaoping_clicked()
//{
//    this->close();
//    ::system("recalibrate > /tmp/tmp &");
//    qDebug()<<"recalibrate";
//    return;
//}


void InteSandTable::mousePressEvent(QMouseEvent *event)
{
    if(ui->stackedWidget->currentIndex()==0)
    {
        if (event->pos().y() > 170 && event->pos().y() < 215)
        {
            if(event->pos().x() > 120 && event->pos().x() < 270)
            {
                this->m_TBF=new TestBasic();
                this->m_TBF->show();
                this->m_TBF->parent=this;
                this->hide();
            }
            if(event->pos().x() > 330 && event->pos().x() < 480)
            {
                this->m_TWF=new TestWifi();
                this->m_TWF->show();
                this->m_TWF->parent=this;
                this->hide();
            }
            if(event->pos().x() > 550 && event->pos().x() < 700)
            {
                this->m_TCM=new TestCom();
                this->m_TCM->show();
                this->m_TCM->parent=this;
                this->hide();

            }
        }

        if (event->pos().y() > 290 && event->pos().y() < 335)
        {
            if(event->pos().x() > 120 && event->pos().x() < 270)
            {
                this->m_TTG=new TestThreeG();
                this->m_TTG->show();
                this->m_TTG->parent=this;
                this->hide();
            }
            if(event->pos().x() > 330 && event->pos().x() < 480)
            {
                this->m_TGprs=new TestGprs();
                this->m_TGprs->show();
                this->m_TGprs->parent=this;
                this->hide();
            }
            if(event->pos().x() > 550 && event->pos().x() < 700)
            {
                this->m_TGps=new TestGps();
                this->m_TGps->show();
                this->m_TGps->parent=this;
                this->hide();
            }
        }
        if(event->pos().y() > 215 && event->pos().y() < 300)
        {
            if(event->pos().x() > 55 && event->pos().x() < 95)
            {
                ui->stackedWidget->setCurrentIndex(3);
            }
        }
    }

    if(ui->stackedWidget->currentIndex()==3)
    {
        if(event->pos().y() > 215 && event->pos().y() < 300)
        {
            if(event->pos().x() > 710 && event->pos().x() < 760)
            {
                ui->stackedWidget->setCurrentIndex(0);
            }
        }
    }


}
