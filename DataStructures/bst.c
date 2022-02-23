#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"


// adds new node to bst
BSTNode *addNewNode(char *key, TYPE value) {
    BSTNode *bstNode = (BSTNode *) malloc(sizeof(BSTNode));
    bstNode->left = NULL;
    bstNode->right = NULL;
    bstNode->item = newItem(key, value);
    bstNode->item->value = value;
    strcpy(bstNode->item->key, key);
    return bstNode;
}

// Create new node from item struct
BSTNode *newNodeByItem(Item *item) {
    BSTNode *bstNode = (BSTNode *) malloc(sizeof(BSTNode));
    bstNode->left = NULL;
    bstNode->right = NULL;
    bstNode->item = item;
    return bstNode;
}

// Inserts new node to bst by key and value
BSTNode *insert(BSTNode *current, char *key, TYPE value) {
    if (!current)
        return addNewNode(key, value);
    if (strcmp(key, current->item->key) < 0)
        current->left = insert(current->left, key, value);
    else if (strcmp(key, current->item->key) > 0)
        current->right = insert(current->right, key, value);
    else
        current->item->value = value;
    return current;
}

// Inserts new node to bst using item
BSTNode *insertByItem(BSTNode *current, Item *item) {
    if (!current)
        return newNodeByItem(item);
    if (strcmp(item->key, current->item->key) < 0)
        current->left = insert(current->left, item->key, item->value);
    else if (strcmp(item->key, current->item->key) > 0)
        current->right = insert(current->right, item->key, item->value);
    else
        current->item->value = item->value;
    return current;
}


// Iterates over the tree in order
void inOrder(BSTNode *root) {
    if (root) {
        inOrder(root->left);
        printf("%s  =    %0.2f \n", root->item->key, root->item->value);
        inOrder(root->right);
    }
}


// Search for a key in tree
int Search(BSTNode *root, char *key, double *value) {
    BSTNode *current = root;
    while (current != NULL) {
        if (strcmp(current->item->key, key) == 0) {
            *value = current->item->value;
            return 1;
        } else if (strcmp(current->item->key, key) > 0) {
            if (current->left == NULL) break;
            else current = current->left;
        } else {
            if (current->right == NULL) break;
            else current = current->right;
        }
    }
    return 0;
}

// Gets the value of the min node in tree
BSTNode * minValueNode(BSTNode* node)
{
    BSTNode* current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

// Free node
void freeNode(BSTNode *node){
    free(node->item->key);
    free(node);
}

// Deletes Node from BST
BSTNode* delete(BSTNode* root, char* data){
    if(root == NULL) return NULL;

    if(strcmp(data,root->item->key) < 0)
        root->left = delete(root->left,data);

    else if(strcmp(data,root->item->key) > 0)
        root->right = delete(root->right,data);

    else{
        if(root->left == NULL&& root->right == NULL){
            freeNode(root);
            return NULL;
        }
        if(root->left == NULL){
            BSTNode* temp = root->right;
            freeNode(root);
            return temp;
        }
        else if (root->right == NULL){
            BSTNode* temp = root->left;
            freeNode(root);
            return temp;
        }
        BSTNode* temp = minValueNode(root->right);

        free(root->item->key);
        root->item->key= malloc(strlen(temp->item->key)+1);
        strcpy(root->item->key,temp->item->key);

        root->right = delete(root->right,temp->item->key);

    }
    return root;
}

// Converts BST to Item Array
void bstToItemArray(BSTNode *node, Item **items, int *i) {
    if (node) {
        *(items + *i) = node->item;
        *i = *i + 1;
        bstToItemArray(node->left, items, i);
        bstToItemArray(node->right, items, i);
    }
}