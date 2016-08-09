#ifndef CKEY_H
#define CKEY_H

#include <QWidget>
#include <QTextEdit>

namespace Ui {
class CKey;
}

class CKey : public QWidget
{
    Q_OBJECT
    
public:
    explicit CKey(QWidget *parent = 0);
    ~CKey();
    QWidget *parent;
    QTextEdit *m_text;
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
    Ui::CKey *ui;
};

#endif // CKEY_H
