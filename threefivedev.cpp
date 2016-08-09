#include "threefivedev.h"
#include "ui_threefivedev.h"
#include "autocontrol_v2.h"

ThreeFiveDev::ThreeFiveDev(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ThreeFiveDev)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    QPalette palette = this->palette();
    palette.setBrush(this->backgroundRole(),QBrush(QPixmap(":/images/150.png")));
    this->setPalette(palette);

    tablerow1=-1;
    m_text=ui->textEdit;
    m_control->whichdialog=3;
    label1=ui->label_5;
    m_table=ui->tableWidget;

    QStringList header;
    header.append(trUtf8("节点名称"));
    header.append(trUtf8("短地址"));
    header.append(trUtf8("MAC地址"));
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setColumnWidth(0, 160);
    ui->tableWidget->setColumnWidth(1, 160);
    ui->tableWidget->setColumnWidth(2, 426);
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->comboBox->insertItem(0,QIcon(":/images/1.png"),trUtf8("门磁"));
    ui->comboBox->insertItem(1,QIcon(":/images/2.png"),trUtf8("人体"));
    ui->comboBox->insertItem(2,QIcon(":/images/4.png"),trUtf8("烟雾"));
    ui->comboBox->insertItem(3,QIcon(":/images/5.png"),trUtf8("气体"));

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
}

ThreeFiveDev::~ThreeFiveDev()
{
    delete ui;
}

void ThreeFiveDev::on_pushButton_5_clicked()//fanhui
{
    m_control->whichdialog=1;
    this->parent->show();
    this->close();
}

//void ThreeFiveDev::ReadThreeFivetable()
//{
////    QString str="";
//    QSqlQuery m_query(m_control->m_sql);
//    m_query.prepare("SELECT * FROM ThreeFiveDevTable");
//    if (m_query.exec())
//    {
//        int Row = 0;
//        while (m_query.next())
//        {
//            ui->tableWidget_2->setRowCount(Row + 1);
//            ui->tableWidget_2->setItem(Row, 0,new QTableWidgetItem(m_query.value(0).toString()));
//            ui->tableWidget_2->setItem(Row, 1,new QTableWidgetItem(m_query.value(1).toString()));
//            ui->tableWidget_2->setItem(Row, 2,new QTableWidgetItem(m_query.value(2).toString()));
//            ui->tableWidget_2->setItem(Row, 3,new QTableWidgetItem(m_query.value(3).toString()));
//            Row++;
//        }
//    }
//}


void ThreeFiveDev::on_pushButton_2_clicked()//add
{
    ui->label_5->setText("");
    if ((tablerow1==-1)||ui->comboBox->currentIndex() == -1|| ui->comboBox_2->currentIndex() == -1/*||ui->textEdit->toPlainText()==""*/)
    {
        ui->label_5->setText(trUtf8("没有输入内容。。"));
        return;
    }
    QSqlQuery m_query(m_control->m_sql);

    m_query.prepare("insert into ThreeFiveDevTable(name,shortaddr,longaddr,dir,code) values(:name,:shortaddr,:longaddr,:dir,:code)");
    m_query.bindValue(":name", ui->comboBox->currentText());
    QTableWidgetItem *item = ui->tableWidget->item(tablerow1, 1);
    m_query.bindValue(":shortaddr", item->text());
    item = ui->tableWidget->item(tablerow1, 2);
    m_query.bindValue(":longaddr", item->text());
    m_query.bindValue(":dir", ui->comboBox_2->currentText());
    m_query.bindValue(":code", ui->textEdit->toPlainText());
    bool ok=m_query.exec();
    if(ok==false)
    {
        ui->label_5->setText(trUtf8("添加表错误。。"));
        return;
    }
    m_control->ReadDatabase();
    ui->label_5->setText(trUtf8("添加OK"));
}

void ThreeFiveDev::on_tableWidget_cellClicked(int row, int column)
{
   tablerow1=row;

}

void ThreeFiveDev::on_pushButton_4_clicked()//shanchu
{

    m_control->whichdialog=17;
    this->hide();
    this->m_viewthreefivedevice = new ViewThreeFiveDevice();
    this->m_viewthreefivedevice->show();
    this->m_viewthreefivedevice->parent = this;

}
