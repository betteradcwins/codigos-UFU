typedef struct node Node;
typedef struct list List;

typedef struct student{
    int enroll;
    char name[51];
    float grades[3];
}Student;

List* list_create(void);
int list_free(List* ls);
int list_push_front(List* ls, Student st);
int list_push_back(List* ls, Student st);
int list_push(List* ls, Student st);
int list_pop_front(List* ls);
int list_pop_back(List* ls);
int list_erase(List* ls, int pos);
int list_front(List* ls, Student* st);
int list_back(List* ls, Student* st);
int list_consult(List* ls, Student* st, int erl);
int list_size(List* ls);
int list_empty(List* ls);
int list_next(List* ls, Student* st);
void list_show(List* ls);
