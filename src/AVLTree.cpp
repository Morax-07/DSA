#include <iostream>
#include <stack>
#include "AVLTree.hpp"









//CONSTRUCTOR
template<typename T> AVLTree<T>::AVLTree() {
    this->root = nullptr;
}



//METHODS
template<typename T> int AVLTree<T>::getNodeBalance(Node<T>*& node) {
    return node ? getNodeHeight(node->right) - getNodeHeight(node->left) : 0;
}

template<typename T> int AVLTree<T>::getNodeHeight(Node<T>*& node) {
    return node ? node->height : 0;
}

template<typename T> void AVLTree<T>::updateNodeHeight(Node<T>*& node) {
    node->height = 1 + std::max(getNodeHeight(node->left), getNodeHeight(node->right));
}

template<typename T> Node<T>* AVLTree<T>::rotateLeft(Node<T>*& node) {
    Node<T>*& x = node->right;
    Node<T>*& t = x->left;
    x->left = node;
    node->right = t;




    updateNodeHeight(node);
    updateNodeHeight(x);


    return x;
}

template<typename T> Node<T>* AVLTree<T>::rotateRight(Node<T>*& node) {
    Node<T>* x = node->left;
    Node<T>* t = x->right;
    x->right = node;
    node->left = t;



    updateNodeHeight(node);
    updateNodeHeight(x);


    return x;
}

template<typename T> Node<T>* AVLTree<T>::balanceNode(Node<T>*& node) {
    int BF = getNodeBalance(node);


    if (BF > 1) {
        if (getNodeBalance(node->right) < 0) 
            node->right = rotateRight(node->right); 
        
        return rotateLeft(node);
    }
    else if (BF < -1) {
        if(getNodeBalance(node->left) > 0)
            node->left = rotateLeft(node->left);

        return rotateRight(node);
    }



    return node;
}

template<typename T> void AVLTree<T>::inOrderTraversal(Node<T>*& node) {
    if (!node) return;


    inOrderTraversal(node->left);
    std::cout<< node->getValue() << " ";
    inOrderTraversal(node->right);
}

template<typename T> void AVLTree<T>::insertNode(T value) {
    if(!root) {
        root = new Node<T>(value);
        return;
    }


    std::stack<Node<T>*&> stack;
    Node<T>*& node = root;



    while (node) {
        stack.push(node);


        if (value < node->getValue()) {
            
        }
    }
}