#ifndef QUEUE_H
#define QUEUE_H

// DO NOT CHANGE THIS FILE.

#include <iostream>

#include "QueueException.h"

#define CAPACITY 1000

template<class T>
class Queue {
public:
    Queue();

    bool isEmpty() const;
    bool isFull() const;
    int size() const;

    void enqueue(const T &item) throw(QueueException);
    T dequeue() throw(QueueException);
    T peek() const throw(QueueException);

    void print() const;

private:
    T items[CAPACITY];
    int front;
    int back;
    int count;
    int capacity;
};

template<class T>
Queue<T>::Queue() {
    front = 0;
    back = CAPACITY - 1;
    count = 0;
    capacity = CAPACITY;
}

template<class T>
bool Queue<T>::isEmpty() const {
    return count == 0;
}

template<class T>
bool Queue<T>::isFull() const {
    return count == capacity;
}

template<class T>
int Queue<T>::size() const {
    return count;
}

template<class T>
void Queue<T>::enqueue(const T &item) throw(QueueException) {
    if (isFull()) {
        // queue is full. return an exception.
        throw QueueException("QueueException: Queue is full! (Queue::enqueue)");
    } else {
        // queue is not full. insert the item.
        back = (back + 1) % capacity;
        items[back] = item;
        ++count;
    }
}

template<class T>
T Queue<T>::dequeue() throw(QueueException) {
    if (isEmpty()) {
        // queue is empty. return an exception.
        throw QueueException("QueueException: Queue is empty! (Queue::dequeue)");
    } else {
        // queue is not empty. remove the front item.
        T val = items[front];
        front = (front + 1) % capacity;
        --count;
        return val;
    }
}

template<class T>
T Queue<T>::peek() const throw(QueueException) {
    if (isEmpty()) {
        // queue is empty. return an exception.
        throw QueueException("QueueException: Queue is empty! (Queue::peek)");
    } else {
        // queue is not empty. return the front item.
        return items[front];
    }
}

template<class T>
void Queue<T>::print() const {
    if (isEmpty()) {
        // the queue is empty.
        std::cout << "Queue{}" << std::endl;
        return;
    }

    // the queue is not empty.

    std::cout << "Queue{" << std::endl;
    for (int i = 0; i < count; ++i) {
        std::cout << "\t" << items[(front + i) % capacity];
        if (i != (count - 1)) {
            std::cout << ",";
        }
        std::cout << std::endl;
    }
    std::cout << "}" << std::endl;
}

#endif //QUEUE_H

