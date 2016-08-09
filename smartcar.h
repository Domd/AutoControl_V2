#ifndef SMARTCAR_H
#define SMARTCAR_H

#include <QWidget>

namespace Ui {
class SmartCar;
}

class SmartCar : public QWidget
{
    Q_OBJECT
    
public:
    explicit SmartCar(QWidget *parent = 0);
    ~SmartCar();
    QWidget *parent;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::SmartCar *ui;
};

#endif // SMARTCAR_H
