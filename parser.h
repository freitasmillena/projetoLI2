/**
* Module : Guião1 (1a semana)
* Description : Parser -> (Guião1) - Trabalho de LI2 2020/2021
*
* No primeiro guião, temos como objetivo criar um programa que fosse capaz de ler
* um input (ex.: " 17 11 - ( 18 9 / ") e devolver um output (ex.: 52).
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stack.h"

/**
* A função parse começa por declarar os delimitadores e chama função @create_stack do ficheiro stack.h.
* Testamos se é um número inteiro ou real e depois fazemos o push ( função no ficheiro stack.h ) caso seja inteiro.
* Usamos o switch (também puderia ser feito com ifs mas achamos mais 'elegante' o código apresentado desta maneira), 
* para que dependendo do token que é lido, será feita a função que lhe está associada,
*
*  |  + - * /         Somar, subtrair, multiplicar e dividir
*  |  ( )             Decrementar e incrementar um valor
*  |  %               Módulo
*  |  #               Exponenciação
*  |  & | ^ ~         E, ou, xor e not (bitwise) para inteiros 
*
* imprimindo no final o resultado.
*/

void parse(char *line) {
    char *delims = " \t\n";
    Stack* s = create_stack();

    for(char *token = strtok(line,delims); token != NULL; token = strtok(NULL,delims)) {
        char *sobra;
        long vi = strtol(token, &sobra, 10);
        if(strlen(sobra) == 0) {
            
            push(s, vi);
            
        }
        int choice = 0;
        if (strcmp(token, "+") == 0) choice = 1;
        if (strcmp(token, "-") == 0) choice = 2;
        if (strcmp(token, "*") == 0) choice = 3;
        if (strcmp(token, "/") == 0) choice = 4;
        if (strcmp(token, "(") == 0) choice = 5;
        if (strcmp(token, ")") == 0) choice = 6;
        if (strcmp(token, "%") == 0) choice = 7;
        if (strcmp(token, "#") == 0) choice = 8;
        if (strcmp(token, "&") == 0) choice = 9;
        if (strcmp(token, "|") == 0) choice = 10;
        if (strcmp(token, "^") == 0) choice = 11;
        if (strcmp(token, "~") == 0) choice = 12;

        
        switch (choice) {
                case 1: {
                    long Y = pop(s);
                    long X = pop(s);
                    push(s, (X + Y));
                    break;
                }
                case 2: {
                    long Y = pop(s);
                    long X = pop(s);
                    push(s, (X - Y));
                    break;
                }
                case 3: {
                    long Y = pop(s);
                    long X = pop(s);
                    push(s, (X * Y));
                    break;
                }
                case 4: {
                    long Y = pop(s);
                    long X = pop(s);
                    push(s, (X / Y));
                    break;
                }
                case 5: {
                    long X = pop(s);
                    push(s, X-1);
                    break;
                }
                case 6: {
                    long X = pop(s);
                    push(s, X+1);
                    break;
                }
                case 7: {
                    long Y = pop(s);
                    long X = pop(s);
                    push(s, (X % Y));
                    break;
                }
                case 8: {
                    long Y = pop(s);
                    long X = pop(s);
                    push(s, (pow(X,Y)));
                    break;
                }
                case 9: {
                    long Y = pop(s);
                    long X = pop(s);
                    push(s,X&Y);
                    break;
                }
                case 10: {
                    long Y = pop(s);
                    long X = pop(s);
                    push(s,X|Y);
                    break;
                }
                case 11: {
                    long Y = pop(s);
                    long X = pop(s);
                    push(s,X^Y);
                    break;
                }
                case 12: {
                    long X = pop(s);
                    push(s,~X);
                    break;
                }
                default: 
                    break;
            }
        
    }
    print_stack(s);

    putchar('\n');
}


