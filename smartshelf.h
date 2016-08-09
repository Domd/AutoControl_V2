#ifndef SMARTSHELF_H
#define SMARTSHELF_H

#include <QWidget>
#include "inshelf.h"
#include <QGroupBox>
#include <QLabel>
namespace Ui {
class smartshelf;
}

class smartshelf : public QWidget
{
    Q_OBJECT
    
public:
    explicit smartshelf(QWidget *parent = 0);
    ~smartshelf();
    QWidget *parent;
    void InitBackground();
    InShelf *m_inshelf;
    QGroupBox *m_gbox1;
    QGroupBox *m_gbox2;
    QGroupBox *m_gbox3;
    QGroupBox *m_gbox4;
    QGroupBox *m_gbox5;
    QGroupBox *m_gbox6;
    QLabel *m_label1;
    QLabel *m_label2;
    QLabel *m_label3;
    QLabel *m_label4;
    QLabel *m_label5;
    QLabel *m_label6;
    QLabel *m_label7;
    QLabel *m_label8;
    QLabel *m_label9;
    QLabel *m_label10;
    QLabel *m_label11;
    QLabel *m_label12;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::smartshelf *ui;
};

#endif // SMARTSHELF_H
