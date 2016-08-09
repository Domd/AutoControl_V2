#include "inteshelf.h"
#include "ui_inteshelf.h"
#include "autocontrol_v2.h"
#include <QPainter>
#include <QMessageBox>

InteShelf::InteShelf(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InteShelf)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);

    tablerow=-1;
    m_control->shelfInteface=true;
//    m_textedit=ui->textEdit;

    QPixmap pixmap;
    pixmap.load(":/images/inteshelf/1.png");
    QPalette p(palette());
    p.setBrush(QPalette::Window,QBrush(pixmap));
    setPalette(p);

    pixmap.load(":/images/inteshelf/2.png");
    ui->bindingTW->setIcon(pixmap);
    ui->bindingTW->setIconSize(pixmap.size());
    ui->bindingTW->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/inteshelf/3.png");
    ui->huajiaTW->setIcon(pixmap);
    ui->huajiaTW->setIconSize(pixmap.size());
    ui->huajiaTW->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/inteshelf/4.png");
    ui->mainpageTW->setIcon(pixmap);
    ui->mainpageTW->setIconSize(pixmap.size());
    ui->mainpageTW->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/inteshelf/5.png");
    ui->label->setPixmap(pixmap);

    pixmap.load(":/images/inteshelf/6.png");
    ui->toolButton->setIcon(pixmap);
    ui->toolButton->setIconSize(pixmap.size());
    ui->toolButton->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/inteshelf/7.png");
    ui->toolButton_2->setIcon(pixmap);
    ui->toolButton_2->setIconSize(pixmap.size());
    ui->toolButton_2->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

    pixmap.load(":/images/button/0010.png");
    ui->toolButton_3->setIcon(pixmap);
    ui->toolButton_3->setIconSize(pixmap.size());
    ui->toolButton_3->setStyleSheet("QToolButton{border-radius:5px;border-width:0px;}");

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

//
    m_timer=new QTimer(this);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(cardData()));
//    m_timer->start(1000);

    QStringList header;
    header.append(trUtf8("名称"));
    header.append(trUtf8("卡号"));

    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setColumnWidth(0, 100);
    ui->tableWidget->setColumnWidth(1, 180);
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->verticalHeader()->setVisible(false);     //隐藏列表头
    ui->tableWidget->horizontalHeader()->setVisible(false);  //隐藏行表头

    ui->stackedWidget->setCurrentIndex(0);//初始化为界面1

}

InteShelf::~InteShelf()
{
    delete ui;

    m_timer->stop();
    delete m_timer;
}

void InteShelf::on_mainpageTW_clicked()
{
    this->m_timer->stop();
    this->parent->show();
    this->close();
}

void InteShelf::on_huajiaTW_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->huajiaTW->setFocus();
}

void InteShelf::on_bindingTW_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->bindingTW->setFocus();
}


void InteShelf::on_toolButton_clicked()
{
    if ((ui->textEdit->toPlainText()=="")||ui->comboBox->currentIndex() == -1)
    {
        QMessageBox::warning(0,trUtf8("提示"),trUtf8("卡号为空或名称未选择！"));
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
//读取货架的数据库
void InteShelf::ReadShevlesTable()
{
    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        ui->tableWidget->removeRow(i);
    }
    m_control->ishelveslength=0;
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

            m_control->m_shevlesstruct[m_control->ishelveslength].name=m_query.value(0).toString();
            m_control->m_shevlesstruct[m_control->ishelveslength].rfidnum=m_query.value(1).toString();
            m_control->ishelveslength++;
        }
    }

}
void InteShelf::on_toolButton_2_clicked()
{
    if(tablerow<0)
    {
        QMessageBox::warning(this,trUtf8("提示"),trUtf8("您未选择货物名称，请选择！"));
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

void InteShelf::on_tableWidget_cellClicked(int row, int column)
{
    tablerow=row;
}


void InteShelf::cardData()
{
    if(m_control->GaopinFlag)
    {
        ui->textEdit->setText(m_control->gaopinNow);


        ui->eg1cardLabel->setText(m_control->ShelfData[0]);
        ui->eg2cardLabel->setText(m_control->ShelfData[2]);
        ui->eg3cardLabel->setText(m_control->ShelfData[4]);
        ui->eg4cardLabel->setText(m_control->ShelfData[6]);
        ui->eg5cardLabel->setText(m_control->ShelfData[8]);
        ui->eg6cardLabel->setText(m_control->ShelfData[10]);

        ui->eg1nameLabel->setText(m_control->ShelfData[1]);
        ui->eg2nameLabel->setText(m_control->ShelfData[3]);
        ui->eg3nameLabel->setText(m_control->ShelfData[5]);
        ui->eg4nameLabel->setText(m_control->ShelfData[7]);
        ui->eg5nameLabel->setText(m_control->ShelfData[9]);
        ui->eg6nameLabel->setText(m_control->ShelfData[11]);

        m_control->GaopinFlag=false;
    }
}

void InteShelf::on_toolButton_3_clicked()
{
    this->hide();
    m_control->show();
    m_control->ISTparent=this;

//    m_control->whichdialog=1;
//    this->hide();
//    this->m_add = new AddDevice();
//    this->m_add->show();
//    this->m_add->parent = this;
}
