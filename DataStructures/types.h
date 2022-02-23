#ifndef TYPES_H
#define TYPES_H

#define TYPE double

#include <stdio.h>

struct Item {
    char *key;
    TYPE value;
};

typedef struct Item Item;

Item *newItem(char *key, TYPE val);

#endif
