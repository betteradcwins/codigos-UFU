#include "menus.h"
#include <stdio.h>


void menuEditaInfo(void) 
{
    puts("\n=========================================");
    puts("    Editar Informações do Estudante");
    puts("=========================================");
    puts("Opções:\n");
    puts("1 - Alterar nome");
    puts("2 - Alterar matrícula");
    puts("3 - Alterar nota da prova 1");
    puts("4 - Alterar nota da prova 2");
    puts("5 - Alterar nota da prova 3");
    puts("6 - Alterar nota do trabalho 1");
    puts("7 - Alterar nota do trabalho 2");
    puts("8 - Alterar número de faltas");
    puts("9 - Voltar ao menu anterior");
}

void menuEditaEstudante(void) {
    puts("\n=========================================");
    puts("    Editar Informações do Estudante");
    puts("=========================================");
    puts("Opções:\n");
    puts("1 - Selecionar por número de matrícula");
    puts("2 - Selecionar por nome");
    puts("3 - Voltar ao menu principal");
}

void cabecalhoImprimeTurma(void) {
    puts("\n=======================================================================================================================");
    puts("                                              Turma de Estudantes");
    puts("=======================================================================================================================");
    puts(" Nome                                                Matrícula    Nota  Nota  Nota  Trab  Trab  Faltas  Nota  Situação ");
    puts("                                                                  1     2     3     1     2             Final");
    puts("=======================================================================================================================");
}

void menuMenuPrincipal(void) {
    puts("\n=========================================");
    puts("             Menu Principal");
    puts("=========================================");
    puts("Opções:\n");
    puts("1 - Ler turma de estudantes do arquivo");
    puts("2 - Imprimir turma de estudantes");
    puts("3 - Imprimir estatísticas da turma");
    puts("4 - Cadastrar novo estudante");
    puts("5 - Editar informações de um estudante");
    puts("6 - Reler turma de estudantes do arquivo");
    puts("7 - Salvar e Sair");
}