#ifndef ZHIWEN_H
#define ZHIWEN_H

#include <QWidget>
#include <QTableWidget>
#include <QLabel>

namespace Ui {
class ZhiWen;
}

class ZhiWen : public QWidget
{
    Q_OBJECT
    
public:
    explicit ZhiWen(QWidget *parent = 0);
    ~ZhiWen();
    int tablerow1;
    int tablerow2;
    QWidget *parent;
    void ReadSensortable();
    QString ZhiWenCutString(int itype,QString str);
    QTableWidget *m_table;
    QLabel *m_label;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_tableWidget_cellClicked(int row, int column);

    void on_tableWidget_2_cellClicked(int row, int column);

private:
    Ui::ZhiWen *ui;
};

#endif // ZHIWEN_H
