#include "point.h"
typedef struct stack Stack;
typedef struct node Node;

Stack* stack_create(void);
int stack_push(Stack* st, Point pt);
int stack_top(Stack* st, Point* pt);
int stack_pop(Stack* st);
int stack_empty(Stack* st);
int stack_free(Stack* st);