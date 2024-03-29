#ifndef BST_H
#define BST_H

#include "heap.h"

struct bNode {
    struct bNode *right;
    struct bNode *left;
    Item *item;
} n;

typedef struct bNode BSTNode;

BSTNode *addNewNode(char *key, TYPE value);

BSTNode *newNodeByItem(Item *item);

BSTNode *insertByItem(BSTNode *current, Item *item);

BSTNode *insert(BSTNode *current, char *key, TYPE value);

void inOrder(BSTNode *root);

int Search(BSTNode *root, char *key, double *value);

BSTNode* delete(BSTNode* root, char* data);

void bstToItemArray(BSTNode *node, Item **items, int *i) ;

#endif