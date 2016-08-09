#ifndef TESTBASIC_H
#define TESTBASIC_H

#include <QWidget>
#include <QLabel>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>
#include <QTimer>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>


#define ADC_INPUT_PIN _IOW('S',0x0c,unsigned long)
#define PWM_IOCTL_SET_FREQ 1
#define PWM_IOCTL_STOP 0
#define ESC_KEY 0x1b

namespace Ui {
class TestBasic;
}

class TestBasic : public QWidget
{
    Q_OBJECT

public:
    explicit TestBasic(QWidget *parent = 0);
    ~TestBasic();
    int leds_fd;
    int keys_fd;
    int adc_fd;
    int pwm_fd;
    int dir;
    int on_off;
    char t;
    int freq;
    int key;
    bool leds_status[8+1];
    bool linkLB;
    QWidget *parent;
    QLabel *m_Lab;
    QTimer *m_timer;
    QTimer *adc_timer;
//    QTimer *led_timer;

    bool ledstatus;

    void ledControl(int i);
    static int getch(void );
    void stop_buzzer(void);

    int nextled;

private slots:
    void on_LEDtB1_clicked();
    void on_LEDtB2_clicked();
    void on_LEDtB3_clicked();
    void on_LEDtB4_clicked();
    void on_LEDtB5_clicked();
    void on_LEDtB6_clicked();
    void on_LEDtB7_clicked();
    void on_LEDtB8_clicked();
    void buttonTest();
//    void on_toolButton_3_clicked();


    void on_TbBack_clicked();
    void on_Tb_Device0_clicked();
    void on_Tb_Device1_clicked();
    void on_Tb_Device2_clicked();
    void on_Tb_Device3_clicked();

    void on_Tb_SBF_clicked();
//    void on_Tb_Key_clicked();

    void on_Tb_Add_clicked();
    void on_Tb_Reduce_clicked();
    void on_Tb_Stop_clicked();


    void on_Cb_LED_clicked(bool checked);
    void on_Cb_KEY_clicked(bool checked);
    void on_Cb_ADC_clicked(bool checked);
    void on_Cb_PWM_clicked(bool checked);

    void adcTest();
//    void on_Tb_Speedled_clicked();
//    void SpeedLed();

    void on_Pb_Link_clicked();

private:
    Ui::TestBasic *ui;
};
#endif // TESTBASIC_H
