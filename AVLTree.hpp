#pragma once

#include <iostream>
#include <deque>








template<typename T> class AVLTree {
    private:
        class Node {
            private:
                T value;
        
            public:
                const T getValue(void) const noexcept;
                void setValue(T);
                
        
                Node* left;
                Node* right;
                int height;
        
        
                Node(void) = default;
                Node(T);
        };

        AVLTree<T>::Node* root; 


        Node* balanceNode(Node*);
        Node* rotateLeft(Node*);
        Node* rotateRight(Node*);
        

        int getNodeBalance(Node*);
        void updateNodeHeight(Node*);
        int getNodeHeight(Node*);
        void inOrderTraversal(Node*);
        bool isBalanced(Node*);
        void replaceNode(Node*, Node*, Node*);

    
    public:
        void inOrderTraversal(void);
        bool isBalanced(void);
        void deleteNode(T);
        void insertNode(T);
        Node getRootCopy(void);


        AVLTree(void);
};











//CONSTRUCTOR
template<typename T> AVLTree<T>::AVLTree() {
    this->root = nullptr;
}



//METHODS
template<typename T> int AVLTree<T>::getNodeBalance(Node* node) {
    return node ? getNodeHeight(node->right) - getNodeHeight(node->left) : 0;
}

template<typename T> int AVLTree<T>::getNodeHeight(Node* node) {
    return node ? node->height : 0;
}

template<typename T> void AVLTree<T>::updateNodeHeight(Node* node) {
    node->height = 1 + std::max(getNodeHeight(node->left), getNodeHeight(node->right));
}

template<typename T> AVLTree<T>::Node* AVLTree<T>::rotateLeft(Node* node) {
    Node* x = node->right;
    Node* t = x->left;
    x->left = node;
    node->right = t;



    updateNodeHeight(node);
    updateNodeHeight(x);


    return x;
}

template<typename T> AVLTree<T>::Node* AVLTree<T>::rotateRight(Node* node) {
    Node* x = node->left;
    Node* t = x->right;
    x->right = node;
    node->left = t;



    updateNodeHeight(node);
    updateNodeHeight(x);


    return x;
}

template<typename T> AVLTree<T>::Node* AVLTree<T>::balanceNode(Node* node) {
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

template<typename T> void AVLTree<T>::inOrderTraversal() {
    inOrderTraversal(root);
}

template<typename T> void AVLTree<T>::inOrderTraversal(Node* node) {
    if (!node) return;


    inOrderTraversal(node->left);
    std::cout<< node->getValue() << " ";
    inOrderTraversal(node->right);
}

template<typename T> void AVLTree<T>::insertNode(T value) {
    if(!root) {
        root = new Node(value);
        return;
    }

    std::deque<Node*> traversedNodes;
    Node* node = root;


    while (node) {
        traversedNodes.push_front(node);


        if (value < node->getValue()) {
            if(node->left) {
                node = node->left;
            }
            else {
                node->left = new Node(value);
                traversedNodes.push_front(node->left);
                break;
            }
        }
        else if(value > node->getValue()) {
            if(node->right) {
                node = node->right;
            }
            else {
                node->right = new Node(value);
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
        Node* newNode = balanceNode(traversedNodes[i]);
        

        if (i == traversedNodes.size() - 1) {
            root = newNode;
        }
        else {
            Node* parent = traversedNodes[i + 1];


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

template<typename T> bool AVLTree<T>::isBalanced(Node* node) {
    if (!node) return true;


    int BF = getNodeBalance(node);



    if (BF < -1 || BF > 1) return false;


    return isBalanced(node->left) && isBalanced(node->right);
}

template<typename T> void AVLTree<T>::deleteNode(T value) {
    Node* node = root;
    Node* parent = nullptr;
    std::deque<Node*> traversedNodes;


    while(node && node->getValue() != value) {
        traversedNodes.push_front(node);
        parent = node;


        if(value < node->getValue()) {
            node = node->left;
        }
        else {
            node = node->right;
        }
    }


    
    if(!node) 
        throw std::runtime_error("The node you're trying to delete doesn't exist!");





    if(!node->left && !node->right) {
        if(parent) {
            if(parent->left == node) 
                parent->left = nullptr;
            else
                parent->right = nullptr;

            delete node;
        }
        else {
            delete node;
            root = nullptr;
        }
    }
    else if (!node->left || !node->right) {
        Node* child = (node->left) ? node->left : node->right;


        if (parent) {
            replaceNode(parent, node, child);

            delete node;
        }
        else {
            root = child;
            delete node;
        }
    }
    else {
        Node* successorParent = node;
        Node* successor = successorParent->right;

        while(successor->left) {
            traversedNodes.push_front(successorParent);
            successorParent = successor;
            successor = successor->left;
        }


        node->setValue(successor->getValue());



        replaceNode(successorParent, successor, successor->right);

        delete successor;
    }




    while(!traversedNodes.empty()) {
        Node* current = traversedNodes.front();
        traversedNodes.pop_front();




        updateNodeHeight(current);
        Node* newNode = balanceNode(current);

        if(traversedNodes.empty()) {
            root = newNode;
        }
        else {
            Node* parentBalancing = traversedNodes.front();

            if(newNode->getValue() < parentBalancing->getValue()) 
                parentBalancing->left = newNode;
            else
                parentBalancing->right = newNode;
        }
    }
}

template<typename T> void AVLTree<T>::replaceNode(Node* parent, Node* oldChild, Node* newChild) {
    if(parent->left == oldChild) 
        parent->left = newChild;
    else
        parent->right = newChild;
}

template<typename T> AVLTree<T>::Node AVLTree<T>::getRootCopy() {
    if(!root)
        throw std::runtime_error("The root node has not been instantiated yed!");

    return *(root);
}









//CONSTRUCTOR
template<typename T> AVLTree<T>::Node::Node(T value) {
    this->value = value;
    this->height = 1;
    this->left = nullptr;
    this->right = nullptr;
}


//METHODS
template<typename T> const T AVLTree<T>::Node::getValue() const noexcept {
    return this->value;
}

template<typename T> void AVLTree<T>::Node::setValue(T value) {
    try {
        this->value = value;
    }
    catch(...) {
        try {
            std::cout<< "An error occurred while trying to assign the value of " << value << " to Node<T>::value.\n";
            std::cout<< "The value of Node<T>::value remains unchanged (Node<T>::value = " << this->value << ")."; 
        }
        catch (...) {
            std::cout<< "Cannot assign the value to Node<T>::value or print out the value you're trying to assign and the value of Node<T>::value.";
        }
    }
}