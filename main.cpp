#include <QtGui/QApplication>
#include "autocontrol_v2.h"
#include "ftcombine.h"
#include "intesandtable.h"
#include "testbasic.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    m_control = new AutoControl_V2(0);
   // m_control->setWindowFlags(Qt::FramelessWindowHint);
   // m_control->show();
 //  InteSandTable *m_IST=new InteSandTable();
   FTCombine w;
   w.show();
    return a.exec();
}
