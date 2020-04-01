#include <stdio.h>
#include <stdlib.h>
#include "tadlistaencadeada.h"
#include <string.h>

void menu1(void);
void preencheAluno(aluno *al);
void verificaErro(int erro);
void imprimeAluno(aluno al);

int main(void){
    int mat = 0;
    int erro = 0;
    int pos = 0;
    char escolha = '\0';
    aluno al;
    Lista *li = NULL;
    li = cria_lista();

    while(escolha == '\0'){
        menu1();

        printf("\nDigite uma opção: ");
        setbuf(stdin, NULL);
        scanf("%c", &escolha);
        getchar();

        switch (escolha){
            case '1':
                preencheAluno(&al);
                erro = insere_lista_final(li, al);
                verificaErro(erro);
                printf("\nO tamanho da lista é %d\n", tamanho_lista(li));
                escolha = '\0';
                break;
            
            case '2':
                preencheAluno(&al);
                erro = insere_lista_inicio(li, al);
                verificaErro(erro);
                printf("\nO tamanho da lista é %d\n", tamanho_lista(li));
                escolha = '\0';
                break;

            case '3':
                preencheAluno(&al);
                
                printf("\nInforme a posição que deseja inserir: ");
                setbuf(stdin, NULL);
                scanf("%d", &pos);
                getchar();

                erro = insere_lista_pos(li, pos, al);
                verificaErro(erro);
                printf("\nO tamanho da lista é %d\n", tamanho_lista(li));
                escolha = '\0';
                break;
            
            case '4':
                preencheAluno(&al);
                erro = insere_lista_ordenada(li, al);
                verificaErro(erro);
                printf("\nO tamanho da lista é %d\n", tamanho_lista(li));
                escolha = '\0';
                break;
            
            case '5':
                printf("\nInforme a matrícula do aluno que deseja remover: ");
                setbuf(stdin, NULL);
                scanf("%d", &mat);
                getchar();
    
                erro = remove_lista(li, mat);
                printf("\nO tamanho da lista é %d\n", tamanho_lista(li));
                escolha = '\0';
                break;
            
            case '6':
                erro = remove_lista_inicio(li);
                verificaErro(erro);
                printf("\nO tamanho da lista é %d\n", tamanho_lista(li));
                escolha = '\0';
                break;

            case '7':
                erro = remove_lista_final(li);
                verificaErro(erro);
                printf("\nO tamanho da lista é %d\n", tamanho_lista(li));
                escolha = '\0';
                break;
            
            case '8':
                printf("\nInforme a matrícula que deseja pesquisar: ");
                setbuf(stdin, NULL);
                scanf("%d", &mat);
                getchar();

                erro = consulta_lista_mat(li, mat, &al);
                verificaErro(erro);
                imprimeAluno(al);
                escolha = '\0';
                break;
            
            case '9':
                printf("\nInforme a posição que deseja pesquisar: ");
                setbuf(stdin, NULL);
                scanf("%d", &pos);
                getchar();

                erro = consulta_lista_pos(li, pos, &al);
                verificaErro(erro);
                imprimeAluno(al);
                escolha = '\0';
                break;
            
            case '0':
                imprime_lista(li);
                escolha = '\0';
                break;

            case 'q':
                libera_lista(li);
                printf("\nAté logo!!!\n");
                break;

            default:
                printf("\nOPÇÃO INVÁLIDA! DIGITE OUTRA!\n");
                escolha = '\0';
                break;
        }
    }
    return 0;
}

void menu1(void){
    puts("=================================================");
    puts("      Gerenciar lista encadeada de alunos");
    puts("=================================================");
    puts("Opções:");
    puts("1 - Inserir aluno no final da lista");
    puts("2 - Inserir aluno no início da lista");
    puts("3 - Inserir aluno em uma posição específica da lista");
    puts("4 - Inserir aluno ordenado pela matrícula");
    puts("5 - Remover aluno da lista pela matrícula");
    puts("6 - Remover aluno do início da lista");
    puts("7 - Remover aluno do final da lista");
    puts("8 - Consulta aluno pela matrícula");
    puts("9 - Consulta aluno pela posição");
    puts("0 - Imprimir lista de alunos");
    puts("q - Sair");
}


void preencheAluno(aluno *al){
    puts("\nInsira as informações do aluno");
    
    printf("Nome: ");
    setbuf(stdin, NULL);
    fgets(al->nome, sizeof(al->nome), stdin);
    al->nome[strcspn(al->nome, "\n")] = '\0';

    printf("Matrícula: ");
    setbuf(stdin, NULL);
    scanf("%d", &al->matricula);
    getchar();

    for(int i = 0; i < 3; i++){
        printf("Nota(%d): ", i+1);
        setbuf(stdin, NULL);
        scanf("%f", &al->notas[i]);
        getchar();
    }
}

void verificaErro(int erro){
    if(erro  == 0)
        printf("\nSucesso. Não houve erros!\n");
    else if(erro == -1){
        printf("\nOcorreu um erro. Problema na memória!\n");
        exit(1);
    } else if(erro == -2){
        printf("\nOcorreu um erro. Elemento não encontrado!\n");
        exit(1);
    }
    return;
}

void imprimeAluno(aluno al){
    printf("\nInformações do aluno\n");
        puts("------------------------------------------");
        printf("Nome: %s\n", al.nome);
        printf("Matrícula: %d\n", al.matricula);
        for(int i = 0; i < 3; i++)
            printf("Nota(%d): %.2f\n", i+1, al.notas[i]);
        puts("------------------------------------------");
        printf("\n");
}
