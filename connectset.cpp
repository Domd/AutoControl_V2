#include "connectset.h"
#include "ui_connectset.h"
#include "autocontrol_v2.h"

ConnectSet::ConnectSet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnectSet)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    m_control->whichdialog=5;


}

ConnectSet::~ConnectSet()
{
    delete ui;
}

void ConnectSet::on_pushButton_clicked()
{
   // m_control->whichdialog=-1;
    this->parent->show();
    this->close();
}

void ConnectSet::on_radioButton_clicked()//guangx
{
    this->hide();
    this->m_cguangxian = new CGuangXian();
    this->m_cguangxian->show();
    this->m_cguangxian->parent = this;
    return;
}

void ConnectSet::on_radioButton_2_clicked()//qiti
{
    this->hide();
    this->m_qiti = new CQiTi();
    this->m_qiti->show();
    this->m_qiti->parent = this;
    return;
}

void ConnectSet::on_radioButton_3_clicked()//yanwu
{
    this->hide();
    this->m_smog = new CSmog();
    this->m_smog->show();
    this->m_smog->parent = this;
    return;
}

void ConnectSet::on_radioButton_4_clicked()//yudi
{
    this->hide();
    this->m_rain = new CRain();
    this->m_rain->show();
    this->m_rain->parent = this;
    return;
}

void ConnectSet::on_radioButton_7_clicked()//wenshidu
{
    this->hide();
    this->m_wenshidu = new CWenShiDu();
    this->m_wenshidu->show();
    this->m_wenshidu->parent = this;
    return;
}

void ConnectSet::on_radioButton_8_clicked()//kongqizhil
{
    this->hide();
    this->m_kongqi = new CKongQi();
    this->m_kongqi->show();
    this->m_kongqi->parent = this;
    return;
}

void ConnectSet::on_radioButton_9_clicked()//key
{
    this->hide();
    this->m_key = new CKey();
    this->m_key->show();
    this->m_key->parent = this;
    return;
}
