#include "set.h"
#include "ui_set.h"
#include "autocontrol_v2.h"
#include <QMessageBox>

Set::Set(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Set)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    //QMessageBox::warning(this,"123","456",QMessageBox::Ok);
}

Set::~Set()
{
    delete ui;
}

void Set::on_pushButton_clicked()//adddevice
{
    m_control->whichdialog=1;
    this->hide();
    this->m_add = new AddDevice();
    this->m_add->show();
    this->m_add->parent = this;
}

void Set::on_pushButton_4_clicked()
{
    m_control->whichdialog=-1;
    this->parent->show();
    this->close();
}

void Set::on_pushButton_2_clicked()//connect
{
    m_control->whichdialog=5;
    this->hide();
    this->m_connectset = new ConnectSet();
    this->m_connectset->show();
    this->m_connectset->parent = this;
}

void Set::on_pushButton_5_clicked()
{
    m_control->whichdialog=10;
    this->hide();
    this->m_telset = new TelSet();
    this->m_telset->show();
    this->m_telset->parent = this;
}

void Set::on_pushButton_6_clicked()//定时
{
    m_control->whichdialog=11;
    this->hide();
    this->m_timerfun = new TimerFun();
    this->m_timerfun->show();
    this->m_timerfun->parent = this;
}

void Set::on_pushButton_7_clicked()
{
    char iaddr[4]={0xCC,0xEE,0xEE,0xDD};
    m_control->m_Com->write(iaddr);

}

void Set::on_pushButton_3_clicked()//panid
{
    char iaddr[4]={0xCC,0xBB,0xBB,0xDD};
    m_control->m_Com->write(iaddr);
}
