#include "yanshiban.h"
#include "ui_yanshiban.h"
#include "autocontrol_v2.h"
#include <QMessageBox>

YanShiBan::YanShiBan(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::YanShiBan)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    m_control->whichdialog=14;

}

YanShiBan::~YanShiBan()
{
    delete ui;
}

void YanShiBan::on_pushButton_clicked()//fengshan on
{
   m_control->YanShi_FengShan_ON(m_control->stryanshibanaddr,m_control->stryanshibanmacaddr);
}

void YanShiBan::on_pushButton_2_clicked()//fengshan off
{
   m_control->YanShi_FengShan_OFF(m_control->stryanshibanaddr,m_control->stryanshibanmacaddr);
}

void YanShiBan::on_pushButton_5_clicked()//buguangdeng on
{
   m_control->YanShi_BuGuangDeng_ON(m_control->stryanshibanaddr,m_control->stryanshibanmacaddr);
}

void YanShiBan::on_pushButton_6_clicked()//buguangdeng off
{
   m_control->YanShi_BuGuangDeng_OFF(m_control->stryanshibanaddr,m_control->stryanshibanmacaddr);
}

void YanShiBan::on_pushButton_3_clicked()//diancifa on
{
   m_control->YanShi_DianCiFa_ON(m_control->stryanshibanaddr,m_control->stryanshibanmacaddr);
}

void YanShiBan::on_pushButton_4_clicked()//diancifa off
{
   m_control->YanShi_DianCiFa_OFF(m_control->stryanshibanaddr,m_control->stryanshibanmacaddr);
}

void YanShiBan::on_pushButton_7_clicked()//shumaguang on
{
    m_control->YanShi_ShuMaGuan(m_control->stryanshibanaddr,m_control->stryanshibanmacaddr,m_control->shumaguanval);
    if(m_control->shumaguanval<=0x63)
    {
       m_control->shumaguanval+=0x01;
    }
    else
    {
       m_control->shumaguanval=0x30;
    }
    return;
}

void YanShiBan::on_pushButton_8_clicked()//shumaguang off
{
    m_control->YanShi_ShuMaGuan(m_control->stryanshibanaddr,m_control->stryanshibanmacaddr,m_control->shumaguanval);
    if(m_control->shumaguanval>0x00)
    {
       m_control->shumaguanval-=0x01;
    }
    else
    {
       m_control->shumaguanval=0x30;
    }
  //  return;
}

void YanShiBan::on_pushButton_9_clicked()//zhengzhuan on
{
    m_control->YanShi_DianJi_ZhengZhuan(m_control->stryanshibanaddr,m_control->stryanshibanmacaddr);
}

void YanShiBan::on_pushButton_10_clicked()//fanzhuang on
{
   m_control->YanShi_DianJi_FanZhuan(m_control->stryanshibanaddr,m_control->stryanshibanmacaddr);
}

void YanShiBan::on_pushButton_11_clicked()//ting
{
   m_control->YanShi_DianJi_Ting(m_control->stryanshibanaddr,m_control->stryanshibanmacaddr);
}

void YanShiBan::on_pushButton_12_clicked()
{
   m_control->whichdialog=-1;
   this->close();
   this->parent->show();
}
