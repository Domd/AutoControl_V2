#include "testwifi.h"
#include "ui_testwifi.h"
#include <QMessageBox>

TestWifi::TestWifi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestWifi)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    QPalette palette = this->palette();
    palette.setBrush(this->backgroundRole(),QBrush(QPixmap(":/images/150.png")));
    this->setPalette(palette);

    tablerow=-1;
    ui->LePasswd->setVisible(false);
    ui->LbPasswd->setVisible(false);
    ui->LePasswd->setEchoMode(QLineEdit::Password);//暗码
    ui->LePasswd->setReadOnly(true);
    ui->LePasswd->setMaxLength(15);

    QStringList header;
    header<<trUtf8("序号")<<trUtf8("网络")<<trUtf8("状态");
    ui->tableWidget->setColumnCount(3);   //设置4列数据
    ui->tableWidget->setColumnWidth(0,0);
    ui->tableWidget->setColumnWidth(1,200);
    ui->tableWidget->setColumnWidth(2,100);
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //设置选择行为 ，以行为单位
//    ui->tableWidget->verticalHeader()->setVisible(false);     //隐藏列表头
    ui->tableWidget->horizontalHeader()->setVisible(false);  //隐藏行表头
    ui->tableWidget->setFrameShape(QFrame::NoFrame);  //设置边框 (不画任何东西)

    connect(ui->LePasswd,SIGNAL(selectionChanged()),this,SLOT(lineClick1()));
    connect(ui->lineEdit,SIGNAL(selectionChanged()),this,SLOT(lineClick2()));
    vKey=new VKey(this);
}

TestWifi::~TestWifi()
{
    delete ui;
    delete vKey;
}

void TestWifi::on_TbOpen_clicked()
{
    ::system("ifconfig eth1 up");
    QString info  = "";
       QList<QNetworkInterface>list=QNetworkInterface::allInterfaces();
       foreach(QNetworkInterface interface,list)
       {

           if (interface.name().compare("eth1")==0 )
           {
               info += "Device:" + interface.name()+"\n";
               info += "HardwareAddress:" + interface.hardwareAddress()+"\n";
               QList<QNetworkAddressEntry>entryList=interface.addressEntries();

               foreach(QNetworkAddressEntry entry,entryList)
               {
                   info += entry.ip().toString()+"\n";
                   info += entry.netmask().toString()+"\n";
                   info += entry.broadcast().toString()+"\n";
               }
               info += "\n";
           }
       }
    ui->textEdit->setText(info);
    return;
}

void TestWifi::on_TbScanning_clicked()
{
    ::system("iwlist eth1 scan > /tmp/tmp &");
    sleep(5);
    QFile pp("/tmp/tmp");
    pp.open(QFile::ReadOnly);
    QString a = pp.readAll();
    ui->textEdit->setText(a);
    QByteArray byte;
    byte=a.toAscii();
    int n=0;int k=-1;
    for(int i=0;i<byte.length();i++)
    {
        if(byte[i]=='C')
        {
            if(byte[i+1]=='e'&&byte[i+2]=='l'&&byte[i+3]=='l')
            {
                ssid.clear();
                n=0;k++;
            }
        }

        if(byte[i]=='E')
        {
            if(byte[i+1]=='S'&&byte[i+2]=='S'&&byte[i+3]=='I'&&byte[i+4]=='D'&&byte[i+5]==':')
            {
                for(int j=i+7;byte[j]!='"';j++)
                {
                    ssid[n++]=byte[j];
                }
                ssid[n]='\0';
                ui->tableWidget->setRowCount(k+1);
                ui->tableWidget->setItem(k,1,new QTableWidgetItem(QString(ssid)));
                ui->tableWidget->setItem(k,2,new QTableWidgetItem(QString(trUtf8("未加密"))));
                ui->tableWidget->setRowHeight(k,36);

            }
        }

        if(byte[i]=='I')
        {
            if(byte[i+1]=='E'&&byte[i+2]==':'&&byte[i+3]==' '&&byte[i+4]=='W'&&byte[i+5]=='P'&&byte[i+6]=='A')
            {
                ui->tableWidget->setItem(k,2,new QTableWidgetItem(QString(trUtf8("已加密"))));
            }
        }

    }
}

void TestWifi::on_TbConnect_clicked()
{
    if(tablerow<0)
    {
        QMessageBox::warning(0,"Tip",trUtf8("您未选择网络！！"));
        return;
    }
    QString str,str1,str2;
    str="iwconfig eth1 essid ";
    str1=str+'"'+ui->tableWidget->item(tablerow,1)->text()+'"';


//    QMessageBox::warning(0,"Tip",str1+'\n'+str2);

    QByteArray byte1 = str1.toAscii();
    const char * command1 = byte1.data();

    if(ui->tableWidget->item(tablerow,2)->text()==trUtf8("已加密"))
    {
        if(ui->LePasswd->text().length()<8)
        {
            QMessageBox::warning(0,trUtf8("提示"),trUtf8("WAP验证码必须大于等于8位！"));
            return;
        }
        QFile wpa2("/etc/wpa_supplicant.conf");
        wpa2.open(QFile::WriteOnly);
        str2="network={\n\tssid=\""+ui->tableWidget->item(tablerow,1)->text()+"\"\n\tpsk=\""+ui->LePasswd->text()+"\"\n}";
        QByteArray byte2 = str2.toAscii();
        const char * command2 = byte2.data();
        wpa2.write(command2);
        sleep(2);
        ::system("wpa_supplicant -B -ieth1 -c /etc/wpa_supplicant.conf > /tmp/tmp1 &");
    }
    else
        ::system(command1);
    sleep(5);
    ::system("iwconfig eth1 > /tmp/tmp2 &");
    sleep(1);
    QFile pp("/tmp/tmp2");
    pp.open(QFile::ReadOnly);
    QString a = pp.readAll();
    ui->textEdit->setText(a);
    QByteArray byte;
    QByteArray tempByte;
    int n=0;
    byte=a.toAscii();
    for(int i=0;i<byte.length();i++)   //取ESSID号
    {
        if(byte[i]=='E')
        {
            if(byte[i+1]=='S'&&byte[i+2]=='S'&&byte[i+3]=='I'&&byte[i+4]=='D'&&byte[i+5]==':')
            {
//                QMessageBox::warning(0,"Tip","success");
                for(int j=i+7;byte[j]!='"';j++)
                {
                    tempByte[n++]=byte[j];
                }
                tempByte[n]='\0';
                break;
            }
        }
    }
//    QMessageBox::warning(0,"Tip","tempByte"+QString(tempByte));
    if(QString::compare(ui->tableWidget->item(tablerow,1)->text(),QString(tempByte))==0)
    {
            QMessageBox::warning(0,"Tip",trUtf8("连接")+ui->tableWidget->item(tablerow,1)->text()+trUtf8("成功！"));
    }
    else
    {
        QMessageBox::warning(0,"Tip",trUtf8("连接")+ui->tableWidget->item(tablerow,1)->text()+trUtf8("失败！"));
        return;
    }
    ::system("udhcpc -ieth1");
    sleep(2);
    tablerow=-1;
}

void TestWifi::on_tableWidget_cellClicked(int row, int column)
{
    tablerow=row;
    if(ui->tableWidget->item(row,2)->text()==trUtf8("已加密"))
    {
        ui->LePasswd->setVisible(true);
        ui->LbPasswd->setVisible(true);
    }
    else
    {
        ui->LePasswd->setVisible(false);
        ui->LbPasswd->setVisible(false);
    }

}

void TestWifi::lineClick1()
{
    disconnect(vKey,0,0,0);
    connect(vKey,SIGNAL(setvalue(const QString &)),ui->LePasswd,SLOT(setText(const QString &)));
    vKey->show();
}
void TestWifi::lineClick2()
{
    disconnect(vKey,0,0,0);
    connect(vKey,SIGNAL(setvalue(const QString &)),ui->lineEdit,SLOT(setText(const QString &)));
    vKey->show();
}


void TestWifi::on_TbBack_clicked()
{
    this->close();
    this->parent->show();
}
//
void TestWifi::on_Pb_Send_clicked()
{
    QString str1,str2;
    str1=ui->lineEdit->text();
    str2=str1+" > /tmp/tmp1 &";
    QByteArray byte = str2.toAscii();
    const char * command = byte.data();

    ::system(command);
    sleep(10);
    QFile pp("/tmp/tmp1");
    pp.open(QFile::ReadOnly);
    QString a = pp.readAll();
    ui->textEdit->setText(a);
}

void TestWifi::on_Pb_Clear_clicked()
{
    ui->textEdit->clear();
}
