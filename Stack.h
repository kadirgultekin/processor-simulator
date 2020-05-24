#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

template <class T>
class Stack {
    private:
        T stackList[2];
        int top;
    public:
        Stack();
        const int length = 2;
        void Push(const T& item);
        T Pop();
        T Peek() const;
        bool StackEmpty();
        bool StackFull();
};

template <class T>
Stack<T>::Stack() { // Constructor
    top = -1;
}

template <class T>
void Stack<T>::Push(const T& item) {
    if(top != length-1) {
        top++;
        stackList[top] = item;
    }
    else {
        cerr << "Stack overflow!" << endl;
        exit(1);
    }
}

template <class T>
T Stack<T>::Pop() {
    T temp;
    if(top == -1) {
        cerr << "Stack is empty!" << endl;
    }
    else {
        temp = stackList[top];
        top--;
        return temp;
    }
}

template <class T>
bool Stack<T>::StackEmpty() {
    if(top == -1)
        return true;
    else
        return false;
}

template <class T>
bool Stack<T>::StackFull() {
    if(top == length-1)
        return true;
    else
        return false;
}

template<class T>
T Stack<T>::Peek() const {
    return stackList[top];
}

#endif // STACK_H
