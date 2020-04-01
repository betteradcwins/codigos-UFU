#include "queue.h"
#include "stdlib.h"

struct queue{
    Node *begin;
    Node *end;
    int size;
};

struct node{
    Student data;
    Node *next;
};

Queue* queue_create(void){
    Queue* qu = NULL;
    qu = malloc(sizeof(Queue));
    
    if(!qu)
        return NULL;
    
    qu->begin = NULL;
    qu->end = NULL;
    qu->size = 0;

    return qu;
}

void queue_free(Queue* qu){
    if(!qu)
        return;
    
    qu->end = NULL;
    for(Node* p = qu->begin; p != NULL; qu->size--){
        qu->begin = p->next;
        free(p);
        p = qu->begin;
    }
    free(qu);
}

int queue_push(Queue* qu, Student st){
    if(!qu)
        return -1;

    Node* p = NULL;
    p = malloc(sizeof(Node));
    p->data = st;
    p->next = NULL;
    
    if(!qu->size){
        qu->begin = p;
        qu->end = p;
        qu->size++;
        return 0;
    }

    qu->end->next = p;
    qu->end = p;
    qu->size++;
    return 0;
}

int queue_front(Queue* qu, Student* st){
    if(!qu)
        return -1;
    
    if(!qu->size)
        return -2;
    
    *st = qu->begin->data;
    return  0;
}

int queue_pop(Queue* qu){
    if(!qu)
        return -1;
    
    if(!qu->size)
        return -2;
    
    if(qu->size == 1)
        qu->end = NULL;
    
    Node* p = qu->begin;
    qu->begin = p->next;
    free(p);
    qu->size--;
    return 0;
}

int queue_size(Queue* qu){
    if(!qu)
        return -1;
    else
        return qu->size; 
}

int queue_empty(Queue *qu){
    if(!qu)
        return -1;
    else if(!qu->size)
        return 1;
    else
        return 0;
}