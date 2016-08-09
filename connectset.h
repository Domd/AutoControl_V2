#ifndef CONNECTSET_H
#define CONNECTSET_H

#include <QWidget>
#include "cguangxian.h"
#include "cqiti.h"
#include "csmog.h"
#include "crain.h"
#include "ckey.h"
#include "cwenshidu.h"
#include "ckongqi.h"
namespace Ui {
class ConnectSet;
}

class ConnectSet : public QWidget
{
    Q_OBJECT
    
public:
    explicit ConnectSet(QWidget *parent = 0);
    ~ConnectSet();
    QWidget *parent;
    CGuangXian *m_cguangxian;
    CQiTi *m_qiti;
    CSmog *m_smog;
    CRain *m_rain;
    CKey *m_key;
    CWenShiDu *m_wenshidu;
    CKongQi *m_kongqi;
private slots:
    void on_pushButton_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_radioButton_7_clicked();

    void on_radioButton_8_clicked();

    void on_radioButton_9_clicked();

private:
    Ui::ConnectSet *ui;
};

#endif // CONNECTSET_H
