#ifndef CURVE_H
#define CURVE_H

#include <QWidget>
#include "Queue.h"

template <class T>
class Queue;

class Curve : public QWidget
{
    Q_OBJECT
public:
    explicit Curve(QWidget *parent = 0);
    ~Curve();

    int init(int gridSize, int xGridNum, int yGridNum, int min, int max);
    void updateData(int value);

    void paintEvent(QPaintEvent *);

private:
    void drawGrid(void);
    void drawCurves(void);
    void unload(void);
    int getYPos(int value);
    int getYValue(int pos);
    int drawCelsius(int x, int y);

private:
    int m_gridSize;           // 网格大小(像素)

    int m_xGridNum;           // X轴网格数
    int m_yGridNum;           // Y轴网格数

    int m_unitY;              // Y轴单位

    int m_minY;               // Y轴最小值
    int m_maxY;               // Y轴最大值

    int m_preValue;           // 上一次更新的值
    int m_curValue;           // 本次更新的值

    int m_viewWidth;          // 曲线图的逻辑宽度
    int m_viewHeight;         // 曲线图的逻辑高度

    int m_xPos;               // x轴当前坐标

    QImage* m_pImage;       // 曲线图句柄
    QPainter* m_pPainter;   // 画曲线图的Painter句柄
    typedef QPair<QPoint, QPoint> point;
    Queue <point>* m_queuePos;
};

#endif // CURVE_H
