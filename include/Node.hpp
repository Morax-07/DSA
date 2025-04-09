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
        Node(Node<T>&) = delete;
        Node(T);
};