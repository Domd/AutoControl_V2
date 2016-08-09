#include "viewthreefivedevice.h"
#include "ui_viewthreefivedevice.h"
#include "autocontrol_v2.h"

ViewThreeFiveDevice::ViewThreeFiveDevice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewThreeFiveDevice)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    m_control->whichdialog=17;

    QStringList header;
    header.append(trUtf8("节点名称"));
    header.append(trUtf8("短地址"));
    header.append(trUtf8("MAC地址"));
    header.append(trUtf8("位置"));
    header.append(trUtf8("节点码"));
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setColumnWidth(0, 128);
    ui->tableWidget->setColumnWidth(1, 126);
    ui->tableWidget->setColumnWidth(2, 300);
    ui->tableWidget->setColumnWidth(3, 106);
    ui->tableWidget->setColumnWidth(4, 100);
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setVisible(false);
    ReadThreeFivetable();
}

ViewThreeFiveDevice::~ViewThreeFiveDevice()
{
    delete ui;
}

void ViewThreeFiveDevice::ReadThreeFivetable()
{

    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        ui->tableWidget->removeRow(i);
    }
    QSqlQuery m_query(m_control->m_sql);
    m_query.prepare("SELECT * FROM ThreeFiveDevTable");
    if (m_query.exec())
    {
        int Row = 0;
        while (m_query.next())
        {
            ui->tableWidget->setRowCount(Row + 1);
            ui->tableWidget->setItem(Row, 0,new QTableWidgetItem(m_query.value(0).toString()));
            ui->tableWidget->setItem(Row, 1,new QTableWidgetItem(m_query.value(1).toString()));
            ui->tableWidget->setItem(Row, 2,new QTableWidgetItem(m_query.value(2).toString()));
            ui->tableWidget->setItem(Row, 3,new QTableWidgetItem(m_query.value(3).toString()));
            ui->tableWidget->setItem(Row, 4,new QTableWidgetItem(m_query.value(4).toString()));
            ui->tableWidget->setRowHeight(Row,50);
            Row++;
        }
    }
}


void ViewThreeFiveDevice::on_tableWidget_cellClicked(int row, int column)
{
    tablerow1=row;
}

void ViewThreeFiveDevice::on_pushButton_clicked()
{

    ui->label->setText("");
    if(tablerow1<0)
    {
       ui->label->setText(trUtf8("您未选择"));
       return;
    }
    QSqlQuery m_query(m_control->m_sql);
    m_query.prepare("delete FROM ThreeFiveDevTable where code=?");
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
    ReadThreeFivetable();
//    m_control->RemoveTable();
    m_control->ReadDatabase();
    tablerow1=-1;
    ui->label->setText(trUtf8("删除OK"));
}

void ViewThreeFiveDevice::on_pushButton_2_clicked()
{
    m_control->whichdialog=3;
    this->parent->show();
    this->close();
}
