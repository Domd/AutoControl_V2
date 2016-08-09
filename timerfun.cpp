#include "timerfun.h"
#include "ui_timerfun.h"
#include "autocontrol_v2.h"


TimerFun::TimerFun(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimerFun)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    m_control->whichdialog=11;
    btimerfuninput=false;

    QStringList header;
    header.append(trUtf8("节点名称"));
    header.append(trUtf8("节点位置"));
    header.append(trUtf8("短地址"));
    header.append(trUtf8("MAC位置"));

    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setColumnWidth(0, 146);
    ui->tableWidget->setColumnWidth(1, 136);
    ui->tableWidget->setColumnWidth(2, 0);
    ui->tableWidget->setColumnWidth(3, 0);
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    SelectDev();
    m_text=ui->textEdit;
}

TimerFun::~TimerFun()
{
    delete ui;
}

void TimerFun::SelectDev()
{
    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
       ui->tableWidget->removeRow(i);
    }
    for(int i=0;i<m_control->isensorlength;i++)
    {
        if((QString::compare(trUtf8("浇花"),m_control->m_sensorstruct[i].name)==0)||(QString::compare(trUtf8("雨蓬"),m_control->m_sensorstruct[i].name)==0)||(QString::compare(trUtf8("电源"),m_control->m_sensorstruct[i].name)==0)||(QString::compare(trUtf8("喷淋"),m_control->m_sensorstruct[i].name)==0)||(QString::compare(trUtf8("电饭煲"),m_control->m_sensorstruct[i].name)==0)||(QString::compare(trUtf8("加湿器"),m_control->m_sensorstruct[i].name)==0)||(QString::compare(trUtf8("换气扇"),m_control->m_sensorstruct[i].name)==0)||(QString::compare(trUtf8("净化器"),m_control->m_sensorstruct[i].name)==0)||(QString::compare(trUtf8("饮水机"),m_control->m_sensorstruct[i].name)==0)||(QString::compare(trUtf8("喷雾器"),m_control->m_sensorstruct[i].name)==0))
        {
            ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
            ui->tableWidget->setItem(((ui->tableWidget)->rowCount()-1),0,new QTableWidgetItem(m_control->m_sensorstruct[i].name));
            ui->tableWidget->setItem(((ui->tableWidget)->rowCount()-1),1,new QTableWidgetItem(m_control->m_sensorstruct[i].dir));
            ui->tableWidget->setItem(((ui->tableWidget)->rowCount()-1),2,new QTableWidgetItem(m_control->m_sensorstruct[i].shortaddr));
            ui->tableWidget->setItem(((ui->tableWidget)->rowCount()-1),3,new QTableWidgetItem(m_control->m_sensorstruct[i].longaddr));
            ui->tableWidget->setRowHeight(((ui->tableWidget)->rowCount()-1),50);
        }
    }
}

void TimerFun::on_textEdit_selectionChanged()
{
    if(btimerfuninput==false)
    {
        m_input=new Input();
        m_input->show();

        btimerfuninput=true;

        bistimerfuninput=true;
    }
}

void TimerFun::on_pushButton_clicked()
{

//    if(m_control->bistimerfunopen==false)
//    {
//        bool ok=false;
//        m_control->bistimerfunopen=true;
//        QTableWidgetItem *item = ui->tableWidget->item(tablerow, 2);
//        m_control->btimerfunaddr=item->text();
//        item = ui->tableWidget->item(tablerow, 3);
//        m_control->btimerfunmacaddr=item->text();
//        m_control->KG_ON(m_control->btimerfunaddr,m_control->btimerfunmacaddr);
//        int i=ui->textEdit->toPlainText().toInt(&ok,10);
//        m_control->m_TimerFun->start(i*1000);
//        qDebug("m_TimerFun->start");
//    }

}

void TimerFun::on_pushButton_2_clicked()
{
//    m_control->m_TimerFun->stop();
//    m_control->KG_OFF(m_control->btimerfunaddr,m_control->btimerfunmacaddr);
//    m_control->btimerfunaddr="";
//    m_control->bistimerfunopen=false;
}

void TimerFun::on_pushButton_3_clicked()
{
  //  m_control->whichdialog=-1;
    this->parent->show();
    this->close();
}

void TimerFun::on_tableWidget_cellClicked(int row, int column)
{
    tablerow=row;
}
