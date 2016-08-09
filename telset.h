#ifndef TELSET_H
#define TELSET_H

#include <QWidget>
#include "input.h"
#include <QTextEdit>

namespace Ui {
class TelSet;
}

class TelSet : public QWidget
{
    Q_OBJECT
    
public:
    explicit TelSet(QWidget *parent = 0);
    ~TelSet();
    QWidget *parent;
    Input *m_input;
    bool istelinput;
    bool telinputtext;
    QTextEdit *m_text;
    void readtel();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_textEdit_selectionChanged();

private:
    Ui::TelSet *ui;
};

#endif // TELSET_H
