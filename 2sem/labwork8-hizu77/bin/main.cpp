#include "lib/BinarySearchTree.h"
#include <vector>

using namespace bst;

int main() {

    //support Kth largest element
    InOrderBST<int> tree(2);
    tree.insert(8);
    tree.insert(3);
    tree.insert(10);
    tree.insert(1);
    tree.insert(6);
    tree.insert(14);
    tree.insert(4);
    tree.insert(7);
    tree.insert(13);

    std::cout << tree.kth_largest(3);
}