#include "button.h"
#include "vkey.h"


VKey::VKey(QWidget *parent)
    : QDialog(parent)
{
    waitingForOperand = true;

    display = new QLineEdit("");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);

    //数字
    for (int i = 0; i < NumDigitButtons; i++) {
        digitButtons[i] = createButton(QString::number(i), SLOT(digitClicked()));
    }



    Button *shiftButton = createButton(tr("shift"),SLOT(shiftClicked()));
    Button *spaceButton = createButton(tr("space"),SLOT(spaceClicked()));
    Button *addButton =  createButton(tr("+"),SLOT(addClicked()));
    Button *reduButton =  createButton(tr("-"),SLOT(reduClicked()));
    Button *equButton = createButton(tr("="),SLOT(equClicked()));
    Button *whyButton = createButton(tr("?"),SLOT(whyClicked()));

    Button *pointButton = createButton(tr("."), SLOT(pointClicked()));
    Button *changeSignButton = createButton(("\261"), SLOT(changeSignClicked()));
    Button *backspaceButton = createButton(trUtf8("退格"), SLOT(backspaceClicked()));
    Button *clearButton = createButton(trUtf8("清除"), SLOT(clear()));
    Button *enterButton = createButton(trUtf8("确认"), SLOT(enterClicked()));
    Button *closeButton = createButton(trUtf8("退出"), SLOT(closeClicked()));

    QLabel *lab=new QLabel;
    lab->setText(trUtf8("无锡泛太科技"));

    mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    mainLayout->addWidget(display, 0, 4, 1, 10);
    mainLayout->addWidget(spaceButton,4,3,1,4);
    mainLayout->addWidget(lab, 0, 1, 1, 4);
    mainLayout->addWidget(shiftButton, 4, 7, 1, 2);
    mainLayout->addWidget(addButton, 1, 12);
    mainLayout->addWidget(reduButton,2,12);
    mainLayout->addWidget(equButton,3,12);
    mainLayout->addWidget(whyButton,4,12);
    mainLayout->addWidget(backspaceButton, 1, 13);
    mainLayout->addWidget(clearButton, 2, 13);
    mainLayout->addWidget(enterButton, 3, 13);
    mainLayout->addWidget(closeButton, 4, 13);

    int row,column;
    for (int i = 1; i < NumDigitButtons; ++i)
    {
        int m=(i-1)/3; int n=(i-1)%3;
        if(m==0) row=1;
        else if(m==1) row=2;
        else if(m==2) row=3;

        if(n==0) column=1+8;
        else if(n==1) column=2+8;
        else if(n==2) column=3+8;
        mainLayout->addWidget(digitButtons[i], row, column);
    }

    capFlag=true; //大小写标志 当前为大写
    lettersFun(65);

    mainLayout->addWidget(digitButtons[0], 4, 9);
    mainLayout->addWidget(pointButton, 4, 10);
    mainLayout->addWidget(changeSignButton, 4, 11);

    setLayout(mainLayout);
    setWindowTitle(trUtf8("正在输入。。。"));
}


void VKey::lettersFun(char capital)
{
    //字母
    for(int i =  0; i < LettersButton ;i++){
        LetButton[i] = createButton(QString(capital+i),SLOT(letClicked()));
    }

    //字母加入
    int row,column;
    for (int i = 0; i <LettersButton ; i++)
    {
        int m=i/8;int n=i%8;
        if(m==0)  row = 1;
        else if(m==1) row=2;
        else if(m==2) row=3;
        else if(m==3) row=4;

        if(n==0) column = 1;
        else if(n==1) column = 2;
        else if(n==2) column = 3;
        else if(n==3) column = 4;
        else if(n==4) column = 5;
        else if(n==5) column = 6;
        else if(n==6) column = 7;
        else if(n==7) column = 8;

        mainLayout->addWidget(LetButton[i], row, column);
    }
}

VKey::~VKey()
{
    delete display;
    delete mainLayout;
}

void VKey::digitClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    int digitValue = clickedButton->text().toInt();
    if (display->text() == "0" && digitValue == 0)
        return;

    if (waitingForOperand) {
        display->clear();
        waitingForOperand = false;
    }

    display->setText(display->text() + QString::number(digitValue));
}

void VKey::letClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
//    char letValue = clickedButton->text().toAscii();
//    if (display->text() == "0" && letValue == 0)
//        return;
    if (waitingForOperand) {
        display->clear();
        waitingForOperand = false;
    }
    display->setText(display->text()+clickedButton->text());
}


void VKey::enterClicked()
{
    waitingForOperand = true;
    emit setvalue(display->text());
    display->clear();
    this->close();
}



void VKey::pointClicked()
{
    if (waitingForOperand)
        display->setText("0");
    if (!display->text().contains("."))
        display->setText(display->text() + tr("."));
    waitingForOperand = false;
}



void VKey::changeSignClicked()
{
    QString text = display->text();
    double value = text.toDouble();

    if (value > 0.0) {
        text.prepend(tr("-"));
    } else if (value < 0.0) {
        text.remove(0, 1);
    }
    display->setText(text);
}

void VKey::backspaceClicked()
{
    QString text = display->text();
    text.chop(1);
    if (text.isEmpty()) {
//        text = "0";
        waitingForOperand = true;
    }
    display->setText(text);
}

void VKey::clear()
{
    display->setText("");
    waitingForOperand = true;
}

void VKey::spaceClicked()
{
    display->setText(display->text()+" ");
}

void VKey::closeClicked()
{
    this->close();
}

void VKey::addClicked()
{
    display->setText(display->text()+"+");
}

void VKey::reduClicked()
{
    display->setText(display->text()+"-");
}

void VKey::equClicked()
{
    display->setText(display->text()+"=");
}

void VKey::whyClicked()
{
    display->setText(display->text()+"?");
}

void VKey::shiftClicked()
{
    if(capFlag)
    {
        lettersFun(97);
        capFlag=false;
    }
    else
    {
        lettersFun(65);
        capFlag=true;
    }
}


Button *VKey::createButton(const QString &text, const char *member)
{
    Button *button = new Button(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}



