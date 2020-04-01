#include <stdio.h>
#include <stdlib.h>
#include "tadlistaencadeada.h"

#define SUCCESS 0
#define OUT_OF_MEMORY -1
#define ELEM_NOT_FOUND -2

typedef struct lista_no Lista_no;

/*struct lista - guarda o ponteiro que aponta pro primeiro elemento dá lista*/
struct lista{
    Lista_no *head;
};

/*struct lista_no - guarda os dados de um aluno e aponta para o proximo nó*/
struct lista_no{
    aluno dado;
    Lista_no *prox;
};

/*
* cria_lista - aloca dinamicamente a cabeça da lista encadeada
* return - endereço da alocação ou NULL caso ocorra algum erro
* parameters - void
*/
Lista *cria_lista(void){
    Lista *li = NULL;
    li = malloc(sizeof(Lista));
    li->head = NULL;
    return li;
}

/*
* consulta_lista_pos - faz uma busca pelos dados do aluno na lista de uma posição
* parameters - endereço da lista, inteiro posição, ponteiro para aluno
* return - 0 para sucesso, -1 para erro de memória, -2 para elemento não encontrado, -3 tipo incorreto de lista
*/
int consulta_lista_pos(Lista *li, int pos, aluno *al){
    Lista_no *p = NULL;
    int i = 1;
    
    if(!li)
        return OUT_OF_MEMORY;

    for(p = li->head; p != NULL && i != pos; p = p->prox,  i++);//verifica a posição

    if(!p) //se for NULL retorna elemento não encontrado
        return ELEM_NOT_FOUND;
    
    *al = p->dado; //struct aluno al recebe conteúdo do ponteiro para dado
    
    return SUCCESS;
}

/*
* consulta_lista_mat - faz uma busca pelos dados do aluno de uma matricula na lista
* parameters - endereço da lista, inteiro matricula e endereço estrutura alunos
* return - 0 para sucesso, -1 para erro de memória, -2 para elemento não encontrado, -3 tipo incorreto de lista
*/
int consulta_lista_mat(Lista *li, int mat, aluno *al){
    Lista_no *p = NULL;

    if(!li)
        return OUT_OF_MEMORY;

    for(p = li->head; p != NULL && mat != p->dado.matricula; p = p->prox);//verifica a matricula

    if(!p)//se for NULL retorna elemento não encontrado
        return ELEM_NOT_FOUND;

    *al = p->dado; //struct aluno al recebe conteúdo do ponteiro para dado
    return SUCCESS;
}

/*
* insere_lista_final - insere um elemento no final da lista
* parameters - endereço da li, e estrutura aluno
* return - 0 para sucesso, -1 para erro de memória, -2 para elemento não encontrado, -3 tipo incorreto de lista
*/
int insere_lista_final(Lista *li, aluno al){
    if(!li)
        return OUT_OF_MEMORY;

    Lista_no *li_no = NULL;
    li_no = malloc(sizeof(Lista_no));
    
    if(!li_no)
        return OUT_OF_MEMORY;
    
    li_no->dado = al; //recebe o conteúdo de al
    li_no->prox = NULL; //recebe NULL, pois é o novo final da lista

    if(!li->head){
        li->head = li_no;
        return SUCCESS;
    }

    Lista_no *p = NULL;

    for(p = li->head; p->prox != NULL;p = p->prox);

    p->prox = li_no;

    return SUCCESS;
}

/*
* insere_lista_inicio - insere um elemento no inicio da lista
* parameters - endereço da li, e estrutura aluno
* return - 0 para sucesso, -1 para erro de memória, -2 para elemento não encontrado, -3 tipo incorreto de lista
*/
int insere_lista_inicio(Lista *li, aluno al){
    if(!li)
        return OUT_OF_MEMORY;

    Lista_no *li_no = NULL;
    li_no = malloc(sizeof(Lista_no));
    
    if(!li_no)
        return OUT_OF_MEMORY;

    li_no->dado = al;//recebe conteúdo de al
    li_no->prox = li->head; //recebe o endereço apontado por li->head
    li->head = li_no; //recebe o endereço de li_no
    
    return SUCCESS;
}

/*
* insere_lista_pos - insere um elemento na posição específica da lista
* parameters - endereço da li, inteiro para posição e estrutura aluno
* return - 0 para sucesso, -1 para erro de memória, -2 para elemento não encontrado, -3 tipo incorreto de lista
*/
int insere_lista_pos(Lista *li, int pos, aluno al){
    int i = 1;

    if(!li)
        return OUT_OF_MEMORY;

    if(pos == 1){
        insere_lista_inicio(li, al);
        return SUCCESS;
    }

    Lista_no *p = NULL;
    Lista_no *psave = NULL;
    
    for(p = li->head; i != pos && p != NULL; p = p->prox, i++)//caminha na lista até a posição ser encontrada ou o ponteiro apontar para NULL
        psave = p; //salva o ponteiro antes de ser incrementado

    if(!p)//se ponteiro for NULL insere no final
        insere_lista_final(li, al);
    else {
        Lista_no *li_no = NULL;
        li_no = malloc(sizeof(Lista_no));
        
        if(!li_no)
            return OUT_OF_MEMORY;

        li_no->dado = al;//recebe o conteúdo de al
        li_no->prox = p; //recebe o proximo ponteiro a ser apontado;
        psave->prox = li_no; //recebe o endereço de li_no;
    }
    return SUCCESS;
}

/*
* insere_lista_ordenada - insere de forma ordenada pela matrícula os alunos
* parameters - endereço da lista, estrutura aluno
* return - 0 para sucesso, -1 para erro de memória, -2 para elemento não encontrado, -3 tipo incorreto de lista
*/
int insere_lista_ordenada(Lista *li, aluno al){
    if(!li)
        return OUT_OF_MEMORY;

    Lista_no *li_no = NULL;
    li_no = malloc(sizeof(Lista_no));

    if(!li_no)
        return OUT_OF_MEMORY;

    Lista_no *p = NULL;
    Lista_no *psave = NULL;
    for(p = li->head; p != NULL && p->dado.matricula < al.matricula; p = p->prox)
        psave = p;

    if(!p){
        insere_lista_final(li,al);
        return SUCCESS;
    }

    if(!psave){
        insere_lista_inicio(li,al);
        return SUCCESS;
    }

    li_no->dado = al;
    li_no->prox = p;
    psave->prox = li_no;

    return SUCCESS;
}

/*
* remove_lista - remove um aluno dado a matrícula
* parameters - endereço da lista, inteiro matrícula
* return - 0 para sucesso, -1 para erro de memória, -2 para elemento não encontrado, -3 tipo incorreto de lista
*/
int remove_lista(Lista *li, int mat){
    if(!li)
        return OUT_OF_MEMORY;
    
    if(!li->head)
        return ELEM_NOT_FOUND;
    
    Lista_no *p = NULL;
    Lista_no *psave = NULL;
    for(p = li->head; p != NULL && mat != p->dado.matricula; p = p->prox)
        psave = p;

    if(!p)
        return ELEM_NOT_FOUND;

    if(!psave){
        li->head = p->prox;
        free(p);
        return SUCCESS;
    }

    psave->prox = p->prox;
    free(p);
    return SUCCESS;
}

/*
* remove_lista_inicio - remove o primeiro elemento da lista
* parameters - endereço da lista
* return - 0 para sucesso, -1 para erro de memória, -2 para elemento não encontrado, -3 tipo incorreto de lista
*/
int remove_lista_inicio(Lista *li){
    Lista_no *p = NULL;
    if(!li)
        return OUT_OF_MEMORY;

    if(!li->head)
        return ELEM_NOT_FOUND;

    p = li->head;
    p = p->prox;
    free(li->head);
    li->head = p;

    return SUCCESS;
}

/*
* remove_lista_final - remove ultimo elemento da lista
* parameters - endereço da lista
* return - 0 para sucesso, -1 para erro de memória, -2 para elemento não encontrado, -3 tipo incorreto de lista
*/
int remove_lista_final(Lista *li){
    Lista_no *p = NULL;
    Lista_no *psave = NULL;
    if(!li)
        return OUT_OF_MEMORY;
    
    if(!li->head)
        return ELEM_NOT_FOUND;

    for(p = li->head; p->prox != NULL; p = p->prox)
        psave = p;

    if(!psave){
        free(li->head);
        li->head = NULL;
        return SUCCESS;
    }
    
    psave->prox = NULL;
    free(p);
    return SUCCESS;
}

/*
* tamanho_lista - informa o tamanho da lista
* parameters - endereço da lista
* return - inteiro tamanho da lista
*/
int tamanho_lista(Lista *li){
    int i = 0;
    Lista_no *p = NULL;
    if(!li)
        return OUT_OF_MEMORY;
    
    for(p = li->head; p != NULL; p = p->prox, i++);

    return i;
}

/*
* lista_cheia - função ínutil;
*/
int lista_cheia(Lista *li){
    return SUCCESS;
}

/*
* lista_vazia - informa se a lista está vazia
* parameters - endereço da lista
* return - 0 para false ou 1 para true
*/
int lista_vazia(Lista *li){
    if(!li->head)
        return 1;
    else
        return 0;
}

/*
* libera_lista - desaloca a lista
* parameters - endereço da lista
* return - void
*/
void libera_lista(Lista *li){
    Lista_no *p = NULL;
    Lista_no *pfree = NULL;
    for(p = li->head; p != NULL;){
        pfree = p;
        p = p->prox;
        free(pfree);
    }
    free(li);
}

/*
* imprime_lista - imprime a lista
* return - void
* parameters - endereço da lista
*/
void imprime_lista(Lista *li){
    Lista_no *p = NULL;
    int j = 1;
    for(p = li->head; p != NULL; p = p->prox, j++){
        printf("\nAluno na %da posição\n", j);
        puts("------------------------------------------");
        printf("O endereço desse elemento é %p\n", p);
        printf("Nome: %s\n", p->dado.nome);
        printf("Matrícula: %d\n", p->dado.matricula);
        for(int i = 0; i < 3; i++)
            printf("Nota(%d): %.2f\n", i+1, p->dado.notas[i]);
        puts("------------------------------------------");
        printf("\n");
    }
}