/*
 * @file students.c
 *
 * @brief O programa cria e executa alterações em um arquivo.txt, que terá como dados informações de alunos 
 *          de uma turma. Cada turma é um arquivo.txt, cada turma comporta no maximo 80 alunos. Cada aluno
 *          tem 10 itens de informação, sendo eles o nome, a matricula, nota da prova 1, prova 2, prova 3,
 *          nota do trabalho 1, trabalho 2, nota final, número de faltas, 
 *          situação do aluno (reprovado por falta, reprovado por nota, aprovado).
 *        Também é possível imprimir os alunos de uma turma, assim como sua estatistica.
 *        Se pode também alterar os dados de cada aluno da turma.
 * 
 *
 * @author Breno Henrique de Oliveira Ferreira 
 * @author Samuel Augusto Meireles da Silva
 * 
 * @date 19/12/2018
 *  
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "readData.h"
#include "menus.h"

#define ALUNOS    80    // tamanho do arranjo do tipo Estudante
#define ARQUIVO   20    // tamanho máximo do nome do arquivo.txt   
#define NOTAMEDIA 60    // media da nota necessária para ser aprovado  
#define MAXFALTAS 18    // faltas máximas para não ser reprovado


/**
 * @brief estrutura de dados contendo informacoes
 * de um estudante
*/

typedef struct
{
    char nome[51];
    char matricula[13];
    float provas[3];
    float trabalhos[2];
    float notaFinal;
    int faltas;
    char situacao;

} Estudante;


/**
 * @brief Protótipo de todas as funções utilizadas 
 * no programa
*/

void menuPrincipal(char nomeArquivo[ARQUIVO], Estudante alunos[ALUNOS], int load);
void lerTurma(char nomeArquivo[ARQUIVO], Estudante alunos[ALUNOS], int load);
void subirTurma(char nomeArquivo[ARQUIVO], Estudante alunos[ALUNOS], int load);
void criarTurma(char nomeArquivo[ARQUIVO], Estudante alunos[ALUNOS], int load);
void imprimeTurma(char nomeArquivo[ARQUIVO], Estudante alunos[ALUNOS], int load);
void menuCadastrarEstudante(char nomeArquivo[ARQUIVO], Estudante alunos[ALUNOS], int load);
double somaNotas(float provas[], float trabalhos[]);
char verificaSituacao(float x,int y);
void editaEstudante(char nomeArquivo[ARQUIVO], Estudante alunos[ALUNOS], int load);
void editaInfo(char nomeArquivo[ARQUIVO], Estudante alunos[ALUNOS], int load, int i);
void relerTurma(char nomeArquivo[ARQUIVO], Estudante alunos[ALUNOS], int load);
void salvarSair(char nomeArquivo[ARQUIVO], Estudante alunos[ALUNOS], int load);
void preencheArq(char nomeArquivo[ARQUIVO], Estudante alunos[ALUNOS], int load);


/*
 * @brief função que altera qualquer dado do estudante escolhido pela função editaEstudante();
 * 
 * @param char nomeArquivo[ARQUIVO], nome do arquivo carregado
 * @param Estudante alunos[ALUNO], dados dos alunos do arquivo
 * @param int load, indicador de arquivo carregado
 * @param int i, posiçao do estudante no arranjo de alunos
 *
 * @return void
*/
void editaInfo(char nomeArquivo[ARQUIVO], Estudante alunos[ALUNOS], int load, int i)
{
    setbuf(stdin, NULL);
    int j = 0;
    int escolha = 0;
    while(true){
        menuEditaInfo();
        escolha = lerOpcao(1 , 9);
        if(escolha == 1){
            printf("\nDigite o nome: ");
            fgets(alunos[i].nome, sizeof(alunos[i].nome), stdin);
            alunos[i].nome[strcspn(alunos[i].nome, "\n")] = '\0';
        }
        else if(escolha == 2){ 
        printf("\nDigite a matrícula: "); 
        fgets(alunos[i].matricula, sizeof(alunos[i].matricula), stdin); 
        alunos[i].matricula[strcspn(alunos[i].matricula, "\n")] = '\0';}
        else if(escolha == 3){ printf("\nDigite a nota da prova 1: "); scanf("%f",&alunos[i].provas[0]); }
        else if(escolha == 4){ printf("\nDigite a nota da prova 2: "); scanf("%f",&alunos[i].provas[1]); }
        else if(escolha == 5){ printf("\nDigite a nota da prova 3: "); scanf("%f",&alunos[i].provas[2]); }
        else if(escolha == 6){ printf("\nDigite a nota do trabalho 1: "); scanf("%f",&alunos[i].trabalhos[0]); }
        else if(escolha == 7){ printf("\nDigite a nota do trabalho 2: "); scanf("%f",&alunos[i].trabalhos[1]); }
        else if(escolha == 8){ printf("\nDigite o número de faltas: "); scanf("%d",&alunos[i].faltas); }
        else if(escolha == 9) break;
        setbuf(stdin, NULL);
    }
    alunos[i].notaFinal = somaNotas(alunos[i].provas, alunos[i].trabalhos);
    alunos[i].situacao = verificaSituacao(alunos[i].notaFinal,alunos[i].faltas);
    editaEstudante(nomeArquivo, alunos, load);
}// edita info


/*
 * @brief função que escolhe e envia para a função editaInfo(); o nome e a posição do aluno no arranjo de alunos
 * 
 * @param char nomeArquivo[ARQUIVO], nome do arquivo carregado
 * @param Estudante alunos[ALUNO], dados dos alunos do arquivo
 * @param int load, indicador de arquivo carregado
 *
 * @return void
*/


void editaEstudante(char nomeArquivo[ARQUIVO], Estudante alunos[ALUNOS], int load)
{
    setbuf(stdin, NULL);
    int escolha = 0;
    char matricula[13] = {'\0'};
    char nome[51] = {'\0'};
    int i = 0;
    if(load == 1){
            menuEditaEstudante();
            escolha = lerOpcao(1, 3);
            if(escolha == 1){
                printf("\nDigite o número de matrícula: ");
                fgets(matricula, sizeof(matricula), stdin);
                matricula[strcspn(matricula, "\n")] = '\0';
                for(i = 0; i < ALUNOS ; i++)
                    if(strcmp(matricula,alunos[i].matricula)==0)
                        break;
                if(i == ALUNOS){ 
                    printf("\nNúmero de matrícula inválido!\n");
                    editaEstudante(nomeArquivo, alunos, load);}
                else 
                    editaInfo(nomeArquivo, alunos, load, i);
            }
            else if(escolha == 2){
                printf("\nDigite o nome do aluno: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';             
                for(i = 0;i<ALUNOS;i++)
                    if(strcmp(nome,alunos[i].nome)==0)
                        break; 
                if(i == ALUNOS){
                    printf("\nNome inválido!\n");
                    editaEstudante(nomeArquivo, alunos, load);}
                else
                    editaInfo(nomeArquivo, alunos, load, i);    
            }
            else if(escolha == 3)
                menuPrincipal(nomeArquivo, alunos, load);
            else{
                printf("\nValor inválido, digitar outro\n");
                editaEstudante(nomeArquivo, alunos, load);
            }
    } else {printf("\nNão há turma carregada!\n"); menuPrincipal(nomeArquivo, alunos, load);}
    return;
}// edita estudante


/**
 * @brief função que recebe dois arranjos float e faz a soma  
 * dos valores recebidos, retorna a soma dos valores
 * @param float provas[], 3 valores de 3 provas
 * @param float trabalhos[], 2 valores de 2 trabalhos
 *
 * @return float somaTotal, soma dos valores 
 */

double somaNotas(float provas[], float trabalhos[])
{
    double somaTotal = 0.0;
    for(int i = 0; i < 3; i++)
        somaTotal += provas[i];

    for(int i = 0; i < 2; i++)
        somaTotal += trabalhos[i];

    return somaTotal;
}// soma notas


/**
 * @brief função que recebe dois valores, um float da nota total e outro int do numero de faltas,
 * depois compara com duas constantes, uma de MAXFALTAS e outra de NOTAMEDIA.
 * Se o número de faltas for maior que o MAXFALTAS, independente da nota, 
 * o aluno está com a situação em F ( Reprovado por falta ),
 * se a nota total for menor que a NOTAMEDIA e o numero de faltas menor que MAXFALTAS
 * o aluno esta com a situação em R ( Reprovado por nota)
 * e se o aluno está com a nota maior que NOTAMEDIA e com o numero de faltas menor que MAXFALTAS,
 * entao ele esta com a situação em A ( Aprovado )
 * 
 * @param float x, nota total do aluno
 * @param int y, numero de faltas do aluno
 *
 * @return char z, situação do aluno ( A ou R ou F) 
 */

char verificaSituacao(float x,int y)
{
  char z = '\0';
  
  if(y>MAXFALTAS){z = 'F';}
  else if(x<NOTAMEDIA){z = 'R';}
  else{z = 'A';}

  return z;
  
}// verifica situação


/**
 * @brief função que recebe dois arranjos um do tipo char e outro do tipo Estudante e um int.  
 * O int indica se há uma turma carregada, se for 0 não há, se for 1 há uma turma carregada.
 * O arranjo de char é o nome do arquivo carregado, se existir.
 * O arranjo do tipo Estudante é os alunos cadastrados e os espaços para alunos ainda não cadastrados.
 * Depois de verificar se há uma turma carregada, são pedidos os dados do estudante, que serão gravados em uma
 * variavel do tipo Estudante e se ja existir algum aluno ele começa a gravar a partir da proxima posiçao disponivel.
 *
 * @param char nomeArquivo[ARQUIVO], nome do arquivo lido, se for lido
 * @param Estudante alunos[ALUNOS], dados dos alunos
 * @param int load, indicador se há arquivo carregado
 *
 * @return void 
 */

void menuCadastrarEstudante(char nomeArquivo[ARQUIVO], Estudante alunos[ALUNOS], int load)
{
  if(load == 0){
    printf("\nNão há turma carregada!\n");
    menuPrincipal(nomeArquivo, alunos, load);
  }// if
  
  else{
    puts("\n========================================");
    puts("       Cadastrar Novo Estudante");
    puts("========================================");

    Estudante aux = {{'\0'},{'\0'},{0.0},{0.0},0,0.0,'\0'};
    int i = 0;
    
    printf("\nDigite o nome: ");

    fgets(aux.nome, sizeof(aux.nome), stdin);
    aux.nome[strcspn(aux.nome, "\n")] = '\0';

    printf("Digite a matrícula: ");
    scanf("%s",aux.matricula);getchar();
    printf("Digite as três notas das provas: ");
    scanf("%f %f %f",&aux.provas[0],&aux.provas[1],&aux.provas[2]);getchar();
    printf("Digite as duas notas dos trabalhos: ");
    scanf("%f %f",&aux.trabalhos[0],&aux.trabalhos[1]);getchar();
    printf("Digite o número de faltas: ");
    scanf("%d",&aux.faltas);getchar();
    
    aux.notaFinal = somaNotas(aux.provas, aux.trabalhos);
    
    printf("\nNota final calculada: %.1f",aux.notaFinal);

    aux.situacao = verificaSituacao(aux.notaFinal,aux.faltas);
    if(aux.situacao == 'A'){printf("\nSituação final: Aprovado\n");}
    else if(aux.situacao == 'R'){printf("\nSituação final: Reprovado\n");}
    else{printf("\nSituação final: Reprovado por faltas\n");}
    
    //coloca esse estudante na proxima posicao disponivel
    int j = 0;
    while(alunos[j].nome[0] != '\0')
    {
      j++;
    }
    alunos[j] = aux;
  }// else
  menuPrincipal(nomeArquivo, alunos, load);
}// menu cadastro


/*
 * @brief função mostra a porcentagem de alunos aprovados, reprovados e reprovados por falta e imprime eles
 * 
 * @param char nomeArquivo[ARQUIVO], nome do arquivo carregado
 * @param Estudante alunos[ALUNO], dados dos alunos do arquivo
 * @param int load, indicador de arquivo carregado
 *
 * @return void
*/

void estatisticaTurma2(char nomeArquivo[ARQUIVO], Estudante alunos[ALUNOS], int load)
{
    int i = 0;
    int aprovado = 0;
    int reprovado = 0;
    int rfaltas = 0;
    double porcaprov = 0.0;
    double porcreprov = 0.0;
    double porcrfaltas = 0.0;
    for(i = 0; i < 80 && alunos[i].nome[1] != '\0'; i++){
        if(alunos[i].situacao == 'A') aprovado++;
        if(alunos[i].situacao == 'R') reprovado++;
        if(alunos[i].situacao == 'F') rfaltas++;
    }
    porcaprov = (double) aprovado/i*100.0;
    porcreprov =  (double) reprovado/i*100.0;
    porcrfaltas = (double) rfaltas/i*100.0;
    puts("\n===================================================================");
    printf("Número de estudantes aprovados:                      %3d  (%3.1lf %%)", aprovado, porcaprov);
    printf("\nNúmero de estudantes reprovados:                     %3d  (%3.1lf %%)", reprovado, porcreprov);
    printf("\nNúmero de estudantes reprovados por falta:           %3d  (%3.1lf %%)", rfaltas, porcrfaltas);
    puts("\n===================================================================");
}// estatistica turma 2


/*
 * @brief função faz a comparação das maiores e menores notas entre cada aluno da turma carregada, e imprime elas
 * 
 * @param char nomeArquivo[ARQUIVO], nome do arquivo carregado
 * @param Estudante alunos[ALUNO], dados dos alunos do arquivo
 * @param int load, indicador de arquivo carregado
 *
 * @return void
*/

float* maioresNotas(Estudante alunos[ALUNOS]) {
    float* maior = calloc(6, sizeof(float));
    for(int i = 0; i < 80 && alunos[i].nome[1] != '\0'; i++){
        for(int j = 0; j < 3; j++)
            if(alunos[i].provas[j] > maior[j]) maior[j] = alunos[i].provas[j];
        if(alunos[i].trabalhos[0] > maior[3]) maior[3] = alunos[i].trabalhos[0];
        if(alunos[i].trabalhos[1] > maior[4]) maior[4] = alunos[i].trabalhos[1];
        if(alunos[i].notaFinal > maior[5]) maior[5] = alunos[i].notaFinal;
    }
    return maior;
}

float* mediaNotas(Estudante alunos[ALUNOS]) {
    float* media = calloc(6, sizeof(float));
    int i = 0;
    for (i = 0; i < 80 && alunos[i].nome[i] != '\0'; i++) {
        for(int j = 0; j < 3; j++)
            media[j] += alunos[i].provas[j];
        media[3] += alunos[i].trabalhos[0];
        media[4] += alunos[i].trabalhos[1];
        media[5] += alunos[i].notaFinal;
    }
    media[0] /= i; media[1] /= i; media[2] /= i; media[3] /= i; media[4] /= i; media[5] /= i;
    return media;
}

float* menoresNotas(Estudante alunos[ALUNOS]) {
    float* menor = calloc(6, sizeof(float));
    float* maior = maioresNotas(alunos);
    for (int i = 0; i < 6; i++) menor[i] = maior[i];
    free(maior);
    for(int i = 0; i < 80 && alunos[i].nome[i] != '\0'; i++){
        for (int j = 0; j < 3; j++)
            if(alunos[i].provas[j] < menor[j]) menor[j] = alunos[i].provas[j];
        if(alunos[i].trabalhos[0] < menor[3]) menor[3] = alunos[i].trabalhos[0];
        if(alunos[i].trabalhos[1] < menor[4]) menor[4] = alunos[i].trabalhos[1];
        if(alunos[i].notaFinal < menor[5]) menor[5] = alunos[i].notaFinal;
    }
    return menor;
}

void estatisticasTurma(char nomeArquivo[ARQUIVO], Estudante alunos[ALUNOS], int load)
{
    if(load == 1){
    printf("AIIAIAAIAI");
    float* maior = maioresNotas(alunos);
    float* media = mediaNotas(alunos);
    float* menor = menoresNotas(alunos);
    puts("\n===================================================================");
    puts("                       Estatisticas da Turma");
    puts("===================================================================");
    puts("                                N1    N2    N3    T1    T2    Final");
    puts("===================================================================");
    printf("Maiores notas da turma         %3.0f  %4.0f  %4.0f %5.0f %5.0f   %6.0f", maior[0], maior[1], maior[2], maior[3], maior[4], maior[5]);
    printf("\nMenores notas da turma         %3.0f  %4.0f  %4.0f %5.0f %5.0f   %6.0f", menor[0], menor[1], menor[2], menor[3], menor[4], menor[5]);
    printf("\nNotas médias da turma         %3.1f  %4.1f  %4.1f %5.1f %5.1f   %6.1f", media[0], media[1], media[2], media[3], media[4], media[5]);
    estatisticaTurma2(nomeArquivo, alunos, load);
    menuPrincipal(nomeArquivo, alunos, load);
    free(maior);
    free(media);
    free(menor);
    } else {printf("\nNão há turma carregada!\n"); menuPrincipal(nomeArquivo, alunos, load);}
}// estatista turma

/**
 * @brief função que rele o arquivo sendo usado no momento  
 * 
 * @param char nomeArquivo[ARQUIVO], nome do arquivo lido, se tiver sido lido
 * @param Estudante alunos[ALUNOS], dados dos alunos
 * @param int load, indicador de arquivo carregado ou não carregado
 * 
 * @return void 
 */

void relerTurma(char nomeArquivo[ARQUIVO], Estudante alunos[ALUNOS], int load)
{
    if(load == 1){
    FILE *fp = NULL;
    fp = fopen(nomeArquivo, "r");
    if (fp == NULL){
          fprintf(stderr, "\nArquivo %s não existe\n", nomeArquivo);
          menuPrincipal(nomeArquivo, alunos, load);
    } /*if end*/ else { 
                printf("\nArquivo %s lido com sucesso\n", nomeArquivo);
                int i = 0;
                int j = 0;
            for(;fscanf(fp, " %c",&alunos[i].nome[0])!=EOF && i < ALUNOS;i++){
                j = 1;
            for(;alunos[i].nome[j-1]!='\n';j++)
            fscanf(fp, "%c",&alunos[i].nome[j]);
            
            alunos[i].nome[j-1] = '\0';
            
            fscanf(fp, "%s\n",alunos[i].matricula);
            fscanf(fp, "%f\n%f\n%f\n",&alunos[i].provas[0],&alunos[i].provas[1],&alunos[i].provas[2]);
            fscanf(fp, "%f\n%f\n",&alunos[i].trabalhos[0],&alunos[i].trabalhos[1]);
            fscanf(fp, "%d\n",&alunos[i].faltas); 
            fscanf(fp, "%f\n",&alunos[i].notaFinal);
            fscanf(fp, "%c\n",&alunos[i].situacao);
            }
            fclose(fp);
            load = 1;
            menuPrincipal(nomeArquivo, alunos, load);
        }
    } else {fprintf(stderr, "\nArquivo %s não existe\n", nomeArquivo); menuPrincipal(nomeArquivo, alunos, load);}
}// reler turma


/*
 * @brief função que preenche o arranjo de alunos com os dados do arquivo lido
 * 
 * @param char nomeArquivo[ARQUIVO], nome do arquivo carregado
 * @param Estudante alunos[ALUNO], dados dos alunos do arquivo
 * @param int load, indicador de arquivo carregado
 *
 * @return void
*/

void preencheArq(char nomeArquivo[ARQUIVO], Estudante alunos[ALUNOS], int load)
{
    int i = 0;
    FILE *fp = fopen(nomeArquivo, "a");
    if(fp == NULL)
    {
        fprintf(stderr, "Erro ao acessar o arquivo %s!\n", nomeArquivo);
        exit(1);
    }
    for(i = 0; i < 80 && alunos[i].nome[1] != '\0'; i++){
        fprintf(fp, "%s\n", alunos[i].nome);
        fprintf(fp, "%s\n", alunos[i].matricula);
        fprintf(fp,  "%.0f\n", alunos[i].provas[0]);
        fprintf(fp,  "%.0f\n", alunos[i].provas[1]);
        fprintf(fp, "%.0f\n", alunos[i].provas[2]);
        fprintf(fp,  "%.0f\n", alunos[i].trabalhos[0]);
        fprintf(fp,  "%.0f\n", alunos[i].trabalhos[1]);
        fprintf(fp,  "%d\n", alunos[i].faltas);
        fprintf(fp, "%.0f\n", alunos[i].notaFinal);
        fprintf(fp, "%c\n", alunos[i].situacao);
    }
  fclose(fp);

  return;
}// preencher turma


/*
 * @brief função que concatena e salva os dados alterados do arquivo carregado e sai do programa
 * 
 * @param char nomeArquivo[ARQUIVO], nome do arquivo carregado
 * @param Estudante alunos[ALUNO], dados dos alunos do arquivo
 * @param int load, indicador de arquivo carregado
 *
 * @return void
*/

void salvarSair(char nomeArquivo[ARQUIVO], Estudante alunos[ALUNOS], int load)
{
  FILE *fp = fopen(nomeArquivo, "r");
  char escolha = ' ';
  if(fp == NULL)
  {
    fprintf(stderr, "\nO arquivo %s não existe. Deseja criar um novo? (S/N) ", nomeArquivo); 
    escolha = leiaChar();
    if(escolha == 'S' || escolha == 's'){
        fp = fopen(nomeArquivo, "w");
        printf("\nArquivo %s criado e preenchido com sucesso\n", nomeArquivo);
        fclose(fp);
        exit(0);
    }
    else {
        printf("\nAté Logo!\n"); exit(0);}
  } else {
    fprintf(stderr, "\nO arquivo %s já existe. Deseja sobrescrevelo? (S/N) ", nomeArquivo); 
    escolha = leiaChar();
    if(escolha == 'S' || escolha == 's'){
        fp = fopen(nomeArquivo, "w");
        printf("\nArquivo %s sobrescrito com sucesso\n", nomeArquivo);
        preencheArq(nomeArquivo, alunos, load);
        exit(0);
    }
    else {
        printf("\nAté Logo!\n"); exit(0);}
  }
}// salvar e sair


/*
 * @brief função que imprime os dados de todos os alunos do arquivo carregado
 * 
 * @param char nomeArquivo[ARQUIVO], nome do arquivo carregado
 * @param Estudante alunos[ALUNO], dados dos alunos do arquivo
 * @param int load, indicador de arquivo carregado
 *
 * @return void
*/


void imprimeTurma(char nomeArquivo[ARQUIVO], Estudante alunos[ALUNOS], int load)
{
    char teste = '\0';
    char auxNome[51] = {'\0'};
    int i = 0;
    if(load == 1){
        cabecalhoImprimeTurma();
    } else { puts("\nNão há turma carregada!"); menuPrincipal(nomeArquivo, alunos, load); }
    FILE *fp = NULL;
    fp = fopen(nomeArquivo, "r");
    for(i = 0; i < 80 && alunos[i].nome[1] != '\0'; i++){
        printf("%-50s", alunos[i].nome);
        printf("%14s", alunos[i].matricula);
        printf("%4.0f", alunos[i].provas[0]);
        printf("%6.0f", alunos[i].provas[1]);
        printf("%6.0f", alunos[i].provas[2]);
        printf("%6.0f", alunos[i].trabalhos[0]);
        printf("%6.0f", alunos[i].trabalhos[1]);
        printf("%6d", alunos[i].faltas);
        printf("%9.0f", alunos[i].notaFinal);
        printf("%10c", alunos[i].situacao);
        printf("\n");                 
    }
    puts("=======================================================================================================================");
    fclose(fp);
    menuPrincipal(nomeArquivo, alunos, load);
}// imprimir turma



/*
 * @brief função que cria um novo arquivo de turma se não existir o nome solicitado,
 * mas se existir ele da a opção de sobrepor o arquivo existente 
 *
 * @param char nomeArquivo[ARQUIVO], nome do arquivo carregado
 * @param Estudante alunos[ALUNO], dados dos alunos do arquivo
 * @param int load, indicador de arquivo carregado
 *
 * @return void
*/

void criarTurma(char nomeArquivo[ARQUIVO], Estudante alunos[ALUNOS], int load)
{
    char nomeArq[20] = {'\0'};
    printf("\nDigite o nome do arquivo para a nova turma: ");
    // fgets(nomeArq, sizeof(nomeArq), stdin);
    if (fgets(nomeArq, sizeof(nomeArq), stdin) == NULL){
            fprintf(stderr, "Erro ao ler o nome\n");   
        exit(1);
    } /*if end*/ else nomeArq[strcspn(nomeArq, "\n")] = '\0';
    strcpy(nomeArquivo, nomeArq);
    FILE *fp = NULL;
    fp = fopen(nomeArquivo, "r");
    if (fp == NULL){
        fp = fopen(nomeArquivo, "w");
        fclose(fp);
        printf("\nArquivo %s criado com sucesso\n", nomeArquivo);
        lerTurma(nomeArquivo, alunos, load);
    } /*if end*/ else {
        char escolha;
        printf("\nArquivo %s já existe. Deseja sobrescrevê-lo? (S/N) ", nomeArquivo);
        escolha = leiaChar();
        if (escolha == 'S' || escolha == 's')
        {
            fp = fopen(nomeArquivo, "w");
            fclose(fp);
            printf("\nArquivo %s sobrescrito\n", nomeArquivo);
            lerTurma(nomeArquivo, alunos, load);
        } /*if end*/ else if (escolha == 'N' || escolha == 'n'){
            fclose(fp);
            lerTurma(nomeArquivo, alunos, load);
        } /*if end*/
    } /*else end*/
}//criar turma



/*
 * @brief função que lê e carrega um arquivo para o arranjo de alunos
 * 
 * @param char nomeArquivo[ARQUIVO], nome do arquivo carregado
 * @param Estudante alunos[ALUNO], dados dos alunos do arquivo
 * @param int load, indicador de arquivo carregado
 *
 * @return void
*/

void subirTurma(char nomeArquivo[ARQUIVO], Estudante alunos[ALUNOS], int load)
{   
    char nomeArq[20] = {'\0'};
    char teste;
    printf("\nDigite o nome do arquivo com a turma: ");
    // fgets(nomeArq, sizeof(nomeArq), stdin);
    if (fgets(nomeArq, sizeof(nomeArq), stdin) == NULL){
        fprintf(stderr, "Erro ao ler o nome\n");  
        exit(1);
    } /*if end*/ else nomeArq[strcspn(nomeArq, "\n")] = '\0';
    strcpy(nomeArquivo, nomeArq);
    FILE *fp = NULL;
    fp = fopen(nomeArquivo, "r");
    if (fp == NULL){
          fprintf(stderr, "\nArquivo %s não existe\n", nomeArquivo);
          lerTurma(nomeArquivo, alunos, load);
    } /*if end*/ else { 
        printf("\nArquivo %s lido com sucesso\n", nomeArquivo);
        int i = 0;
        int j = 0;
    for(;fscanf(fp, " %c",&alunos[i].nome[0])!=EOF && i < ALUNOS;i++){
        j = 1;
    for(;alunos[i].nome[j-1]!='\n';j++)
      fscanf(fp, "%c",&alunos[i].nome[j]);
    
    alunos[i].nome[j-1] = '\0';
    
    fscanf(fp, "%s\n",alunos[i].matricula);
    fscanf(fp, "%f\n%f\n%f\n",&alunos[i].provas[0],&alunos[i].provas[1],&alunos[i].provas[2]);
    fscanf(fp, "%f\n%f\n",&alunos[i].trabalhos[0],&alunos[i].trabalhos[1]);
    fscanf(fp, "%d\n",&alunos[i].faltas); 
    fscanf(fp, "%f\n",&alunos[i].notaFinal);
    fscanf(fp, "%c\n",&alunos[i].situacao);
    } 
        fclose(fp);
        load = 1;
        lerTurma(nomeArquivo, alunos, load);
    } /*else end*/
}// subir turma


/*
 * @brief função de escolha para criar um arquivo ou ler um arquivo
 * 
 * @param char nomeArquivo[ARQUIVO], nome do arquivo carregado
 * @param Estudante alunos[ALUNO], dados dos alunos do arquivo
 * @param int load, indicador de arquivo carregado
 *
 * @return void
*/

void lerTurma(char nomeArquivo[ARQUIVO], Estudante alunos[ALUNOS], int load)
{
    int escolha = 0;
    puts("\n=========================================");
    puts("             Ler Turma");
    puts("=========================================");
    puts("Opções:\n");
    puts("1 - Ler turma existente");
    puts("2 - Criar nova turma");
    puts("3 - Voltar ao menu principal");
    escolha = lerOpcao(1, 3);
    if (escolha == 1)
        subirTurma(nomeArquivo, alunos, load);
    else if (escolha == 2)
        criarTurma(nomeArquivo, alunos, load);
    else if (escolha == 3)
        menuPrincipal(nomeArquivo, alunos, load);
}// ler turma


/*
 * @brief função menu principal que serve para realizar todas as açoes do programa atravez das chamadas de funções
 * 
 * @param char nomeArquivo[ARQUIVO], nome do arquivo carregado
 * @param Estudante alunos[ALUNO], dados dos alunos do arquivo
 * @param int load, indicador de arquivo carregado
 *
 * @return void
*/



void menuPrincipal(char nomeArquivo[ARQUIVO], Estudante alunos[ALUNOS], int load)
{
    int escolha = 0;
    menuMenuPrincipal();
    escolha = lerOpcao(1, 7);
    if(escolha == 1)
        lerTurma(nomeArquivo, alunos, load);
    else if(escolha == 2)
        imprimeTurma(nomeArquivo, alunos, load);
    else if(escolha == 3)
        estatisticasTurma(nomeArquivo, alunos, load);
    else if(escolha == 4)
        menuCadastrarEstudante(nomeArquivo, alunos, load);
    else if(escolha == 5)
        editaEstudante(nomeArquivo, alunos, load);
    else if(escolha == 6)
        relerTurma(nomeArquivo, alunos, load);
    else if(escolha == 7)
        salvarSair(nomeArquivo, alunos, load);
}// menu principal


int main(void)
{
    int load = 0;
    char nomeArquivo[ARQUIVO] = {'\0'};  
    Estudante alunos[ALUNOS] = {{'\0'},{'\0'},{0.0},{0.0},0,0.0,'\0'};
    menuPrincipal(nomeArquivo, alunos, load);
    return 0;
}// main