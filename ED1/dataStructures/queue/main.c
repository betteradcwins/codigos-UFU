#include <stdio.h>
#include "queue.h"

int main(void){
    int erro = 0;
    Queue *qu = queue_create();
    Student al = {245,"Breno", {9.4,8.3,10}};
    Student al3 = {252,"Samuel", {7.4,7.4,10}};
    Student al2;

    erro = queue_push(qu, al);
    if(erro)
        printf("Houve um erro\n");
    else {
        printf("\nO tamanho da fila é %d\n", queue_size(qu));
        erro = queue_front(qu, &al2);
        if(erro)
            printf("Houve um erro\n");
        else{
            printf("Nome: %s\n", al2.name);
            printf("matricula: %d\n", al2.enroll);
            for(int i = 0; i < 3; i++)
                printf("Nota(%d): %.2f\n", i+1, al2.grades[i]);
            erro = queue_pop(qu);
            if(erro)
                printf("Houve um erro\n");
            printf("\nO tamanho da fila é %d\n", queue_size(qu));
            
            erro = queue_push(qu, al3);
            if(erro)
                printf("Houve um erro\n");
            else{
                printf("\nO tamanho da fila é %d\n", queue_size(qu));            
                erro = queue_front(qu, &al2);
                if(erro)
                    printf("Houve um erro\n");
                else{
                    printf("Nome: %s\n", al2.name);
                    printf("matricula: %d\n", al2.enroll);
                    for(int i = 0; i < 3; i++)
                        printf("Nota(%d): %.2f\n", i+1, al2.grades[i]);
                    erro = queue_pop(qu);
                    if(erro)
                    printf("Houve um erro\n");
                }
                if(queue_empty(qu))
                    printf("\nFila vazia\n");
            }
        }
    }
        queue_free(qu);
        return 0;
}