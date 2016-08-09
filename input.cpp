#include "input.h"
#include "ui_input.h"
#include "autocontrol_v2.h"

Input::Input(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Input)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->move(300,210);
    this->setWindowFlags(windowFlags()|Qt::WindowStaysOnTopHint);
}

Input::~Input()
{
    delete ui;
}

void Input::on_pushButton_clicked()
{
    qDebug("77");
    switch(m_control->whichdialog)
    {
        case 7:
        {
            if(m_control->m_set->m_connectset->m_cguangxian->m_isgxinput==true)
            {

                m_control->m_set->m_connectset->m_cguangxian->m_text->setText(m_control->m_set->m_connectset->m_cguangxian->m_text->toPlainText()+"1");

            }
             break;
        }
        case 8:
        {
            if(m_control->m_set->m_connectset->m_wenshidu->m_bistext1==true)
            {
                m_control->m_set->m_connectset->m_wenshidu->m_text1->setText(m_control->m_set->m_connectset->m_wenshidu->m_text1->toPlainText()+"1");

            }
            if(m_control->m_set->m_connectset->m_wenshidu->m_bistext2==true)
            {
                m_control->m_set->m_connectset->m_wenshidu->m_text2->setText(m_control->m_set->m_connectset->m_wenshidu->m_text2->toPlainText()+"1");

            }
             break;
        }
        case 10:
        {
            if(m_control->m_set->m_telset->telinputtext==true)
            {
                m_control->m_set->m_telset->m_text->setText(m_control->m_set->m_telset->m_text->toPlainText()+"1");

            }
             break;
        }
        case 11:
        {
            if(m_control->m_set->m_timerfun->bistimerfuninput==true)
            {
                m_control->m_set->m_timerfun->m_text->setText(m_control->m_set->m_timerfun->m_text->toPlainText()+"1");
            }
             break;
        }
        default:
        {
            break;
        }
    }


}

void Input::on_pushButton_2_clicked()
{
    switch(m_control->whichdialog)
    {
        case 7:
        {
            if(m_control->m_set->m_connectset->m_cguangxian->m_isgxinput==true)
            {
                m_control->m_set->m_connectset->m_cguangxian->m_text->setText(m_control->m_set->m_connectset->m_cguangxian->m_text->toPlainText()+"2");
            }
             break;
        }
        case 8:
        {
            if(m_control->m_set->m_connectset->m_wenshidu->m_bistext1==true)
            {
                m_control->m_set->m_connectset->m_wenshidu->m_text1->setText(m_control->m_set->m_connectset->m_wenshidu->m_text1->toPlainText()+"2");
            }
            if(m_control->m_set->m_connectset->m_wenshidu->m_bistext2==true)
            {
                m_control->m_set->m_connectset->m_wenshidu->m_text2->setText(m_control->m_set->m_connectset->m_wenshidu->m_text2->toPlainText()+"2");
            }
             break;
        }
        case 10:
        {
            if(m_control->m_set->m_telset->telinputtext==true)
            {
                m_control->m_set->m_telset->m_text->setText(m_control->m_set->m_telset->m_text->toPlainText()+"2");

            }
             break;
        }
        case 11:
        {
            if(m_control->m_set->m_timerfun->bistimerfuninput==true)
            {
                m_control->m_set->m_timerfun->m_text->setText(m_control->m_set->m_timerfun->m_text->toPlainText()+"2");
            }
             break;
        }
        default:
        {
            break;
        }
    }


}

void Input::on_pushButton_3_clicked()
{
    switch(m_control->whichdialog)
    {
        case 7:
        {
            if(m_control->m_set->m_connectset->m_cguangxian->m_isgxinput==true)
            {
                m_control->m_set->m_connectset->m_cguangxian->m_text->setText(m_control->m_set->m_connectset->m_cguangxian->m_text->toPlainText()+"3");
            }
             break;
        }
        case 8:
        {

            if(m_control->m_set->m_connectset->m_wenshidu->m_bistext1==true)
            {
                m_control->m_set->m_connectset->m_wenshidu->m_text1->setText(m_control->m_set->m_connectset->m_wenshidu->m_text1->toPlainText()+"3");
            }
            if(m_control->m_set->m_connectset->m_wenshidu->m_bistext2==true)
            {
                m_control->m_set->m_connectset->m_wenshidu->m_text2->setText(m_control->m_set->m_connectset->m_wenshidu->m_text2->toPlainText()+"3");
            }
             break;
        }
        case 10:
        {
            if(m_control->m_set->m_telset->telinputtext==true)
            {
                m_control->m_set->m_telset->m_text->setText(m_control->m_set->m_telset->m_text->toPlainText()+"3");

            }
             break;
        }
        case 11:
        {
            if(m_control->m_set->m_timerfun->bistimerfuninput==true)
            {
                m_control->m_set->m_timerfun->m_text->setText(m_control->m_set->m_timerfun->m_text->toPlainText()+"3");
            }
             break;
        }
        default:
        {
            break;
        }
    }

}

void Input::on_pushButton_4_clicked()
{
    switch(m_control->whichdialog)
    {
        case 7:
        {
            if(m_control->m_set->m_connectset->m_cguangxian->m_isgxinput==true)
            {
                m_control->m_set->m_connectset->m_cguangxian->m_text->setText(m_control->m_set->m_connectset->m_cguangxian->m_text->toPlainText()+"4");
            }
             break;
        }
        case 8:
        {
            if(m_control->m_set->m_connectset->m_wenshidu->m_bistext1==true)
            {
                m_control->m_set->m_connectset->m_wenshidu->m_text1->setText(m_control->m_set->m_connectset->m_wenshidu->m_text1->toPlainText()+"4");
            }
            if(m_control->m_set->m_connectset->m_wenshidu->m_bistext2==true)
            {
                m_control->m_set->m_connectset->m_wenshidu->m_text2->setText(m_control->m_set->m_connectset->m_wenshidu->m_text2->toPlainText()+"4");
            }
             break;
        }
        case 10:
        {
            if(m_control->m_set->m_telset->telinputtext==true)
            {
                m_control->m_set->m_telset->m_text->setText(m_control->m_set->m_telset->m_text->toPlainText()+"4");

            }
             break;
        }
        case 11:
        {
            if(m_control->m_set->m_timerfun->bistimerfuninput==true)
            {
                m_control->m_set->m_timerfun->m_text->setText(m_control->m_set->m_timerfun->m_text->toPlainText()+"4");
            }
             break;
        }
        default:
        {
            break;
        }
    }


}

void Input::on_pushButton_5_clicked()
{
    switch(m_control->whichdialog)
    {
        case 7:
        {
            if(m_control->m_set->m_connectset->m_cguangxian->m_isgxinput==true)
            {
                m_control->m_set->m_connectset->m_cguangxian->m_text->setText(m_control->m_set->m_connectset->m_cguangxian->m_text->toPlainText()+"5");
            }
             break;
        }
        case 8:
        {
            if(m_control->m_set->m_connectset->m_wenshidu->m_bistext1==true)
            {
                m_control->m_set->m_connectset->m_wenshidu->m_text1->setText(m_control->m_set->m_connectset->m_wenshidu->m_text1->toPlainText()+"5");
            }
            if(m_control->m_set->m_connectset->m_wenshidu->m_bistext2==true)
            {
                m_control->m_set->m_connectset->m_wenshidu->m_text2->setText(m_control->m_set->m_connectset->m_wenshidu->m_text2->toPlainText()+"5");
            }
             break;
        }
        case 10:
        {
            if(m_control->m_set->m_telset->telinputtext==true)
            {
                m_control->m_set->m_telset->m_text->setText(m_control->m_set->m_telset->m_text->toPlainText()+"5");

            }
             break;
        }
        case 11:
        {
            if(m_control->m_set->m_timerfun->bistimerfuninput==true)
            {
                m_control->m_set->m_timerfun->m_text->setText(m_control->m_set->m_timerfun->m_text->toPlainText()+"5");
            }
             break;
        }
        default:
        {
            break;
        }
    }


}

void Input::on_pushButton_6_clicked()
{
    switch(m_control->whichdialog)
    {
        case 7:
        {
            if(m_control->m_set->m_connectset->m_cguangxian->m_isgxinput==true)
            {
                m_control->m_set->m_connectset->m_cguangxian->m_text->setText(m_control->m_set->m_connectset->m_cguangxian->m_text->toPlainText()+"6");
            }
             break;
        }
        case 8:
        {
            if(m_control->m_set->m_connectset->m_wenshidu->m_bistext1==true)
            {
                m_control->m_set->m_connectset->m_wenshidu->m_text1->setText(m_control->m_set->m_connectset->m_wenshidu->m_text1->toPlainText()+"6");
            }
            if(m_control->m_set->m_connectset->m_wenshidu->m_bistext2==true)
            {
                m_control->m_set->m_connectset->m_wenshidu->m_text2->setText(m_control->m_set->m_connectset->m_wenshidu->m_text2->toPlainText()+"6");
            }
             break;
        }
        case 10:
        {
            if(m_control->m_set->m_telset->telinputtext==true)
            {
                m_control->m_set->m_telset->m_text->setText(m_control->m_set->m_telset->m_text->toPlainText()+"6");

            }
             break;
        }
        case 11:
        {
            if(m_control->m_set->m_timerfun->bistimerfuninput==true)
            {
                m_control->m_set->m_timerfun->m_text->setText(m_control->m_set->m_timerfun->m_text->toPlainText()+"6");
            }
             break;
        }
        default:
        {
            break;
        }
    }


}

void Input::on_pushButton_7_clicked()
{
    switch(m_control->whichdialog)
    {
        case 7:
        {
            if(m_control->m_set->m_connectset->m_cguangxian->m_isgxinput==true)
            {
                m_control->m_set->m_connectset->m_cguangxian->m_text->setText(m_control->m_set->m_connectset->m_cguangxian->m_text->toPlainText()+"7");
            }
             break;
        }
        case 8:
        {
            if(m_control->m_set->m_connectset->m_wenshidu->m_bistext1==true)
            {
                m_control->m_set->m_connectset->m_wenshidu->m_text1->setText(m_control->m_set->m_connectset->m_wenshidu->m_text1->toPlainText()+"7");
            }
            if(m_control->m_set->m_connectset->m_wenshidu->m_bistext2==true)
            {
                m_control->m_set->m_connectset->m_wenshidu->m_text2->setText(m_control->m_set->m_connectset->m_wenshidu->m_text2->toPlainText()+"7");
            }
             break;
        }
        case 10:
        {
            if(m_control->m_set->m_telset->telinputtext==true)
            {
                m_control->m_set->m_telset->m_text->setText(m_control->m_set->m_telset->m_text->toPlainText()+"7");

            }
             break;
        }
        case 11:
        {
            if(m_control->m_set->m_timerfun->bistimerfuninput==true)
            {
                m_control->m_set->m_timerfun->m_text->setText(m_control->m_set->m_timerfun->m_text->toPlainText()+"7");
            }
             break;
        }
        default:
        {
            break;
        }
    }


}

void Input::on_pushButton_8_clicked()
{
    switch(m_control->whichdialog)
    {
        case 7:
        {
            if(m_control->m_set->m_connectset->m_cguangxian->m_isgxinput==true)
            {
                m_control->m_set->m_connectset->m_cguangxian->m_text->setText(m_control->m_set->m_connectset->m_cguangxian->m_text->toPlainText()+"8");
            }
             break;
        }
        case 8:
        {
            if(m_control->m_set->m_connectset->m_wenshidu->m_bistext1==true)
            {
                m_control->m_set->m_connectset->m_wenshidu->m_text1->setText(m_control->m_set->m_connectset->m_wenshidu->m_text1->toPlainText()+"8");
            }
            if(m_control->m_set->m_connectset->m_wenshidu->m_bistext2==true)
            {
                m_control->m_set->m_connectset->m_wenshidu->m_text2->setText(m_control->m_set->m_connectset->m_wenshidu->m_text2->toPlainText()+"8");
            }
             break;
        }
        case 10:
        {
            if(m_control->m_set->m_telset->telinputtext==true)
            {
                m_control->m_set->m_telset->m_text->setText(m_control->m_set->m_telset->m_text->toPlainText()+"8");

            }
             break;
        }
        case 11:
        {
            if(m_control->m_set->m_timerfun->bistimerfuninput==true)
            {
                m_control->m_set->m_timerfun->m_text->setText(m_control->m_set->m_timerfun->m_text->toPlainText()+"8");
            }
             break;
        }
        default:
        {
            break;
        }
    }


}

void Input::on_pushButton_9_clicked()
{
    switch(m_control->whichdialog)
    {
        case 7:
        {
            if(m_control->m_set->m_connectset->m_cguangxian->m_isgxinput==true)
            {
                m_control->m_set->m_connectset->m_cguangxian->m_text->setText(m_control->m_set->m_connectset->m_cguangxian->m_text->toPlainText()+"9");
            }
             break;
        }
        case 8:
        {
            if(m_control->m_set->m_connectset->m_wenshidu->m_bistext1==true)
            {
                m_control->m_set->m_connectset->m_wenshidu->m_text1->setText(m_control->m_set->m_connectset->m_wenshidu->m_text1->toPlainText()+"9");
            }
            if(m_control->m_set->m_connectset->m_wenshidu->m_bistext2==true)
            {
                m_control->m_set->m_connectset->m_wenshidu->m_text2->setText(m_control->m_set->m_connectset->m_wenshidu->m_text2->toPlainText()+"9");
            }
             break;
        }
        case 10:
        {
            if(m_control->m_set->m_telset->telinputtext==true)
            {
                m_control->m_set->m_telset->m_text->setText(m_control->m_set->m_telset->m_text->toPlainText()+"9");

            }
             break;
        }
        case 11:
        {
            if(m_control->m_set->m_timerfun->bistimerfuninput==true)
            {
                m_control->m_set->m_timerfun->m_text->setText(m_control->m_set->m_timerfun->m_text->toPlainText()+"9");
            }
             break;
        }
        default:
        {
            break;
        }
    }


}

void Input::on_pushButton_10_clicked()
{
    switch(m_control->whichdialog)
    {
        case 7:
        {
            if(m_control->m_set->m_connectset->m_cguangxian->m_isgxinput==true)
            {
                m_control->m_set->m_connectset->m_cguangxian->m_text->setText(m_control->m_set->m_connectset->m_cguangxian->m_text->toPlainText()+"0");
            }
             break;
        }
        case 8:
        {
            if(m_control->m_set->m_connectset->m_wenshidu->m_bistext1==true)
            {
                m_control->m_set->m_connectset->m_wenshidu->m_text1->setText(m_control->m_set->m_connectset->m_wenshidu->m_text1->toPlainText()+"0");
            }
            if(m_control->m_set->m_connectset->m_wenshidu->m_bistext2==true)
            {
                m_control->m_set->m_connectset->m_wenshidu->m_text2->setText(m_control->m_set->m_connectset->m_wenshidu->m_text2->toPlainText()+"0");
            }
             break;
        }
        case 10:
        {
            if(m_control->m_set->m_telset->telinputtext==true)
            {
                m_control->m_set->m_telset->m_text->setText(m_control->m_set->m_telset->m_text->toPlainText()+"0");

            }
             break;
        }
        case 11:
        {
            if(m_control->m_set->m_timerfun->bistimerfuninput==true)
            {
                m_control->m_set->m_timerfun->m_text->setText(m_control->m_set->m_timerfun->m_text->toPlainText()+"0");
            }
             break;
        }
        default:
        {
            break;
        }
    }


}

void Input::on_pushButton_11_clicked()
{
    switch(m_control->whichdialog)
    {
        case 7:
        {
            if(m_control->m_set->m_connectset->m_cguangxian->m_isgxinput==true)
            {
                m_control->m_set->m_connectset->m_cguangxian->m_text->setText(m_control->m_set->m_connectset->m_cguangxian->m_text->toPlainText()+".");
            }
             break;
        }
        case 8:
        {
            if(m_control->m_set->m_connectset->m_wenshidu->m_bistext1==true)
            {
                m_control->m_set->m_connectset->m_wenshidu->m_text1->setText(m_control->m_set->m_connectset->m_wenshidu->m_text1->toPlainText()+".");
            }
            if(m_control->m_set->m_connectset->m_wenshidu->m_bistext2==true)
            {
                m_control->m_set->m_connectset->m_wenshidu->m_text2->setText(m_control->m_set->m_connectset->m_wenshidu->m_text2->toPlainText()+".");
            }
             break;
        }
        case 10:
        {
            if(m_control->m_set->m_telset->telinputtext==true)
            {
                m_control->m_set->m_telset->m_text->setText(m_control->m_set->m_telset->m_text->toPlainText()+".");

            }
             break;
        }
        case 11:
        {
            if(m_control->m_set->m_timerfun->bistimerfuninput==true)
            {
                m_control->m_set->m_timerfun->m_text->setText(m_control->m_set->m_timerfun->m_text->toPlainText()+".");
            }
             break;
        }
        default:
        {
            break;
        }
    }


}

void Input::on_pushButton_13_clicked()
{
    switch(m_control->whichdialog)
    {
        case 7:
        {
            if(m_control->m_set->m_connectset->m_cguangxian->m_isgxinput==true)
            {
                m_control->m_set->m_connectset->m_cguangxian->m_text->setText("");
            }
             break;
        }
        case 8:
        {
            if(m_control->m_set->m_connectset->m_wenshidu->m_bistext1==true)
            {
                m_control->m_set->m_connectset->m_wenshidu->m_text1->setText("");
            }
            if(m_control->m_set->m_connectset->m_wenshidu->m_bistext2==true)
            {
                m_control->m_set->m_connectset->m_wenshidu->m_text2->setText("");
            }
             break;
        }
        case 10:
        {
            if(m_control->m_set->m_telset->telinputtext==true)
            {
                m_control->m_set->m_telset->m_text->setText("");

            }
             break;
        }
        case 11:
        {
            if(m_control->m_set->m_timerfun->bistimerfuninput==true)
            {
                m_control->m_set->m_timerfun->m_text->setText("");
            }
             break;
        }
        default:
        {
            break;
        }
    }


}

void Input::on_pushButton_12_clicked()
{
    switch(m_control->whichdialog)
    {
        case 7:
        {
            if(m_control->m_set->m_connectset->m_cguangxian->m_isgxinput==true)
            {
                m_control->m_set->m_connectset->m_cguangxian->m_gxinput=false;
                m_control->m_set->m_connectset->m_cguangxian->m_isgxinput=false;
                close();

            }
             break;
        }
        case 8:
        {
            if(m_control->m_set->m_connectset->m_wenshidu->m_bistext2==true)
            {
                m_control->m_set->m_connectset->m_wenshidu->m_bistext2=false;
                m_control->m_set->m_connectset->m_wenshidu->m_bistext1=false;
                m_control->m_set->m_connectset->m_wenshidu->m_biswenshiduinput=false;
                close();
            }
            if(m_control->m_set->m_connectset->m_wenshidu->m_bistext1==true)
            {
                m_control->m_set->m_connectset->m_wenshidu->m_bistext1=false;
                m_control->m_set->m_connectset->m_wenshidu->m_bistext2=false;
                m_control->m_set->m_connectset->m_wenshidu->m_biswenshiduinput=false;
                close();
            }
             break;
        }
        case 10:
        {
            if(m_control->m_set->m_telset->telinputtext==true)
            {
                m_control->m_set->m_telset->telinputtext=false;
                m_control->m_set->m_telset->istelinput=false;
                close();
            }
             break;
        }
        case 11:
        {
            if(m_control->m_set->m_timerfun->bistimerfuninput==true)
            {
               m_control->m_set->m_timerfun->bistimerfuninput=false;
               m_control->m_set->m_timerfun->btimerfuninput=false;
               close();
            }
             break;
        }
        default:
        {
            break;
        }
    }


}
