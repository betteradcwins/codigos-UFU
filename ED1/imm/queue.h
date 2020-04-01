#include "point.h"
typedef struct queue Queue;
typedef struct node Node;

Queue* queue_create(void);
int queue_push(Queue* st, Point pt);
int queue_front(Queue* st, Point* pt);
int queue_pop(Queue* st);
int queue_empty(Queue* st);
int queue_free(Queue* st);