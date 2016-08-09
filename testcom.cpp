#include "testcom.h"
#include "ui_testcom.h"
#include <QMessageBox>


TestCom::TestCom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestCom)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    QPalette palette = this->palette();
    palette.setBrush(this->backgroundRole(),QBrush(QPixmap(":/images/150.png")));
    this->setPalette(palette);
    ui->TbSend->setEnabled(false);
    comNum=-1;ret=-1;portno=0;

    connect(ui->lineEdit,SIGNAL(selectionChanged()),this,SLOT(lineClick()));
    vKey=new VKey(this);
}

TestCom::~TestCom()
{
    delete ui;
    m_Com->close();
    delete m_Com;

    m_timer->stop();
    delete m_timer;

    delete vKey;
}
//返回
void TestCom::on_TbBack_clicked()
{
    this->close();
    this->parent->show();
}

void TestCom::on_TbOpen_clicked()
{
    if(comNum==0)
    {
        QFile f("/dev/ttySAC0");
        if (f.exists())
        {
            m_Com = new Posix_QextSerialPort("/dev/ttySAC0",QextSerialBase::Polling);//定义串口对象，指定串口名,使用查询方式
//            m_Com =  new Posix_QextSerialPort("/dev/ttySAC0",QextSerialBase::EventDriven);
            if (m_Com->open(QIODevice::ReadWrite))
            {
                ui->label->setText(trUtf8("串口1打开成功 波特率115200 "));
                m_Com->setBaudRate(BAUD115200);//波特率
                m_Com->setDataBits(DATA_8);
                m_Com->setParity(PAR_NONE);
                m_Com->setStopBits(STOP_1);
                m_Com->setFlowControl(FLOW_OFF);
                m_Com->setTimeout(500);
            }
            else
            {
                ui->label->setText(trUtf8("串口1打开失败！"));
                return;
            }
        }
        else
        {
            ui->label->setText(trUtf8("串口1不存在！"));
            return;
        }
    }
    else if(comNum==1)
    {
        QFile f("/dev/ttySAC1");
        if (f.exists())
        {
            m_Com = new Posix_QextSerialPort("/dev/ttySAC1",QextSerialBase::Polling);//定义串口对象，指定串口名,使用查询方式
//            m_Com =  new Posix_QextSerialPort("/dev/ttySAC1",QextSerialBase::EventDriven);
            if (m_Com->open(QIODevice::ReadWrite))
            {
                ui->label->setText(trUtf8("串口2打开成功 波特率115200 "));
                m_Com->setBaudRate(BAUD115200);//波特率
                m_Com->setDataBits(DATA_8);
                m_Com->setParity(PAR_NONE);
                m_Com->setStopBits(STOP_1);
                m_Com->setFlowControl(FLOW_OFF);
                m_Com->setTimeout(500);
            }
            else
            {
                ui->label->setText(trUtf8("串口2打开失败"));
                return;
            }
        }
        else
        {
            ui->label->setText(trUtf8("串口2不存在"));
            return;
        }
    }
    else if(comNum==2)
    {
        QFile f("/dev/ttySAC2");
        if (f.exists())
        {
            m_Com = new Posix_QextSerialPort("/dev/ttySAC2",QextSerialBase::Polling);//定义串口对象，指定串口名,使用查询方式
//            m_Com =  new Posix_QextSerialPort("/dev/ttySAC2",QextSerialBase::EventDriven);
            if (m_Com->open(QIODevice::ReadWrite))
            {
                ui->label->setText(trUtf8("串口3打开成功 波特率115200 "));
                m_Com->setBaudRate(BAUD115200);//波特率
                m_Com->setDataBits(DATA_8);
                m_Com->setParity(PAR_NONE);
                m_Com->setStopBits(STOP_1);
                m_Com->setFlowControl(FLOW_OFF);
                m_Com->setTimeout(500);
            }
            else
            {
                ui->label->setText(trUtf8("串口3打开失败"));
                return;
            }
        }
        else
        {
            ui->label->setText(trUtf8("串口3不存在"));
            return;
        }
    }
    else if(comNum==3)
    {
        QFile f("/dev/ttySAC3");
        if (f.exists())
        {
            m_Com = new Posix_QextSerialPort("/dev/ttySAC3",QextSerialBase::Polling);//定义串口对象，指定串口名,使用查询方式
//            m_Com =  new Posix_QextSerialPort("/dev/ttySAC3",QextSerialBase::EventDriven);
            if (m_Com->open(QIODevice::ReadWrite))
            {
                ui->label->setText(trUtf8("串口4打开成功 波特率115200 "));
                m_Com->setBaudRate(BAUD115200);//波特率
                m_Com->setDataBits(DATA_8);
                m_Com->setParity(PAR_NONE);
                m_Com->setStopBits(STOP_1);
                m_Com->setFlowControl(FLOW_OFF);
                m_Com->setTimeout(10);
            }
            else
            {
                ui->label->setText(trUtf8("串口4打开失败"));
                return;
            }
        }
        else
        {
            ui->label->setText(trUtf8("串口4不存在"));
            return;
        }
    }
    else
    {
        ui->label->setText(trUtf8("未选择串口号"));
        return;
    }
    ui->TbSend->setEnabled(true);
    m_timer=new QTimer(this);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(readData()));
    m_timer->start(100);
//    connect(m_Com,SIGNAL(readyRead()),this,SLOT(readData()));
}

void TestCom::on_RbCom0_clicked()
{
    comNum=0;
}

void TestCom::on_RbCom1_clicked()
{
    comNum=1;
}

void TestCom::on_RbCom2_clicked()
{
    comNum=2;
}

void TestCom::on_RbCom3_clicked()
{
    comNum=3;
}

void TestCom::on_TbSend_clicked()
{
//    QString str="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int iLen=m_Com->write(ui->lineEdit->text().toAscii());
    if(iLen>0)
    {
        ui->label->setText(trUtf8("数据发送成功！"));
        return;
    }
    ui->label->setText(trUtf8("数据发送失败！"));
}


void TestCom::on_TbClose_clicked()
{
    ui->TbSend->setEnabled(false);
    m_Com->close();
}

void TestCom::readData()
{

    qint64 n = m_Com->bytesAvailable();
    if(n>0)
    {
        QByteArray temp=m_Com->readAll();
        ui->textBrowser->insertPlainText(temp);

        if(temp[0]!='\0')
            ui->label->setText(trUtf8("成功接收数据！"));
    }
}

void TestCom::lineClick()
{
    disconnect(vKey,0,0,0);
    connect(vKey,SIGNAL(setvalue(const QString &)),ui->lineEdit,SLOT(setText(const QString &)));
    vKey->show();
}
