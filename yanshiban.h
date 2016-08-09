#ifndef YANSHIBAN_H
#define YANSHIBAN_H

#include <QWidget>

namespace Ui {
class YanShiBan;
}

class YanShiBan : public QWidget
{
    Q_OBJECT
    
public:
    explicit YanShiBan(QWidget *parent = 0);
    ~YanShiBan();
    QWidget *parent;
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

private:
    Ui::YanShiBan *ui;
};

#endif // YANSHIBAN_H
