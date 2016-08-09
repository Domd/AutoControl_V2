#ifndef TESTTHREEG_H
#define TESTTHREEG_H

#include <QWidget>
#include <QFile>
#include "vkey.h"

namespace Ui {
class TestThreeG;
}

class TestThreeG : public QWidget
{
    Q_OBJECT
    
public:
    explicit TestThreeG(QWidget *parent = 0);
    ~TestThreeG();

    QWidget *parent;
    VKey *vKey;

private slots:
    void on_Tb_Back_clicked();
    void on_Pb_Send_clicked();
    void on_Pb_on_clicked();

    void lineClick();

private:
    Ui::TestThreeG *ui;
};

#endif // TESTTHREEG_H
