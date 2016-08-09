#ifndef CGUANGXIAN_H
#define CGUANGXIAN_H

#include <QWidget>
#include "input.h"
#include <QTextEdit>
#include <QTableWidget>

namespace Ui {
class CGuangXian;
}

class CGuangXian : public QWidget
{
    Q_OBJECT
    
public:
    explicit CGuangXian(QWidget *parent = 0);
    ~CGuangXian();
    QWidget *parent;
    Input *m_input;
    bool m_gxinput;
    bool m_isgxinput;
    QTextEdit *m_text;
    QTableWidget *m_table;
    void SelectGuanXianControl();
    void SelectGuanXianAddr();
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

    void on_textEdit_2_selectionChanged();

private:
    Ui::CGuangXian *ui;
};

#endif // CGUANGXIAN_H
