#pragma once

#include <iostream>
#include "Node.hpp"
#include <deque>








template<typename T> class AVLTree {
    private:
        Node<T>* root; 


        Node<T>* balanceNode(Node<T>*);
        Node<T>* rotateLeft(Node<T>*);
        Node<T>* rotateRight(Node<T>*);
        

        int getNodeBalance(Node<T>*);
        void updateNodeHeight(Node<T>*);
        int getNodeHeight(Node<T>*);
        void inOrderTraversal(Node<T>*);
        bool isBalanced(Node<T>*);

    
    public:
        void inOrderTraversal(void);
        bool isBalanced(void);
        void deleteNode(T);
        void insertNode(T);


        AVLTree(void);
};











//CONSTRUCTOR
template<typename T> AVLTree<T>::AVLTree() {
    this->root = nullptr;
}



//METHODS
template<typename T> int AVLTree<T>::getNodeBalance(Node<T>* node) {
    return node ? getNodeHeight(node->right) - getNodeHeight(node->left) : 0;
}

template<typename T> int AVLTree<T>::getNodeHeight(Node<T>* node) {
    return node ? node->height : 0;
}

template<typename T> void AVLTree<T>::updateNodeHeight(Node<T>* node) {
    node->height = 1 + std::max(getNodeHeight(node->left), getNodeHeight(node->right));
}

template<typename T> Node<T>* AVLTree<T>::rotateLeft(Node<T>* node) {
    Node<T>* x = node->right;
    Node<T>* t = x->left;
    x->left = node;
    node->right = t;



    updateNodeHeight(node);
    updateNodeHeight(x);


    return x;
}

template<typename T> Node<T>* AVLTree<T>::rotateRight(Node<T>* node) {
    Node<T>* x = node->left;
    Node<T>* t = x->right;
    x->right = node;
    node->left = t;



    updateNodeHeight(node);
    updateNodeHeight(x);


    return x;
}

template<typename T> Node<T>* AVLTree<T>::balanceNode(Node<T>* node) {
    int BF = getNodeBalance(node);

    
    if (BF > 1) {
        if (getNodeBalance(node->right) < 0) 
            node->right = rotateRight(node->right); 
        
        return rotateLeft(node);
    }
    else if (BF < -1) {
        if(getNodeBalance(node->left) > 0)
            node->left = rotateLeft(node->left);

        std::cout<< "BILANCIATO";
        return rotateRight(node);
    }



    return node;
}

template<typename T> void AVLTree<T>::inOrderTraversal() {
    inOrderTraversal(root);
}

template<typename T> void AVLTree<T>::inOrderTraversal(Node<T>* node) {
    if (!node) return;


    inOrderTraversal(node->left);
    std::cout<< node->getValue() << "\n";
    inOrderTraversal(node->right);
}

template<typename T> void AVLTree<T>::insertNode(T value) {
    if(!root) {
        root = new Node<T>(value);
        return;
    }

    std::deque<Node<T>*> traversedNodes;
    Node<T>* node = root;


    while (node) {
        traversedNodes.push_front(node);


        if (value < node->getValue()) {
            if(node->left) {
                node = node->left;
            }
            else {
                node->left = new Node<T>(value);
                traversedNodes.push_front(node->left);
                break;
            }
        }
        else if(value > node->getValue()) {
            if(node->right) {
                node = node->right;
            }
            else {
                node->right = new Node<T>(value);
                traversedNodes.push_front(node->right);
                break;
            }
        }
        else if(value == node->getValue()) {
            throw std::runtime_error("A node with the value that you're trying to insert already exists!\n");
        }
    }


    for(int i = 0; i < traversedNodes.size(); i++) {
        updateNodeHeight(traversedNodes[i]);
        Node<T>* newNode = balanceNode(traversedNodes[i]);
        

        if (i == traversedNodes.size() - 1) {
            root = newNode;
        }
        else {
            Node<T>* parent = traversedNodes[i + 1];


            if(newNode->getValue() < parent->getValue()) {
                parent->left = newNode;
            }
            else {
                parent->right = newNode;
            }
        }
    }
}

template<typename T> bool AVLTree<T>::isBalanced() {
    return isBalanced(root);
}

template<typename T> bool AVLTree<T>::isBalanced(Node<T>* node) {
    if (!node) return true;


    int BF = getNodeBalance(node);



    if (BF < -1 || BF > 1) return false;


    return isBalanced(node->left) && isBalanced(node->right);
}