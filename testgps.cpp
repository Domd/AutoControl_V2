#include "testgps.h"
#include "ui_testgps.h"
#include <QMessageBox>

TestGps::TestGps(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestGps)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    QPalette palette = this->palette();
    palette.setBrush(this->backgroundRole(),QBrush(QPixmap(":/images/150.png")));
    this->setPalette(palette);

    gpsstatus=false;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(up_date()));

    ui->label_3->setScaledContents(true);
    ui->label_3->setPixmap(QPixmap(":/images/inteagri/30.png"));
}

TestGps::~TestGps()
{
    delete ui;

    ::close(fd);

    this->timer->stop();
    delete timer;
}

void TestGps::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

int TestGps::set_bound()
{
    int bound = ui->bound->currentText().toInt();
    QString dev = "/dev/" + ui->com->currentText();
    const char *dev_name = dev.toUtf8().constData();

    this->fd = open(dev_name, O_RDWR);
    if (fd < 0)
    {
        QMessageBox::warning(0,trUtf8("提示"),trUtf8("打开失败！"));
        qDebug() << "open error!";
        return -1;
    }

    struct termios newtio;

    if (bound == 4800)
    {
        newtio.c_cflag = B4800 | CRTSCTS | CS8 | CLOCAL | CREAD;/*ctrol flag*/
    }
    else
    {
        newtio.c_cflag = B9600 | CRTSCTS | CS8 | CLOCAL | CREAD;/*ctrol flag*/
    }
    newtio.c_iflag = IGNPAR; /*input flag*/
    newtio.c_oflag = 0;		/*output flag*/
    newtio.c_lflag = 0;
    newtio.c_cc[VMIN]=1;
    newtio.c_cc[VTIME]=0;
/* now clean the modem line and activate the settings for modem */
    tcflush(fd, TCIFLUSH);
    tcsetattr(fd,TCSANOW,&newtio);/*set attrib	  */

    return 1;
}

void TestGps::up_date()
{
    GPS_INFO GPS;

    int i=0;
    int j=0;
    char c;
    char buf[1024];

    while(1){
    read(fd,&c,1); /* com port */
            buf[i++] = c;
            j++;
                    if(c == '\n' ){
                        strncpy(GPS_BUF,buf,i);
                        i=0;
                        j=0;
                        break;
                    }
           if (j>1024)
           {
               ui->text->setText("该波特率不能读出数据");
               timer->stop();
               break;
           }
           }
    gps_parse(GPS_BUF, &GPS);

    if ( GPS.D.year > 1900 && GPS.D.year < 2100)
    {
        QString date = QString("%1-%2-%3").arg(GPS.D.year).arg(GPS.D.month).arg(GPS.D.day);
        QString time = QString("%1-%2-%3").arg(GPS.D.hour).arg(GPS.D.minute).arg(GPS.D.second);
        QString Latitude = QString("%1 %2").arg(GPS.latitude).arg(GPS.NS);          //纬度
        QString Longtitude = QString("%1 %2").arg(GPS.longitude).arg(GPS.EW);   //经度
        QString high = QString("%1").arg(GPS.high);
        QString status = QString("%1").arg(GPS.status);

        QString text = trUtf8("日期:  ") + date +
                          trUtf8("\n时间:  ") + time +
                          trUtf8("\n纬度:  ") + Latitude +
                          trUtf8("\n经度:  ") + Longtitude +
                          trUtf8("\n高度:  ") + high +
                          trUtf8("\n状态:  ") + status;

        ui->text->setText(text + "\n\n\n" + ui->text->toPlainText() );
    }
}

void TestGps::on_start_clicked()
{
    if(gpsstatus==false)
    {
        int ret=this->set_bound();
        if(ret < 0)
        {
            QMessageBox::warning(0,trUtf8("提示"),trUtf8("打开失败"));
            return;
        }
        this->timer->start(1000);
        gpsstatus=true;
        ui->start->setText("Close");
        ui->label_3->setPixmap(QPixmap(":/images/inteagri/31.png"));
    }
    else
    {
        ::close(fd);
        ui->start->setText("Start");
        ui->label_3->setPixmap(QPixmap(":/images/inteagri/30.png"));
        gpsstatus=false;
    }
}

void TestGps::on_close_clicked()
{
    ::close(fd);
    this->close();
    this->parent->show();
}

void TestGps::on_clear_clicked()
{
    ui->text->clear();
}
