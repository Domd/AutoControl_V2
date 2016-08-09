#include "inshelf.h"
#include "ui_inshelf.h"
#include "autocontrol_v2.h"


InShelf::InShelf(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InShelf)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    m_control->whichdialog=13;
    m_text=ui->textEdit;



    ui->comboBox->insertItem(0,QIcon(":/images/1.png"),trUtf8("红椒"));
    ui->comboBox->insertItem(1,QIcon(":/images/2.png"),trUtf8("南瓜"));
    ui->comboBox->insertItem(2,QIcon(":/images/4.png"),trUtf8("青椒"));
    ui->comboBox->insertItem(3,QIcon(":/images/5.png"),trUtf8("萝卜"));
    ui->comboBox->insertItem(4,QIcon(":/images/6.png"),trUtf8("白菜"));
    ui->comboBox->insertItem(5,QIcon(":/images/6.png"),trUtf8("青菜"));
    ui->comboBox->insertItem(6,QIcon(":/images/9.png"),trUtf8("西红柿"));
    ui->comboBox->insertItem(7,QIcon(":/images/7.png"),trUtf8("货物一"));
    ui->comboBox->insertItem(8,QIcon(":/images/10.png"),trUtf8("货物二"));
    ui->comboBox->insertItem(9,QIcon(":/images/4.png"),trUtf8("货物三"));
    ui->comboBox->insertItem(10,QIcon(":/images/5.png"),trUtf8("货物四"));
    ui->comboBox->insertItem(11,QIcon(":/images/6.png"),trUtf8("货物五"));
    ui->comboBox->insertItem(12,QIcon(":/images/9.png"),trUtf8("货物六"));

    QStringList header;
    header.append(trUtf8("名称"));
    header.append(trUtf8("卡号"));

    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setColumnWidth(0, 136);
    ui->tableWidget->setColumnWidth(1, 296);
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    ReadShevlesTable();
}

InShelf::~InShelf()
{
    delete ui;
}

void InShelf::ReadShevlesTable()
{
    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        ui->tableWidget->removeRow(i);
    }
    QSqlQuery m_query(m_control->m_sql);
    m_query.prepare("SELECT * FROM ShelvesMessTable");
    if (m_query.exec())
    {
        int Row = 0;
        while (m_query.next())
        {
            ui->tableWidget->setRowCount(Row + 1);
            ui->tableWidget->setItem(Row, 0,new QTableWidgetItem(m_query.value(0).toString()));
            ui->tableWidget->setItem(Row, 1,new QTableWidgetItem(m_query.value(1).toString()));
            Row++;
        }
    }

}

void InShelf::on_pushButton_clicked()
{
    if ((ui->textEdit->toPlainText()=="")||ui->comboBox->currentIndex() == -1)
    {
        return;
    }
    QSqlQuery m_query(m_control->m_sql);

    m_query.prepare("insert into ShelvesMessTable(name,rfidnum) values(:name,:rfidnum)");
    m_query.bindValue(":name",ui->comboBox->currentText());
    m_query.bindValue(":rfidnum", ui->textEdit->toPlainText());

    bool ok=m_query.exec();
    if(ok==false)
    {
        return;
    }
    ReadShevlesTable();

}

void InShelf::on_pushButton_3_clicked()
{
    if(tablerow<0)
    {
       return;
    }
    QSqlQuery m_query(m_control->m_sql);
    m_query.prepare("delete FROM ShelvesMessTable where rfidnum=?");
    m_query.bindValue(0,ui->tableWidget->item(tablerow,1)->text());

    bool ok=m_query.exec();
    if(ok==false)
    {
        return;
    }
    int i=ui->tableWidget->rowCount();
    if(i==1)
    {
       ui->tableWidget->removeRow(0);
    }
    ReadShevlesTable();
    tablerow=-1;
}

void InShelf::on_pushButton_2_clicked()//fanhui
{
    m_control->ReadShevlesTable();
    //m_control->whichdialog=-1;
    this->parent->show();
    close();
}

void InShelf::on_tableWidget_cellClicked(int row, int column)
{
    tablerow=row;
}
