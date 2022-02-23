#ifndef TOOLS_H
#define TOOLS_H

#include "DataStructures/stack.h"
#include "DataStructures/types.h"

int charType(char c);
int precedence(char c);

void deblank(char *s);

Element charToElement(char c);

Element doubleToElement(double d);
int isComment(char* instruction);
int isIfStatement(char * instruction);
void printItems(Item** items, int counter);

/** Tools */

#endif

