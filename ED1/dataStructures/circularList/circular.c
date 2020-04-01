#include <stdlib.h>
#include "circular.h"
#include <stdio.h>

struct list{
    Node* end;
    Node* next;
    int size;
};

struct node{
    Student data;
    Node* next;
};

int list_next(List* ls, Student* st){
    if(!ls)
        return -1;
    
    if(!ls->end)
        return -2;
    
    *st = ls->next->data;
    ls->next = ls->next->next;
    
    return 0;
}

List* list_create(void){
    List* ls = NULL;
    ls = malloc(sizeof(List));

    if(!ls)
        return NULL;
    
    ls->end = NULL;
    ls->next = NULL;
    ls->size = 0;

    return ls;
}

int list_free(List* ls){
    if(!ls)
        return -1;
    
    for(Node* p = ls->end; ls->size > 0; ls->size--){
        ls->end = p->next;
        free(p);
        p = ls->end;
    }
    free(ls); 

    return 0;
}

int list_push_front(List* ls, Student st){
    if(!ls)
        return -1;
    
    Node* new = NULL;
    new = malloc(sizeof(Node));
    new->data = st;

    if(!new)
        return -1;

    if(!ls->end){
        ls->end = new;
        new->next = new;
        ls->next = ls->end;
        ls->size++;
        return 0;
    }

    new->next = ls->end->next;
    ls->end->next = new;
    ls->size++;
    return 0;
}

int list_push_back(List* ls, Student st){
    if(!ls)
        return -1;
    
    if(!ls->end)
        return list_push_front(ls, st);
    
    Node* new = NULL;
    new = malloc(sizeof(Node));
    
    if(!new)
        return -1;

    new->data = st;
    new->next = ls->end->next;
    ls->end->next = new;
    ls->end = new;
    ls->size++;
    return 0;
}

int list_push(List* ls, Student st){
    if(!ls)
        return -1;
    
    if(!ls->end)
        return list_push_front(ls, st);
    
    Node* p = NULL;
    Node* psave = NULL;
    int i = ls->size;

    for(p = ls->end->next; i > 0 && st.enroll > p->data.enroll; p = p->next, i--)
        psave = p;
    
    if(i == ls->size)
        return list_push_front(ls, st);

    if(!i)
        return list_push_back(ls, st);
    
    Node* new = NULL;
    new = malloc(sizeof(Node));
    if(!new)
        return -1;
    
    new->data = st;
    psave->next = new;
    new->next = p;
    ls->size++;
    return 0;
}

int list_pop_back(List* ls){
    if(!ls)
        return -1;
    
    if(!ls->end)
        return -2;

    Node* end = ls->end;

    for(ls->end = ls->end->next; ls->end->next != end; ls->end = ls->end->next);
    
    if(ls->next == end)
        ls->next = end->next;

    ls->end->next = end->next;
    free(end);
    ls->size--;

    if(!ls->size)
        ls->end = NULL;
    
    return 0;
}

int list_pop_front(List* ls){
    if(!ls)
        return -1;
    
    if(!ls->end)
        return -2;
    
    Node* first = ls->end->next;

    if(ls->next == first)
        ls->next = first->next;

    ls->end->next = first->next;
    free(first);
    ls->size--;
    
    if(!ls->size)
        ls->end = NULL;
    
    return 0;
}

int list_erase(List* ls, int pos){
    if(!ls)
        return -1;
    
    if(!ls->end || pos <= 0 || pos > ls->size)
        return -2;
    
    Node* temp = NULL;
    Node* aux = NULL;

    if(pos == ls->size)
        return list_pop_back(ls);

    for(temp = ls->end; pos > 1; temp = temp->next, pos--);
    
    if(ls->next == temp->next)
        ls->next = temp->next->next;

    aux = temp->next;
    temp->next = temp->next->next;
    free(aux);
    ls->size--;

    if(!ls->size)
        ls->end = NULL;
    
    return 0;
}

int list_front(List* ls, Student* st){
    if(!ls)
        return -1;

    if(!ls->end)
        return -2;
    
    *st = ls->end->next->data;
    return 0;
}

int list_back(List* ls, Student* st){
    if(!ls)
        return -1;

    if(!ls->end)
        return -2;
    
    *st = ls->end->data;
    return 0;
}

int list_consult(List* ls, Student* st, int erl){
    if(!ls)
        return -1;
    
    if(!ls->end)
        return -2;
    
    Node* end = NULL;
    int i = 1;
    
    for(end = ls->end->next; i <= ls->size && erl != end->data.enroll; end = end->next, i++);

    if(i == ls->size+1)
        return -2;

    *st = end->data;
    return 0;
}

int list_size(List* ls){
    if(!ls)
        return -1;
    else
        return ls->size;
}

int list_empty(List* ls){
    if(!ls)
        return 1;
    else if(!ls->size)
        return 1;
    else
        return 0;
}

void list_show(List *ls){
    if(!ls->end)
        return;

    Node *p = NULL;
    int i = 1;
    for(p = ls->end->next; i <= ls->size; p = p->next, i++){
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
        printf("Enroll number: %d\n", p->data.enroll);
        for(int i = 0; i < 3; i++)
            printf("Grade(%d): %.2f\n", i+1, p->data.grades[i]);
        printf("Next element address is %p\n", p->next);
        printf("\n");
    }
}