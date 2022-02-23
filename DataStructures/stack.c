#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

// Creates new Stack Node
StackNode *newStackNode(Element element) {
    StackNode *newStackNode = malloc(sizeof(StackNode));
    newStackNode->element = element;
    newStackNode->next = NULL;
    return newStackNode;
}

// Creates new Stack
Stack *newStack() {
    Stack *stack = malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

// Pushes an element into the stack
void push(Stack *stack, Element element) {
    StackNode *stackNode = newStackNode(element);
    stackNode->next = stack->top;
    stack->top = stackNode;
}

// Pops an element out of the stack
Element pop(Stack *stack) {
    StackNode *temp = stack->top;
    Element element = temp->element;
    stack->top = temp->next;
    free(temp);
    return element;
}

// Gets the element on the top of the stack
Element top(Stack *stack) {
    return stack->top->element;
}

// Checks if a stack is empty
int isEmpty(Stack *stack) {
    if (stack->top)
        return 0;
    else
        return 1;
}

// destroys the stack
void destroy(Stack *stack) {
    while (!isEmpty(stack))
        pop(stack);
    free(stack);
}

