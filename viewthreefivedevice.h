#ifndef VIEWTHREEFIVEDEVICE_H
#define VIEWTHREEFIVEDEVICE_H

#include <QWidget>

namespace Ui {
class ViewThreeFiveDevice;
}

class ViewThreeFiveDevice : public QWidget
{
    Q_OBJECT
    
public:
    explicit ViewThreeFiveDevice(QWidget *parent = 0);
    ~ViewThreeFiveDevice();
    int tablerow1;
    QWidget *parent;
    void ReadThreeFivetable();

private slots:
    void on_tableWidget_cellClicked(int row, int column);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ViewThreeFiveDevice *ui;
};

#endif // VIEWTHREEFIVEDEVICE_H
