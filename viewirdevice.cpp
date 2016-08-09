#include "viewirdevice.h"
#include "ui_viewirdevice.h"
#include "autocontrol_v2.h"

ViewIRDevice::ViewIRDevice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewIRDevice)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    tablerow1=-1;

    QStringList header;
    header.append(trUtf8("节点名称"));
    header.append(trUtf8("短地址"));
    header.append(trUtf8("长地址"));
    header.append(trUtf8("节点位置"));
    header.append(trUtf8("节点码"));
    header.append(trUtf8("节点功能"));
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setColumnWidth(0, 110);
    ui->tableWidget->setColumnWidth(1, 120);
    ui->tableWidget->setColumnWidth(2, 330);
    ui->tableWidget->setColumnWidth(3, 140);
    ui->tableWidget->setColumnWidth(4, 90);
    ui->tableWidget->setColumnWidth(5, 160);
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(false);
    readirtable();

}

ViewIRDevice::~ViewIRDevice()
{
    delete ui;
}

void ViewIRDevice::readirtable()//
{
    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        ui->tableWidget->removeRow(i);
    }
    QSqlQuery m_query(m_control->m_sql);QString str="";
    m_query.prepare("SELECT * FROM IRHWTable");
    if (m_query.exec())
    {
        int Row = 0;
        while (m_query.next())
        {
            ui->tableWidget->setRowCount(Row + 1);
            ui->tableWidget->setItem(Row, 0,new QTableWidgetItem(m_query.value(0).toString()));
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
            ui->tableWidget->setItem(Row, 1,new QTableWidgetItem(str));
            ui->tableWidget->setItem(Row, 2,new QTableWidgetItem(m_query.value(2).toString()));
            ui->tableWidget->setItem(Row, 3,new QTableWidgetItem(m_query.value(3).toString()));
            ui->tableWidget->setItem(Row, 4,new QTableWidgetItem(m_query.value(4).toString()));
            ui->tableWidget->setItem(Row, 5,new QTableWidgetItem(m_query.value(5).toString()));
            ui->tableWidget->setRowHeight(Row,50);
            Row++;
        }
    }
}


void ViewIRDevice::on_pushButton_clicked()
{
    ui->label->setText(trUtf8(""));
    if(tablerow1<0)
    {
       ui->label->setText(trUtf8("您未选择"));
       return;
    }
    QSqlQuery m_query(m_control->m_sql);
    m_query.prepare("delete FROM IRHWTable where code=?");
    m_query.bindValue(0,ui->tableWidget->item(ui->tableWidget->currentRow(),4)->text());

    bool ok=m_query.exec();
    if(ok==false)
    {
        ui->label->setText(trUtf8("删除错误"));
        return;
    }
    int i=ui->tableWidget->rowCount();
    if(i==1)
    {
       ui->tableWidget->removeRow(0);
    }
    readirtable();
    //m_control->RemoveTable();
    m_control->ReadDatabase();
    tablerow1=-1;
    ui->label->setText(trUtf8("删除OK"));
}

void ViewIRDevice::on_tableWidget_cellClicked(int row, int column)
{
    tablerow1=row;
}

void ViewIRDevice::on_pushButton_2_clicked()
{
    m_control->whichdialog=2;
    this->parent->show();
    this->close();
}
