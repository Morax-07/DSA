#pragma once

#include <iostream>
#include <deque>







namespace DSA {
    //AVLTree<T> class definition
    template<typename T> class AVLTree {
        private:
            //Inner class node to prevent the creation of other nodes outside a tree
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
            void deleteNodes(Node*);
    
        
        public:
            void inOrderTraversal(void);
            bool isBalanced(void);
            void deleteNode(T);
            void insertNode(T);
            Node getRootCopy(void);
    
    
            AVLTree(void);
            ~AVLTree(void);
    };
    
    
    
    
    
    
    
    
    
    
    //AVLTREE
    //CONSTRUCTOR
    template<typename T> AVLTree<T>::AVLTree() {
        this->root = nullptr;
    }

    //DESTRUCTOR
    template<typename T> AVLTree<T>::~AVLTree() {
        deleteNodes(root);
        root = nullptr;
    }
    
    //METHODS
    //deletes all nodes of the tree recursively
    template<typename T> void AVLTree<T>::deleteNodes(Node* node) {
        if(!node) return;

        deleteNodes(node->left);
        delete node;
        deleteNodes(node->right);
    }

    //returns the balance factor of a node
    //the BF is the difference of the heights of the right and left subrtee of a node
    template<typename T> int AVLTree<T>::getNodeBalance(Node* node) {
        return node ? getNodeHeight(node->right) - getNodeHeight(node->left) : 0;
    }
    
    //return the height of a node
    //if the node is nullptr the height is 0
    template<typename T> int AVLTree<T>::getNodeHeight(Node* node) {
        return node ? node->height : 0;
    }
    
    //updates the height of a node.
    //the height of a node is the max value between the height of the left and right subtrees
    template<typename T> void AVLTree<T>::updateNodeHeight(Node* node) {
        node->height = 1 + std::max(getNodeHeight(node->left), getNodeHeight(node->right));
    }
    
    //it executes a left rotation on a node
    template<typename T> AVLTree<T>::Node* AVLTree<T>::rotateLeft(Node* node) {
        Node* x = node->right;
        Node* t = x->left;
        x->left = node;
        node->right = t;
    
    
    
        updateNodeHeight(node);
        updateNodeHeight(x);
    
    
        return x;
    }
    
    //it executes a right rotation on a node
    template<typename T> AVLTree<T>::Node* AVLTree<T>::rotateRight(Node* node) {
        Node* x = node->left;
        Node* t = x->right;
        x->right = node;
        node->left = t;
    
    
    
        updateNodeHeight(node);
        updateNodeHeight(x);
    
    
        return x;
    }
    
    //checks the balanc factor of a node to either rotate it left, or rotate it right or leave it untouched
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
    
    //public method to execute an in-order traversal in the tree starting from root node
    template<typename T> void AVLTree<T>::inOrderTraversal() {
        inOrderTraversal(root);
    }
    
    //executes a recursive in-order traversal in the tree starting from a node
    template<typename T> void AVLTree<T>::inOrderTraversal(Node* node) {
        if (!node) return;
    
    
        inOrderTraversal(node->left);
        std::cout<< node->getValue() << " ";
        inOrderTraversal(node->right);
    }
    
    //inserts a node inside the tree
    template<typename T> void AVLTree<T>::insertNode(T value) {
        //if root node isn't instantiated it instantiates it
        if(!root) {
            root = new Node(value);
            return;
        }
    
        std::deque<Node*> traversedNodes;
        Node* node = root;
    
    
        //iterates through the tree by going left when the value is less than the value of the current node,
        //by going right when the value is geater then the value of the current node
        //or by throwing an std::runtime_error if the node already exists.
        
        //pushes the node into a deque (front) all the traversed nodes to balance them later.
        while (node) {
            traversedNodes.push_front(node);
    
    
            if (value < node->getValue()) {
                if(node->left) {
                    //goes left
                    node = node->left;
                }
                else {
                    //inserts the node
                    node->left = new Node(value);
                    traversedNodes.push_front(node->left);
                    break;
                }
            }
            else if(value > node->getValue()) {
                if(node->right) {
                    //goes right
                    node = node->right;
                }
                else {
                    //inserts the node
                    node->right = new Node(value);
                    traversedNodes.push_front(node->right);
                    break;
                }
            }
            else if(value == node->getValue()) 
                //the node already exists
                throw std::runtime_error("A node with the value that you're trying to insert already exists!\n");
        }
    
    
        //iterates through the traversed nodes to balance them
        for(int i = 0; i < traversedNodes.size(); i++) {
            //updates the node height
            updateNodeHeight(traversedNodes[i]);

            //balances the node
            Node* newNode = balanceNode(traversedNodes[i]);
            
    


            if (i == traversedNodes.size() - 1) {
                //the root node has no parent so it is assigned directly the value of the newNode
                root = newNode;
            }
            else {
                //a node's parent is alwais the next node in the deque
                Node* parent = traversedNodes[i + 1];
    
    
                //inserts the balanced node either to the lef or to the right of it's parent based on their values
                if(newNode->getValue() < parent->getValue()) {
                    parent->left = newNode;
                }
                else {
                    parent->right = newNode;
                }
            }
        }
    }
    
    //public method used to know if the tree is balanced or not starting from the root node
    template<typename T> bool AVLTree<T>::isBalanced() {
        return isBalanced(root);
    }
    
    //recursively checks if every node is balanced calculating their balance factors 
    template<typename T> bool AVLTree<T>::isBalanced(Node* node) {
        if (!node) return true;
    
    
        int BF = getNodeBalance(node);
    
    
    
        if (BF < -1 || BF > 1) return false;
    
    
        return isBalanced(node->left) && isBalanced(node->right);
    }
    
    //deletes a node of the tree
    template<typename T> void AVLTree<T>::deleteNode(T value) {
        Node* node = root;
        Node* parent = nullptr;
        std::deque<Node*> traversedNodes;
    
    
        //finds the parent of the node to delete and pushes every node that it goes through into a deque (front)
        while(node && node->getValue() != value) {
            traversedNodes.push_front(node);
            parent = node;
    
    
            //goes left or right of a node based on the value that you want to delete 
            if(value < node->getValue()) {
                node = node->left;
            }
            else {
                node = node->right;
            }
        }
    
    
        //at the end of the iteration, if the node tourns out to be nullptr it means thet the node doesn't exist so 
        //it throws an exception
        if(!node) 
            throw std::runtime_error("The node you're trying to delete doesn't exist!");
    
    
    
    
        //there are different rules to delete a node based on how many child does that node have
        //deleting a leaf node (no children)
        if(!node->left && !node->right) {
            if(parent) {
                if(parent->left == node) 
                    parent->left = nullptr;
                else
                    parent->right = nullptr;
    
                delete node;
            }
            else {
                //the node to delete is the root node
                delete node;
                root = nullptr;
            }
        }
        //the node has only one child (either the lef or the right one)
        else if (!node->left || !node->right) {
            Node* child = (node->left) ? node->left : node->right;
    
    
            if (parent) {
                //replaces a parent's child (node) with the only node's child (child) then deletes the node
                replaceNode(parent, node, child);
    
                delete node;
            }
            else {
                //the node to delete is the root node
                root = child;
                delete node;
            }
        }
        //the node has two children
        else {
            Node* successorParent = node;
            Node* successor = successorParent->right;
    
            //finds the in-order successor of the node that has to be deleted
            while(successor->left) {
                traversedNodes.push_front(successorParent);
                successorParent = successor;
                successor = successor->left;
            }
    
    
            //changes the value of the node to delete with its in-order successor's value
            node->setValue(successor->getValue());
    
    
    
            //replaces the in-order successor with it's right child (if it has one)
            replaceNode(successorParent, successor, successor->right);
    
            delete successor;
        }
    
    
    
        
        //balances all the nodes it went through 
        while(!traversedNodes.empty()) {
            //the node to balance is the first of the deque
            Node* current = traversedNodes.front();

            //the address of the node to balance has already been assigned to current so it is popped
            //from the deque
            traversedNodes.pop_front();
    
    
    
    
            //updates the node height and balances it
            updateNodeHeight(current);
            Node* newNode = balanceNode(current);
    
            if(traversedNodes.empty()) {
                //if there are no more elements in the deque the balance node is assigned to teh root node
                root = newNode;
            }
            else {
                //the node's parent is the front of the deque after popping the front before
                Node* parentBalancing = traversedNodes.front();
    
                //assignes the balanced node to the left or right child of it's parent based on their values
                if(newNode->getValue() < parentBalancing->getValue()) 
                    parentBalancing->left = newNode;
                else
                    parentBalancing->right = newNode;
            }
        }
    }
    
    //replaces an old child, a parent's left or right node, with a new child 
    template<typename T> void AVLTree<T>::replaceNode(Node* parent, Node* oldChild, Node* newChild) {
        if(parent->left == oldChild) 
            parent->left = newChild;
        else
            parent->right = newChild;
    }
    
    //return a copy of the root node or throws a runtime_error if the root is nullptr
    template<typename T> AVLTree<T>::Node AVLTree<T>::getRootCopy() {
        if(!root)
            throw std::runtime_error("The root node has not been instantiated yed!");
    
        return *(root);
    }
    
    
    
    
    
    
    
    
    //NODE
    //CONSTRUCTOR
    template<typename T> AVLTree<T>::Node::Node(T value) {
        this->value = value;
        this->height = 1;
        this->left = nullptr;
        this->right = nullptr;
    }
    
    
    //METHODS
    //returns the value of the node
    template<typename T> const T AVLTree<T>::Node::getValue() const noexcept {
        return this->value;
    }
    
    //sets the value of the node or throws an exception if the type doesn't correspond or if the value cannot be printed
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
}