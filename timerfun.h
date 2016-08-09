#ifndef TIMERFUN_H
#define TIMERFUN_H

#include <QWidget>
#include "input.h"
#include <QTextEdit>

namespace Ui {
class TimerFun;
}

class TimerFun : public QWidget
{
    Q_OBJECT
    
public:
    explicit TimerFun(QWidget *parent = 0);
    ~TimerFun();
    void SelectDev();
    Input *m_input;
    bool btimerfuninput;
    bool bistimerfuninput;
    QWidget *parent;
    QTextEdit *m_text;
    int tablerow;
private slots:
    void on_textEdit_selectionChanged();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_tableWidget_cellClicked(int row, int column);

private:
    Ui::TimerFun *ui;
};

#endif // TIMERFUN_H
