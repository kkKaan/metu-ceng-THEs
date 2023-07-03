#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template<class T>
class LinkedList {
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList<T> &obj);

    ~LinkedList();

    int getSize() const;
    bool isEmpty() const;
    bool contains(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void insertAtTheFront(const T &data);
    void insertAtTheEnd(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAsEveryKthNode(const T &data, int k);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeAllNodes();
    void removeEveryKthNode(int k);

    void swap(Node<T> *node1, Node<T> *node2);
    void shuffle(int seed);

    void print(bool reverse=false) const;

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    Node<T> *head;

    int size;
};


template<class T>
LinkedList<T>::LinkedList(): head(NULL), size(0)
{ }

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj) 
{
    /* TODO */
    
    this->head = NULL;
    this->size = 0;
    *this = obj;
}

template<class T>
LinkedList<T>::~LinkedList() 
{
    /* TODO */

    this->removeAllNodes();
    delete this->head;
}

template<class T>
int LinkedList<T>::getSize() const 
{
    /* TODO */
    
    return this->size;
}

template<class T>
bool LinkedList<T>::isEmpty() const 
{
    /* TODO */
    
    return this->head == NULL;
}

template<class T>
bool LinkedList<T>::contains(Node<T> *node) const  // Checks the given node is in the llist by its addresses.
{
    /* TODO */
    
    if(this->isEmpty()){return false;}

    Node<T>* curr = this->head;

    do
    {
        if(curr->data == node->data && curr->next == node->next && curr->prev == node->prev){return true;} 
        curr = curr->next;

    }while(curr != this->head);

    return false;
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const 
{
    /* TODO */

    return this->head;
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const 
{
    /* TODO */
    
    if(this->isEmpty()){return NULL;}

    return this->head->prev;
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const  // Returns a pointer to the node whose data is the argument.
{
    /* TODO */

    if(this->isEmpty()){return NULL;}

    Node<T>* curr = this->head;
    
    do
    {
        if(curr->data == data){return curr;} 
        curr = curr->next;

    }while(curr != this->head);

    return NULL;
}

template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const // Returns a pointer to the node in that index, if it is a valid one.
{
    /* TODO */

    if(this->isEmpty()){return NULL;}

    if(index < 0 || index >= this->size){return NULL;}

    Node<T>* curr = this->head;
    int a=0;

    do
    {
        if(a == index){return curr;}
        ++a; 
        curr = curr->next;

    }while(curr != this->head);
}

template<class T>
void LinkedList<T>::insertAtTheFront(const T &data) 
{
    /* TODO */
    
    Node<T>* newNode = new Node<T>(data);
    ++(this->size);

    if(this->isEmpty())
    {
        newNode->next = newNode;
        newNode->prev = newNode;
        this->head = newNode;
        return;
    }

    newNode->prev = this->head->prev;
    newNode->next = this->head;
    newNode->prev->next = newNode;
    newNode->next->prev = newNode;

    this->head = newNode; // The same as insert at the end except this line.
}

template<class T>
void LinkedList<T>::insertAtTheEnd(const T &data) 
{
    /* TODO */

    Node<T>* newNode = new Node<T>(data);
    ++(this->size);

    if(this->isEmpty())
    {
        newNode->next = newNode;
        newNode->prev = newNode;
        this->head = newNode;
        return;
    }

    newNode->prev = this->head->prev;
    newNode->next = this->head;
    newNode->prev->next = newNode;
    newNode->next->prev = newNode; 
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node) 
{
    /* TODO */

    if(this->isEmpty()){return;}

    Node<T>* curr = this->head;

    do
    {
        if(curr->data == node->data && curr->next == node->next && curr->prev == node->prev)
        {
            Node<T>* newNode = new Node<T>(data);
            newNode->prev = curr;
            newNode->next = curr->next;
            newNode->next->prev = newNode;
            newNode->prev->next = newNode;
            ++(this->size);
            return;
        }
        curr = curr->next;

    }while(curr != this->head); 
}

template<class T>
void LinkedList<T>::insertAsEveryKthNode(const T &data, int k) 
{
    /* TODO */

    if(k<2){return;}

    if(this->isEmpty()){return;}

    int a = 1; // Index variable
    Node<T> *curr = this->head;

    do
    {
        if(a == k)
        {
            insertAfterNode(data, curr->prev);
            a = 1;
        }
        ++a;
        curr = curr->next;

    }while(curr != this->head);

    if(a == k){insertAfterNode(data, curr->prev);}
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node) 
{
    /* TODO */

    if(this->isEmpty()){return;}

    Node<T>* curr = this->head;
    int a=0; // To check something if it's used for the first time.

    do
    {
        if(curr->data == node->data && curr->next == node->next && curr->prev == node->prev)
        {
            Node<T>* tmp = curr;

            if(this->size == 1)
            {
                delete tmp;
                tmp = NULL;
                this->head = NULL;
                --(this->size);
                return;
            }
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;

            curr = curr->next;
            if(!a){this->head = curr;}

            delete tmp;
            tmp = NULL;
            --(this->size);
            return;
        }
        curr = curr->next;
        ++a;

    }while(curr != this->head);
}

template<class T>
void LinkedList<T>::removeNode(const T &data) 
{
    /* TODO */

    if(this->isEmpty()){return;}

    Node<T>* curr = this->head;
    int a = 0; // To check something if it's used for the first time.
    bool change = false;
    
    do
    {
        if(curr->data == data)
        {
            Node<T>* tmp = curr;
            
            if(this->head->next == this->head)
            {
                this->head = NULL;
                this->size = 0;
                delete tmp;
                return;
            }

            if(!a)
            {
                curr = curr->next;
                ++a;
                change = true;
                continue;
            }
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;

            curr = curr->next;
            --(this->size);
            delete tmp;
            ++a;
            continue;
        }
        curr = curr->next;
        ++a;

    } while (curr != this->head);
    
    if(change)
    {
        if(this->head->next == this->head)
        {
            delete this->head;
            this->head = NULL;
            this->size = 0;
            return;
        }
        
        Node<T> *temp = this->head;
        
        this->head->prev->next = this->head->next;
        this->head->next->prev = this->head->prev;
        this->head = this->head->next;
        --(this->size);
        delete temp;
    }
}

template<class T>
void LinkedList<T>::removeAllNodes() 
{
    /* TODO */

    if(this->isEmpty()){return;}

    Node<T>* tmp;

    for(int a = 0; a < this->size; ++a)
    {
        tmp = this->head;
        this->head = this->head->next;
        delete tmp;
    }

    this->head = NULL;
    this->size = 0;
}

template<class T>
void LinkedList<T>::removeEveryKthNode(int k) 
{
    /* TODO */

    if(this->isEmpty()){return;}
    if(k<2){return;}

    int a=1;
    Node<T> *curr = this->head;

    do
    {
        if(a == k)
        {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;

            Node<T> *tmp = curr;
            curr = curr->next;
            delete tmp;
            tmp = NULL;

            --(this->size);
            a = 1;
            continue;
        }
        curr = curr->next;
        ++a;

    } while (curr != this->head);
}

template<class T>
void LinkedList<T>::swap(Node<T> *node1, Node<T> *node2) 
{
    /* TODO */

    if(this->isEmpty()){return;}

    Node<T>* p1 = this->head;
    int x=0, isItHereX=0;
    Node<T>* p2 = this->head;
    int y=0, isItHereY=0;

    do
    {
        if(p1->data == node1->data && p1->next == node1->next && p1->prev == node1->prev){++isItHereX; break;}
        p1 = p1->next;
        ++x;
    } while (p1 != this->head);
    
    if(!isItHereX){return;}

    do
    {
        if(p2->data == node2->data && p2->next == node2->next && p2->prev == node2->prev){++isItHereY; break;}
        p2 = p2->next;
        ++y;
    } while (p2 != this->head);

    if(!isItHereY){return;}

    if(y<x)
    {
        Node<T>* tmp = p1;
        int z = y;
        p1 = p2;
        p2 = tmp;
        y = x;
        x = z;
    }

    if(p1->next == p2 && p2->next == p1) // Only 2 of them in the list.
    {
        this->head = p2;
        return;
    }

    if(p1->prev == p2 && p2->next == p1) // p2 is the last element.
    {
        Node<T>* p1n = p1->next; 
        Node<T>* p2p = p2->prev;

        p1n->prev = p2;
        p2p->next = p1;
        p1->next = p2;
        p2->prev = p1;
        p1->prev = p2p;
        p2->next = p1n;

        this->head = p2; 
        return;
    }

    if(y-x == 1) // Only 1 element between them.
    {
        Node<T>* p1p = p1->prev; 
        Node<T>* p2n = p2->next;

        p1p->next = p2;
        p2n->prev = p1;
        p1->next = p2n;
        p2->prev = p1p;
        p1->prev = p2;
        p2->next = p1;

        if(!x){this->head = p2; return;}
    }

    else // Every other possibility.
    {
        Node<T>* p1p = p1->prev; 
        Node<T>* p2p = p2->prev;
        Node<T>* p1n = p1->next; 
        Node<T>* p2n = p2->next;

        p1p->next = p2;
        p1n->prev = p2;
        p2p->next = p1;
        p2n->prev = p1;
        p1->next = p2n;
        p1->prev = p2p;
        p2->next = p1n;
        p2->prev = p1p;

        if(!x){this->head = p2; return;}
    }

}

template<class T>
void LinkedList<T>::shuffle(int seed) 
{
    /* TODO */

    for(int a=0; a < this->size; ++a)
    {
        int index = (a*a + seed) % (this->size);
        int i = 0;
        Node<T>* nd1 = this->head;
        Node<T>* nd2 = this->head;

        do
        {
            if(i == a){break;}
            nd1 = nd1->next;
            ++i;
        } while (nd1 != this->head);

        i = 0;

        do
        {
            if(i == index){break;}
            nd2 = nd2->next;
            ++i;
        } while (nd2 != this->head);
        
        this->swap(nd1,nd2);
    }
}

template<class T>
void LinkedList<T>::print(bool reverse) const {
    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    if (reverse) {
        // traverse in reverse order (last node to first node).

        Node<T> *node = this->getLastNode();

        do {
            std::cout << *node << std::endl;
            node = node->prev;
        }
        while (node != this->getLastNode());
    } else {
        // traverse in normal order (first node to last node).

        Node<T> *node = this->getFirstNode();

        do {
            std::cout << *node << std::endl;
            node = node->next;
        }
        while (node != this->getFirstNode());
    }
}


template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs) 
{
    /* TODO */

    if(this != &rhs)
    {
        removeAllNodes();
        this->size = rhs.size;

        if(!(rhs.head)){return *this;}
        
        Node<T> *cpy = rhs.head; 
        Node<T> *newNode = new Node<T>(cpy->data);
        this->head = newNode;
        this->head->next = this->head;
        this->head->prev = this->head;
        cpy = cpy->next;
        
        do
        {
            Node<T> *newN = new Node<T>(cpy->data);
            
            newNode->next = newN;    
            newN->prev = newNode;
            newN->next = this->head;
            this->head->prev = newN;
            
            cpy = cpy->next;
            newNode = newNode->next;

        } while (cpy != rhs.head);
    }

    return *this;
}

#endif //LINKEDLIST_H
