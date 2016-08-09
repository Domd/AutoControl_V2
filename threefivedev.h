#ifndef THREEFIVEDEV_H
#define THREEFIVEDEV_H

#include <QWidget>
#include <QTableWidget>
#include <QTextEdit>
#include <QLabel>
#include "viewthreefivedevice.h"

namespace Ui {
class ThreeFiveDev;
}

class ThreeFiveDev : public QWidget
{
    Q_OBJECT
    
public:
    explicit ThreeFiveDev(QWidget *parent = 0);
    ~ThreeFiveDev();
    QWidget *parent;
    QTableWidget *m_table;
    QTextEdit *m_text;
    QLabel *label1;
    int tablerow1;
    ViewThreeFiveDevice *m_viewthreefivedevice;
private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_2_clicked();

    void on_tableWidget_cellClicked(int row, int column);

    void on_pushButton_4_clicked();

private:
    Ui::ThreeFiveDev *ui;
};

#endif // THREEFIVEDEV_H
