#include "curve.h"

#include <QPainter>
#include <QLabel>
#include <stdio.h>
//#include "queue"

Curve::Curve(QWidget *parent) :
    QWidget(parent)
{
    m_gridSize = 0;

    m_xGridNum = 0;
    m_yGridNum = 0;

    m_minY = 0;
    m_maxY = 0;

    m_preValue = 0;
    m_curValue = 0;

    m_viewWidth = 0;
    m_viewHeight = 0;

    m_xPos = 0;

    m_pImage = 0;
    m_pPainter = 0;
}

Curve::~Curve()
{
    unload();
}

int Curve::getYPos(int value)
{
    return (m_viewHeight - (value - m_minY) * m_yGridNum  * m_gridSize / (m_maxY - m_minY));
}

int Curve::getYValue(int pos)
{
    return ((m_viewHeight - pos) * (m_maxY - m_minY) / (m_yGridNum  * m_gridSize) + m_minY);
}

void Curve::unload(void)
{
    if (m_pPainter)
    {
        delete m_pPainter;
        m_pPainter = 0;
    }

    if (m_pImage)
    {
        delete m_pImage;
        m_pImage = 0;
    }
}

void Curve::drawGrid(void)
{
    Q_ASSERT(m_pPainter);

    m_pPainter->setPen(Qt::darkGreen);

    // ����ֱ����
    for (int x = 0; x < m_viewWidth; x += m_gridSize)
    {
         m_pPainter->drawLine(x, 0, x, m_viewHeight);
    }

    // ��ˮƽ����
    for (int y = 0; y < m_viewHeight; y += m_gridSize)
    {
        m_pPainter->drawLine(0, y, m_viewWidth, y);
    }

    if (m_minY < 0)
    {
        // ����X���λ��
        int temp = getYPos(0);
        // �������û���
        QPen pen(Qt::green, 5);
        m_pPainter->setPen(pen);
        // ��X��
        m_pPainter->drawLine(0, temp, m_viewWidth, temp);
    }
}

int Curve::init(int gridSize, int xGridNum, int yGridNum, int min, int max)
{
    m_gridSize = gridSize;

    m_xGridNum = xGridNum;
    m_queuePos = new Queue<point>(xGridNum);
    m_yGridNum = yGridNum;

    if (min >= max)
    {
        return -1;
    }

    m_minY = min;
    m_maxY = max;

    m_viewWidth = m_xGridNum * m_gridSize;
    m_viewHeight = m_yGridNum * m_gridSize;

    m_preValue = getYPos(0);
    m_curValue = getYPos(0);

    m_pImage = new QImage(m_viewWidth, m_viewHeight, QImage::Format_RGB32);
    if (0 == m_pImage)
    {
        return -1;
    }

    m_pPainter = new QPainter;
    if (0 == m_pPainter)
    {
        unload();
        return -1;
    }
    m_pPainter->begin(m_pImage);
    m_pPainter->setBrush(Qt::white);//���û��Ʊ����ıʵ���ɫ
    m_pPainter->drawRect(0, 0, m_viewWidth, m_viewHeight);//���Ʊ���

    drawGrid();

    return 0;
}

void Curve::paintEvent(QPaintEvent *)
{
    int x = 20;
    int y = 20;

    QPainter paint(this);

    // ��ͼ
    paint.drawImage(x, y, *m_pImage, 0, 0, m_viewWidth, m_viewHeight);

    // ��Y������̶�
    int pos = getYPos(m_minY);
    int value  = m_minY;

    QFont font = paint.font();
    font.setBold(true);
    paint.setFont(font);

    for (int i = 0; i <= m_yGridNum; i+= 2)
    {
        QString str;
        str.sprintf("%d", value);
        QRectF rect(0, pos + y - m_gridSize, x, m_gridSize * 2);
        paint.drawText(rect , Qt::AlignRight | Qt::AlignVCenter, str);
        pos -= (m_gridSize * 2);
        value  = getYValue(pos);
    }
}

void Curve::updateData(int value)
{
    m_preValue = m_curValue;
    m_curValue = getYPos(value);

    drawCurves();

    this->update();
}

void Curve::drawCurves(void)
{
    int x1;

    if ((0 == m_pImage) || (0 == m_pPainter))
    {
        return;
    }

    x1 = m_xPos;
    m_xPos += m_gridSize;

    if (m_xPos > m_viewWidth) { // ���������󣬿��Բ��ö����ػ����ƶ�ͼƬ��������̬Ч�������õ���ǰ��

        m_pPainter->fillRect(0, 0, m_viewWidth, m_viewHeight, /*Qt::SolidPattern*/Qt::white);
        drawGrid();

        m_queuePos->pop();
        m_queuePos->push( qMakePair( QPoint(x1,m_preValue), QPoint(m_xPos,m_curValue) ) );

        // �������û���
        m_pPainter->setPen( QPen(Qt::blue) );

        int x1 = 0, x2 = 0;
        for( int i=0; i<m_xGridNum; i++)
        {
            QPoint a1 = (*m_queuePos)[i].first;
            QPoint b1 = (*m_queuePos)[i].second;
            x2 = x1 + b1.x()-a1.x();
            m_pPainter->drawLine(x1, a1.y(), x2, b1.y());
            x1 = x2;
        }
        m_xPos = m_viewWidth;
    }
    else
    {
        m_queuePos->push(  qMakePair( QPoint(x1,m_preValue), QPoint(m_xPos,m_curValue) ) );
        m_pPainter->setPen( QPen(Qt::blue) );
        m_pPainter->drawLine(x1, m_preValue, m_xPos, m_curValue);
    }
}
