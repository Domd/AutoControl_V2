#ifndef QUEUE_H
#define QUEUE_H

template <class T>
class Queue
{
public:
    Queue( int size )
    {
        count = 0;
        maxsize = size;
        front = rear = 0;
        m_pBuff = new T[size];
    }
    void pop()
    {
        if( empty() )
            return;
        count--;
        front = (front+1) % maxsize;
    }
    void push(const T& tar)
    {
        if( full() )
            return;
        count++;
        m_pBuff[rear] = tar;
        rear = (rear+1) % maxsize;
    }
    const T& operator [] (const int& index)
    {
        return m_pBuff[ (front+index)%maxsize ];
    }

    bool empty() { return count==0; }
    bool full() { return count==maxsize; }

private:
    int count;
    int maxsize;
    int front;
    int rear;
    T* m_pBuff;
};

#endif // QUEUE_H
