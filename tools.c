#include <ctype.h>

#include "tools.h"
#include "DataStructures/types.h"

int charType(char c) {
    if (isdigit(c))
        return 1;
    if (isalpha(c) || c == '_' || c == '$')
        return 2;
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^')
        return 3;
    if (c == '.')
        return 4;
    if (c == '(' || c == '[' || c == '{')
        return 5;
    if (c == ')' || c == ']' || c == '}')
        return 6;
    return 0;
}

// Gives each item a precedence to do operations in correct order
int precedence(char c) {
    if (c == '+' || c == '-')
        return 1;
    if (c == '*' || c == '/' || c == '%')
        return 2;
    if (c == '^')
        return 3;
    return 0;
}

void deblank(char *s) {
    int i = 0, j;
    while (s[i]) {
        if (s[i] == ' ') {
            for (j = i; s[j]; j++) {
                s[j] = s[j + 1];
            }
        }
        if (s[i] != ' ')
            i++;
    }
}

// Returns element with char value in
Element charToElement(char c) {
    Element element;
    element.character = c;
    return element;
}

// Returns element with double value in
Element doubleToElement(double d) {
    Element element;
    element.constant = d;
    return element;
}

// Checks if the line is a comment
int isComment(char* instruction){
    if(instruction[0] == '/' && instruction[1] =='/')
        return 1;
    return 0;
}

// Checks if line is an if statement
int isIfStatement(char * instruction){
    int hasEqualEqual = 0;
    if(!(instruction[0] == 'i' && instruction[1] == 'f' && instruction[2] == ' '))
        return 0;
    int i = 3;
    do{
        if(charType(instruction[i]) != 2)
            return 0;
    } while (instruction[i++] == ' ');

    for (i; instruction[i]; ++i) {
        if(instruction[i] == '='){
            if(instruction[i+1] == '=')
                hasEqualEqual = 1;
        }
        if(instruction[i] == ':' && hasEqualEqual)
            return i;
    }
    return 0;
}

// prints list of items
void printItems(Item** items, int counter) {
    for (int i = 0; i < counter; i++) {
        printf("%s  =    %0.2f \n", (*(items+i))->key, (*(items+i))->value);
    }
}