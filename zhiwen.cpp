#include "zhiwen.h"
#include "ui_zhiwen.h"
#include "autocontrol_v2.h"


char zhiwensend[21]={0xFD,0x0F,0x0A,0xFF,0x00,0x00,0x23,0x0A,0xFF,0xDD,0x01,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00};
char zhiwenaddr[2]={0x00,0x00};
QChar zw_qchar;
ZhiWen::ZhiWen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZhiWen)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    m_control->whichdialog=18;
    tablerow1=-1;
    tablerow2=-1;
    m_table=ui->tableWidget;
    m_label=ui->label_4;
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
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(false);

    ui->comboBox->insertItem(0,QIcon(":/images/10.png"),trUtf8("上"));
    ui->comboBox->insertItem(1,QIcon(":/images/2.png"),trUtf8("下"));
    ui->comboBox->insertItem(2,QIcon(":/images/3.png"),trUtf8("左"));
    ui->comboBox->insertItem(3,QIcon(":/images/4.png"),trUtf8("右"));
    ui->comboBox->insertItem(4,QIcon(":/images/5.png"),trUtf8("正中"));
    ui->comboBox->insertItem(5,QIcon(":/images/6.png"),trUtf8("正右"));
    ui->comboBox->insertItem(6,QIcon(":/images/7.png"),trUtf8("正左"));
    ui->comboBox->insertItem(7,QIcon(":/images/1.png"),trUtf8("卧室"));
    ui->comboBox->insertItem(8,QIcon(":/images/2.png"),trUtf8("厨房"));
    ui->comboBox->insertItem(9,QIcon(":/images/3.png"),trUtf8("餐厅"));
    ui->comboBox->insertItem(10,QIcon(":/images/4.png"),trUtf8("书房"));
    ui->comboBox->insertItem(11,QIcon(":/images/5.png"),trUtf8("客厅"));
    ui->comboBox->insertItem(12,QIcon(":/images/6.png"),trUtf8("阳台"));
    ui->comboBox->insertItem(13,QIcon(":/images/5.png"),trUtf8("大棚"));
    ui->comboBox->insertItem(14,QIcon(":/images/8.png"),trUtf8("超市"));
    ui->comboBox->insertItem(15,QIcon(":/images/6.png"),trUtf8("加工厂入"));
    ui->comboBox->insertItem(16,QIcon(":/images/5.png"),trUtf8("冷链"));
    ui->comboBox->insertItem(17,QIcon(":/images/6.png"),trUtf8("仓储"));
    ui->comboBox->insertItem(18,QIcon(":/images/5.png"),trUtf8("客厅"));
    ui->comboBox->insertItem(19,QIcon(":/images/6.png"),trUtf8("阳台"));
    ui->comboBox->insertItem(20,QIcon(":/images/5.png"),trUtf8("鱼塘"));
    ui->comboBox->insertItem(21,QIcon(":/images/6.png"),trUtf8("养殖场"));
    ui->comboBox->insertItem(22,QIcon(":/images/7.png"),trUtf8("储物室"));
    ui->comboBox->insertItem(23,QIcon(":/images/8.png"),trUtf8("卫生间"));
    ui->comboBox->insertItem(24,QIcon(":/images/8.png"),trUtf8("五型柜"));
    ui->comboBox->insertItem(25,QIcon(":/images/8.png"),trUtf8("加工厂出"));
    ui->comboBox->setCurrentIndex(0);

    header.clear();
    header.append(trUtf8("节点名称"));
    header.append(trUtf8("短地址"));
    header.append(trUtf8("MAC地址"));
    header.append(trUtf8("位置"));
    header.append(trUtf8("指纹码"));
    ui->tableWidget_2->setColumnCount(5);
    ui->tableWidget_2->setColumnWidth(0, 128);
    ui->tableWidget_2->setColumnWidth(1, 126);
    ui->tableWidget_2->setColumnWidth(2, 300);
    ui->tableWidget_2->setColumnWidth(3, 106);
    ui->tableWidget_2->setColumnWidth(4, 100);
    ui->tableWidget_2->setHorizontalHeaderLabels(header);
    ui->tableWidget_2->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_2->verticalHeader()->setVisible(false);
    ui->tableWidget_2->horizontalHeader()->setVisible(false);
    ReadSensortable();

}

ZhiWen::~ZhiWen()
{
    delete ui;
}

void ZhiWen::on_pushButton_clicked()//
{
    m_control->whichdialog=1;
    this->parent->show();
    this->close();
}

void ZhiWen::ReadSensortable()
{
    QString str="";
    for(int i=0;i<ui->tableWidget_2->rowCount();i++)
    {
       ui->tableWidget_2->removeRow(i);
    }
    QSqlQuery m_query(m_control->m_sql);
    m_query.prepare("SELECT * FROM ZhiWenTable");
    if (m_query.exec())
    {
        int Row = 0;
        str="";
        while (m_query.next())
        {
            ui->tableWidget_2->setRowCount(Row + 1);
            switch(m_query.value(1).toString().length())
            {
               case 1:
               {
                   str="000"+m_query.value(1).toString();
                   break;
               }
               case 2:
               {
                   str="00"+m_query.value(1).toString();
                   break;
               }
               case 3:
               {
                   str="0"+m_query.value(1).toString();
                    break;
               }
               case 4:
               {
                   str=m_query.value(1).toString();
                    break;
               }
            }
            ui->tableWidget_2->setItem(Row, 0,new QTableWidgetItem(m_query.value(0).toString()));
            ui->tableWidget_2->setItem(Row, 1,new QTableWidgetItem(str));
            ui->tableWidget_2->setItem(Row, 2,new QTableWidgetItem(m_query.value(2).toString()));
            ui->tableWidget_2->setItem(Row, 3,new QTableWidgetItem(m_query.value(3).toString()));
            ui->tableWidget_2->setItem(Row, 4,new QTableWidgetItem(m_query.value(4).toString()));
            ui->tableWidget_2->setRowHeight(Row,50);
            Row++;
        }
    }
}

void ZhiWen::on_pushButton_3_clicked()//add
{
    ui->label_4->setText("");
    if ((tablerow1==-1)||ui->comboBox->currentIndex() == -1)
    {
        ui->label_4->setText(trUtf8("没有输入内容。。"));
        return;
    }
    QSqlQuery m_query(m_control->m_sql);
    QTableWidgetItem *item = ui->tableWidget->item(tablerow1, 1);
    m_query.prepare("insert into ZhiWenTable(name,shortaddr,longaddr,dir,code) values(:name,:shortaddr,:longaddr,:dir,:code)");


    m_query.bindValue(":name", trUtf8("指纹"));

    m_query.bindValue(":shortaddr", item->text());
    QTableWidgetItem *item1 = ui->tableWidget->item(tablerow1, 2);
    m_query.bindValue(":longaddr", item1->text());
    m_query.bindValue(":direction", ui->comboBox->currentText());
    m_query.bindValue(":code", QString::number(ui->spinBox->value()));
    bool ok=m_query.exec();
    if(ok==false)
    {
        ui->label_4->setText(trUtf8("添加表错误。。"));
        return;
    }
    ReadSensortable();


    m_control->ReadDatabase();
    ui->label_4->setText(trUtf8("添加OK"));
}



void ZhiWen::on_pushButton_2_clicked()//shanchu
{
    ui->label_4->setText(trUtf8(""));
    if(tablerow2<0)
    {
       ui->label_4->setText(trUtf8("您未选择"));
       return;
    }
    QSqlQuery m_query(m_control->m_sql);
    m_query.prepare("delete FROM ZhiWenTable where code=?");
    m_query.bindValue(0,ui->tableWidget_2->item(ui->tableWidget_2->currentRow(),4)->text());

    bool ok=m_query.exec();
    if(ok==false)
    {
        ui->label_4->setText(trUtf8("删除错误"));
        return;
    }
    int i=ui->tableWidget_2->rowCount();
    if(i==1)
    {
       ui->tableWidget_2->removeRow(0);
    }
    ReadSensortable();

    m_control->ReadDatabase();
    tablerow2=-1;
    ui->label_2->setText(trUtf8("删除OK"));
}

QString ZhiWen::ZhiWenCutString(int itype,QString str)
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


void ZhiWen::on_pushButton_4_clicked()//luru
{
     ui->label_4->setText(trUtf8(""));
    QString str1="";
    if(tablerow1<0)
    {
        ui->label_4->setText(trUtf8("未选择"));
       return;
    }
    QTableWidgetItem *item = ui->tableWidget->item(tablerow1, 1);
    QString str2=item->text();
    bool ok=1;
    zw_qchar=str2.toInt(&ok,16);
    zhiwenaddr[0]=(zw_qchar.unicode())/256;
    zhiwenaddr[1]=(zw_qchar.unicode())%256;
    zhiwensend[2]=zhiwenaddr[0];
    zhiwensend[3]=zhiwenaddr[1];
    zhiwensend[6]=0x23;
    zhiwensend[7]=zhiwenaddr[0];
    zhiwensend[8]=zhiwenaddr[1];
    zhiwensend[9]=0xAA;
    zhiwensend[10]=0x00;
    QString str=QString::number(ui->spinBox->value());
    char c=str.toInt(&ok,16);
    zhiwensend[11]=c;
    item = ui->tableWidget->item(tablerow1, 2);
    str2=item->text();
    str1=ZhiWenCutString(1,str2);
    zw_qchar=str1.toInt(&ok,16);
    zhiwenaddr[0]=(zw_qchar.unicode())/256;
    zhiwenaddr[1]=(zw_qchar.unicode())%256;
    zhiwensend[13]=zhiwenaddr[0];
    zhiwensend[14]=zhiwenaddr[1];
    str1=ZhiWenCutString(2,str2);
    zw_qchar=str1.toInt(&ok,16);
    zhiwenaddr[0]=(zw_qchar.unicode())/256;
    zhiwenaddr[1]=(zw_qchar.unicode())%256;
    zhiwensend[15]=zhiwenaddr[0];
    zhiwensend[16]=zhiwenaddr[1];
    str1=ZhiWenCutString(3,str2);
    zw_qchar=str1.toInt(&ok,16);
    zhiwenaddr[0]=(zw_qchar.unicode())/256;
    zhiwenaddr[1]=(zw_qchar.unicode())%256;
    zhiwensend[17]=zhiwenaddr[0];
    zhiwensend[18]=zhiwenaddr[1];
    str1=ZhiWenCutString(4,str2);
    zw_qchar=str1.toInt(&ok,16);
    zhiwenaddr[0]=(zw_qchar.unicode())/256;
    zhiwenaddr[1]=(zw_qchar.unicode())%256;
    zhiwensend[19]=zhiwenaddr[0];
    zhiwensend[20]=zhiwenaddr[1];
    m_control->m_Com->write(zhiwensend,21);
}

void ZhiWen::on_pushButton_5_clicked()//suo
{
//    ui->label_4->setText(trUtf8(""));
//    QString str1="";
//    if(tablerow2<0)
//    {
//        ui->label_4->setText(trUtf8("未选择"));
//       //  qDebug("22");
//       return;
//    }
//    QTableWidgetItem *item = ui->tableWidget_2->item(tablerow2, 1);
//    QString str2=item->text();
//    bool ok=1;
//    zw_qchar=str2.toInt(&ok,16);
//    zhiwenaddr[0]=(zw_qchar.unicode())/256;
//    zhiwenaddr[1]=(zw_qchar.unicode())%256;
//    zhiwensend[2]=zhiwenaddr[0];
//    zhiwensend[3]=zhiwenaddr[1];
//    zhiwensend[6]=0x23;
//    zhiwensend[7]=zhiwenaddr[0];
//    zhiwensend[8]=zhiwenaddr[1];
//    zhiwensend[9]=0xBB;
//    zhiwensend[10]=0x00;
//    zhiwensend[11]=0x00;
//    item = ui->tableWidget_2->item(tablerow2, 2);
//    str2=item->text();
//    str1=ZhiWenCutString(1,str2);
//    zw_qchar=str1.toInt(&ok,16);
//    zhiwenaddr[0]=(zw_qchar.unicode())/256;
//    zhiwenaddr[1]=(zw_qchar.unicode())%256;
//    zhiwensend[13]=zhiwenaddr[0];
//    zhiwensend[14]=zhiwenaddr[1];
//    str1=ZhiWenCutString(2,str2);
//    zw_qchar=str1.toInt(&ok,16);
//    zhiwenaddr[0]=(zw_qchar.unicode())/256;
//    zhiwenaddr[1]=(zw_qchar.unicode())%256;
//    zhiwensend[15]=zhiwenaddr[0];
//    zhiwensend[16]=zhiwenaddr[1];
//    str1=ZhiWenCutString(3,str2);
//    zw_qchar=str1.toInt(&ok,16);
//    zhiwenaddr[0]=(zw_qchar.unicode())/256;
//    zhiwenaddr[1]=(zw_qchar.unicode())%256;
//    zhiwensend[17]=zhiwenaddr[0];
//    zhiwensend[18]=zhiwenaddr[1];
//    str1=ZhiWenCutString(4,str2);
//    zw_qchar=str1.toInt(&ok,16);
//    zhiwenaddr[0]=(zw_qchar.unicode())/256;
//    zhiwenaddr[1]=(zw_qchar.unicode())%256;
//    zhiwensend[19]=zhiwenaddr[0];
//    zhiwensend[20]=zhiwenaddr[1];
//    QString s33="";
//    for(int i=0;i<21;i++)
//    {
//        s33.sprintf("%02x",zhiwensend[i]);
//        qDebug()<<s33;
//    }
//    m_control->m_Com->write(zhiwensend,21);

    ui->label_4->setText(trUtf8(""));
    QString str1="";
    if(tablerow2<0)
    {
        ui->label_4->setText(trUtf8("未选择"));
       //  qDebug("22");
       return;
    }
    QTableWidgetItem *item = ui->tableWidget_2->item(tablerow2, 1);
    QString str2=item->text();
    bool ok=1;
    zw_qchar=str2.toInt(&ok,16);
    zhiwenaddr[0]=(zw_qchar.unicode())/256;
    zhiwenaddr[1]=(zw_qchar.unicode())%256;
    zhiwensend[2]=zhiwenaddr[0];
    zhiwensend[3]=zhiwenaddr[1];
    zhiwensend[6]=0x23;
    zhiwensend[7]=zhiwenaddr[0];
    zhiwensend[8]=zhiwenaddr[1];
    zhiwensend[9]=0xCC;
    zhiwensend[10]=0xFF;
    zhiwensend[11]=0xFF;
    item = ui->tableWidget_2->item(tablerow2, 2);
    str2=item->text();
    str1=ZhiWenCutString(1,str2);
    zw_qchar=str1.toInt(&ok,16);
    zhiwenaddr[0]=(zw_qchar.unicode())/256;
    zhiwenaddr[1]=(zw_qchar.unicode())%256;
    zhiwensend[13]=zhiwenaddr[0];
    zhiwensend[14]=zhiwenaddr[1];
    str1=ZhiWenCutString(2,str2);
    zw_qchar=str1.toInt(&ok,16);
    zhiwenaddr[0]=(zw_qchar.unicode())/256;
    zhiwenaddr[1]=(zw_qchar.unicode())%256;
    zhiwensend[15]=zhiwenaddr[0];
    zhiwensend[16]=zhiwenaddr[1];
    str1=ZhiWenCutString(3,str2);
    zw_qchar=str1.toInt(&ok,16);
    zhiwenaddr[0]=(zw_qchar.unicode())/256;
    zhiwenaddr[1]=(zw_qchar.unicode())%256;
    zhiwensend[17]=zhiwenaddr[0];
    zhiwensend[18]=zhiwenaddr[1];
    str1=ZhiWenCutString(4,str2);
    zw_qchar=str1.toInt(&ok,16);
    zhiwenaddr[0]=(zw_qchar.unicode())/256;
    zhiwenaddr[1]=(zw_qchar.unicode())%256;
    zhiwensend[19]=zhiwenaddr[0];
    zhiwensend[20]=zhiwenaddr[1];
    m_control->m_Com->write(zhiwensend,21);
}

void ZhiWen::on_tableWidget_cellClicked(int row, int column)
{
    tablerow1=row;
}

void ZhiWen::on_tableWidget_2_cellClicked(int row, int column)
{
    tablerow2=row;
}
