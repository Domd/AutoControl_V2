#include "qtbfthread.h"
#include "testbasicfun.h"
#include <QDebug>

QTbfThread::QTbfThread(QObject *parent) :
    QThread(parent)
{

}

void QTbfThread::run()
{
    qDebug()<<"TBF  thread run";
    TestBasicFun *m_TBF;
//    m_TBF->m_Lab->setText("thread run");
    while(1)
    {
        temp=read(m_TBF->keys_fd,NULL,1);
        temp=(~temp);
        if(temp!=0)
        {
            switch(temp)
            {
                case 0x01:m_TBF->m_Lab->setText(trUtf8("按键1"));
                                    if(m_TBF->linkLB==true)
                                       m_TBF->ledControl(1);
                                    break;
                case 0x02:m_TBF->m_Lab->setText(trUtf8("按键2"));
                                    if(m_TBF->linkLB==true)
                                       m_TBF->ledControl(2);
                                    break;
                case 0x04:m_TBF->m_Lab->setText(trUtf8("按键3"));
                                    if(m_TBF->linkLB==true)
                                       m_TBF->ledControl(3);
                                    break;
                case 0x08:m_TBF->m_Lab->setText(trUtf8("按键4"));
                                    if(m_TBF->linkLB==true)
                                       m_TBF->ledControl(4);
                                    break;
                case 0x10:m_TBF->m_Lab->setText(trUtf8("按键5"));
                                    if(m_TBF->linkLB==true)
                                       m_TBF->ledControl(5);
                                    break;
                case 0x20:m_TBF->m_Lab->setText(trUtf8("按键6"));
                                    if(m_TBF->linkLB==true)
                                       m_TBF->ledControl(6);
                                    break;
                case 0x40:m_TBF->m_Lab->setText(trUtf8("按键7"));
                                    if(m_TBF->linkLB==true)
                                       m_TBF->ledControl(7);
                                    break;
                case 0x80:m_TBF->m_Lab->setText(trUtf8("按键8"));
                                    if(m_TBF->linkLB==true)
                                       m_TBF->ledControl(8);
                                    break;
                 default:
                        break;
            }
        }
        usleep(500);
    }
}
