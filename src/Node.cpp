#include "Node.hpp"
#include <iostream>








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