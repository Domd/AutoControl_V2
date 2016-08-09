#ifndef CWENSHIDU_H
#define CWENSHIDU_H

#include <QWidget>
#include "input.h"
#include <QTextEdit>

namespace Ui {
class CWenShiDu;
}

class CWenShiDu : public QWidget
{
    Q_OBJECT
    
public:
    explicit CWenShiDu(QWidget *parent = 0);
    ~CWenShiDu();
    QWidget *parent;
    Input *m_input;
    bool m_biswenshiduinput;
    bool m_bistext1;
    bool m_bistext2;
    QTextEdit *m_text1;
    QTextEdit *m_text2;
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

    void on_textEdit_selectionChanged();

    void on_textEdit_2_selectionChanged();

    void on_tableWidget_cellClicked(int row, int column);

    void on_tableWidget_2_cellClicked(int row, int column);

    void on_tableWidget_3_cellClicked(int row, int column);

private:
    Ui::CWenShiDu *ui;
};

#endif // CWENSHIDU_H
