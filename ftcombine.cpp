#include "ftcombine.h"
#include "ui_ftcombine.h"

FTCombine::FTCombine(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FTCombine)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);

    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start(1000);
//    resize(800,480);

   this->m_IHF=new InteHomeFurn();
   this->m_IST=new InteSandTable();
   this->m_IAC=new InteAgricul();
   this->m_ISF=new InteShelf();

    QPixmap pixmap(":/images/ftcombine/ftbackground.png");
    QPalette palette=this->palette();
    palette.setBrush(backgroundRole(),QBrush(pixmap));
    setPalette(palette);

    QPixmap pb1;
    pb1.load(":/images/ftcombine/ftbutton1.png");
    ui->PBInteHomeFurn->setIcon(pb1);
    ui->PBInteHomeFurn->setIconSize(pb1.size());
    ui->PBInteHomeFurn->setStyleSheet("QPushButton{border-radius:5px;border-width:0px;}");
    QPixmap pb2;
    pb2.load(":/images/ftcombine/ftbutton2.png");
    ui->PBInteShelf->setIcon(pb2);
    ui->PBInteShelf->setIconSize(pb2.size());
    ui->PBInteShelf->setStyleSheet("QPushButton{border-radius:5px;border-width:0px;}");
    QPixmap pb3;
    pb3.load(":/images/ftcombine/ftbutton3.png");
    ui->PBInteAgricul->setIcon(pb3);
    ui->PBInteAgricul->setIconSize(pb3.size());
    ui->PBInteAgricul->setStyleSheet("QPushButton{border-radius:5px;border-width:0px;}");
    QPixmap pb4;
    pb4.load(":/images/ftcombine/ftbutton4.png");
    ui->PBInteSandTable->setIcon(pb4);
    ui->PBInteSandTable->setIconSize(pb4.size());
    ui->PBInteSandTable->setStyleSheet("QPushButton{border-radius:5px;border-width:0px;}");
}
FTCombine::~FTCombine()
{
    delete ui;
}

void FTCombine::paintEvent(QPaintEvent *)
{
    QPainter m_pain(this);//定义一个画笔
    m_pain.setRenderHint(QPainter::Antialiasing);//开启反转
    m_pain.translate(150,150);

    draw(&m_pain);//开始画图片
}

void FTCombine::draw(QPainter *m_pain)
{
    static const QPoint hourHand[3]={    //定义时针图像
        QPoint(7,8),QPoint(-7,8),QPoint(0,-40)
    };
    static const QPoint minuteHand[3]={    //定义分针图像
        QPoint(7,8),QPoint(-7,8),QPoint(0,-65)
    };
    static const QPoint secondHand[3]={    //定义秒针图像
        QPoint(3,4),QPoint(-3,4),QPoint(0,-85)
    };
    QColor hourColor(127,0,127);//定义时针的颜色
    QColor minuteColor(0,0,127,191);
    QColor secondColor(0,0,255);

    QDate myDate=QDate::currentDate();
    int year=myDate.year();
    int month=myDate.month();
    int day=myDate.day();
    int week=myDate.dayOfWeek();
    QString DateOfWeek=GetWeek(week);
    QString DateNowText=QString::number(year)+'-'+QString::number(month)+'-'+QString::number(day);
    ui->dateLabel->setText("<font color=black>"+DateNowText+"</font>");
    ui->weekLabel->setText("<font color=black>"+DateOfWeek+"</font>");

    QTime time =QTime::currentTime();  //获取当前时间
    m_pain->setPen(Qt::NoPen);  //画秒针所在位置
    m_pain->setBrush(secondColor);
    m_pain->save();
    m_pain->rotate(time.second()*6);  //360/60=6
    m_pain->drawConvexPolygon(secondHand,3);
    m_pain->restore();

    m_pain->setPen(Qt::NoPen);  //画时针所在位置
    m_pain->setBrush(hourColor);
    m_pain->save();
    m_pain->rotate(30.0 *  ((time.hour() + time.minute() / 60.0)));
    m_pain->drawConvexPolygon(secondHand,3);
    m_pain->restore();
    m_pain->setPen(hourColor);
    for(int i=0;i<12;++i)
    {
        m_pain->drawLine(88,0,96,0);
        m_pain->rotate(30.0);
    }
    m_pain->setPen(Qt::NoPen);
    m_pain->setBrush(minuteColor);
    m_pain->save();
    m_pain->rotate(6.0*(time.minute()+time.second()/60.0));
    m_pain->drawConvexPolygon(minuteHand,3);
    m_pain->restore();
    m_pain->setPen(minuteColor);
    for(int j=0;j<60;++j)
    {
        if(( j % 5 ) != 0)
        {
            m_pain->drawLine(92,0,96,0);
        }
        m_pain->rotate(6.0);
    }
}


QString FTCombine::GetWeek(int week)//星期
{
    QString temp;
    switch(week)
    {
    case 1:temp=trUtf8("星期一");break;
    case 2:temp=trUtf8("星期二");break;
    case 3:temp=trUtf8("星期三");break;
    case 4:temp=trUtf8("星期四");break;
    case 5:temp=trUtf8("星期五");break;
    case 6:temp=trUtf8("星期六");break;
    case 7:temp=trUtf8("星期天");break;
    }
    return temp;
}
//智能家居界面
void FTCombine::on_PBInteHomeFurn_clicked()
{
    this->m_IHF->show();
    this->m_IHF->parent=this;
    this->hide();
    this->m_IHF->m_timer->start(2000);
}
//智慧农业界面
void FTCombine::on_PBInteAgricul_clicked()
{
    this->m_IAC->show();
    this->m_IAC->parent=this;
    this->hide();
    this->m_IAC->m_timer->start(2000);
}
//智能货架界面
void FTCombine::on_PBInteShelf_clicked()
{
    this->m_ISF->show();
    this->m_ISF->parent=this;
    this->hide();
    this->m_ISF->m_timer->start(1000);
}
//基础测试界面
void FTCombine::on_PBInteSandTable_clicked()
{

    this->m_IST->show();
    this->m_IST->parent=this;
    this->hide();
}

//版本信息
void FTCombine::mousePressEvent(QMouseEvent *event)
{
    if (event->pos().x() > 500/*&& event->pos().x() < 490*/)
    {
        if(event->pos().y() > 410 /*&& event->pos().y() < 215*/)
        {
            QMessageBox message(QMessageBox::NoIcon,trUtf8("版本信息"),trUtf8("\t无锡泛太科技(CN).\nWuxi Fantai Technology Co,Ltd(EN).\n版本：五型柜_V 1.0.1版.\n地址：无锡新区坊前坊兴路19号\n电话：0510-88236212"));
            message.setIconPixmap(QPixmap(":/images/ftcombine/logo.png"));
            message.exec();
        }
    }
}


