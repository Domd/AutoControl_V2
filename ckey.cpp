#include "ckey.h"
#include "ui_ckey.h"
#include "autocontrol_v2.h"

CKey::CKey(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CKey)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    m_control->whichdialog=9;
    m_text=ui->textEdit;

    QStringList header;
    header.append(trUtf8("MAC地址"));
    header.append(trUtf8("短地址"));

    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setColumnWidth(0, 236);
    ui->tableWidget->setColumnWidth(1, 136);
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(false);

    header.clear();
    header.append(trUtf8("节点名称"));
    header.append(trUtf8("短地址"));
    header.append(trUtf8("MAC地址"));
    header.append(trUtf8("节点位置"));
    header.append(trUtf8("功能"));
    ui->tableWidget_2->setColumnCount(5);
    ui->tableWidget_2->setColumnWidth(0, 120);
    ui->tableWidget_2->setColumnWidth(1, 128);
    ui->tableWidget_2->setColumnWidth(2, 128);
    ui->tableWidget_2->setColumnWidth(3, 128);
    ui->tableWidget_2->setColumnWidth(4, 128);
    ui->tableWidget_2->setHorizontalHeaderLabels(header);
    ui->tableWidget_2->setSelectionMode(QAbstractItemView::SingleSelection);
 //   ui->tableWidget_2->verticalHeader()->setVisible(false);
    ui->tableWidget_2->horizontalHeader()->setVisible(false);
    SelectGuanXianAddr();

    header.clear();
    header.append(trUtf8("主控名称"));
    header.append(trUtf8("主控短地址"));
    header.append(trUtf8("主控MAC地址"));
    header.append(trUtf8("主控位置"));
    header.append(trUtf8("主控界值"));
    header.append(trUtf8("被控名称"));
    header.append(trUtf8("被控短地址"));
    header.append(trUtf8("被控MAC地址"));
    header.append(trUtf8("被控位置"));
    header.append(trUtf8("功能"));
    header.append(trUtf8("实际功能"));
    ui->tableWidget_3->setColumnCount(11);
    ui->tableWidget_3->setColumnWidth(0, 100);
    ui->tableWidget_3->setColumnWidth(1, 100);
    ui->tableWidget_3->setColumnWidth(2, 268);
    ui->tableWidget_3->setColumnWidth(3, 100);
    ui->tableWidget_3->setColumnWidth(4, 110);
    ui->tableWidget_3->setColumnWidth(5, 100);
    ui->tableWidget_3->setColumnWidth(6, 148);
    ui->tableWidget_3->setColumnWidth(7, 248);
    ui->tableWidget_3->setColumnWidth(8, 118);
    ui->tableWidget_3->setColumnWidth(9, 108);
    ui->tableWidget_3->setColumnWidth(10, 108);
    ui->tableWidget_3->setHorizontalHeaderLabels(header);
    ui->tableWidget_3->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_3->verticalHeader()->setVisible(false);
    ui->tableWidget_3->horizontalHeader()->setVisible(false);

    SelectGuanXianControl();
    readtable();

    ui->comboBox->insertItem(0,QIcon(":/images/1.png"),trUtf8("开"));
    ui->comboBox->insertItem(1,QIcon(":/images/2.png"),trUtf8("关"));
    ui->comboBox->setCurrentIndex(0);
    tablerow1=-1;
    tablerow2=-1;
    tablerow3=-1;
}

CKey::~CKey()
{
    delete ui;
}

void CKey::readtable()//
{
    for(int i=0;i<ui->tableWidget_3->rowCount();i++)
    {
        ui->tableWidget_3->removeRow(i);
    }
    QSqlQuery m_query(m_control->m_sql);
    m_query.prepare("SELECT * FROM KeyTable");
    if (m_query.exec())
    {
        int Row = 0;
        while (m_query.next())
        {
            ui->tableWidget_3->setRowCount(Row + 1);
            ui->tableWidget_3->setItem(Row, 0,new QTableWidgetItem(m_query.value(0).toString()));
            ui->tableWidget_3->setItem(Row, 1,new QTableWidgetItem(m_query.value(1).toString()));
            ui->tableWidget_3->setItem(Row, 2,new QTableWidgetItem(m_query.value(2).toString()));
            ui->tableWidget_3->setItem(Row, 3,new QTableWidgetItem(m_query.value(3).toString()));
            ui->tableWidget_3->setItem(Row, 4,new QTableWidgetItem(m_query.value(4).toString()));
            ui->tableWidget_3->setItem(Row, 5,new QTableWidgetItem(m_query.value(5).toString()));
            ui->tableWidget_3->setItem(Row, 6,new QTableWidgetItem(m_query.value(6).toString()));
            ui->tableWidget_3->setItem(Row, 7,new QTableWidgetItem(m_query.value(7).toString()));
            ui->tableWidget_3->setItem(Row, 8,new QTableWidgetItem(m_query.value(8).toString()));
            ui->tableWidget_3->setItem(Row, 9,new QTableWidgetItem(m_query.value(9).toString()));
            ui->tableWidget_3->setItem(Row, 10,new QTableWidgetItem(m_query.value(10).toString()));
            Row++;
        }
    }
}


void CKey::on_pushButton_clicked()
{
    if (tablerow1<0||ui->textEdit->toPlainText()=="" || tablerow2<0)
     {
        ui->label_3->setText(trUtf8("您未选择"));
         return;
     }
     QSqlQuery m_query(m_control->m_sql);


     m_query.prepare("insert into KeyTable(name,shortaddr,longaddr,dir,keyval,cname,cshortaddr,clongaddr,cdir,cfunction,truefunction) values(:name,:shortaddr,:longaddr,:dir,:keyval,:cname,:caddr,:cdir,:cfunction,:truefunction)");

     m_query.bindValue(":name", trUtf8("按键"));
     QTableWidgetItem *item = ui->tableWidget->item(tablerow1, 1);
     m_query.bindValue(":shortaddr", item->text());
     item = ui->tableWidget->item(tablerow1, 0);
     m_query.bindValue(":longaddr", item->text());
     m_query.bindValue(":dir",m_control->RetDirByMacAddr(item->text()));
     m_query.bindValue(":keyval", ui->textEdit->toPlainText());
     item = ui->tableWidget_2->item(tablerow2, 0);
     m_query.bindValue(":cname", item->text());
     item = ui->tableWidget_2->item(tablerow2, 1);
     m_query.bindValue(":cshortaddr", item->text());
     item = ui->tableWidget_2->item(tablerow2, 2);
     m_query.bindValue(":clongaddr", item->text());
     item = ui->tableWidget_2->item(tablerow2, 3);
     m_query.bindValue(":cdir", item->text());
     item = ui->tableWidget_2->item(tablerow2, 4);
     m_query.bindValue(":cfunction", item->text());
     m_query.bindValue(":truefunction", ui->comboBox->currentText());
     bool ok=m_query.exec();
     if(ok==false)
     {
          ui->label_3->setText(trUtf8("您未选择"));
         return;
     }
     readtable();
}

void CKey::on_pushButton_2_clicked()
{
    if(tablerow3<0)
    {
       return;
    }
    QSqlQuery m_query(m_control->m_sql);
    m_query.prepare("delete FROM KeyTable where keyval=?");
    m_query.bindValue(0,ui->tableWidget_3->item(tablerow3,3)->text());//ui->tableWidget_3->currentRow()

    bool ok=m_query.exec();
    if(ok==false)
    {

        return;
    }
    int i=ui->tableWidget_3->rowCount();
    if(i==1)
    {
       ui->tableWidget_3->removeRow(0);
    }
    readtable();
    tablerow3=-1;
}

void CKey::on_pushButton_3_clicked()//fanhui
{
     m_control->whichdialog=5;
     m_control->ReadControlTable();
    this->parent->show();
    this->close();
}

void CKey::SelectGuanXianAddr()
{
    for(int i=0;i<m_control->isensorlength;i++)
    {
        if(QString::compare(trUtf8("按键"),m_control->m_sensorstruct[i].name)==0)
        {
            ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
            ui->tableWidget->setItem(((ui->tableWidget)->rowCount()-1),0,new QTableWidgetItem(m_control->m_sensorstruct[i].longaddr));
            ui->tableWidget->setItem(((ui->tableWidget)->rowCount()-1),1,new QTableWidgetItem(m_control->m_sensorstruct[i].shortaddr));
            ui->tableWidget->setRowHeight(((ui->tableWidget)->rowCount()-1),50);
        }

    }

}

void CKey::SelectGuanXianControl()
{
    for(int i=0;i<m_control->isensorlength;i++)
    {
        if((QString::compare(trUtf8("浇花"),m_control->m_sensorstruct[i].name)==0)||(QString::compare(trUtf8("窗帘"),m_control->m_sensorstruct[i].name)==0)||(QString::compare(trUtf8("调光"),m_control->m_sensorstruct[i].name)==0)||(QString::compare(trUtf8("雨蓬"),m_control->m_sensorstruct[i].name)==0)||(QString::compare(trUtf8("电源"),m_control->m_sensorstruct[i].name)==0)||(QString::compare(trUtf8("喷淋"),m_control->m_sensorstruct[i].name)==0)||(QString::compare(trUtf8("电饭煲"),m_control->m_sensorstruct[i].name)==0)||(QString::compare(trUtf8("加湿器"),m_control->m_sensorstruct[i].name)==0)||(QString::compare(trUtf8("换气扇"),m_control->m_sensorstruct[i].name)==0)||(QString::compare(trUtf8("净化器"),m_control->m_sensorstruct[i].name)==0)||(QString::compare(trUtf8("饮水机"),m_control->m_sensorstruct[i].name)==0)||(QString::compare(trUtf8("喷雾器"),m_control->m_sensorstruct[i].name)==0))
        {
            ui->tableWidget_2->setRowCount(ui->tableWidget_2->rowCount()+1);
            ui->tableWidget_2->setItem(((ui->tableWidget_2)->rowCount()-1),0,new QTableWidgetItem(m_control->m_sensorstruct[i].name));
            ui->tableWidget_2->setItem(((ui->tableWidget_2)->rowCount()-1),1,new QTableWidgetItem(m_control->m_sensorstruct[i].shortaddr));
            ui->tableWidget_2->setItem(((ui->tableWidget_2)->rowCount()-1),2,new QTableWidgetItem(m_control->m_sensorstruct[i].longaddr));
            ui->tableWidget_2->setItem(((ui->tableWidget_2)->rowCount()-1),3,new QTableWidgetItem(m_control->m_sensorstruct[i].dir));
            ui->tableWidget_2->setItem(((ui->tableWidget_2)->rowCount()-1),4,new QTableWidgetItem(""));
            ui->tableWidget_2->setRowHeight(((ui->tableWidget_2)->rowCount()-1),50);
        }

    }
    for(int i=0;i<m_control->iirtructlength;i++)
    {
        if((QString::compare(trUtf8("空调"),m_control->m_irstruct[i].name)==0)||(QString::compare(trUtf8("空调扇"),m_control->m_irstruct[i].name)==0)||(QString::compare(trUtf8("音箱"),m_control->m_irstruct[i].name)==0)||(QString::compare(trUtf8("电视"),m_control->m_irstruct[i].name)==0)||(QString::compare(trUtf8("投影机"),m_control->m_irstruct[i].name)==0))
        {
            ui->tableWidget_2->setRowCount(ui->tableWidget_2->rowCount()+1);
            ui->tableWidget_2->setItem(((ui->tableWidget_2)->rowCount()-1),0,new QTableWidgetItem(m_control->m_irstruct[i].name));
            ui->tableWidget_2->setItem(((ui->tableWidget_2)->rowCount()-1),1,new QTableWidgetItem(m_control->m_irstruct[i].shortaddr));
            ui->tableWidget_2->setItem(((ui->tableWidget_2)->rowCount()-1),2,new QTableWidgetItem(m_control->m_irstruct[i].longaddr));
            ui->tableWidget_2->setItem(((ui->tableWidget_2)->rowCount()-1),3,new QTableWidgetItem(m_control->m_irstruct[i].dir));
            ui->tableWidget_2->setItem(((ui->tableWidget_2)->rowCount()-1),4,new QTableWidgetItem(m_control->m_irstruct[i].function));

            ui->tableWidget_2->setRowHeight(((ui->tableWidget_2)->rowCount()-1),50);
        }

    }
}


void CKey::on_tableWidget_cellClicked(int row, int column)
{
     tablerow1=row;
}

void CKey::on_tableWidget_2_cellClicked(int row, int column)
{
     tablerow2=row;
}

void CKey::on_tableWidget_3_cellClicked(int row, int column)
{
     tablerow3=row;
}
