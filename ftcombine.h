#ifndef FTCOMBINE_H
#define FTCOMBINE_H

//  InteHomeFurn  智能家居
//  InteAgricul       智慧农业
//  InteShelf         智能货架
//  InteSandTable 基础测试

#include <QWidget>
#include "intesandtable.h"
#include "inteagricul.h"
#include "inteshelf.h"
#include "intehomefurn.h"

namespace Ui {
class FTCombine;
}

class FTCombine : public QWidget
{
    Q_OBJECT
    
public:
    explicit FTCombine(QWidget *parent = 0);
    ~FTCombine();
    void paintEvent(QPaintEvent *);
    void draw(QPainter *m_pain);
    QString GetWeek(int);
   InteHomeFurn *m_IHF;
    InteSandTable *m_IST;
    InteAgricul *m_IAC;
    InteShelf *m_ISF;
public slots:
    void mousePressEvent(QMouseEvent * event);
private slots:
    void on_PBInteSandTable_clicked();
    void on_PBInteAgricul_clicked();
    void on_PBInteShelf_clicked();
    void on_PBInteHomeFurn_clicked();

private:
    Ui::FTCombine *ui;
};

#endif // FTCOMBINE_H
