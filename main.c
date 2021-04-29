/**
* @file main.c Ficheiro que contém a função principal.
*
* Module : Guião1 + Guião 2 + Guião 3
* Description : Main - Trabalho de LI2 2020/2021
*
*/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"


void parse(char *line, Stack* s); ///< declaração da função parse

/**
* \brief Esta é a função principal do programa.
*
* @returns O valor 0.
*/
int main() {
    
    Stack* s = create_stack(); ///< cria stack

    char line[10240]; ///< array de char com capacidade alta para receber a linha a executar

    assert(fgets(line, 10240, stdin) != NULL); ///< confirmar que o input não é null
    assert(line[strlen(line) - 1] == '\n'); ///< confirmar que o último elemento é '\n' ou seja o enter

    parse(line,s); ///< chama função parse

    print_stack(s); ///< imprime stack

    putchar('\n'); ///< pula linha para melhor visualização
    
    return 0; 
}

