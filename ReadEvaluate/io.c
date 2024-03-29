#include <string.h>
#include <stdio.h>

#include "../validations.h"
#include "../tools.h"
#include "io.h"

/** Processing Input from File */


// Parses expression into variable and  instruction
int parse(char *instruction, char **variable, char **expression) {
    char *cursor = instruction;
    int found = 0;
    while (*cursor) {
        if (*cursor == '=') {
            *cursor = '\0';
            *variable = instruction;
            *expression = cursor + 1;
            found = 1;
            break;
        }
        cursor++;
    }
    return found;
}

// Validates if condition
int validateIf(char *instruction, int end, BSTNode **root) {
    char leftHandSide[end];
    strcpy(leftHandSide, "");
    int i = 3;
    while (instruction[i] != '=') {
        if (instruction[i] == ' ') {
            i++;
            continue;
        }
        char dummy[2];
        dummy[0] = instruction[i];
        dummy[1] = '\0';
        strcat(leftHandSide, dummy);
        i++;
    }

    char rightHandSide[end];
    strcpy(rightHandSide, "");
    i = i + 2;
    while (i < end) {
        if (instruction[i] == ' ') {
            i++;
            continue;
        }
        char dummy[2];
        dummy[0] = instruction[i];
        dummy[1] = '\0';
        strcat(rightHandSide, dummy);
        i++;
    }

    BSTNode *copy = *root;
    char leftHandSideExpression[end + 7];
    strcpy(leftHandSideExpression, "_LHS = ");
    strcat(leftHandSideExpression, leftHandSide);

    compute(&copy, leftHandSideExpression, 1);

    char rightHandSideExpression[end + 7];
    strcpy(rightHandSideExpression, "_RHS = ");
    strcat(rightHandSideExpression, rightHandSide);
    compute(&copy,  rightHandSideExpression, 1);

    double valueOfLHS;
    double valueOfRHS;
    Search(copy, "_LHS", &valueOfLHS);
    Search(copy, "_RHS", &valueOfRHS);

    delete(copy, "_LHS");
    delete(copy, "_RHS");
    if (valueOfLHS != valueOfRHS)
        return 0;

    return 1;
}

// Makes sure the statement is correct then
// Computes the value of the expression
// Creates a BST node and insert it into the tree
void compute(BSTNode **root, char *instruction, int line) {
    char *variable, *expression;
    char copy[strlen(instruction)];
    int i;

    strcpy(copy, instruction);

    if (isComment(instruction)) return;

    if ((i = isIfStatement(instruction)) > 0) {
        if (validateIf(instruction, i, root))
            compute(root, &instruction[i + 1], line);
        return;
    }

    if (!parse(instruction, &variable, &expression)) {
        printf("Error in line %d : %s > Missing Equal sign\n", line, copy);
        return;
    }

    if (!validVariable(&variable)) {
        printf("Error in line %d : %s > More than one/Invalid variable\n", line, copy);
        return;
    }

    if (!validExpression(expression)) {
        printf("Error in line %d : %s > Invalid Expression\n", line, copy);
        return;
    }

    double value = 7;
    if (!evaluate(*root, expression, &value)) {
        printf("Error in line %d : %s > Error in Evaluation\n", line, copy);
        return;
    }

    *root = insert(*root, variable, value);
}

// Reads the input line by line from file
void readInput(FILE *file, BSTNode **root) {
    char input[256];
    int line = 1;
    while (!feof(file)) {
        fgets(input, 256, file);
        if (input[strlen(input) - 1] == '\n')
            input[strlen(input) - 1] = '\0';
        compute(root, input, line++);
    }
}

// Gets the file name and starts the process of reading the input
void process(BSTNode **root) {
    char filename[32];
    FILE *file;
    int found = 0;
    while (!found) {
        printf("Please enter source file:\n");
        fgets(filename, 32, stdin);
        filename[strlen(filename) - 1] = '\0';
        file = fopen(filename, "r");
        if (file) {
            found = 1;
            readInput(file, root);
        } else {
            printf("File not found!\n");
        }
    }
}