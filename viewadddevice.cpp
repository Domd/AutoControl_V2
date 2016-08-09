#include "viewadddevice.h"
#include "ui_viewadddevice.h"
#include "autocontrol_v2.h"



ViewAddDevice::ViewAddDevice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewAddDevice)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    m_control->whichdialog=15;
    m_table=ui->tableWidget;
    tablerow1=-1;

    QStringList header;
    header.append(trUtf8("节点名称"));
    header.append(trUtf8("节点短地址"));
    header.append(trUtf8("节点长地址"));
    header.append(trUtf8("节点位置"));

    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setColumnWidth(0, 148);
    ui->tableWidget->setColumnWidth(1, 130);
    ui->tableWidget->setColumnWidth(2, 308);
    ui->tableWidget->setColumnWidth(3, 148);
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(false);

    ReadSensortable();
}

ViewAddDevice::~ViewAddDevice()
{
    delete ui;
}

void ViewAddDevice::ReadSensortable()
{
    QString str="";
    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
       ui->tableWidget->removeRow(i);
    }
    QSqlQuery m_query(m_control->m_sql);
    m_query.prepare("SELECT * FROM SensorTable");
    if (m_query.exec())
    {
        int Row = 0;
        str="";
        while (m_query.next())
        {
            ui->tableWidget->setRowCount(Row + 1);
            switch(m_query.value(1).toString().length())
            {
               case 1:
               {
                   str="000"+m_query.value(2).toString();
                   break;
               }
               case 2:
               {
                   str="00"+m_query.value(2).toString();
                   break;
               }
               case 3:
               {
                   str="0"+m_query.value(2).toString();
                    break;
               }
               case 4:
               {
                   str=m_query.value(2).toString();
                    break;
               }
            }
            ui->tableWidget->setItem(Row, 0,new QTableWidgetItem(m_query.value(1).toString()));
            ui->tableWidget->setItem(Row, 1,new QTableWidgetItem(str));
            ui->tableWidget->setItem(Row, 2,new QTableWidgetItem(m_query.value(3).toString()));
            ui->tableWidget->setItem(Row, 3,new QTableWidgetItem(m_query.value(4).toString()));
            ui->tableWidget->setRowHeight(Row,50);
            Row++;
        }
    }
}


void ViewAddDevice::on_tableWidget_cellClicked(int row, int column)
{
    tablerow1=row;
}

void ViewAddDevice::on_pushButton_clicked()//“删除”按键
{
    ui->label_2->setText(trUtf8(""));
    if(tablerow1<0)
    {
       ui->label_2->setText(trUtf8("您未选择"));
       return;
    }

    DeleteRowNum();

    QSqlQuery m_query(m_control->m_sql);
    m_query.prepare("delete FROM SensorTable where longaddr=?");
    m_query.bindValue(0,ui->tableWidget->item(ui->tableWidget->currentRow(),2)->text());

    bool ok=m_query.exec();
    if(ok==false)
    {
        ui->label_2->setText(trUtf8("删除错误"));
        return;
    }
    int i=ui->tableWidget->rowCount();
    if(i==1)
    {
       ui->tableWidget->removeRow(0);
    }
    ReadSensortable();
    m_control->addChange=true;//基础测试界面 数据表 改变
    m_control->ReadDatabase();



    tablerow1=-1;
    ui->label_2->setText(trUtf8("删除OK"));
}
void ViewAddDevice::DeleteRowNum()
{
    if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("三轴加速度"))
    {
        m_control->rownum[0]=0;
        m_control->JDFlag[0]=false;
    }
    else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("颜色"))
    {
        m_control->rownum[1]=0;
        m_control->JDFlag[1]=false;
    }
     else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("温湿度") && ui->tableWidget->item(tablerow1,0)->text()==trUtf8("智能家居"))
    {
        m_control->rownum[2]=0;
        m_control->JDFlag[2]=false;
    }
     else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("火焰") && ui->tableWidget->item(tablerow1,0)->text()==trUtf8("智能家居"))
    {
         m_control->rownum[3]=0;
         m_control->JDFlag[3]=false;
    }
    else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("空气质量"))
    {
        m_control->rownum[4]=0;
        m_control->JDFlag[4]=false;
    }
            else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("气压"))
            {
                m_control->rownum[5]=0;
                m_control->JDFlag[5]=false;
            }
           else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("结露"))
           {
                m_control->rownum[6]=0;
                m_control->JDFlag[6]=false;
            }
           else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("按键"))
           {
               m_control->rownum[7]=0;
               m_control->JDFlag[7]=false;
           }
           else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("光敏"))
           {
               m_control->rownum[8]=0;
               m_control->JDFlag[8]=false;
           }
           else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("演示板")&& ui->tableWidget->item(tablerow1,0)->text()==trUtf8("智能家居"))
           {
               m_control->rownum[9]=0;
               m_control->JDFlag[9]=false;
           }
           else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("光线"))
           {
               m_control->rownum[10]=0;
               m_control->JDFlag[10]=false;
           }
           else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("温湿度")&& ui->tableWidget->item(tablerow1,0)->text()==trUtf8("智慧农业"))
           {
               m_control->rownum[11]=0;
               m_control->JDFlag[11]=false;
           }
           else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("土壤温湿度"))
           {
               m_control->rownum[12]=0;
               m_control->JDFlag[12]=false;
           }
           else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("二氧化碳"))
           {
               m_control->rownum[13]=0;
               m_control->JDFlag[13]=false;
           }
           else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("火焰")&& ui->tableWidget->item(tablerow1,0)->text()==trUtf8("智慧农业"))
           {
               m_control->rownum[14]=0;
               m_control->JDFlag[14]=false;
           }
           else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("演示板")&& ui->tableWidget->item(tablerow1,0)->text()==trUtf8("智慧农业"))
           {
               m_control->rownum[15]=m_control->idnum;
               m_control->JDFlag[15]=false;
           }
           else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("货架"))
           {
               m_control->rownum[16]=m_control->idnum;
               m_control->JDFlag[16]=false;
           }
           else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("高频"))
           {
               m_control->rownum[17]=0;
               m_control->JDFlag[17]=false;
           }
//           else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("震动"))
//           {
//               m_control->rownum[14]=0;
//               m_control->JDFlag[14]=false;
//           }
//           else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("雨篷"))
//           {
//               m_control->rownum[15]=0;
//               m_control->JDFlag[15]=false;
//           }
//           else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("小车"))
//           {
//               m_control->rownum[16]=0;
//               m_control->JDFlag[16]=false;
//           }
//           else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("超高频"))
//           {
//               m_control->rownum[17]=0;
//               m_control->JDFlag[17]=false;
//           }
//           else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("高频"))
//           {
//               m_control->rownum[18]=0;
//               m_control->JDFlag[18]=false;
//           }
//           else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("演示板"))
//           {
//               m_control->rownum[19]=0;
//               m_control->JDFlag[19]=false;
//               m_control->yanshibanID=0;
//           }
//           else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("噪声"))
//           {
//               m_control->rownum[20]=0;
//               m_control->JDFlag[20]=false;
//           }
//           else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("货架"))
//           {
//               m_control->rownum[22]=0;
//               m_control->JDFlag[22]=false;
//           }
//           else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("门锁"))
//           {
//               m_control->rownum[23]=0;
//               m_control->JDFlag[23]=false;
//           }
//           else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("指纹"))
//           {
//               m_control->rownum[24]=0;
//               m_control->JDFlag[24]=false;
//           }
//           else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("氧气"))
//           {
//               m_control->rownum[25]=0;
//               m_control->JDFlag[25]=false;
//           }
//           else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("水位"))
//           {
//               m_control->rownum[26]=0;
//               m_control->JDFlag[26]=false;
//           }
//           else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("二氧化碳"))
//           {
//               m_control->rownum[27]=0;
//               m_control->JDFlag[27]=false;
//               m_control->changeAgriDB=true;

//           }
//           else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("PH"))
//           {
//               m_control->rownum[28]=0;
//               m_control->JDFlag[28]=false;
//           }
//            else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("光敏"))
//            {
//                m_control->rownum[30]=0;
//                m_control->JDFlag[30]=false;
//            }
//            else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("结露"))
//            {
//                m_control->rownum[31]=0;
//                m_control->JDFlag[31]=false;
//            }
//            else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("三轴加速度"))
//            {
//                m_control->rownum[32]=0;
//                m_control->JDFlag[32]=false;
//            }
//            else if(ui->tableWidget->item(tablerow1,0)->text()==trUtf8("颜色"))
//            {
//                m_control->rownum[33]=0;
//                m_control->JDFlag[33]=false;
//            }
}
void ViewAddDevice::on_pushButton_2_clicked()//“返回”按键
{
    m_control->whichdialog=1;
    this->parent->show();
    this->close();
}
