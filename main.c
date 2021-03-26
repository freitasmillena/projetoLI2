/**
* @file main.c Ficheiro que contém a função principal.
*
* Module : Guião1 (1a semana)
* Description : Main - Trabalho de LI2 2020/2021
*
*/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

/**
* \brief Esta é a função principal do programa.
*
* @Returns O valor 0.
*/
void parse(char *line);

int main() {
    

    char line[10240]; 

    assert(fgets(line, 10240, stdin) != NULL);
    assert(line[strlen(line) - 1] == '\n');

    parse(line);

    
    return 0;
}

