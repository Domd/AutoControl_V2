#ifndef CSMOG_H
#define CSMOG_H

#include <QWidget>

namespace Ui {
class CSmog;
}

class CSmog : public QWidget
{
    Q_OBJECT
    
public:
    explicit CSmog(QWidget *parent = 0);
    ~CSmog();
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

    void on_tableWidget_2_cellClicked(int row, int column);

    void on_tableWidget_3_cellClicked(int row, int column);

private:
    Ui::CSmog *ui;
};

#endif // CSMOG_H
