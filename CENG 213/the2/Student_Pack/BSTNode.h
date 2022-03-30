#ifndef BSTNODE_H
#define BSTNODE_H

// DO NOT CHANGE THIS FILE.

#include <ostream>

template<class T>
class BSTNode {
public:
    T data;
    BSTNode<T> *left;
    BSTNode<T> *right;

    BSTNode() {
        this->left = NULL;
        this->right = NULL;
    }

    BSTNode(T data, BSTNode<T> *left, BSTNode<T> *right) {
        this->data = data;
        this->left = left;
        this->right = right;
    }

    friend std::ostream &operator<<(std::ostream &os, const BSTNode &node) {
        os << node.data;
        return os;
    }
};

#endif //BSTNODE_H
