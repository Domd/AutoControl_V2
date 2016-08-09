#include "adddevice.h"
#include "ui_adddevice.h"
#include "autocontrol_v2.h"
#include "QStringList"
#include "viewadddevice.h"
//#include "intesandtable.h"
#include <QMessageBox>
#include "set.h"

//==========================================================================================================
char sendcf[10]={0xFD,0x04,0xFF,0xFF,0x00,0x00,'K',0xFF,0xFF,0x00};  //添加节点
char sendkg[21]={0xFD,0x0F,0x0A,0xFF,0x00,0x00,'K',0x0A,0xFF,0xDD,0x01,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00};
char demoaddr[2]={0x00,0x00};
QChar m_qchar;


AddDevice::AddDevice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddDevice)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);//无标题栏界面
    m_control->whichdialog=1;   //？
    tablerow1=-1;
    tablerow2=-1;
    label1=ui->label_4;
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
    //ui->tableWidget->verticalHeader()->setVisible(false);
    //ui->tableWidget->horizontalHeader()->setVisible(false);
//    header.clear();
//    header.append(trUtf8("节点名称"));
//    header.append(trUtf8("节点地址"));
//    header.append(trUtf8("节点位置"));
//    ui->tableWidget_2->setColumnCount(3);
//    ui->tableWidget_2->setColumnWidth(0, 148);
//    ui->tableWidget_2->setColumnWidth(1, 160);
//    ui->tableWidget_2->setColumnWidth(2, 168);
//    ui->tableWidget_2->setHorizontalHeaderLabels(header);
//    ui->tableWidget_2->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->comboBox->insertItem(0,QIcon(":/images/9.png"),trUtf8("未选择"));
    ui->comboBox->insertItem(1,QIcon(":/images/7.png"),trUtf8("设备1"));
    ui->comboBox->insertItem(2,QIcon(":/images/2.png"),trUtf8("设备2"));
    ui->comboBox->insertItem(3,QIcon(":/images/1.png"),trUtf8("窗帘"));
    ui->comboBox->insertItem(4,QIcon(":/images/2.png"),trUtf8("调光"));
    ui->comboBox->insertItem(5,QIcon(":/images/4.png"),trUtf8("浇花"));
    ui->comboBox->insertItem(6,QIcon(":/images/5.png"),trUtf8("光线"));
    ui->comboBox->insertItem(7,QIcon(":/images/9.png"),trUtf8("温湿度"));
    ui->comboBox->insertItem(8,QIcon(":/images/8.png"),trUtf8("雨滴"));
    ui->comboBox->insertItem(9,QIcon(":/images/10.png"),trUtf8("噪声"));
    ui->comboBox->insertItem(10,QIcon(":/images/3.png"),trUtf8("雨蓬"));
    ui->comboBox->insertItem(11,QIcon(":/images/3.png"),trUtf8("小车"));
    ui->comboBox->insertItem(12,QIcon(":/images/1.png"),trUtf8("气压"));
    ui->comboBox->insertItem(13,QIcon(":/images/2.png"),trUtf8("按键"));
    ui->comboBox->insertItem(14,QIcon(":/images/2.png"),trUtf8("高频"));
    ui->comboBox->insertItem(15,QIcon(":/images/5.png"),trUtf8("火焰"));
    ui->comboBox->insertItem(16,QIcon(":/images/10.png"),trUtf8("演示板"));
    ui->comboBox->insertItem(17,QIcon(":/images/7.png"),trUtf8("超高频"));
    ui->comboBox->insertItem(18,QIcon(":/images/8.png"),trUtf8("空气质量"));
    ui->comboBox->insertItem(19,QIcon(":/images/2.png"),trUtf8("智能货架"));
    ui->comboBox->insertItem(20,QIcon(":/images/3.png"),trUtf8("土壤温湿度"));
    ui->comboBox->insertItem(21,QIcon(":/images/1.png"),trUtf8("氧气"));
    ui->comboBox->insertItem(22,QIcon(":/images/7.png"),trUtf8("灯"));
    ui->comboBox->setCurrentIndex(0);//表示显示第0个

//    ui->comboBox_2->insertItem(0,QIcon(":/images/9.png"),trUtf8("无"));
    ui->comboBox_2->insertItem(0,QIcon(":/images/10.png"),trUtf8("基础测试"));
    ui->comboBox_2->insertItem(1,QIcon(":/images/2.png"),trUtf8("智能家居"));
    ui->comboBox_2->insertItem(2,QIcon(":/images/3.png"),trUtf8("智慧农业"));
    ui->comboBox_2->insertItem(3,QIcon(":/images/4.png"),trUtf8("智能货架"));
    ui->comboBox_2->setCurrentIndex(0);

    ui->comboBox_3->insertItem(0,QIcon(":/images/1.png"),trUtf8("未选择"));
    ui->comboBox_3->insertItem(1,QIcon(":/images/2.png"),trUtf8("温湿度"));
    ui->comboBox_3->insertItem(2,QIcon(":/images/3.png"),trUtf8("土壤温湿度"));
    ui->comboBox_3->setCurrentIndex(0);

   // ReadSensortable();

    ui->label->setVisible(false);
    ui->comboBox->setVisible(false);
    ui->comboBox_3->setVisible(false);
}

AddDevice::~AddDevice()
{
    delete ui;
}

void AddDevice::on_pushButton_2_clicked()
{
  //  m_control->whichdialog=-1;
    this->parent->show();
    this->close();

}

void AddDevice::on_radioButton_clicked()//开关按钮按下
{
    if(ui->radioButton->isChecked()==true)
    {
       m_control->iaddtype=1;
       for(int i=ui->tableWidget->rowCount();i>=0;i--)
       {
           ui->tableWidget->removeRow(i);
       }
       ui->pushButton->setVisible(true);
       ui->label->setVisible(true);
       ui->comboBox->setVisible(true);
       ui->comboBox_3->setVisible(false);
    }

}

void AddDevice::on_radioButton_2_clicked()//窗帘类单选按钮按下
{

    if(ui->radioButton_2->isChecked()==true)
    {
        m_control->iaddtype=2;
        for(int i=ui->tableWidget->rowCount();i>=0;i--)
        {
            ui->tableWidget->removeRow(i);
        }
       ui->pushButton->setVisible(true);
       ui->label->setVisible(true);
       ui->comboBox->setVisible(true);
       ui->comboBox_3->setVisible(false);
    }
}

void AddDevice::on_radioButton_3_clicked()//调光类单选按钮按下
{
    if(ui->radioButton_3->isChecked()==true)
    {
       m_control->iaddtype=3;
       for(int i=ui->tableWidget->rowCount();i>=0;i--)
       {
           ui->tableWidget->removeRow(i);
       }
       ui->pushButton->setVisible(true);
       ui->label->setVisible(true);
       ui->comboBox->setVisible(true);
       ui->comboBox_3->setVisible(false);
    }
}

void AddDevice::on_radioButton_4_clicked()//红外类单选按钮按下
{
    if(ui->radioButton_4->isChecked()==true)
    {
       m_control->iaddtype=4;
       m_control->whichdialog=2;
       for(int i=ui->tableWidget->rowCount();i>=0;i--)
       {
           ui->tableWidget->removeRow(i);
       }
       ui->pushButton->setVisible(false);
       this->hide();
       this->m_irdev = new IRDev();
       this->m_irdev->show();
       this->m_irdev->parent = this;
       return;
    }
}

void AddDevice::on_radioButton_5_clicked()//315单选按钮按下
{

    if(ui->radioButton_5->isChecked()==true)
    {
        m_control->iaddtype=5;
        m_control->whichdialog=3;
        for(int i=ui->tableWidget->rowCount();i>=0;i--)
        {
            ui->tableWidget->removeRow(i);
        }
        ui->pushButton->setVisible(false);
       this->hide();
       this->m_threefive = new ThreeFiveDev();
       this->m_threefive->show();
       this->m_threefive->parent = this;
    }
}

void AddDevice::on_radioButton_7_clicked()//雨棚单选按钮按下
{

    if(ui->radioButton_7->isChecked()==true)
    {
       m_control->iaddtype=7;
       for(int i=ui->tableWidget->rowCount();i>=0;i--)
       {
           ui->tableWidget->removeRow(i);
       }
       ui->pushButton->setVisible(true);
       ui->label->setVisible(true);
       ui->comboBox->setVisible(true);
       ui->comboBox_3->setVisible(false);
    }
}

void AddDevice::on_radioButton_6_clicked()//其他单选按钮按下
{
    if(ui->radioButton_6->isChecked()==true)
    {
       m_control->iaddtype=6;
       for(int i=ui->tableWidget->rowCount();i>=0;i--)
       {
           ui->tableWidget->removeRow(i);
       }
       ui->pushButton->setVisible(false);
       ui->label->setVisible(false);
       ui->comboBox->setVisible(false);
       ui->comboBox_3->setVisible(true);
    }
}

void AddDevice::on_pushButton_clicked()//触发按钮按下
{
    if(ui->radioButton->isChecked()==true)
    {
        sendcf[6]='K';
        ui->label_4->setText(trUtf8("开关触发了。。。。"));
    }
    if(ui->radioButton_3->isChecked()==true)
    {
        sendcf[6]='S';
         ui->label_4->setText(trUtf8("调光触发了。。。。"));
    }
    if(ui->radioButton_2->isChecked()==true)
    {
        sendcf[6]='H';
        ui->label_4->setText(trUtf8("窗帘触发了。。。。"));
    }
    if(ui->radioButton_7->isChecked()==true)
    {
        sendcf[6]=0x05;
        ui->label_4->setText(trUtf8("雨蓬触发了。。。。"));
    }
    if(ui->radioButton_8->isChecked()==true)
    {
        sendcf[6]=0x12;
        ui->label_4->setText(trUtf8("门锁触发了。。。。"));
    }
//    if(ui->radioButton_6->isChecked()==true)
//    {
//        sendcf[6]='E';
//        ui->label_4->setText(trUtf8("温湿度触发了。。。。"));
//    }
    m_control->m_Com->write(sendcf,10);//
}

void AddDevice::on_pushButton_3_clicked()//“添加”按键按钮按下
{
    ui->label_4->setText("");
    if ((tablerow1==-1)||ui->comboBox->currentIndex() == -1|| ui->comboBox_2->currentIndex() == -1)
    {
        ui->label_4->setText(trUtf8("没有输入内容。。"));
        return;
    }
    QSqlQuery m_query(m_control->m_sql);
    QTableWidgetItem *item = ui->tableWidget->item(tablerow1, 1);
//    m_query.prepare("insert into SensorTable(name,shortaddr,longaddr,direction) values(:name,:shortaddr,:longaddr,:direction)");//插入新的行
    m_query.prepare("insert into SensorTable(name,shortaddr,longaddr,direction,status) values(:name,:shortaddr,:longaddr,:direction,:status)");//插入新的行

//    if(m_control->iaddtype==6||m_control->iaddtype==8)
      if(m_control->iaddtype==8)
    {
       QTableWidgetItem *item2 = ui->tableWidget->item(tablerow1, 0);
       m_query.bindValue(":name", item2->text());
       qDebug()<<item2->text();
    }
      else if(m_control->iaddtype==6)
      {
          if(ui->comboBox_3->currentText()==trUtf8("未选择"))
          {
              QTableWidgetItem *item2 = ui->tableWidget->item(tablerow1, 0);
              m_query.bindValue(":name", item2->text());
          }
          else
          {
              m_query.bindValue(":name", ui->comboBox_3->currentText());
          }
      }
    else
    {
       m_query.bindValue(":name", ui->comboBox->currentText());
    }

    m_query.bindValue(":shortaddr", item->text());
    qDebug()<<item->text();
    QTableWidgetItem *item1 = ui->tableWidget->item(tablerow1, 2);
    m_query.bindValue(":longaddr", item1->text());
     qDebug()<<item1->text();
    m_query.bindValue(":direction", ui->comboBox_2->currentText());
    qDebug()<<ui->comboBox_2->currentText();

    m_query.bindValue(":status",trUtf8("在线"));

    bool ok=m_query.exec();
    if(ok==false)
    {
        ui->label_4->setText(trUtf8("添加表错误。。"));
        return;
    }

    m_control->ReadDatabase();
    m_control->addChange=true;
    SensorNameJudge();
    ui->label_4->setText(trUtf8("添加OK"));
    ui->comboBox_3->setCurrentIndex(0);
}

void AddDevice::SensorNameJudge()
{
    if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("三轴加速度") && ui->comboBox_2->currentText()==trUtf8("基础测试"))
        {
            m_control->rownum[0]=m_control->idnum;
        }
        else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("颜色") && ui->comboBox_2->currentText()==trUtf8("基础测试"))
        {
            m_control->rownum[1]=m_control->idnum;
        }
        else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("温湿度") && ui->comboBox_2->currentText()==trUtf8("智能家居"))
        {
             m_control->rownum[2]=m_control->idnum;
         }
        else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("火焰")&& ui->comboBox_2->currentText()==trUtf8("智能家居"))
        {
            m_control->rownum[3]=m_control->idnum;
        }
       else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("空气质量")&& ui->comboBox_2->currentText()==trUtf8("智能家居"))
       {
           m_control->rownum[4]=m_control->idnum;
       }
       else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("气压")&& ui->comboBox_2->currentText()==trUtf8("智能家居"))
       {
           m_control->rownum[5]=m_control->idnum;
       }
       else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("结露")&& ui->comboBox_2->currentText()==trUtf8("智能家居"))
       {
           m_control->rownum[6]=m_control->idnum;
       }
       else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("按键")&& ui->comboBox_2->currentText()==trUtf8("智能家居"))
       {
           m_control->rownum[7]=m_control->idnum;
       }
       else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("光敏")&& ui->comboBox_2->currentText()==trUtf8("智能家居"))
       {
           m_control->rownum[8]=m_control->idnum;
       }
       else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("演示板")&& ui->comboBox_2->currentText()==trUtf8("智能家居"))
       {
           m_control->rownum[9]=m_control->idnum;
           m_control->stryanshibanaddr=ui->tableWidget->item(tablerow1, 1)->text();
           m_control->stryanshibanmacaddr=ui->tableWidget->item(tablerow1, 2)->text();
       }
       else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("光线")&& ui->comboBox_2->currentText()==trUtf8("智慧农业"))
       {
           m_control->rownum[10]=m_control->idnum;
       }
        else if(ui->comboBox_3->currentText()==trUtf8("土壤温湿度") && ui->comboBox_2->currentText()==trUtf8("智慧农业"))
        {
            m_control->rownum[12]=m_control->idnum;
//            char buf[10];
//            sprintf(buf,"r12=%d",m_control->rownum[12]);
//            QMessageBox::warning(0,"this",QString(buf));
        }
       else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("温湿度")&& ui->comboBox_2->currentText()==trUtf8("智慧农业"))
       {
           m_control->rownum[11]=m_control->idnum;
//           char buf[10];
//           sprintf(buf,"r11=%d",m_control->rownum[11]);
//           QMessageBox::warning(0,"this",QString(buf));
       }
        else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("二氧化碳")&& ui->comboBox_2->currentText()==trUtf8("智慧农业"))
        {
            m_control->rownum[13]=m_control->idnum;
        }
        else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("火焰")&& ui->comboBox_2->currentText()==trUtf8("智慧农业"))
        {
            m_control->rownum[14]=m_control->idnum;
        }
        else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("演示板")&& ui->comboBox_2->currentText()==trUtf8("智慧农业"))
        {
            m_control->rownum[15]=m_control->idnum;
            m_control->stryanshibanaddr2=ui->tableWidget->item(tablerow1, 1)->text();
            m_control->stryanshibanmacaddr2=ui->tableWidget->item(tablerow1, 2)->text();
        }
       else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("货架")&& ui->comboBox_2->currentText()==trUtf8("智能货架"))
       {
           m_control->rownum[16]=m_control->idnum;
       }
//       else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("高频")&& ui->comboBox_2->currentText()==trUtf8("智能货架"))
//       {
//           m_control->rownum[17]=m_control->idnum;
//       }
        else if(ui->comboBox->currentText()==trUtf8("设备1"))
        {
            m_control->powerID1=m_control->idnum;
        }
        else if(ui->comboBox->currentText()==trUtf8("设备2"))
        {
            m_control->powerID2=m_control->idnum;
        }
      m_control->idnum++;
}

//信号是当表格中的一个cell单元被单击时发出的。它的两个参数分别为表格中cell的行号和列号
void AddDevice::on_tableWidget_cellClicked(int row, int column)
{
    tablerow1=row;
}

void AddDevice::on_tableWidget_2_cellClicked(int row, int column)
{
    tablerow2=row;
}

QString AddDevice::CutLongString(int itype,QString str)
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

void AddDevice::on_pushButton_5_clicked()//“测试”按键按下
{
    if(tablerow1==-1)
    {
        ui->label_4->setText(trUtf8("您未选择节点地址！"));
        return;
    }
    if(ui->radioButton->isChecked()==true)  //开关类的单选按钮按下的状态
    {
           QTableWidgetItem *item = ui->tableWidget->item(tablerow1, 1);
           QString str1="";
           QString str2=item->text();//读取当前选中一条取其文本内容
           bool ok=1;
           m_qchar=str2.toInt(&ok,16);
           demoaddr[0]=(m_qchar.unicode())/256;
           demoaddr[1]=(m_qchar.unicode())%256;//得到Unicode编码
           sendkg[2]=demoaddr[0];
           sendkg[3]=demoaddr[1];
           sendkg[6]='K';
           sendkg[7]=demoaddr[0];
           sendkg[8]=demoaddr[1];
           sendkg[9]=0xDD;
           sendkg[10]=0x01;
           sendkg[11]=0xAA;                 //（从C到E控制节点）
           item = ui->tableWidget->item(tablerow1, 2);
           str2=item->text();
           str1=CutLongString(1,str2);
           m_qchar=str1.toInt(&ok,16);
           demoaddr[0]=(m_qchar.unicode())/256;
           demoaddr[1]=(m_qchar.unicode())%256;
           sendkg[13]=demoaddr[0];
           sendkg[14]=demoaddr[1];
           str1=CutLongString(2,str2);
           m_qchar=str1.toInt(&ok,16);
           demoaddr[0]=(m_qchar.unicode())/256;
           demoaddr[1]=(m_qchar.unicode())%256;
           sendkg[15]=demoaddr[0];
           sendkg[16]=demoaddr[1];
           str1=CutLongString(3,str2);
           m_qchar=str1.toInt(&ok,16);
           demoaddr[0]=(m_qchar.unicode())/256;
           demoaddr[1]=(m_qchar.unicode())%256;
           sendkg[17]=demoaddr[0];
           sendkg[18]=demoaddr[1];
           str1=CutLongString(4,str2);
           m_qchar=str1.toInt(&ok,16);
           demoaddr[0]=(m_qchar.unicode())/256;
           demoaddr[1]=(m_qchar.unicode())%256;
           sendkg[19]=demoaddr[0];
           sendkg[20]=demoaddr[1];

           m_control->m_Com->write(sendkg,21);
           sleep(2);
           sendkg[11]=0xBB;
           m_control->m_Com->write(sendkg,21);
    }
    if(ui->radioButton_3->isChecked()==true)//调光
    {
        QTableWidgetItem *item = ui->tableWidget->item(tablerow1, 1);
           QString str1="";
           QString str2=item->text();
           bool ok=1;
           m_qchar=str2.toInt(&ok,16);
           demoaddr[0]=(m_qchar.unicode())/256;
           demoaddr[1]=(m_qchar.unicode())%256;
           sendkg[2]=demoaddr[0];
           sendkg[3]=demoaddr[1];
           sendkg[6]='S';
           sendkg[7]=demoaddr[0];
           sendkg[8]=demoaddr[1];
           sendkg[9]=0xAB;
           sendkg[10]=0xB2;
           sendkg[11]=0x75;
           item = ui->tableWidget->item(tablerow1, 2);
           str2=item->text();
           str1=CutLongString(1,str2);
           m_qchar=str1.toInt(&ok,16);
           demoaddr[0]=(m_qchar.unicode())/256;
           demoaddr[1]=(m_qchar.unicode())%256;
           sendkg[13]=demoaddr[0];
           sendkg[14]=demoaddr[1];
           str1=CutLongString(2,str2);
           m_qchar=str1.toInt(&ok,16);
           demoaddr[0]=(m_qchar.unicode())/256;
           demoaddr[1]=(m_qchar.unicode())%256;
           sendkg[15]=demoaddr[0];
           sendkg[16]=demoaddr[1];
           str1=CutLongString(3,str2);
           m_qchar=str1.toInt(&ok,16);
           demoaddr[0]=(m_qchar.unicode())/256;
           demoaddr[1]=(m_qchar.unicode())%256;
           sendkg[17]=demoaddr[0];
           sendkg[18]=demoaddr[1];
           str1=CutLongString(4,str2);
           m_qchar=str1.toInt(&ok,16);
           demoaddr[0]=(m_qchar.unicode())/256;
           demoaddr[1]=(m_qchar.unicode())%256;
           sendkg[19]=demoaddr[0];
           sendkg[20]=demoaddr[1];


           m_control->m_Com->write(sendkg,21);
           sleep(2);
           sendkg[11]=0x00;
           m_control->m_Com->write(sendkg,21);
    }

    if(ui->radioButton_2->isChecked()==true)//窗帘
    {
           QString str1="";
           QTableWidgetItem *item = ui->tableWidget->item(tablerow1, 1);
           QString str2=item->text();
           bool ok=1;
           m_qchar=str2.toInt(&ok,16);
           demoaddr[0]=(m_qchar.unicode())/256;
           demoaddr[1]=(m_qchar.unicode())%256;
           sendkg[2]=demoaddr[0];
           sendkg[3]=demoaddr[1];
           sendkg[6]='H';
           sendkg[7]=demoaddr[0];
           sendkg[8]=demoaddr[1];
           sendkg[9]=0xDD;
           sendkg[10]=0xC0;
           sendkg[11]=0xAA;
           item = ui->tableWidget->item(tablerow1, 2);
           str2=item->text();
           str1=CutLongString(1,str2);
           m_qchar=str1.toInt(&ok,16);
           demoaddr[0]=(m_qchar.unicode())/256;
           demoaddr[1]=(m_qchar.unicode())%256;
           sendkg[13]=demoaddr[0];
           sendkg[14]=demoaddr[1];
           str1=CutLongString(2,str2);
           m_qchar=str1.toInt(&ok,16);
           demoaddr[0]=(m_qchar.unicode())/256;
           demoaddr[1]=(m_qchar.unicode())%256;
           sendkg[15]=demoaddr[0];
           sendkg[16]=demoaddr[1];
           str1=CutLongString(3,str2);
           m_qchar=str1.toInt(&ok,16);
           demoaddr[0]=(m_qchar.unicode())/256;
           demoaddr[1]=(m_qchar.unicode())%256;
           sendkg[17]=demoaddr[0];
           sendkg[18]=demoaddr[1];
           str1=CutLongString(4,str2);
           m_qchar=str1.toInt(&ok,16);
           demoaddr[0]=(m_qchar.unicode())/256;
           demoaddr[1]=(m_qchar.unicode())%256;
           sendkg[19]=demoaddr[0];
           sendkg[20]=demoaddr[1];

           m_control->m_Com->write(sendkg,21);
           sleep(2);
           sendkg[11]=0xBB;
           m_control->m_Com->write(sendkg,21);
    }

    if(ui->radioButton_8->isChecked()==true)//门锁类
    {
           QString str1="";
           QTableWidgetItem *item = ui->tableWidget->item(tablerow1, 1);
           QString str2=item->text();
           bool ok=1;
           m_qchar=str2.toInt(&ok,16);
           demoaddr[0]=(m_qchar.unicode())/256;
           demoaddr[1]=(m_qchar.unicode())%256;
           sendkg[2]=demoaddr[0];
           sendkg[3]=demoaddr[1];
           sendkg[6]=0x12;
           sendkg[7]=demoaddr[0];
           sendkg[8]=demoaddr[1];
           sendkg[9]=0xDD;
           sendkg[10]=0xC0;
           sendkg[11]=0xAA;
           item = ui->tableWidget->item(tablerow1, 2);
           str2=item->text();
           str1=CutLongString(1,str2);
           m_qchar=str1.toInt(&ok,16);
           demoaddr[0]=(m_qchar.unicode())/256;
           demoaddr[1]=(m_qchar.unicode())%256;
           sendkg[13]=demoaddr[0];
           sendkg[14]=demoaddr[1];
           str1=CutLongString(2,str2);
           m_qchar=str1.toInt(&ok,16);
           demoaddr[0]=(m_qchar.unicode())/256;
           demoaddr[1]=(m_qchar.unicode())%256;
           sendkg[15]=demoaddr[0];
           sendkg[16]=demoaddr[1];
           str1=CutLongString(3,str2);
           m_qchar=str1.toInt(&ok,16);
           demoaddr[0]=(m_qchar.unicode())/256;
           demoaddr[1]=(m_qchar.unicode())%256;
           sendkg[17]=demoaddr[0];
           sendkg[18]=demoaddr[1];
           str1=CutLongString(4,str2);
           m_qchar=str1.toInt(&ok,16);
           demoaddr[0]=(m_qchar.unicode())/256;
           demoaddr[1]=(m_qchar.unicode())%256;
           sendkg[19]=demoaddr[0];
           sendkg[20]=demoaddr[1];

           m_control->m_Com->write(sendkg,21);
           sleep(2);
           sendkg[11]=0xBB;
           m_control->m_Com->write(sendkg,21);
    }
    tablerow1=-1;
}

void AddDevice::on_pushButton_4_clicked()//查看按钮
{
    m_control->whichdialog=15;
    this->hide();
    this->m_viewadddevice = new ViewAddDevice();
    this->m_viewadddevice->show();
    this->m_viewadddevice->parent = this;
}

void AddDevice::on_radioButton_8_clicked()//门锁类单选按钮
{
    if(ui->radioButton_8->isChecked()==true)
    {
       m_control->iaddtype=8;
       for(int i=ui->tableWidget->rowCount();i>=0;i--)//清空tabelwidget表格
       {
           ui->tableWidget->removeRow(i);
       }
       ui->pushButton->setVisible(true);
       ui->label->setVisible(false);
       ui->comboBox->setVisible(false);
    }
}

void AddDevice::on_radioButton_9_clicked()//指纹类单选按钮
{
    if(ui->radioButton_9->isChecked()==true)
    {
       m_control->iaddtype=9;

       this->hide();
       this->m_zhiwen = new ZhiWen();
       this->m_zhiwen->show();
       this->m_zhiwen->parent = this;
       return;
    }
}
