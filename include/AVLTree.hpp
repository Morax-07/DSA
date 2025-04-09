#pragma once

#include <iostream>
#include "Node.hpp"








template<typename T> class AVLTree {
    private:
        Node<T>* root; 


        Node<T>* balanceNode(Node<T>*&);
        Node<T>* rotateLeft(Node<T>*&);
        Node<T>* rotateRight(Node<T>*&);
        

        int getNodeBalance(Node<T>*&);
        void updateNodeHeight(Node<T>*&);
        int getNodeHeight(Node<T>*&);

    
    public:
        void inOrderTraversal(Node<T>*&);
        void deleteNode(T);
        void insertNode(T);


        AVLTree(void);
        AVLTree(AVLTree&) = delete;
        AVLTree(AVLTree&&) = delete;
};