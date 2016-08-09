#ifndef CZAOSHENG_H
#define CZAOSHENG_H

#include <QWidget>

namespace Ui {
class CZaoSheng;
}

class CZaoSheng : public QWidget
{
    Q_OBJECT
    
public:
    explicit CZaoSheng(QWidget *parent = 0);
    ~CZaoSheng();
    
private:
    Ui::CZaoSheng *ui;
};

#endif // CZAOSHENG_H
