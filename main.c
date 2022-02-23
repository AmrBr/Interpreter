#include <stdio.h>

#include "ReadEvaluate/io.h"
#include "tools.h"

int main() {

    BSTNode *root = NULL;
    Item **items;

    process(&root);


    printf("\nBinary Search Tree InOrder:\n");
    inOrder(root);

    printf("\n");
    printf("\nHeap Sort by value:\n");


    int co = 0;
    bstToItemArray(root, items, &co);
    heapSort(items, co);

    printItems(items, co);

    return 0;
}
