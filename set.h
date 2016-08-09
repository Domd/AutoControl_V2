#ifndef SET_H
#define SET_H

#include <QWidget>
#include "adddevice.h"
//#include "duanxinset.h"
#include "connectset.h"
#include "telset.h"
#include "timerfun.h"

namespace Ui {
class Set;
}

class Set : public QWidget
{
    Q_OBJECT

public:
    explicit Set(QWidget *parent = 0);
    ~Set();
    QWidget *parent;
    AddDevice *m_add;
    ConnectSet *m_connectset;
    TelSet *m_telset;
    TimerFun *m_timerfun;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Set *ui;
};

#endif // SET_H
