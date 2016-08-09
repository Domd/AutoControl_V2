#include "czaosheng.h"
#include "ui_czaosheng.h"

CZaoSheng::CZaoSheng(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CZaoSheng)
{
    ui->setupUi(this);
}

CZaoSheng::~CZaoSheng()
{
    delete ui;
}
