#include "testgprs.h"
#include "ui_testgprs.h"
#include <QMessageBox>
#include <QDebug>

TestGprs::TestGprs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestGprs)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    QPalette palette = this->palette();
    palette.setBrush(this->backgroundRole(),QBrush(QPixmap(":/images/150.png")));
    this->setPalette(palette);

    this->fd = open(DEV,O_RDWR);
    if(fd < 0)
    {
        QMessageBox::warning(0,trUtf8("提示"),trUtf8("接口打开失败"));
    }
    this->init_ttyS(); //初始化接口

    connect(ui->Le_PhoneNum,SIGNAL(selectionChanged()),this,SLOT(lineClick1()));
    connect(ui->lineEdit,SIGNAL(selectionChanged()),this,SLOT(lineClick2()));
    connect(ui->Le_Message,SIGNAL(selectionChanged()),this,SLOT(lineClick3()));
    connect(ui->Le_ATData,SIGNAL(selectionChanged()),this,SLOT(lineClick4()));
    vKey=new VKey(this);

}

TestGprs::~TestGprs()
{
    delete ui;
    delete vKey;

    ::close(fd);
}

void TestGprs::init_ttyS()
{
    struct termios options;
    bzero(&options, sizeof(options));

    cfsetispeed(&options, B115200);
    cfsetospeed(&options, B115200);

    options.c_cflag |= (CS8 | CREAD);
    options.c_iflag = IGNPAR;

    tcsetattr(this->fd, TCSANOW, &options);
}

void TestGprs::send_cmd(char *cmd)
{
    ssize_t ret;
    ret = write(this->fd,cmd,strlen(cmd));
    if(ret==-1)
    {
        QMessageBox::warning(0,trUtf8("提示"),trUtf8("写入数据错误！"));
        return;
    }
}

void TestGprs::read_data(char *data, int rcv_wait)
{
    int retval;
    fd_set rfds;
    struct timeval tv;

    int ret,pos;
    tv.tv_sec = rcv_wait;
    tv.tv_usec = 0;
    pos = 0;

    while(1)
    {
        FD_ZERO(&rfds);
        FD_SET(fd, &rfds);

        retval = select(this->fd+1, &rfds, NULL, NULL, &tv);
        if(retval == -1)
        {
            QMessageBox::warning(0,"Tip","Select() error.");
            break;
        }
        else if( retval )
        {

            ret = read(fd, data+pos ,2048 );
            pos +=ret;

            if( data[pos-2 ] == '\r' && data[pos-1] == '\n')
            {
                FD_ZERO(&rfds);
                FD_SET( fd, &rfds);

                retval = select(this->fd+1, &rfds, NULL, NULL, &tv);

                if(!retval ) break;
            }
        }
        else
        {
            QMessageBox::warning(0,"Tip","No Data .");
            break;
        }
    }
}

void TestGprs::on_Tb_Simple_clicked()
{
    char *data;
    data = (char *)malloc(2048);
    memset(data,'\0',2048);
    this->send_cmd("AT\r");
    this->read_data(data, RECEIVE_BUF_WAIT_1S);

    QString q = "AT \n";
    QString c = trUtf8("         简单测试\n");
    ui->line_data->setText(c+"Send:  "+q+"Receive:  "+data);

    ::free(data);
}

void TestGprs::on_Tb_Call_clicked()
{
    if (ui->Le_PhoneNum->text().length() < 11)
    {
        ui->line_data->setText("输入的电话号码错误。\n");
    }
    else
    {
        char *data;
        data = (char *)malloc(2048);
        memset(data, '\0', 2048);

        char send_buf[17];
        send_buf[0] = 'A';
        send_buf[1] = 'T';
        send_buf[2] = 'D';
        send_buf[16] = '\0';

        QByteArray qb = ui->Le_PhoneNum->text().toLatin1();

        int i;
        for (i = 0; i < 11; i++)
        {
            send_buf[i+3] = qb[i];
        }
        send_buf[14] = ';';
        send_buf[15] = '\r';

        this->send_cmd(send_buf);
        this->read_data(data, RECEIVE_BUF_WAIT_1S);

        QString c =trUtf8( "         电话测试\n");
        ui->line_data->setText(c+"Send:  "+data);

        ::free(data);
    }
}

void TestGprs::on_Tb_ReadID_clicked()
{
    char *data;
    data = (char *)malloc(2048);
    memset(data, '\0', 2048);

    this->send_cmd("AT+CCID\r");
    this->read_data(data, RECEIVE_BUF_WAIT_1S);

    QString q = "AT+CCID \n";
    QString c = trUtf8("         读取SIM卡ID号\n");
    ui->line_data->setText(c+"Send:  "+q+"Receive:  "+data);

    ::free(data);
}

void TestGprs::on_Tb_Signal_clicked()
{
    char *data_1;
    data_1 = (char *)malloc(248);
    memset(data_1, '\0', 248);

    char *data_2;
    data_2 = (char *)malloc(248);
    memset(data_2, '\0', 248);

    char *data_3;
    data_3 = (char *)malloc(248);
    memset(data_3, '\0', 248);

    char *data_4;
    data_4 = (char *)malloc(248);
    memset(data_4, '\0', 248);

    this->send_cmd("AT+CREG?\r");
    this->read_data(data_1, RECEIVE_BUF_WAIT_1S);

    this->send_cmd("AT+CGREG?\r");
    this->read_data(data_2, RECEIVE_BUF_WAIT_1S);

    this->send_cmd("AT+CSQ\r");
    this->read_data(data_3, RECEIVE_BUF_WAIT_1S);

    this->send_cmd("AT+COPS?\r");
    this->read_data(data_4, RECEIVE_BUF_WAIT_1S);

    QString c = trUtf8("          信号测试\n");
    QString q1 = "AT+CREG?\r";
    QString q2 = "AT+CGREG?\r";
    QString q3 = "AT+CSQ\r";
    QString q4 = "AT+COPS?\r";

    ui->line_data->setText(c + "Send: " + q1 + "Receive: " + data_1 +
                           "Send: " + q2 + "Receive: " + data_2 +
                           "Send: " + q3 + "Receive: " + data_3 +
                           "Send: " + q4 + "Receive: " + data_4);
    ::free(data_1);
    ::free(data_2);
    ::free(data_3);
    ::free(data_4);
}

void TestGprs::on_Tb_Message_clicked()
{
    // GSM_CONF_MESSAGE
//    ui->line_data->setText("");
    char *data;
    data = (char *)malloc(2048);
    memset(data, '\0', 2048);

    char *cmd_1 = "AT+CMGF=1\r";

    char cmd_center[30];
    memset(cmd_center, '\0', 30);

    cmd_center[0] = 'A';
    cmd_center[1] = 'T';
    cmd_center[2] = '+';
    cmd_center[3] = 'C';
    cmd_center[4] = 'S';
    cmd_center[5] = 'C';
    cmd_center[6] = 'A';
    cmd_center[7] = '=';
    cmd_center[8] = '"';
    cmd_center[9] = '+';
    cmd_center[10] = '8';
    cmd_center[11] = '6';

    QByteArray qb = ui->lineEdit->text().toLatin1();

    for (int i = 0; i < 11; i++)
    {
        cmd_center[i+12] = qb[i];
    }

    cmd_center[23] = '"';
    cmd_center[24] = '\r';

    this->send_cmd(cmd_1);
    this->read_data(data, RECEIVE_BUF_WAIT_1S);
    printf("%s\n",data);

    memset(data, '\0', 248);

    this->send_cmd(cmd_center);
    this->read_data(data, RECEIVE_BUF_WAIT_1S);
    printf("%s\n",data);

    /*  发送短信 */
    memset(data, '\0', 248);

    char cmd_m[30];
    memset(cmd_m, '\0', 30);
    strcat(cmd_m, "AT+CMGS=");
    cmd_m[8] = '"';

    QByteArray qp = ui->Le_PhoneNum->text().toLatin1();
    for (int i=0; i<11; i++)
    {
        cmd_m[i+9] = qp[i];
    }

    cmd_m[20] = '"';
    cmd_m[21] = '\r';
    cmd_m[22] = '\0';

    printf("%s\n",cmd_m);
    this->send_cmd(cmd_m);

    sleep(1);

    char msg[30];
    memset(msg, '\0', 30);
    QByteArray QbMess = ui->Le_Message->text().toLatin1();
    int j;
    for(j=0;j<QbMess.length() && j<=25 ; j++)
    {
        msg[j]=QbMess[j];
    }
//    strcat(msg, "Short message test");
    msg[j++] = 0x1A;
    msg[j++] = '\r';
    msg[j] = '\0';

    this->send_cmd(msg);
    this->read_data(data,RECEIVE_BUF_WAIT_5S);

    ui->line_data->setText(QString(data)+"SEND FINISH.");
}

void TestGprs::lineClick1()
{
    disconnect(vKey,0,0,0);
    connect(vKey,SIGNAL(setvalue(const QString &)),ui->Le_PhoneNum,SLOT(setText(const QString &)));
    vKey->show();
}
void TestGprs::lineClick2()
{
    disconnect(vKey,0,0,0);
    connect(vKey,SIGNAL(setvalue(const QString &)),ui->lineEdit,SLOT(setText(const QString &)));
    vKey->show();
}
void TestGprs::lineClick3()
{
    disconnect(vKey,0,0,0);
    connect(vKey,SIGNAL(setvalue(const QString &)),ui->Le_Message,SLOT(setText(const QString &)));
    vKey->show();
}
void TestGprs::lineClick4()
{
    disconnect(vKey,0,0,0);
    connect(vKey,SIGNAL(setvalue(const QString &)),ui->Le_ATData,SLOT(setText(const QString &)));
    vKey->show();
}

void TestGprs::on_Tb_Back_clicked()
{
    this->close();
    this->parent->show();
}

//直接发送AT指令
void TestGprs::on_Tb_Send_clicked()
{
    char *data1;
    data1 = (char *)malloc(248);
    memset(data1,'\0',248);

    char send_buf[30];
    memset(send_buf,'\0',30);
    QByteArray qb = ui->Le_ATData->text().toLatin1();
    int i;
    for (i = 0; i < qb.length(); i++)
    {
        send_buf[i] = qb[i];
    }
    send_buf[i++]='\r';
    send_buf[i]='\0';
    qDebug()<<send_buf;

    this->send_cmd(send_buf);
    this->read_data(data1, 2);
    ui->line_data->setText(trUtf8("      发送AT指令\n")+QString(data1));
    ::free(data1);
}

//void TestGprs::on_Tb_SMPH_clicked()
//{
//    char *data1;
//    data1 = (char *)malloc(248);
//    memset(data1,'\0',248);
//    char send_buf[30];
//    memset(send_buf,'\0',30);
//    QByteArray qb = ui->Le_mph->text().toLatin1();
//    int i;
//    for (i = 0; i < qb.length(); i++)
//    {
//        send_buf[i] = qb[i];
//    }
//    send_buf[i++]='\r';
//    send_buf[i]='\0';
//    qDebug()<<send_buf;
//    this->send_cmd(send_buf);
//    sleep(1);
//    char send_buf2[30];
//    memset(send_buf2,'\0',30);
//    QByteArray qb2 = ui->Le_mess->text().toLatin1();
//    int j;
//    for (j = 0; j < qb2.length(); j++)
//    {
//        send_buf2[j] = qb2[j];
//    }
//    send_buf2[j++]=0x1A;
//    send_buf2[j++]='\r';
//    send_buf2[j]='\0';
//    qDebug()<<send_buf2;
//    this->send_cmd(send_buf2);
//    this->read_data(data1, RECEIVE_BUF_WAIT_5S);
//    ui->line_data->setText(QString(data1));
//    ::free(data1);
//}


void TestGprs::on_Tb_Break_clicked()
{
    char *data;
    data = (char *)malloc(2048);
    memset(data,'\0',2048);
    this->send_cmd("ATH\r");
    this->read_data(data, RECEIVE_BUF_WAIT_1S);

    QString q = "ATH \n";
    QString c = trUtf8("         挂断电话\n");
    ui->line_data->setText(c+"Send:  "+q+"Receive:  "+data);

    ::free(data);
}
