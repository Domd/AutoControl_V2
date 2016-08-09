#ifndef IRDEV_H
#define IRDEV_H

#include <QWidget>
#include <QTableWidget>
#include <QLabel>
#include "viewirdevice.h"

namespace Ui {
class IRDev;
}

class IRDev : public QWidget
{
    Q_OBJECT
    
public:
    explicit IRDev(QWidget *parent = 0);
    ~IRDev();
    QWidget *parent;
    QTableWidget *m_table;
    QLabel *label1;
    int tablerow1;
    QChar m_qchar;
    ViewIRDevice *m_viewirdevice;
    //void readirtable();
    QString IRCutString(int itype,QString str);
private slots:
     void on_pushButton_5_clicked();

     void on_pushButton_clicked();

     void on_pushButton_2_clicked();

    // void on_pushButton_3_clicked();

     void on_pushButton_4_clicked();

     void on_pushButton_6_clicked();

     void on_tableWidget_cellClicked(int row, int column);

     void on_comboBox_currentIndexChanged(int index);

private:
    Ui::IRDev *ui;
};

#endif // IRDEV_H
