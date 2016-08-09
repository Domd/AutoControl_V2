#ifndef ADDDEVICE_H
#define ADDDEVICE_H

#include <QWidget>
#include "irdev.h"
#include "threefivedev.h"
#include "viewadddevice.h"
#include <QTableWidget>
#include <QLabel>
#include <zhiwen.h>


//#include "intesandtable.h"

namespace Ui {
class AddDevice;
}

class AddDevice : public QWidget
{
    Q_OBJECT
    
public:
    explicit AddDevice(QWidget *parent = 0);
    ~AddDevice();

    QWidget *parent;
    IRDev *m_irdev;
   // class InteSandTable *m_intesandtable;
    ThreeFiveDev *m_threefive;
    QTableWidget *m_table;
    QLabel *label1;
    ViewAddDevice *m_viewadddevice;
    ZhiWen *m_zhiwen;
    int tablerow1;
    int tablerow2;
    void ReadSensortable();
    void SensorNameJudge();
    QString CutLongString(int itype,QString str);
private slots:
    void on_pushButton_2_clicked();
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
    void on_radioButton_3_clicked();
    void on_radioButton_4_clicked();
    void on_radioButton_5_clicked();
    void on_radioButton_7_clicked();
    void on_radioButton_6_clicked();
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_tableWidget_cellClicked(int row, int column);
    void on_tableWidget_2_cellClicked(int row, int column);
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();
    void on_radioButton_8_clicked();
    void on_radioButton_9_clicked();

//    void on_tableWidget_clicked(const QModelIndex &index);
//    void on_tableWidget_activated(const QModelIndex &index);
    
private:
    Ui::AddDevice *ui;
};

#endif // ADDDEVICE_H
