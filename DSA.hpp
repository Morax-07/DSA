#pragma once

#include <iostream>
#include <deque>
#include <vector>
#include <list>
#include <array>
#include <string>
#include <optional>







namespace DSA {
    #pragma region AVLTREE
    //AVLTree<T> class definition
    template<typename T> class AVLTree {
        private:
            //Inner class node to prevent the creation of other nodes outside a tree
            class Node {
                private:
                    T value;
            
                public:
                    T getValue(void) const noexcept;
                    void setValue(T);
                    
            
                    Node* left;
                    Node* right;
                    int height;
            
            
                    Node(void) = default;
                    Node(T);
            };




    
            Node* root; 
    
    
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
            void remove(T);
            void add(T);
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
    template<typename T> typename AVLTree<T>::Node* AVLTree<T>::rotateLeft(Node* node) {
        Node* x = node->right;
        Node* t = x->left;
        x->left = node;
        node->right = t;
    
    
    
        updateNodeHeight(node);
        updateNodeHeight(x);
    
    
        return x;
    }
    
    //it executes a right rotation on a node
    template<typename T> typename AVLTree<T>::Node* AVLTree<T>::rotateRight(Node* node) {
        Node* x = node->left;
        Node* t = x->right;
        x->right = node;
        node->left = t;
    
    
    
        updateNodeHeight(node);
        updateNodeHeight(x);
    
    
        return x;
    }
    
    //checks the balanc factor of a node to either rotate it left, or rotate it right or leave it untouched
    template<typename T> typename AVLTree<T>::Node* AVLTree<T>::balanceNode(Node* node) {
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
    template<typename T> void AVLTree<T>::add(T value) {
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
    template<typename T> void AVLTree<T>::remove(T value) {
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
    template<typename T> typename AVLTree<T>::Node AVLTree<T>::getRootCopy() {
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
    template<typename T> T AVLTree<T>::Node::getValue() const noexcept {
        return this->value;
    }
    
    //sets the value of the node or throws an exception if the type doesn't correspond or if the value cannot be printed
    template<typename T> void AVLTree<T>::Node::setValue(T value) {
        try {
            this->value = value;
        }
        catch(...) {
            try {
                std::cout<< "An error occurred while trying to assign the value of " << value << " to AVLTree<T>::Node::value.\n";
                std::cout<< "The value of AVLTree<T>::Node::value remains unchanged (AVLTree<T>::Node::value = " << this->value << ")."; 
            }
            catch (...) {
                std::cout<< "Cannot assign the value to AVLTree<T>::Node::value or print out the value you're trying to assign and the value of AVLTree<T>::Node::value.";
            }
        }
    }



    #pragma endregion

    #pragma region HASHMAP
    //Pair<T> class definition
    //this class is used inside the class HashMap<T> and HashMap<T>::Bucket in which it rappresents
    //a key associated with a value
    template<typename T> class Pair {
        private:
            const std::string key;
            T value;


        public:
            const std::string getKey(void) const noexcept;
            T& getValue(void) noexcept;
            void setValue(T);
            std::string toString();


            Pair();
            Pair(std::string, T);
    };


    //HashMap<T> class definition
    template<typename T> class HashMap {
        private:
            //private inner class Bucket that can only be used inside HashMap<T> class
            class Bucket {
                private:
                    std::list<Pair<T>> bucket;


                public:
                    void add(Pair<T>&);
                    void remove(std::string&);
                    T& operator[](std::string&);
                    bool exist(std::string&);
                    std::string toString(void);
                    std::vector<Pair<T>*> getPairs(void);


                    Bucket(void);
            };






            std::vector<Bucket> hashTable;
            std::list<std::string> hashMapKeys;
            const int maxElementNumber;


            int calculateHashValue(const std::string&);

        
        public:
            void add(Pair<T>);
            void remove(std::string);
            T& operator[](std::string);
            bool exist(std::string);
            std::string toString(void);
            std::vector<std::string> getKeys(void);
            std::vector<Pair<T>*> getPairs(void);



            HashMap(int);
            HashMap(void);
            HashMap(HashMap&) = delete;
            HashMap(HashMap&&) = delete;
    };






    //HASHMAP
    //CONSTRUCTOR
    template<typename T> HashMap<T>::HashMap(int maxElementNumber): maxElementNumber(maxElementNumber) {
        hashTable = std::vector<Bucket>(maxElementNumber);

        for(int i = 0; i < maxElementNumber; i++) hashTable[i] = Bucket();
    }
    
    //CONSTRUCTOR
    template<typename T> HashMap<T>::HashMap(): maxElementNumber(100) {
        hashTable = std::vector<Bucket>(maxElementNumber);

        for(int i = 0; i < 100; i++) hashTable[i] = Bucket();
    }




    //METHODS
    //it calculates the hash value of the string passed by argument
    template<typename T> int HashMap<T>::calculateHashValue(const std::string& key) {
        int sum;

        for(char character : key) sum += (int)character;
        
        
        return sum % maxElementNumber;
    }

    //adds a Pair to the hash map
    template<typename T> void HashMap<T>::add(Pair<T> pair) {
        const int hashValue = calculateHashValue(pair.getKey());

        hashTable[hashValue].add(pair);  
        hashMapKeys.push_back(pair.getKey());      
    } 

    //removes a Pair from the hash map
    template<typename T> void HashMap<T>::remove(std::string key) {
        const int hashValue = calculateHashValue(key);

        hashTable[hashValue].remove(key);


        auto it = hashMapKeys.begin();

        while(it != hashMapKeys.end()) {
            if(*it == key) {
                hashMapKeys.erase(it);
                return;
            }
            else {
                ++it;
            }
        }
    }

    //returns a modifiable reference to the value associated with the specified key
    template<typename T> T& HashMap<T>::operator[](std::string key) {
        const int hashValue = calculateHashValue(key);

        return hashTable[hashValue][key];
    }

    //checks if a key exist in the hash map
    template<typename T> bool HashMap<T>::exist(std::string key) {
        const int hashValue = calculateHashValue(key);

        return hashTable[hashValue].exist(key);
    }

    //returns the std::string rappresenting the hash map
    template<typename T> std::string HashMap<T>::toString() {
        std::string stringFormat = "{\n";

        for(auto& bucket : hashTable) stringFormat += bucket.toString();
        

        stringFormat += "}\n";

        return stringFormat;
    }

    //returns a vector of the keys of the hash map
    template<typename T> std::vector<std::string> HashMap<T>::getKeys() {
        std::vector<std::string> keysVector;

        for(std::string key : hashMapKeys) {
            keysVector.push_back(key);
        }



        return keysVector;
    }

    //returns the reference of all the pairs in the hash map
    template<typename T> std::vector<Pair<T>*> HashMap<T>::getPairs() {
        std::vector<Pair<T>*> pairs;


        for(auto& bucket : hashTable) {
            std::vector<Pair<T>*> bucketPairs = bucket.getPairs();
            pairs.insert(pairs.end(), bucketPairs.begin(), bucketPairs.end());
        }


        return pairs;
    }









    //BUCKET
    //CONSTRUCTOR
    template<typename T> HashMap<T>::Bucket::Bucket(): bucket() {}




    //METHODS
    //add a Pair<T> into a Bucket
    template<typename T> void HashMap<T>::Bucket::add(Pair<T>& pair) {
        if(bucket.size() != 0) {
            for(auto& p : bucket) {
                if(pair.getKey() == p.getKey()) throw std::runtime_error("A pair with the key \"" + pair.getKey() + "\" already exist!");
            }
        }


        bucket.push_back(pair);
    }

    //removes a pair from the bucket
    template<typename T> void HashMap<T>::Bucket::remove(std::string& key) {
        if(bucket.size() == 0) throw std::runtime_error("The Pair<T> you're trying to remove doesn't exist!");

        auto it = bucket.begin();

        while(it != bucket.end()) {
            if(it->getKey() == key) {
                bucket.erase(it);
                return;
            }
            else {
                ++it;
            } 
        }
        
        
        throw std::runtime_error("The Pair<T> you're trying to remove doesn't exist!");
    }

    //returns a modifiable reference to the value associated with the specified key found in the bucket
    template<typename T> T& HashMap<T>::Bucket::operator[](std::string& key) {
        if(bucket.size() == 0) throw std::runtime_error("There is no value associated with the key \"" + key + "\" in the HashMap<T>!");


        for(auto& pair : bucket) {
            if(pair.getKey() == key) return pair.getValue();
        }

        throw std::runtime_error("There is no value associated with the key \"" + key + "\" in the HashMap<T>!");
    }

    //checks if a key exist inside a bucket
    template<typename T> bool HashMap<T>::Bucket::exist(std::string& key) {
        if(bucket.size() == 0) return false;


        for(auto& pair : bucket) {
            if(pair.getKey() == key) return true;
        }

        return false;
    }

    //returns the string rappresenting the bucket
    template<typename T> std::string HashMap<T>::Bucket::toString() {
        if(bucket.size() == 0) return "";


        std::string stringFormat = "";

        for(auto& pair : bucket) stringFormat += pair.toString();

        return stringFormat;
    }

    //returns the reference of all the pairs in the bucket
    template<typename T> std::vector<Pair<T>*> HashMap<T>::Bucket::getPairs() {
        std::vector<Pair<T>*> pairs;

        for(auto& pair : bucket) pairs.push_back(&pair);


        return pairs;
    }









    //PAIR
    //CONSTRUCTOR
    template<typename T> Pair<T>::Pair(std::string key, T value): key(key) {
        this->value = value;
    }

    //CONSTRUCTOR
    template<typename T> Pair<T>::Pair(): key("_") {
        this->value = NULL;
    }




    //METHODS
    //it returns the key of a Pair
    template<typename T> const std::string Pair<T>::getKey() const noexcept {
        return this->key;
    }

    //it returns the value of a Pair
    template<typename T> T& Pair<T>::getValue() noexcept {
        return this->value;
    }

    //it sets the value of a Pair
    template<typename T> void Pair<T>::setValue(T value) {
        try {
            this->value = value;
        }
        catch(...) {
            try {
                std::cout<< "An error occurred while trying to assign the value of " << value << " to HashMap<T>::Bucket::Pair::value.\n";
                std::cout<< "The value of HashMap<T>::Bucket::Pair::value remains unchanged (HashMap<T>::Bucket::Pair::value = " << this->value << ")."; 
            }
            catch(...) {
                std::cout<< "Cannot assign the value to HashMap<T>::Bucket::Pair::value or print out the value you're trying to assign and the value of HashMap<T>::Bucket::Pair::value.";
            }
        }
    }

    //returns the string rappresenting a pair
    template<typename T> std::string Pair<T>::toString() {
        try {
            return "\t{\"" + this->key + "\": " + std::to_string(this->value) + "}\n";
        }
        catch(...) {
            return "It's impossible to display a string format of this HashMap<T> because of the type of it's value";
        }
    }
    
    
    
    #pragma endregion
}