#include "AVltree.h"

int main () {

    Tree::AVLTree tree;

    tree.insert(5);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);

    std::cout << tree.serialize();

    tree.deleteValue(6);

    std::cout << tree.serialize();

}