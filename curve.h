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
    int m_gridSize;           // �����С(����)

    int m_xGridNum;           // X��������
    int m_yGridNum;           // Y��������

    int m_unitY;              // Y�ᵥλ

    int m_minY;               // Y����Сֵ
    int m_maxY;               // Y�����ֵ

    int m_preValue;           // ��һ�θ��µ�ֵ
    int m_curValue;           // ���θ��µ�ֵ

    int m_viewWidth;          // ����ͼ���߼����
    int m_viewHeight;         // ����ͼ���߼��߶�

    int m_xPos;               // x�ᵱǰ����

    QImage* m_pImage;       // ����ͼ���
    QPainter* m_pPainter;   // ������ͼ��Painter���
    typedef QPair<QPoint, QPoint> point;
    Queue <point>* m_queuePos;
};

#endif // CURVE_H
