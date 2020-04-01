/*
 * @file readData.c
 * 
 * @brief Modúlo para ler dados de opções
 * 
 * @author Breno Henrique de Oliveira Ferreira 
 * 
 * @date 19/12/2018
 *  
 *
*/


#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readData.h"

/**
 * @brief função que lê um dado e retorna o valor lido
 * 
 * @param void
 *
 * @return int, dado
 */

int lerOpcao(int min, int max)
{
    setbuf(stdin, NULL);
    char opcao[12];
    while (true) 
    {
        printf("Digite uma opção: ");
        fgets(opcao, sizeof(opcao), stdin);
        if (atoi(opcao) != 0 && atoi(opcao) >= min && atoi(opcao) <= max)
            return atoi(opcao);
        else
            printf("Opção inválida. Tente novamente.\n");
    }
}// ler opção


/**
 * @brief função que confere se um char é S,N,s ou n, se não, não permite 
 * sair da verificação
 *
 * @param void
 *
 * @return char, char conferido
 */

char leiaChar(void)
{
  char opcao = '\0';
  scanf(" %c", &opcao); 
  while(opcao != 's' && opcao != 'S' && opcao != 'n' && opcao != 'N'){
    printf("valor inválido! Digite novamente: ");
    scanf(" %c",&opcao);} /*while end*/
  return opcao;
}// leia char
