#ifndef TESTGPS_H
#define TESTGPS_H

#include <QWidget>
#include "gpsinfo.h"
#include <QTimer>
#include <QDebug>

namespace Ui {
class TestGps;
}

class TestGps : public QWidget
{
    Q_OBJECT
    
public:
    explicit TestGps(QWidget *parent = 0);
    ~TestGps();

    QWidget *parent;
    bool gpsstatus;

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_start_clicked();
    void on_close_clicked();
    void up_date();

    void on_clear_clicked();

private:
    Ui::TestGps *ui;

    volatile int fd;
    GPS_INFO gps_info;
    char GPS_BUF[1024];
    int set_bound();
    QTimer *timer;
};

#endif // TESTGPS_H
