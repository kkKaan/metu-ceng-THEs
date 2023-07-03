#ifndef BST_H
#define BST_H

#include <iostream>

#include "BSTNode.h"

enum TraversalPlan {preorder, inorder, postorder};

template<class T>
class BST {
public: // DO NOT CHANGE THIS PART.
    BST();
    BST(const BST<T> &obj);

    ~BST();

    BSTNode<T> *getRoot() const;
    bool isEmpty() const;
    bool contains(BSTNode<T> *node) const;

    void insert(const T &data);

    void remove(const T &data);
    void removeAllNodes();

    BSTNode<T> *search(const T &data) const;
    BSTNode<T> *getSuccessor(BSTNode<T> *node, TraversalPlan tp) const;

    void print(TraversalPlan tp=inorder) const;

    BST<T> &operator=(const BST<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void print(BSTNode<T> *node, TraversalPlan tp) const;
    void insertRec(BSTNode<T> *rooty, const T &data);
    void removeRec(BSTNode<T> *rooty, const T &data);
    void clearRec(BSTNode<T> *rooty);
    bool containsRec(BSTNode<T> *root, BSTNode<T> *node) const;
    BSTNode<T> *searchRec(BSTNode<T> *rooty, const T &data) const;
    BSTNode<T> *findMax(BSTNode<T> *rooty) const;
    BSTNode<T> *findMin(BSTNode<T> *rooty) const;
    BSTNode<T> *findParentNode(BSTNode<T> *rooty, BSTNode<T> *node) const;
    void travRec(BSTNode<T> *rhsRooty);
    
private: // DO NOT CHANGE THIS PART.
    BSTNode<T> *root;
};

#endif //BST_H

template<class T>
BST<T>::BST(): root(NULL) 
{}

template<class T>
BST<T>::BST(const BST<T> &obj) 
{
    /* TODO */
    this->root = NULL;
    *this = obj;
}

template<class T>
BST<T>::~BST() 
{
    /* TODO */
    removeAllNodes();
}

template<class T>
BSTNode<T> *BST<T>::getRoot() const 
{
    /* TODO */
    return root;
}

template<class T>
bool BST<T>::isEmpty() const 
{
    /* TODO */
    return root == NULL;
}

template<class T>
bool BST<T>::containsRec(BSTNode<T> *rooty, BSTNode<T> *node) const
{
    if(!(rooty == NULL))
    {
        if(rooty->data == node->data && rooty->left == node->left && rooty->right == node->right){return true;}
        else if(rooty->data > node->data){return containsRec(rooty->left, node);}
        else if(rooty->data < node->data){return containsRec(rooty->right, node);}
    }
    return false;
}

template<class T>
bool BST<T>::contains(BSTNode<T> *node) const 
{
    /* TODO */
    if(isEmpty()){return false;}
    return containsRec(this->root, node);
}

template<class T>
void BST<T>::insertRec(BSTNode<T> *rooty ,const T &data) // helper for insert function
{
    if(rooty->data > data)
    {
        if(rooty->left){insertRec(rooty->left, data);}
        else
        {
            BSTNode<T>* newN = new BSTNode<T>(data, NULL, NULL);
            rooty->left = newN;
            return;
        }
    }
    else
    {
        if(rooty->right){insertRec(rooty->right, data);}
        else
        {
            BSTNode<T>* newN = new BSTNode<T>(data, NULL, NULL);
            rooty->right = newN;
            return;
        }
    }
}

template<class T>
void BST<T>::insert(const T &data) 
{
    /* TODO */

    if(isEmpty())
    {
        BSTNode<T>* newN = new BSTNode<T>(data, NULL, NULL);
        this->root = newN;
        return;
    }
    insertRec(this->root, data);
}


template<class T>
void BST<T>::removeRec(BSTNode<T>* rooty, const T &data)
{
    if(!rooty){return;}
    else if(rooty->data > data){return removeRec(rooty->left, data);}
    else if(rooty->data < data){return removeRec(rooty->right, data);}
    else
    {
        if(rooty->right && rooty->left)
        {
            BSTNode<T>* rootyPar = findParentNode(this->root, rooty);
            BSTNode<T>* newR = findMin(rooty->right);
            BSTNode<T>* newPar = findParentNode(this->root, newR);

            if(!(rootyPar))
            {
                if(newPar == rooty)
                {
                    newR->left = rooty->left;
                    this->root = newR;
                    delete rooty;
                    return;
                }
                newPar->left = newR->right;
                newR->left = rooty->left;
                newR->right = rooty->right;
                this->root = newR;
                delete rooty;
            }
            else if(newPar == rooty)
            {
                newR->left = rooty->left;
                if(rootyPar->left == rooty){rootyPar->left = newR;}
                else{rootyPar->right = newR;}
                delete rooty;
            }
            else
            {
                newPar->left = newR->right;
                newR->left = rooty->left;
                newR->right = rooty->right;
                if(rootyPar->left == rooty){rootyPar->left = newR;}
                else{rootyPar->right = newR;}
                delete rooty;
            }
        }
        else
        {
            bool isItRight = true;
            BSTNode<T>* tmp = rooty;
            BSTNode<T>* par = findParentNode(this->root, rooty);

            if(par->data > rooty->data){isItRight = false;}

            rooty = (rooty->right != NULL) ? rooty->right : rooty->left;
            
            if(isItRight){par->right = rooty;}
            else{par->left = rooty;}

            delete tmp;
        }
    }
}

template<class T>
void BST<T>::remove(const T &data) 
{
    /* TODO */
    removeRec(this->root, data);
}

template<class T>
void BST<T>::clearRec(BSTNode<T>* rooty)
{
    if(rooty)
    {
        clearRec(rooty->left);
        clearRec(rooty->right);
        delete rooty;
    }
}

template<class T>
void BST<T>::removeAllNodes() 
{
    /* TODO */
    clearRec(this->root);
    this->root = NULL;
}

template<class T>
BSTNode<T> *BST<T>::findMax(BSTNode<T>* rooty) const
{
    if(!rooty){return NULL;}
    if(!(rooty->right)){return rooty;}
    else{return findMax(rooty->right);}
}

template<class T>
BSTNode<T> *BST<T>::findMin(BSTNode<T>* rooty) const
{
    if(!rooty){return NULL;}
    if(!(rooty->left)){return rooty;}
    else{return findMin(rooty->left);}
}

template<class T>
BSTNode<T> *BST<T>::findParentNode(BSTNode<T>* rooty, BSTNode<T>* node) const 
{
    if(!rooty){return NULL;}
    
    if(rooty == node){return NULL;}
    else if(rooty->left == node || rooty->right == node){return rooty;}
    else if(rooty->data > node->data){return findParentNode(rooty->left, node);}
    else if(rooty->data < node->data){return findParentNode(rooty->right, node);}
}

template<class T>
BSTNode<T> *BST<T>::searchRec(BSTNode<T>* rooty, const T &data) const 
{
    if(rooty)
    {
        if(rooty->data > data){return searchRec(rooty->left, data);} 
        else if(rooty->data < data){return searchRec(rooty->right, data);}
        return rooty;
    }
    return NULL;
}

template<class T>
BSTNode<T>* BST<T>::search(const T &data) const 
{
    /* TODO */

    if(isEmpty()){return NULL;}
    return searchRec(this->root, data);
}

template<class T>
BSTNode<T>* BST<T>::getSuccessor(BSTNode<T>* node, TraversalPlan tp) const 
{
    if(!(this->contains(node))){return NULL;}

    if (tp == inorder) 
    {
        /* TODO */
        
        if(node->right){return findMin(node->right);}
        else
        {
            BSTNode<T>* willBeParent = this->root;
            BSTNode<T>* succ = NULL;
            
            while(willBeParent != node)
            {
                if(willBeParent->data > node->data)
                {
                    succ = willBeParent;
                    willBeParent = willBeParent->left;
                }
                else
                {
                    willBeParent = willBeParent->right;
                }
            }
            return succ;
        }
    }

    else if (tp == preorder) 
    {
        /* TODO */
        
        if(node->left){return node->left;}
        else if(node->right){return node->right;}
        else
        {
            BSTNode<T>* succ = NULL;
            BSTNode<T>* willBeParent = this->root;
            
            while(willBeParent != node)
            {
                if(willBeParent->data < node->data)
                {
                    willBeParent = willBeParent->right;
                }
                else
                {
                    if(willBeParent->right){succ = willBeParent->right;}
                    willBeParent = willBeParent->left;
                }
            }
            return succ;
        }
    } 

    else if (tp == postorder) 
    {
        /* TODO */
        
        if(node == this->root){return NULL;}
        
        BSTNode<T>* parent = findParentNode(this->root, node);
        BSTNode<T>* succ = NULL;
        
        if(node == parent->left)
        {
            if(!(parent->right)){return parent;}
            else
            {
                succ = parent->right;
                while(succ->right || succ->left)
                {
                    if(succ->left){succ = succ->left;}
                    else{succ = succ->right;}
                }
                return succ;
            }
        }
        else{return parent;}
    }
}

template<class T>
void BST<T>::print(TraversalPlan tp) const {

    if (tp == inorder) 
    {
        // check if the tree is empty?
        if (isEmpty()) 
        {
            // the tree is empty.
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.
        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, inorder);
        std::cout << std::endl << "}" << std::endl;
    } 

    else if (tp == preorder) 
    {
        /* TODO */

        if (isEmpty()) 
        {
            std::cout << "BST_preorder{}" << std::endl;
            return;
        }

        std::cout << "BST_preorder{" << std::endl;
        print(root, preorder);
        std::cout << std::endl << "}" << std::endl;
    } 

    else if (tp == postorder) 
    {
        /* TODO */

        if (isEmpty()) 
        {
            std::cout << "BST_postorder{}" << std::endl;
            return;
        }

        std::cout << "BST_postorder{" << std::endl;
        print(root, postorder);
        std::cout << std::endl << "}" << std::endl;
    }
}

template<class T>
void BST<T>::travRec(BSTNode<T>* rhsRooty)
{
    if(rhsRooty)
    {
        this->insert(rhsRooty->data);
        travRec(rhsRooty->left);
        travRec(rhsRooty->right);
    }
}

template<class T>
BST<T> &BST<T>::operator=(const BST<T> &rhs) 
{
    /* TODO */

    if(this != &rhs)
    {
        this->removeAllNodes();
        if(!(rhs.root)){return *this;}
        travRec(rhs.root);
    }
    return *this;
}

template<class T>
void BST<T>::print(BSTNode<T>* node, TraversalPlan tp) const {

    // check if the node is NULL?
    if (node == NULL)
        return;

    if (tp == inorder) 
    {
        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        if (node->left) 
        {
            std::cout << "," << std::endl;
        }
        
        // then, output the node.
        std::cout << "\t" << node->data;
        
        // finally, output comma (if needed) and the right subtree.
        if (node->right)
        {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);
    } 
    else if (tp == preorder) 
    {
        /* TODO */
        
        std::cout << "\t" << node->data;
        if(node->left)
        {
            std::cout << "," << std::endl;
        }
        print(node->left, preorder);
        
        if(node->right)
        {
            std::cout << "," << std::endl;
        }
        print(node->right, preorder);
        
    } 
    else if (tp == postorder) 
    {
        /* TODO */
        
        print(node->left, postorder);
        if(node->left)
        {
            std::cout << "," << std::endl;
        }
        
        print(node->right,postorder);
        if(node->right)
        {
            std::cout << "," << std::endl;
        }
        
        std::cout << "\t" << node->data;

    }
}