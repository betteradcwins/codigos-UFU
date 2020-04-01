#include "tadlistDL.h"
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define OUT_OF_MEMORY -1
#define ELEM_NOT_FOUND -2

struct list
{
    Node *begin;
    Node *end;
    unsigned size;
};

struct node
{
    Node *prev;
    Student data;
    Node *next;
};


List *list_create(void){
    List *li = NULL;
    li = malloc(sizeof(List));
    
    if(!li)
        return NULL;

    li->begin = NULL;
    li->end = NULL;
    li->size = 0;

    return li;    
}


int list_push_front(List *li, Student st){
    if(!li)
        return OUT_OF_MEMORY;

    Node *li_no = NULL;
    li_no = malloc(sizeof(Node));

    if(!li_no)
        return OUT_OF_MEMORY;

    li_no->data = st;
    li_no->next = li->begin;
    li_no->prev = NULL;

    if(!li->begin)
        li->end = li_no;
    else
        li->begin->prev = li_no;
    
    li->begin = li_no;
    li->size++;
    return SUCCESS;
}

int list_push_back(List *li, Student st){
    if(!li)
        return OUT_OF_MEMORY;

    Node *li_no = NULL;
    li_no = malloc(sizeof(Node));
    
    if(!li_no)
        return OUT_OF_MEMORY;
    
    li_no->data = st;
    li_no->next = NULL;
    li_no->prev = li->end;

    if(!li->begin)
        li->begin = li_no;
    else
        li->end->next = li_no;
    
    li->end = li_no;
    li->size++;
    return SUCCESS;
}

int list_insert_position(List *li, int pos, Student st){
    if(!li)
        return OUT_OF_MEMORY;
    
    if(pos <= 1)
        return list_push_front(li,st);

    if(!li->begin)
        return list_push_front(li, st);

    if(li->size < pos)
        return list_push_back(li, st);

    Node *li_no = NULL;
    li_no = malloc(sizeof(Node));
    li_no->data = st;
    
    Node *p = NULL;
    int i = 0;

    for(i = 1, p = li->begin; i != pos; i++, p = p->next);

    li_no->prev = p->prev;
    li_no->next = p;
    p->prev->next = li_no;
    p->prev = li_no;
    li->size++;
    
    return SUCCESS;
}

int list_insert(List *li, Student st){
    if(!li)
        return OUT_OF_MEMORY;

    if(!li->begin)
        return list_push_front(li, st);

    Node *p = NULL;

    for(p = li->begin; p != NULL && st.enroll_num > p->data.enroll_num; p = p->next);

    if(!p)
        return list_push_back(li, st);

    if(!p->prev)
        return list_push_front(li, st);

    Node *li_no = NULL;
    li_no = malloc(sizeof(Node));
    li_no->data = st;

    li_no->prev = p->prev;
    li_no->next = p;
    p->prev->next = li_no;
    p->prev = li_no;
    li->size++;

    return SUCCESS;    
}

int list_pop_front(List *li){
    if(!li)
        return OUT_OF_MEMORY;
    if(!li->begin)
        return ELEM_NOT_FOUND;

    if(li->size == 1){
        free(li->begin);
        li->begin = NULL;
        li->end = NULL;
        li->size--;
        return SUCCESS;
    }

    li->begin = li->begin->next;
    free(li->begin->prev);
    li->begin->prev = NULL;
    li->size--;

    return SUCCESS;
}

int list_pop_back(List *li){
    if(!li)
        return OUT_OF_MEMORY;
    if(!li->begin)
        return ELEM_NOT_FOUND;
    
    if(li->size == 1){
        free(li->end);
        li->begin = NULL;
        li->end = NULL;
        li->size--;
        return SUCCESS;
    }

    li->end = li->end->prev;
    free(li->end->next);
    li->end->next = NULL;
    li->size--;

    return SUCCESS;
}

int list_remove(List *li, int enroll){
    if(!li)
        return OUT_OF_MEMORY;
    if(!li->begin)
        return ELEM_NOT_FOUND;

    Node *p = NULL;
    for(p = li->begin; p != NULL && enroll != p->data.enroll_num; p = p->next);

    if(!p)
        return ELEM_NOT_FOUND;
    
    if(!p->prev)
        return list_pop_front(li);
    
    if(!p->next)
        return list_pop_back(li);
    
    p->prev->next = p->next;
    p->next->prev = p->prev;
    free(p);
    li->size--;
    
    return SUCCESS;
}

int list_eraser(List *li, int position){
    if(!li)
        return OUT_OF_MEMORY;
    
    if(!li->begin)
        return ELEM_NOT_FOUND;

    if(position <= 0 || position > li->size)
        return ELEM_NOT_FOUND;
    
    Node *p = NULL;
    p = li->begin;
    for(int i = 1; i != position && p != NULL; p = p->next, i++);

    if(!p)
        return ELEM_NOT_FOUND;
    
    if(!p->prev)
        return list_pop_front(li);
    
    if(!p->next)
        return list_pop_back(li); 
    
    p->prev->next = p->next;
    p->next->prev = p->prev;
    free(p);
    li->size--;

    return SUCCESS;
}

int list_front(List *li, Student *st){
    if(!li)
        return OUT_OF_MEMORY;
    
    if(!li->begin)
        return ELEM_NOT_FOUND;
    
    *st = li->begin->data;
    
    return SUCCESS;
}

int list_back(List *li, Student *st){
    if(!li)
        return OUT_OF_MEMORY;
    
    if(!li->end)
        return ELEM_NOT_FOUND;
    
    *st = li->end->data;

    return SUCCESS;
}

int list_find(List *li, Student *st, int enroll){
    if(!li)
        return OUT_OF_MEMORY;

    if(!li->begin)
        return ELEM_NOT_FOUND;
    
    Node *p = NULL;
    for(p = li->begin; p != NULL && enroll != p->data.enroll_num; p = p->next);

    if(!p)
        return ELEM_NOT_FOUND;
    
    *st = p->data;

    return SUCCESS;
}

int list_fbp(List *li, Student *st, int position){
    if(!li)
        return OUT_OF_MEMORY;
    
    if(!li->begin)
        return ELEM_NOT_FOUND;
    
    if(position <= 0 || position > li->size)
        return ELEM_NOT_FOUND;
    
    Node *p = NULL;
    p = li->begin;
    for(int i = 1; i != position && p != NULL; i++, p = p->next);

    if(!p)
        return ELEM_NOT_FOUND;
    
    *st = p->data;

    return SUCCESS;
}

int list_get_position(List *li, int enroll, int *position){
    if(!li)
        return OUT_OF_MEMORY;
    
    if(!li->begin)
        return ELEM_NOT_FOUND;
    
    Node *p = NULL;
    int i = 0;
    for(p = li->begin, i = 1; p != NULL && p->data.enroll_num != enroll; i++, p = p->next);

    if(!p)
        return ELEM_NOT_FOUND;

    *position = i;
    return SUCCESS;

}

int list_size(List *li){
    if(!li)
        return OUT_OF_MEMORY;
    return li->size;
}

/* feita por mim */ 
/*int list_free(List *li){
    if(!li)
        return OUT_OF_MEMORY;
    
    Node *p = NULL;
    p = li->begin;

    while(p){
        li->begin = p->next;
        free(p);
        li->size--;
        p = li->begin;
    }
    free(li);
    return SUCCESS;
}*/

/* feita pelo professor */
int list_free(List *li){
   if (li == NULL){
      return -1;
   } else {
       Node *p;
       p = li->begin;
       while (p != NULL){
            li->begin = p->next;
            free(p);
            p = li->begin;
        }
        free(li);
        return 0;
   }
};

void list_show(List *li){
    Node *p = NULL;
    int i = 1;
    for(p = li->begin; p != NULL; p = p->next, i++){
        if(i == 1)
            printf("\nStudent in %dst position\n", i);
        else if(i == 2)
            printf("\nStudent in %dnd position\n", i);
        else if(i == 3)
            printf("\nStudent in %drd position\n", i);
        else
            printf("\nStudent in %dth position\n", i);        
        puts("------------------------------------------");
        printf("Element address is %p\n", p);
        printf("Name: %s\n", p->data.name);
        printf("Enroll number: %d\n", p->data.enroll_num);
        for(int i = 0; i < 3; i++)
            printf("Grade(%d): %.2f\n", i+1, p->data.grades[i]);
        printf("Previous element address is %p\n", p->prev);
        printf("Next element address is %p\n", p->next);
        printf("\n");
    }
}