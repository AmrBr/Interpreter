#include <stdlib.h>
#include <string.h>
#include "heap.h"


// Creates new Item
Item *newItem(char *key, TYPE val) {
    Item *item = malloc(sizeof(Item));
    item->key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(item->key, key);
    item->value = val;
    return item;
}


// Swap to elements in items array
void swapArrayItems(Item **nodeArr, int i, int j) {
    Item *temp = nodeArr[i];
    nodeArr[i] = nodeArr[j];
    nodeArr[j] = temp;
}

// Converts a tree to a heap (whether its partially heapified or not at all)
void heapify(Item **array, int size, int index) {
    int largest = index;
    int left = 2 * index + 1; // left child
    int right = 2 * index + 2; // right child


    // Checking the largest child to replace it with current
    if (left < size && array[left]->value > array[largest]->value)
        largest = left;

    if (right < size && array[right]->value > array[largest]->value)
        largest = right;

    if (largest != index) {
        swapArrayItems(array, index, largest);

        heapify(array, size, largest);
    }
}

// Builds a heap from an item Array
void buildHeap(Item **arr, int size) {
    int lastNonLeafNode = size / 2 - 1;

    for (int i = lastNonLeafNode; i >= 0; i--) {
        heapify(arr, size, i);
    }
}

// Sort Array of items using heaps
void heapSort(Item **nodeArr, int n) {
    buildHeap(nodeArr, n);

    for (int i = n - 1; i >= 0; i--) {
        swapArrayItems(nodeArr, 0, i);
        heapify(nodeArr, i, 0);
    }
}
