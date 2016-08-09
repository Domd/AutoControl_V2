#ifndef QTBFTHREAD_H
#define QTBFTHREAD_H

#include <QThread>


class QTbfThread : public QThread
{
    Q_OBJECT

public:
    explicit QTbfThread(QObject *parent = 0);

    char temp;
    int count;

private:
    void run();
signals:

public slots:

};

#endif // QTBFTHREAD_H
