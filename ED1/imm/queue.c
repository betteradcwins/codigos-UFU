#include <stdlib.h>
#include "queue.h"

struct queue{
    Node* front;
    Node* end;
};

struct node{
    Point data;
    Node* next;
};

Queue* queue_create(void){
    Queue* qu = NULL;
    qu = malloc(sizeof(Queue));

    if(!qu)
        return NULL;
    
    qu->front = NULL;
    qu->end = NULL;

    return qu;
}

int queue_push(Queue* qu, Point pt){
    if(!qu)
        return -1;

    Node* push = NULL;
    push = malloc(sizeof(Node));
    if(!push)
        return -1;
    
    push->data = pt;
    push->next = NULL;

    if(!qu->front){
        qu->front = push;
        qu->end = push;
        return 0;
    }

    qu->end->next = push;
    qu->end = push;

    return 0;
}

int queue_pop(Queue* qu){
    if(!qu)
        return -1;

    if(!qu->front)
        return -2;
    
    if(qu->front == qu->end)
        qu->end = NULL;

    Node* pop = qu->front;
    qu->front = qu->front->next;
    free(pop);
    return 0;
}

int queue_front(Queue* qu, Point* pt){
    if(!qu)
        return -1;
    
    if(!qu->front)
        return -2;
    
    *pt = qu->front->data;

    return 0;
}

int queue_free(Queue* qu){
    if(!qu)
        return -1;
    
    if(qu->front){
        qu->end = NULL;
        for(Node* fr = qu->front; fr != NULL; fr = qu->front){
            qu->front = qu->front->next;
            free(fr);
        }
    }
    free(qu);
    return 0;
}

int queue_empty(Queue *qu){
    if(!qu)
        return -1;
    else if(!qu->front)
        return 1;
    else
        return 0;
}