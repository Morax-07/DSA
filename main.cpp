#include <iostream>
#include "AVLTree.hpp"







int main(int argc, char** argv) {
    

    AVLTree<int> tree = AVLTree<int>();
    tree.insertNode(10);
    tree.insertNode(20);
    tree.insertNode(25);
    tree.insertNode(30);
    tree.insertNode(40);
    tree.insertNode(50);


    tree.inOrderTraversal();


    if(tree.isBalanced()) 
        std::cout<< "Albero bilanciato\n";
    else
        std::cout<< "Albero non bilanciato\n";



    
    return 0;
}