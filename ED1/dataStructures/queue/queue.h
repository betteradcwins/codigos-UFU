typedef struct queue Queue;
typedef struct node Node;

typedef struct student
{
    int enroll;
    char name[51];
    float grades[3];
}Student;

Queue* queue_create(void);
void queue_free(Queue* qu);
int queue_push(Queue* qu, Student st);
int queue_front(Queue* qu, Student* st);
int queue_pop(Queue* qu);
int queue_size(Queue* qu);
int queue_empty(Queue *qu);