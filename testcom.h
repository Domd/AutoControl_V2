#ifndef TESTCOM_H
#define TESTCOM_H

#include <QWidget>
#include <posix_qextserialport.h>
#include <qextserialbase.h>
#include <QTimer>
#include "vkey.h"

namespace Ui {
class TestCom;
}

class TestCom : public QWidget
{
    Q_OBJECT
    
public:
    explicit TestCom(QWidget *parent = 0);
    ~TestCom();
    QWidget *parent;
    int comNum;
    int ret,portno,nWritten,nRead;
    Posix_QextSerialPort *m_Com;
    QTimer *m_timer;
    VKey *vKey;

private slots:
    void on_TbBack_clicked();
    void on_TbOpen_clicked();
    void on_RbCom0_clicked();
    void on_RbCom1_clicked();
    void on_RbCom2_clicked();
    void on_RbCom3_clicked();
    void on_TbSend_clicked();

    void on_TbClose_clicked();
    void readData();

    void lineClick();

private:
    Ui::TestCom *ui;
};

#endif // TESTCOM_H
