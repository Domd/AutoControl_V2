#include "smartshelf.h"
#include "ui_smartshelf.h"
#include "autocontrol_v2.h"

smartshelf::smartshelf(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::smartshelf)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    m_control->whichdialog=12;
    this->setFont(QFont("tt",70));
    InitBackground();
    m_gbox1=ui->groupBox;
    m_gbox2=ui->groupBox_2;
    m_gbox3=ui->groupBox_3;
    m_gbox4=ui->groupBox_4;
    m_gbox5=ui->groupBox_5;
    m_gbox6=ui->groupBox_6;
    m_label1=ui->label;
    m_label2=ui->label_2;
    m_label3=ui->label_3;
    m_label4=ui->label_4;
    m_label5=ui->label_5;
    m_label6=ui->label_6;
    m_label7=ui->label_7;
    m_label8=ui->label_8;
    m_label9=ui->label_9;
    m_label10=ui->label_10;
    m_label11=ui->label_11;
    m_label12=ui->label_12;

}

smartshelf::~smartshelf()
{
    delete ui;
}

void smartshelf::on_pushButton_clicked()
{
    m_control->whichdialog=-1;
    this->parent->show();
    close();
}

void smartshelf::InitBackground()
{
    qDebug("11");
//    ui->groupBox->setStyleSheet("background-color: rgb(255, 255, 255);");
//    ui->groupBox->setStyleSheet("color:rgb(0, 0, 0);");
//    ui->groupBox->setFont(QFont("tt",50));
//    ui->groupBox_2->setStyleSheet("background-color: rgb(255, 255, 255);");
//    ui->groupBox_2->setStyleSheet("color:rgb(0, 0, 0);");
//    ui->groupBox_2->setFont(QFont("tt",50));
//    ui->groupBox_3->setStyleSheet("background-color: rgb(255, 255, 255);");
//    ui->groupBox_3->setStyleSheet("color:rgb(0, 0, 0);");
//    ui->groupBox_3->setFont(QFont("tt",50));
//    ui->groupBox_4->setStyleSheet("background-color: rgb(255, 255, 255);");
//    ui->groupBox_4->setStyleSheet("color:rgb(0, 0, 0);");
//    ui->groupBox_4->setFont(QFont("tt",50));
//    ui->groupBox_5->setStyleSheet("background-color: rgb(255, 255, 255);");
//    ui->groupBox_5->setStyleSheet("color:rgb(0, 0, 0);");
//    ui->groupBox_5->setFont(QFont("tt",50));
//    ui->groupBox_6->setStyleSheet("background-color: rgb(255, 255, 255);");
//    ui->groupBox_6->setStyleSheet("color:rgb(0, 0, 0);");
//    ui->groupBox_6->setFont(QFont("tt",50));

 //   ui->label->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->label->setPixmap(QPixmap(":/images/17.png"));
//    ui->label->setStyleSheet("color:rgb(0, 0, 0);");
//    ui->label->setFont(QFont("tt",50));
//    ui->label_2->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->label_2->setStyleSheet("color:rgb(255, 0, 0);");
    ui->label_2->setFont(QFont("tt",46));
//    ui->label_3->setStyleSheet("background-color: rgb(255, 255, 255);");
     ui->label_3->setPixmap(QPixmap(":/images/17.png"));
//    ui->label_3->setStyleSheet("color:rgb(0, 0, 0);");
//    ui->label_3->setFont(QFont("tt",50));
//    ui->label_4->setStyleSheet("background-color: rgb(255, 255, 255);");

    ui->label_4->setStyleSheet("color:rgb(255, 0, 0);");
    ui->label_4->setFont(QFont("tt",46));
//    ui->label_5->setStyleSheet("background-color: rgb(255, 255, 255);");
     ui->label_5->setPixmap(QPixmap(":/images/17.png"));
//    ui->label_5->setStyleSheet("color:rgb(0, 0, 0);");
//    ui->label_5->setFont(QFont("tt",50));
//    ui->label_6->setStyleSheet("background-color: rgb(255, 255, 255);");

    ui->label_6->setStyleSheet("color:rgb(255, 0, 0);");
    ui->label_6->setFont(QFont("tt",46));
//    ui->label_7->setStyleSheet("background-color: rgb(255, 255, 255);");
     ui->label_7->setPixmap(QPixmap(":/images/17.png"));
//    ui->label_7->setStyleSheet("color:rgb(0, 0, 0);");
//    ui->label_7->setFont(QFont("tt",50));
//    ui->label_8->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->label_8->setStyleSheet("color:rgb(255, 0, 0);");
    ui->label_8->setFont(QFont("tt",46));
//    ui->label_9->setStyleSheet("background-color: rgb(255, 255, 255);");
     ui->label_9->setPixmap(QPixmap(":/images/17.png"));
//    ui->label_9->setStyleSheet("color:rgb(0, 0, 0);");
//    ui->label_9->setFont(QFont("tt",50));
//    ui->label_10->setStyleSheet("background-color: rgb(255, 255, 255);");

    ui->label_10->setStyleSheet("color:rgb(255, 0, 0);");
    ui->label_10->setFont(QFont("tt",46));
//    ui->label_11->setStyleSheet("background-color: rgb(255, 255, 255);");
     ui->label_11->setPixmap(QPixmap(":/images/17.png"));
//    ui->label_11->setStyleSheet("color:rgb(0, 0, 0);");
//    ui->label_11->setFont(QFont("tt",50));
//    ui->label_12->setStyleSheet("background-color: rgb(255, 255, 255);");

    ui->label_12->setStyleSheet("color:rgb(255, 0, 0);");
    ui->label_12->setFont(QFont("tt",46));

//    ui->pushButton->setStyleSheet("background-color: rgb(255, 255, 255, 0);");
//    ui->pushButton->setStyleSheet("color:rgb(0, 0, 0);");
//    ui->pushButton->setFont(QFont("tt",50));
//    ui->pushButton_2->setStyleSheet("background-color: rgb(255, 255, 255, 0);");
//    ui->pushButton_2->setStyleSheet("color:rgb(0, 0, 0);");
//    ui->pushButton_2->setFont(QFont("tt",50));

    // qDebug("44");
}

void smartshelf::on_pushButton_2_clicked()
{
    m_control->whichdialog=13;
    this->hide();
    this->m_inshelf = new InShelf();
    this->m_inshelf->show();
    this->m_inshelf->parent = this;
    return;
}
