#ifndef TESTWIFI_H
#define TESTWIFI_H

#include <QWidget>
#include <QtNetwork>
#include <QNetworkAddressEntry>
#include <time.h>
#include <sys/time.h>
#include "vkey.h"

namespace Ui {
class TestWifi;
}

class TestWifi : public QWidget
{
    Q_OBJECT
    
public:
    explicit TestWifi(QWidget *parent = 0);
    ~TestWifi();
    QWidget *parent;
    QByteArray ssid;
    int tablerow;

private slots:
    void on_TbOpen_clicked();
    void on_TbScanning_clicked();
    void on_TbConnect_clicked();
    void on_tableWidget_cellClicked(int row, int column);
    void lineClick1();
    void lineClick2();
    void on_TbBack_clicked();

    void on_Pb_Send_clicked();

    void on_Pb_Clear_clicked();

private:
    Ui::TestWifi *ui;
    VKey *vKey;
};

#endif // TESTWIFI_H
