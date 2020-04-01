#include <stdlib.h>
#include "stack.h"

struct stack{
    Node* top;
};

struct node{
    Point data;
    Node* next;
};

Stack* stack_create(void){
    Stack* st = NULL;
    st = malloc(sizeof(Stack));

    if(!st)
        return NULL;
    
    st->top = NULL;

    return st;
}

int stack_push(Stack* st, Point pt){
    if(!st)
        return -1;

    Node* new = NULL;
    new = malloc(sizeof(Node));
    if(!new)
        return -1;

    new->data = pt;

    if(!st->top)
        new->next = NULL;
    else
        new->next = st->top;
    
    st->top = new;
    return 0;
}

int stack_pop(Stack* st){
    if(!st)
        return -1;
    
    if(!st->top)
        return -2;

    Node* pop = NULL;
    pop = st->top;
    st->top = st->top->next;
    free(pop);
    return 0;
}

int stack_top(Stack* st, Point* pt){
    if(!st)
        return -1;
    
    if(!st->top)
        return -2;
    
    *pt = st->top->data;
    return 0;
}

int stack_free(Stack* st){
    if(!st)
        return 0;
    
    if(st->top){
        for(Node* fr = st->top; fr != NULL; fr = st->top){
            st->top = fr->next;
            free(fr);
        }
    }
    free(st);
    return 0;    
}

int stack_empty(Stack* st){
    if(!st)
        return 1;
    else if(!st->top)
        return 1;
    else
        return 0;
}