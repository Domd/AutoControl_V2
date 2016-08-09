#ifndef TESTGPRS_H
#define TESTGPRS_H

#include <QWidget>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/signal.h>
#include "vkey.h"

#define DEV "/dev/ttySAC1"
#define RECEIVE_BUF_WAIT_1S 1
#define RECEIVE_BUF_WAIT_2S 2
#define RECEIVE_BUF_WAIT_3S 3
#define RECEIVE_BUF_WAIT_4S 4
#define RECEIVE_BUF_WAIT_5S 5

namespace Ui {
class TestGprs;
}

class TestGprs : public QWidget
{
    Q_OBJECT
    
public:
    explicit TestGprs(QWidget *parent = 0);
    ~TestGprs();
    QWidget *parent;
    

private slots:
    void on_Tb_Simple_clicked();
    void on_Tb_Call_clicked();
    void on_Tb_ReadID_clicked();
    void on_Tb_Signal_clicked();
    void on_Tb_Message_clicked();
    void on_Tb_Back_clicked();
    void lineClick1();
    void lineClick2();
    void lineClick3();
    void lineClick4();

    void on_Tb_Send_clicked();
//    void on_Tb_SMPH_clicked();

    void on_Tb_Break_clicked();

private:
    Ui::TestGprs *ui;
    VKey *vKey;
    int fd;
    void init_ttyS();
    void send_cmd(char *cmd);
    void read_data(char *data,int rcv_wait);
};

#endif // TESTGPRS_H
