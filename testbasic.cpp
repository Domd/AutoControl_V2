#include "testbasic.h"
#include "ui_testbasic.h"
#include <QMessageBox>


TestBasic::TestBasic(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestBasic)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);//无标题栏界面

    QPalette palette = this->palette();
    palette.setBrush(this->backgroundRole(),QBrush(QPixmap(":/images/150.png")));
    this->setPalette(palette);

    for(int i=1;i<=8;i++)
    {
        leds_status[i]=false;
    }
    m_Lab=ui->labelbutton;
    linkLB=false;
    ledstatus=false;
    nextled=0;

    QPixmap pixmap;
    pixmap.load(":/images/inteagri/30.png");
    ui->st1->setScaledContents(true);
    ui->st1->setPixmap(pixmap);
    ui->st2->setScaledContents(true);
    ui->st2->setPixmap(pixmap);
    ui->st3->setScaledContents(true);
    ui->st3->setPixmap(pixmap);
    ui->st4->setScaledContents(true);
    ui->st4->setPixmap(pixmap);
}

TestBasic::~TestBasic()
{
    delete ui;

    this->m_timer->stop();
    delete m_timer;

    this->adc_timer->stop();
    delete adc_timer;

//    this->led_timer->stop();
//    delete led_timer;

    ::close(adc_fd);
    ::close(leds_fd);
    ::close(keys_fd);
    ::close(pwm_fd);
}


//led 按钮
void TestBasic::on_LEDtB1_clicked()
{
    ledControl(1);
}

void TestBasic::on_LEDtB2_clicked()
{
    ledControl(2);
}

void TestBasic::on_LEDtB3_clicked()
{
    ledControl(3);
}

void TestBasic::on_LEDtB4_clicked()
{
    ledControl(4);
}

void TestBasic::on_LEDtB5_clicked()
{
    ledControl(5);
}

void TestBasic::on_LEDtB6_clicked()
{
   ledControl(6);
}

void TestBasic::on_LEDtB7_clicked()
{
    ledControl(7);
}

void TestBasic::on_LEDtB8_clicked()
{
    ledControl(8);
}
void TestBasic::ledControl(int i)
{
    //0 开  1 关
    if(leds_status[i]==false)
    {
        ioctl(leds_fd,0,i);
        leds_status[i]=true;
    }
    else
    {
        ioctl(leds_fd,1,i);
        leds_status[i]=false;
    }
}




void TestBasic::buttonTest()
{
    t=read(keys_fd,NULL,1);
    t=(~t);
    if(t!=0)
    {
        switch(t)
        {
            case 0x01:ui->labelbutton->setText(trUtf8("按键1"));
                                if(linkLB==true)
                                   ledControl(1);
                                break;
            case 0x02:ui->labelbutton->setText(trUtf8("按键2"));
                                if(linkLB==true)
                                   ledControl(2);
                                break;
            case 0x04:ui->labelbutton->setText(trUtf8("按键3"));
                                if(linkLB==true)
                                   ledControl(3);
                                break;
            case 0x08:ui->labelbutton->setText(trUtf8("按键4"));
                                if(linkLB==true)
                                   ledControl(4);
                                break;
            case 0x10:ui->labelbutton->setText(trUtf8("按键5"));
                                if(linkLB==true)
                                   ledControl(5);
                                break;
            case 0x20:ui->labelbutton->setText(trUtf8("按键6"));
                                if(linkLB==true)
                                   ledControl(6);
                                break;
            case 0x40:ui->labelbutton->setText(trUtf8("按键7"));
                                if(linkLB==true)
                                   ledControl(7);
                                break;
            case 0x80:ui->labelbutton->setText(trUtf8("按键8"));
                                if(linkLB==true)
                                   ledControl(8);
                                break;
        }
    }
}


void TestBasic::on_TbBack_clicked()
{
    this->close();
    this->parent->show();
//    ::close(adc_fd);
//    ::close(leds_fd);
//    ::close(keys_fd);
//    ::close(pwm_fd);
}


void TestBasic::on_Tb_Device0_clicked()
{
    ioctl(adc_fd,ADC_INPUT_PIN,0);
    char buffer[2];
    int adc_len = read(adc_fd, buffer, sizeof buffer -1);
    char buf[20];
    if (adc_len > 0) {
         //scanf(buffer, "%d", &value);
         sprintf(buf,"%d  %d\n", 0,256*buffer[1]+buffer[0]);
         ui->label->setText(QString(buf));
    } else {
         perror("read ADC device:error");
         return ;
    }
    usleep(500* 1000);

}

void TestBasic::on_Tb_Device1_clicked()
{
    ioctl(adc_fd,ADC_INPUT_PIN,1);
    char buffer[2];
    int adc_len = read(adc_fd, buffer, sizeof buffer -1);
    char buf[20];
    if (adc_len > 0) {
         //scanf(buffer, "%d", &value);
         sprintf(buf,"%d  %d\n", 1,256*buffer[1]+buffer[0]);
         ui->label->setText(QString(buf));
    } else {
         perror("read ADC device:error");
         return ;
    }
    usleep(500* 1000);
}

void TestBasic::on_Tb_Device2_clicked()
{
    ioctl(adc_fd,ADC_INPUT_PIN,2);
    char buffer[2];
    int adc_len = read(adc_fd, buffer, sizeof buffer -1);
    char buf[20];
    if (adc_len > 0) {
         //scanf(buffer, "%d", &value);
         sprintf(buf,"%d  %d\n", 2,256*buffer[1]+buffer[0]);
         ui->label->setText(QString(buf));
    } else {
         perror("read ADC device:error");
         return ;
    }
    usleep(500* 1000);
}

void TestBasic::on_Tb_Device3_clicked()
{
    ioctl(adc_fd,ADC_INPUT_PIN,3);
    char buffer[2];
    int adc_len = read(adc_fd, buffer, sizeof buffer -1);
    char buf[20];
    if (adc_len > 0) {
         //scanf(buffer, "%d", &value);
         sprintf(buf,"%d  %d\n", 3,256*buffer[1]+buffer[0]);
         ui->label->setText(QString(buf));
    } else {
         perror("read ADC device:error");
         return ;
    }
    usleep(500* 1000);
}

//int TestBasic::getch(void)
//{
//    struct termios oldt,newt;
//    int ch;
//    if(!isatty(STDIN_FILENO))
//    {
//        fprintf(stderr,"this problem should be run at a terminal\n");
////        return;
//        exit(1);
//    }
//    if(tcgetattr(STDIN_FILENO,&oldt)<0)
//    {
//        perror("save the terminal setting");
////        return;
//        exit(1);
//    }
//    //set terminal as need
//    newt=oldt;
//    newt.c_lflag &=~(ICANON | ECHO);
//    if( tcsetattr(STDIN_FILENO,TCSANOW,&newt)<0)
//    {
//        perror("set terminal");
////        return;
//        exit(1);
//    }
//    ch=getchar();
//    //restore termial setting
//    if(tcsetattr(STDIN_FILENO,TCSANOW,&oldt)<0)
//    {
//        perror("restore termial setting");
////        return;
//        exit(1);
//    }
//    return ch;
//}


void TestBasic::on_Tb_SBF_clicked()
{
    int pwm_ret=ioctl(pwm_fd,PWM_IOCTL_SET_FREQ, freq);
    if(pwm_ret <0 )
    {
        QMessageBox::warning(0,"Tip","Set the frequency of the buzzer");
        return;
    }
}

void TestBasic::stop_buzzer(void )
{
     int ret = ioctl(pwm_fd,PWM_IOCTL_STOP);
     if(ret < 0)
     {
         perror("stop the buzzer");
         return;
     }
     if(ioctl(pwm_fd,2)<0)
     {
         perror("ioctl 2:");
     }
}

void TestBasic::on_Tb_Add_clicked()
{
    if(freq <20000-50)
    {
        freq+=50;
        int pwm_ret=ioctl(pwm_fd,PWM_IOCTL_SET_FREQ, freq);
        if(pwm_ret <0 )
        {
            QMessageBox::warning(0,"Tip","Set the frequency of the buzzer");
            return;
        }
    }
}

void TestBasic::on_Tb_Reduce_clicked()
{
    if(freq >51)
    {
        freq-=50;
        int pwm_ret=ioctl(pwm_fd,PWM_IOCTL_SET_FREQ, freq);
        if(pwm_ret <0 )
        {
            QMessageBox::warning(0,"Tip","Set the frequency of the buzzer");
            return;
        }
    }
}

void TestBasic::on_Tb_Stop_clicked()
{
    stop_buzzer();
}


void TestBasic::adcTest()
{
    ioctl(adc_fd,ADC_INPUT_PIN,0);
    char buffer[2];
    int adc_len = read(adc_fd, buffer, sizeof buffer -1);
    char buf[20];
    if (adc_len > 0) {
         //scanf(buffer, "%d", &value);
         sprintf(buf,"%d  %d\n", 0,256*buffer[1]+buffer[0]);
         ui->label->setText("<font colot=green>"+QString(buf)+"</font>");
    } else {
         perror("read ADC device:error");
         return ;
    }
//    usleep(500* 1000);
}

void TestBasic::on_Cb_LED_clicked(bool checked)
{
    if(checked)
    {
        leds_fd=open("/dev/leds",O_RDONLY);
        if(leds_fd<=0)
        {
            QMessageBox::warning(0,trUtf8("提示"),"/dev/leds"+trUtf8("未打开"));
            return ;
         }
//        QMessageBox::warning(0,trUtf8("提示"),trUtf8("打开成功！"));
        ui->Cb_LED->setText("LED-ON");
        ui->st1->setPixmap(QPixmap(":/images/inteagri/31.png"));
    }
    else
    {
        ::close(leds_fd);
        ui->Cb_LED->setText("LED-OFF");
        ui->st1->setPixmap(QPixmap(":/images/inteagri/30.png"));
    }
}

void TestBasic::on_Cb_KEY_clicked(bool checked)
{
    if(checked)
    {
        keys_fd=open("/dev/keys",O_RDONLY);
        if(keys_fd<=0)
        {
            QMessageBox::warning(0,trUtf8("提示"),"/dev/keys"+trUtf8("未打开"));
            return;
        }
//        QMessageBox::warning(0,trUtf8("提示"),trUtf8("打开成功！"));
        ui->Cb_KEY->setText("KEY-ON");
        ui->st2->setPixmap(QPixmap(":/images/inteagri/31.png"));
        m_timer=new QTimer(this);
        connect(m_timer,SIGNAL(timeout()),this,SLOT(buttonTest()));
        m_timer->start(200);

    }
    else
    {
        ui->Cb_KEY->setText("KEY-OFF");
        ui->labelbutton->setText("");
        m_timer->stop();
        ui->st2->setPixmap(QPixmap(":/images/inteagri/30.png"));
        ::close(keys_fd);
    }
}

void TestBasic::on_Cb_ADC_clicked(bool checked)
{
    if(checked)
    {
        adc_fd=open("/dev/adc",0);
        if(adc_fd<0)
        {
            QMessageBox::warning(0,trUtf8("提示"),"/dev/adc"+trUtf8("未打开"));
            return;
        }
//        QMessageBox::warning(0,trUtf8("提示"),trUtf8("打开成功！"));
        ui->st3->setPixmap(QPixmap(":/images/inteagri/31.png"));
        ui->Cb_ADC->setText("ADC-ON");
        ui->label_3->setText("ADC Value:");
        adc_timer =new QTimer(this);
        connect(adc_timer,SIGNAL(timeout()),this,SLOT(adcTest()));
        adc_timer->start(1000);
    }
    else
    {
        ui->label_3->setText("");
        ui->label->setText("");
        ui->Cb_ADC->setText("ADC-OFF");
        ui->st3->setPixmap(QPixmap(":/images/inteagri/30.png"));
        ::close(adc_fd);
        adc_timer->stop();
    }

}


void TestBasic::on_Cb_PWM_clicked(bool checked)
{
    if(checked)
    {
        pwm_fd = open("/dev/pwm",0);
        if(pwm_fd<0)
        {
             QMessageBox::warning(0,trUtf8("提示"),"/dev/pwm"+trUtf8("未打开"));
             return;
        }
//        QMessageBox::warning(0,trUtf8("提示"),trUtf8("打开成功！"));
        ui->Cb_PWM->setText("PWM-ON");
        ui->st4->setPixmap(QPixmap(":/images/inteagri/31.png"));
        freq=1000;
    }
    else
    {
        ::close(pwm_fd);
        ui->Cb_PWM->setText("PWM-OFF");
        ui->st4->setPixmap(QPixmap(":/images/inteagri/30.png"));
    }
}

//void TestBasic::SpeedLed()
//{
//    nextled++;
//    switch(nextled)
//    {
//        case 1: ledControl(1);  break;
//        case 2: ledControl(2);  break;
//        case 3: ledControl(3);  break;
//        case 4: ledControl(4);  break;
//        case 5: ledControl(5);  break;
//        case 6: ledControl(6);  break;
//        case 7: ledControl(7);  break;
//        case 8: ledControl(8);  break;
//    }
//    if(nextled==8)
//        nextled=0;
//}

//void TestBasic::on_Tb_Speedled_clicked()
//{
//    if(ledstatus==false)
//    {
//        led_timer = new QTimer(this);
//        connect(led_timer,SIGNAL(timeout()),this,SLOT(SpeedLed()));
//        led_timer->start(1000);
//        ledstatus=true;
//    }
//    else
//    {
//        ledstatus=false;
//        led_timer->stop();
//    }

//}



void TestBasic::on_Pb_Link_clicked()
{
    if(linkLB==false)
    {
        linkLB=true;
        ui->Pb_Link->setText("ON");
    }
    else
    {
        linkLB=false;
        ui->Pb_Link->setText("OFF");
    }
}
