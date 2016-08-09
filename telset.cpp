#include "telset.h"
#include "ui_telset.h"
#include "autocontrol_v2.h"

TelSet::TelSet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TelSet)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    m_control->whichdialog=10;
    istelinput=false;
    telinputtext=false;
    m_text=ui->textEdit;
    readtel();
}

TelSet::~TelSet()
{
    delete ui;
}

void TelSet::readtel()
{
   // for(int i=0;i<m_control->itelephonelength;i++)
    {
        ui->textEdit->setText(m_control->telnumber);
        qDebug()<<"PP"+m_control->telnumber;
//        ui->textEdit->setText(m_control->m_telstruct[i].telephone);
//        qDebug()<<"PP"+m_control->m_telstruct[i].telephone;
    }
}

void TelSet::on_pushButton_clicked()//确定
{
    if(ui->textEdit->toPlainText().length()!=11)
    {
        ui->label->setText(trUtf8("输入号码有误"));
        return;
    }
    QSqlQuery m_query(m_control->m_sql);
    m_query.prepare("insert into TelNumTable (number) values(:number)");

    m_query.bindValue(":number",ui->textEdit->toPlainText());
    qDebug()<<"DD"+ui->textEdit->toPlainText();
    bool ok=m_query.exec();
    if(ok==false)
    {
        ui->label->setText(trUtf8("添加表13错误。。"));
        return;
    }

    m_control->ReadTelNumber();
    readtel();
    ui->label->setText(trUtf8("添加OK"));
}

void TelSet::on_pushButton_2_clicked()
{
   //m_control->whichdialog=-1;
   this->parent->show();
   this->close();
}

void TelSet::on_textEdit_selectionChanged()
{
    if(istelinput==false)
    {
        m_input=new Input();
        m_input->show();

        istelinput=true;

        telinputtext=true;

    }
}
