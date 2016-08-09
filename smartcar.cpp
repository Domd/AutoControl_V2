#include "smartcar.h"
#include "ui_smartcar.h"
#include "autocontrol_v2.h"

SmartCar::SmartCar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SmartCar)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
     m_control->whichdialog=4;
//     if(m_control->bcaropen==false)
//     {
//        m_control->SendWenDuOrderToCarNoDuanXin(m_control->maccaraddr);
//        m_control->bcaropen=true;
//     }
}

SmartCar::~SmartCar()
{
    delete ui;
}

void SmartCar::on_pushButton_clicked()
{
     m_control->Car_AutoXun(m_control->mcaraddr,m_control->maccaraddr);
//     m_control->SendCarByUdp(7,m_control->maccaraddr);
}

void SmartCar::on_pushButton_2_clicked()
{
     m_control->Car_Stop(m_control->mcaraddr,m_control->maccaraddr);
//     m_control->SendCarByUdp(2,m_control->maccaraddr);
}

void SmartCar::on_pushButton_3_clicked()
{
    m_control->Car_Left(m_control->mcaraddr,m_control->maccaraddr);
//     m_control->SendCarByUdp(3,m_control->maccaraddr);

}

void SmartCar::on_pushButton_4_clicked()
{
    m_control->Car_Back(m_control->mcaraddr,m_control->maccaraddr);
//    m_control->SendCarByUdp(6,m_control->maccaraddr);
}

void SmartCar::on_pushButton_5_clicked()
{
   m_control->Car_Right(m_control->mcaraddr,m_control->maccaraddr);
//   m_control->SendCarByUdp(4,m_control->maccaraddr);
}

void SmartCar::on_pushButton_6_clicked()
{
    m_control->Car_Go(m_control->mcaraddr,m_control->maccaraddr);
//    m_control->SendCarByUdp(1,m_control->maccaraddr);
}

void SmartCar::on_pushButton_7_clicked()
{
     m_control->whichdialog=-1;
     this->parent->show();
     close();
}
