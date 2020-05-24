#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <string>

using namespace std;

template <class T>
class Queue
{
    private:
        int front;
        int rear;
        int count;
        T queueList[1000];

    public:
        Queue();
        const int length = 1000;
        void Insert(const T& item);
        T Delete();
        T QFront() const;
        int QueueLength();
        bool QueueEmpty();
        bool QueueFull();
};

template <class T>
Queue<T>::Queue(): front(0),rear(0),count(0) {}; // Constructor

template <class T>
void Queue<T>::Insert(const T& item) {
    if(count == length) {
        cerr << "Queue is full!" << endl;
        exit(1);
    }
    else {
        count++;
        queueList[rear] = item;
        rear = (rear+1)%length; // rear = 0, rear+1=1/1000 = 1. rear 1000, rear+1=1001/1000 = 1
    }
}

template <class T>
T Queue<T>::Delete() {
    T temp;
    if(count == 0) {
        cerr << "Queue is empty!" << endl;
    }
    else {
        count--;
        temp = queueList[front];
        front = (front+1)%length;
        return temp;
    }

}

template <class T>
int Queue<T>::QueueLength() {
    return length;
}

template <class T>
bool Queue<T>::QueueEmpty() {
    if(count == 0)
        return true;
    else
        return false;
}

template <class T>
bool Queue<T>::QueueFull() {
    if(count == length)
        return true;
    else
        return false;
}

template <class T>
T Queue<T>::QFront() const {
    return queueList[front];
}


#endif // QUEUE_H
