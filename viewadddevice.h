#ifndef VIEWADDDEVICE_H
#define VIEWADDDEVICE_H

#include <QWidget>
#include <QTableWidget>


namespace Ui {
class ViewAddDevice;
}

class ViewAddDevice : public QWidget
{
    Q_OBJECT
    
public:
    explicit ViewAddDevice(QWidget *parent = 0);
    ~ViewAddDevice();
    QWidget *parent;
    QTableWidget *m_table;
    int tablerow1;
    void ReadSensortable();
    void DeleteRowNum();

private slots:
    void on_tableWidget_cellClicked(int row, int column);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ViewAddDevice *ui;
};

#endif // VIEWADDDEVICE_H
