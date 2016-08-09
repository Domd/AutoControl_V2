#ifndef FTSHTLINE_H
#define FTSHTLINE_H

#include <QWidget>
#include "curve.h"

namespace Ui {
class FtShtLine;
}

class FtShtLine : public QWidget
{
    Q_OBJECT
    
public:
    explicit FtShtLine(QWidget *parent = 0);
    ~FtShtLine();

     void timerEvent(QTimerEvent *event);
private slots:
    void on_startButton_clicked();
    void on_stopButton_clicked();

private:
    Ui::FtShtLine *ui;

    Curve* m_pCurve;
    int timerId;
};

#endif // FTSHTLINE_H
