#ifndef INTESHELF_H
#define INTESHELF_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QTimer>

#include "adddevice.h"

namespace Ui {
class InteShelf;
}

class InteShelf : public QWidget
{
    Q_OBJECT
    
public:
    explicit InteShelf(QWidget *parent = 0);
    ~InteShelf();
    QWidget *parent;
    void ReadShevlesTable();
    int tablerow;
    QTimer *m_timer;

    AddDevice *m_add;
private slots:
    void on_mainpageTW_clicked();
    void on_huajiaTW_clicked();
    void on_bindingTW_clicked();
    void on_toolButton_clicked();
    void on_toolButton_2_clicked();
    void on_tableWidget_cellClicked(int row, int column);

    void cardData();
    void on_toolButton_3_clicked();

private:
    Ui::InteShelf *ui;
};

#endif // INTESHELF_H
