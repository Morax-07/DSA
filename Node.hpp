#pragma once

#include <iostream>





template<typename T> class Node {
    private:
        const T value;

    public:
        const T getValue(void) const noexcept;
        

        Node* left;
        Node* right;
        int height;


        Node(void) = default;
        Node(T);
};














//CONSTRUCTOR
template<typename T> Node<T>::Node(T value): value(value) {
    this->height = 1;
    this->left = nullptr;
    this->right = nullptr;
}


//METHODS
template<typename T> const T Node<T>::getValue() const noexcept {
    return this->value;
}