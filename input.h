#ifndef INPUT_H
#define INPUT_H

#include <QWidget>

namespace Ui {
class Input;
}

class Input : public QWidget
{
    Q_OBJECT
    
public:
    explicit Input(QWidget *parent = 0);
    ~Input();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_12_clicked();

private:
    Ui::Input *ui;
};

#endif // INPUT_H
