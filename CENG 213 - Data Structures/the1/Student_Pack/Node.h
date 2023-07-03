#ifndef NODE_H
#define NODE_H

// DO NOT CHANGE THIS FILE.

#include <iostream>

template<class T>
class Node {
public:
    T data;
    Node<T> *prev;
    Node<T> *next;

    Node(T data) {
        this->data = data;
        this->prev = NULL;
        this->next = NULL;
    }

    Node(T data, Node<T> *prev, Node<T> *next) {
        this->data = data;
        this->prev = prev;
        this->next = next;
    }

    friend std::ostream &operator<<(std::ostream &os, const Node &node) {
        os << node.data;
        return os;
    }
};

#endif //NODE_H
