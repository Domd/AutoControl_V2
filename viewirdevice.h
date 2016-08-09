#ifndef VIEWIRDEVICE_H
#define VIEWIRDEVICE_H

#include <QWidget>

namespace Ui {
class ViewIRDevice;
}

class ViewIRDevice : public QWidget
{
    Q_OBJECT
    
public:
    explicit ViewIRDevice(QWidget *parent = 0);
    ~ViewIRDevice();
    QWidget *parent;
    int tablerow1;
    void readirtable();
private slots:
    void on_pushButton_clicked();

    void on_tableWidget_cellClicked(int row, int column);

    void on_pushButton_2_clicked();

private:
    Ui::ViewIRDevice *ui;
};

#endif // VIEWIRDEVICE_H
