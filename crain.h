#ifndef CRAIN_H
#define CRAIN_H

#include <QWidget>

namespace Ui {
class CRain;
}

class CRain : public QWidget
{
    Q_OBJECT
    
public:
    explicit CRain(QWidget *parent = 0);
    ~CRain();
    QWidget *parent;
    void SelectGuanXianAddr();
    void SelectGuanXianControl();
    int tablerow1;
    int tablerow2;
    int tablerow3;
     void readtable();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_tableWidget_cellClicked(int row, int column);

    void on_tableWidget_3_cellClicked(int row, int column);

    void on_tableWidget_2_cellClicked(int row, int column);

private:
    Ui::CRain *ui;
};

#endif // CRAIN_H
