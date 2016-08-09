#include "testthreeg.h"
#include "ui_testthreeg.h"


TestThreeG::TestThreeG(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestThreeG)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    QPalette palette = this->palette();
    palette.setBrush(this->backgroundRole(),QBrush(QPixmap(":/images/150.png")));
    this->setPalette(palette);

    connect(ui->lineEdit,SIGNAL(selectionChanged()),this,SLOT(lineClick()));
    vKey = new VKey(this);
    ui->label->setScaledContents(true);
    ui->label->setPixmap(QPixmap(":/images/inteagri/30.png"));
}

TestThreeG::~TestThreeG()
{
    delete ui;

    delete vKey;
}



void TestThreeG::on_Tb_Back_clicked()
{
    this->parent->show();
    this->close();

}

void TestThreeG::on_Pb_Send_clicked()
{
    QString str1,str2;
    str1=ui->lineEdit->text();
    str2=str1+" > /tmp/tmp1 &";
    QByteArray byte = str2.toAscii();
    const char * command = byte.data();

    ::system(command);
    sleep(6);
    QFile pp("/tmp/tmp1");
    pp.open(QFile::ReadOnly);
    QString a = pp.readAll();
    ui->textEdit->setText(a);
}

void TestThreeG::on_Pb_on_clicked()
{
    ::system("evdo-on&");
    sleep(2);
    ui->label->setPixmap(QPixmap(":/images/inteagri/31.png"));
}

void TestThreeG::lineClick()
{
    disconnect(vKey,0,0,0);
    connect(vKey,SIGNAL(setvalue(const QString &)),ui->lineEdit,SLOT(setText(const QString &)));
    vKey->show();
}
