#ifndef CQITI_H
#define CQITI_H

#include <QWidget>

namespace Ui {
class CQiTi;
}

class CQiTi : public QWidget
{
    Q_OBJECT
    
public:
    explicit CQiTi(QWidget *parent = 0);
    ~CQiTi();
    QWidget *parent;
    void SelectGuanXianAddr();
    void SelectGuanXianControl();
    int tablerow1;
    int tablerow2;
    int tablerow3;
     void readtable();
private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_tableWidget_cellClicked(int row, int column);

    void on_tableWidget_2_cellClicked(int row, int column);

    void on_tableWidget_3_cellClicked(int row, int column);

private:
    Ui::CQiTi *ui;
};

#endif // CQITI_H
