#include "ftshtline.h"
#include "ui_ftshtline.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtCore>
//#include <QDebug>

FtShtLine::FtShtLine(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FtShtLine)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);

    m_pCurve = new Curve;
//    m_pCurve->init(10, 30, 25, -10, 90);
    m_pCurve->init(15,50,25,-10,90);

    QHBoxLayout *layout1 = new QHBoxLayout;
    layout1->addStretch();
    layout1->addWidget(ui->startButton);
    layout1->addWidget(ui->stopButton);
    layout1->addStretch();

    QVBoxLayout *layout2 = new QVBoxLayout;
    layout2->addWidget((Curve*)this->m_pCurve);
    layout2->addLayout(layout1);
    this->setLayout(layout2);

    timerId = 0;
}

FtShtLine::~FtShtLine()
{
    if (m_pCurve)
    {
        delete m_pCurve;
        m_pCurve = 0;
    }

    delete ui;
}

void FtShtLine::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == timerId){
        int value  = rand() % 60;
        qDebug("value = %d", value);
        m_pCurve->updateData(value);
    }
    else{
        QWidget::timerEvent(event);
    }
}

void FtShtLine::on_startButton_clicked()
{
    if (0 == timerId)
    {
        timerId = startTimer(10);
        qDebug("startTimer()");
    }
    else
    {
        qDebug("Timer already started!");
    }
}

void FtShtLine::on_stopButton_clicked()
{
    if (timerId)
    {
        killTimer(timerId);
        timerId = 0;
        qDebug("killTimer()");
    }
    else
    {
        qDebug("Timer not start!");
    }

}
