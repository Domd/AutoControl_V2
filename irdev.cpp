#include "irdev.h"
#include "ui_irdev.h"
#include "autocontrol_v2.h"

//======================================================================================================================
char ircf[10]={0xFD,0x04,0xFF,0xFF,0x00,0x00,'K',0xFF,0xFF,0x00};
char sendhw[21]={0xFD,0x0F,0x0A,0xFF,0x00,0x00,'K',0x0A,0xFF,0xDD,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
char iraddr[2]={0x00,0x00};
IRDev::IRDev(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IRDev)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    m_control->whichdialog=2;
    tablerow1=-1;
    label1=ui->label_5;
    QStringList header;
    header.append(trUtf8("名称"));
    header.append(trUtf8("短地址"));
    header.append(trUtf8("MAC地址"));
    m_table=ui->tableWidget;
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setColumnWidth(0, 147);
    ui->tableWidget->setColumnWidth(1, 130);
    ui->tableWidget->setColumnWidth(2, 350);
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->comboBox->insertItem(0,QIcon(":/images/7.png"),trUtf8("空调"));
    ui->comboBox->insertItem(1,QIcon(":/images/2.png"),trUtf8("电视机"));
    ui->comboBox->insertItem(2,QIcon(":/images/4.png"),trUtf8("投影机"));
    ui->comboBox->insertItem(3,QIcon(":/images/5.png"),trUtf8("空调扇"));
    ui->comboBox->insertItem(4,QIcon(":/images/10.png"),trUtf8("音箱"));
    ui->comboBox->insertItem(4,QIcon(":/images/1.png"),trUtf8("DVD"));

    ui->comboBox->setCurrentIndex(0);

    ui->comboBox_2->insertItem(0,QIcon(":/images/10.png"),trUtf8("上"));
    ui->comboBox_2->insertItem(1,QIcon(":/images/2.png"),trUtf8("下"));
    ui->comboBox_2->insertItem(2,QIcon(":/images/3.png"),trUtf8("左"));
    ui->comboBox_2->insertItem(3,QIcon(":/images/4.png"),trUtf8("右"));
    ui->comboBox_2->insertItem(4,QIcon(":/images/5.png"),trUtf8("正中"));
    ui->comboBox_2->insertItem(5,QIcon(":/images/6.png"),trUtf8("正右"));
    ui->comboBox_2->insertItem(6,QIcon(":/images/7.png"),trUtf8("正左"));
    ui->comboBox_2->insertItem(7,QIcon(":/images/1.png"),trUtf8("卧室"));
    ui->comboBox_2->insertItem(8,QIcon(":/images/2.png"),trUtf8("厨房"));
    ui->comboBox_2->insertItem(9,QIcon(":/images/3.png"),trUtf8("餐厅"));
    ui->comboBox_2->insertItem(10,QIcon(":/images/4.png"),trUtf8("书房"));
    ui->comboBox_2->insertItem(11,QIcon(":/images/5.png"),trUtf8("客厅"));
    ui->comboBox_2->insertItem(12,QIcon(":/images/6.png"),trUtf8("阳台"));
    ui->comboBox_2->insertItem(13,QIcon(":/images/5.png"),trUtf8("大棚"));
    ui->comboBox_2->insertItem(14,QIcon(":/images/8.png"),trUtf8("超市"));
    ui->comboBox_2->insertItem(15,QIcon(":/images/6.png"),trUtf8("加工厂入"));
    ui->comboBox_2->insertItem(16,QIcon(":/images/5.png"),trUtf8("冷链"));
    ui->comboBox_2->insertItem(17,QIcon(":/images/6.png"),trUtf8("仓储"));
    ui->comboBox_2->insertItem(18,QIcon(":/images/5.png"),trUtf8("客厅"));
    ui->comboBox_2->insertItem(19,QIcon(":/images/6.png"),trUtf8("阳台"));
    ui->comboBox_2->insertItem(20,QIcon(":/images/5.png"),trUtf8("鱼塘"));
    ui->comboBox_2->insertItem(21,QIcon(":/images/6.png"),trUtf8("养殖场"));
    ui->comboBox_2->insertItem(22,QIcon(":/images/7.png"),trUtf8("储物室"));
    ui->comboBox_2->insertItem(23,QIcon(":/images/8.png"),trUtf8("卫生间"));
    ui->comboBox_2->insertItem(24,QIcon(":/images/8.png"),trUtf8("五型柜"));
    ui->comboBox_2->insertItem(25,QIcon(":/images/8.png"),trUtf8("加工厂出"));

    ui->comboBox_2->setCurrentIndex(0);

//    ui->comboBox_3->insertItem(0,QIcon(":/images/9.png"),trUtf8("开"));
//    ui->comboBox_3->insertItem(1,QIcon(":/images/2.png"),trUtf8("关"));
//    ui->comboBox_3->insertItem(2,QIcon(":/images/3.png"),trUtf8("音量+"));
//    ui->comboBox_3->insertItem(3,QIcon(":/images/4.png"),trUtf8("音量-"));
//    ui->comboBox_3->insertItem(4,QIcon(":/images/5.png"),trUtf8("预设温度"));
//    ui->comboBox_3->insertItem(5,QIcon(":/images/6.png"),trUtf8("风速"));
//    ui->comboBox_3->insertItem(6,QIcon(":/images/7.png"),trUtf8("风向"));
//    ui->comboBox_3->insertItem(7,QIcon(":/images/3.png"),trUtf8("AV模式"));
//    ui->comboBox_3->insertItem(8,QIcon(":/images/4.png"),trUtf8("频道-"));
//    ui->comboBox_3->insertItem(9,QIcon(":/images/5.png"),trUtf8("频道+"));
//    ui->comboBox_3->insertItem(10,QIcon(":/images/10.png"),trUtf8("进/出仓"));
//    ui->comboBox_3->insertItem(11,QIcon(":/images/1.png"),trUtf8("播放/暂停"));
//    ui->comboBox_3->insertItem(12,QIcon(":/images/3.png"),trUtf8("快进"));
//    ui->comboBox_3->insertItem(13,QIcon(":/images/4.png"),trUtf8("快退"));
//    ui->comboBox_3->setCurrentIndex(0);
   // readirtable();
}

IRDev::~IRDev()
{
    delete ui;
}

void IRDev::on_pushButton_5_clicked()//fanhui
{
    m_control->whichdialog=1;
    this->parent->show();
    this->close();
}

void IRDev::on_pushButton_clicked()//chufa
{
    ircf[6]='P';
    m_control->m_Com->write(ircf,10);



    ui->label_5->setText(trUtf8("红外触发发送类"));
}




void IRDev::on_pushButton_2_clicked()//add
{
    ui->label_5->setText(trUtf8(""));
    if ((tablerow1==-1)||ui->comboBox->currentIndex() == -1|| ui->comboBox_2->currentIndex() == -1|| ui->comboBox_3->currentIndex() == -1)
    {
        ui->label_5->setText(trUtf8("没有输入内容。。"));
        return;
    }
    QSqlQuery m_query(m_control->m_sql);

    QTableWidgetItem *item = ui->tableWidget->item(tablerow1, 1);
    m_query.prepare("insert into IRHWTable(name,shortaddr,longaddr,direction,code,cfunction) values(:name,:shortaddr,:longaddr,:direction,:code,:cfunction)");

    m_query.bindValue(":name", ui->comboBox->currentText());
    m_query.bindValue(":shortaddr", item->text());
    item = ui->tableWidget->item(tablerow1, 2);
    m_query.bindValue(":longaddr", item->text());
    m_query.bindValue(":direction", ui->comboBox_2->currentText());
    m_query.bindValue(":code", QString::number(ui->spinBox->value()));
    m_query.bindValue(":cfunction", (ui->comboBox_3->currentText()));

    bool ok=m_query.exec();
    if(ok==false)
    {
        ui->label_5->setText(trUtf8("添加表3错误。。"));
        return;
    }
    //readirtable();
    m_control->ReadDatabase();
    ui->label_5->setText(trUtf8("添加OK"));
}

//void IRDev::on_pushButton_3_clicked()//ceshi
//{
//    QTableWidgetItem *item = ui->tableWidget->item(tablerow1, 1);
//    QString str=item->text();
//    bool ok=1;
//    m_qchar=str.toInt(&ok,16);
//    iraddr[0]=(m_qchar.unicode())/256;
//    iraddr[1]=(m_qchar.unicode())%256;
//    sendhw[2]=iraddr[0];
//    sendhw[3]=iraddr[1];
//    sendhw[6]='P';
//    sendhw[7]=iraddr[0];
//    sendhw[8]=iraddr[1];
//    sendhw[9]=0x81;
//    item = ui->tableWidget->item(tablerow1, 3);
//    str=item->text();
//  //  QString str=QString::number(ui->spinBox->value());
//    char c=str.toInt(&ok,16);
//    sendhw[10]=c;
//    m_control->m_Com->write(sendhw,12);
//}

void IRDev::on_pushButton_4_clicked()//查看 按钮在
{
    m_control->whichdialog=16;
    this->hide();
    this->m_viewirdevice = new ViewIRDevice();
    this->m_viewirdevice->show();
    this->m_viewirdevice->parent = this;

}

QString IRDev::IRCutString(int itype,QString str)
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


void IRDev::on_pushButton_6_clicked()//学习
{
    QString str1="";
    if(tablerow1<0)
    {
        ui->label_5->setText(trUtf8("未选择"));
       return;
    }
    QTableWidgetItem *item = ui->tableWidget->item(tablerow1, 1);
    QString str2=item->text();
    bool ok=1;
    m_qchar=str2.toInt(&ok,16);
    iraddr[0]=(m_qchar.unicode())/256;
    iraddr[1]=(m_qchar.unicode())%256;
    sendhw[2]=iraddr[0];
    sendhw[3]=iraddr[1];
    sendhw[6]='P';
    sendhw[7]=iraddr[0];
    sendhw[8]=iraddr[1];
    sendhw[9]=0x80;
    QString str=QString::number(ui->spinBox->value());
    char c=str.toInt(&ok,16);
    sendhw[10]=c;
    item = ui->tableWidget->item(tablerow1, 2);
    str2=item->text();
    str1=IRCutString(1,str2);
    m_qchar=str1.toInt(&ok,16);
    iraddr[0]=(m_qchar.unicode())/256;
    iraddr[1]=(m_qchar.unicode())%256;
    sendhw[13]=iraddr[0];
    sendhw[14]=iraddr[1];
    str1=IRCutString(2,str2);
    m_qchar=str1.toInt(&ok,16);
    iraddr[0]=(m_qchar.unicode())/256;
    iraddr[1]=(m_qchar.unicode())%256;
    sendhw[15]=iraddr[0];
    sendhw[16]=iraddr[1];
    str1=IRCutString(3,str2);
    m_qchar=str1.toInt(&ok,16);
    iraddr[0]=(m_qchar.unicode())/256;
    iraddr[1]=(m_qchar.unicode())%256;
    sendhw[17]=iraddr[0];
    sendhw[18]=iraddr[1];
    str1=IRCutString(4,str2);
    m_qchar=str1.toInt(&ok,16);
    iraddr[0]=(m_qchar.unicode())/256;
    iraddr[1]=(m_qchar.unicode())%256;
    sendhw[19]=iraddr[0];
    sendhw[20]=iraddr[1];
//    QString s1="";QString s2="";
//    for(int i=0;i<21;i++)
//    {
//        s1.sprintf("%02x",sendhw[i]);
//        s2+=s1;
//    }
//    qDebug()<<s2;
    m_control->m_Com->write(sendhw,21);
}

void IRDev::on_tableWidget_cellClicked(int row, int column)
{
    tablerow1=row;
}


void IRDev::on_comboBox_currentIndexChanged(int index)
{
//    for(int i=0;i<ui->comboBox_3->count();i++)
//    {
//        ui->comboBox_3->removeItem(i);
//    }
    ui->comboBox_3->clear();
    if(QString::compare(ui->comboBox->currentText(),trUtf8("空调"))==0)
    {
        ui->comboBox_3->insertItem(0,QIcon(":/images/9.png"),trUtf8("开"));
        ui->comboBox_3->insertItem(1,QIcon(":/images/2.png"),trUtf8("关"));
        ui->comboBox_3->insertItem(2,QIcon(":/images/5.png"),trUtf8("预设温度"));
        ui->comboBox_3->insertItem(3,QIcon(":/images/6.png"),trUtf8("风速"));
        ui->comboBox_3->insertItem(4,QIcon(":/images/7.png"),trUtf8("风向"));
        ui->comboBox_3->setCurrentIndex(0);
    }
    if(QString::compare(ui->comboBox->currentText(),trUtf8("空调扇"))==0)
    {
        ui->comboBox_3->insertItem(0,QIcon(":/images/9.png"),trUtf8("开"));
        ui->comboBox_3->insertItem(1,QIcon(":/images/2.png"),trUtf8("关"));
        ui->comboBox_3->insertItem(2,QIcon(":/images/6.png"),trUtf8("风速"));
        ui->comboBox_3->insertItem(3,QIcon(":/images/7.png"),trUtf8("风向"));
        ui->comboBox_3->setCurrentIndex(0);
    }
    if(ui->comboBox->currentText().contains(trUtf8("音箱"))==true)
    {
        ui->comboBox_3->insertItem(0,QIcon(":/images/9.png"),trUtf8("开"));
        ui->comboBox_3->insertItem(1,QIcon(":/images/2.png"),trUtf8("关"));
        ui->comboBox_3->insertItem(2,QIcon(":/images/6.png"),trUtf8("音量+"));
        ui->comboBox_3->insertItem(3,QIcon(":/images/7.png"),trUtf8("音量-"));
        ui->comboBox_3->setCurrentIndex(0);
    }
    if(ui->comboBox->currentText().contains(trUtf8("投影机"))==true)
    {
        ui->comboBox_3->insertItem(0,QIcon(":/images/9.png"),trUtf8("开"));
        ui->comboBox_3->insertItem(1,QIcon(":/images/2.png"),trUtf8("关"));
        ui->comboBox_3->setCurrentIndex(0);
    }
    if(ui->comboBox->currentText().contains(trUtf8("电视机"))==true)
    {
        ui->comboBox_3->insertItem(0,QIcon(":/images/9.png"),trUtf8("开"));
        ui->comboBox_3->insertItem(1,QIcon(":/images/2.png"),trUtf8("关"));
        ui->comboBox_3->insertItem(2,QIcon(":/images/6.png"),trUtf8("音量+"));
        ui->comboBox_3->insertItem(3,QIcon(":/images/7.png"),trUtf8("音量-"));
        ui->comboBox_3->insertItem(4,QIcon(":/images/3.png"),trUtf8("AV模式"));
        ui->comboBox_3->insertItem(5,QIcon(":/images/4.png"),trUtf8("频道-"));
        ui->comboBox_3->insertItem(6,QIcon(":/images/5.png"),trUtf8("频道+"));
        ui->comboBox_3->setCurrentIndex(0);
    }
    if(ui->comboBox->currentText().contains(trUtf8("DVD"))==true)
    {
        ui->comboBox_3->insertItem(0,QIcon(":/images/9.png"),trUtf8("开/关"));
        ui->comboBox_3->insertItem(1,QIcon(":/images/6.png"),trUtf8("音量+"));
        ui->comboBox_3->insertItem(2,QIcon(":/images/7.png"),trUtf8("音量-"));
        ui->comboBox_3->insertItem(3,QIcon(":/images/10.png"),trUtf8("进/出仓"));
        ui->comboBox_3->insertItem(4,QIcon(":/images/1.png"),trUtf8("播放/暂停"));
        ui->comboBox_3->insertItem(5,QIcon(":/images/3.png"),trUtf8("快进"));
        ui->comboBox_3->insertItem(6,QIcon(":/images/4.png"),trUtf8("快退"));
        ui->comboBox_3->setCurrentIndex(0);
    }
}
