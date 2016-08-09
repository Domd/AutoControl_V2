#ifndef INSHELF_H
#define INSHELF_H

#include <QWidget>
#include <QTextEdit>

namespace Ui {
class InShelf;
}

class InShelf : public QWidget
{
    Q_OBJECT
    
public:
    explicit InShelf(QWidget *parent = 0);
    ~InShelf();
    QWidget *parent;
    void ReadShevlesTable();
    int tablerow;
    QTextEdit *m_text;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_tableWidget_cellClicked(int row, int column);

private:
    Ui::InShelf *ui;
};

#endif // INSHELF_H
