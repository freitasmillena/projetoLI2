/**
* @file parser.h
*
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
#include <assert.h>
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
            
            push_LONG(s, vi);
            
        }
        
        switch (*token) {
                case 'l': {     //CONFIRMAR -- no idea se é algo assim
                    char l[10240];
                    assert(fgets(l, 10240, stdin) != NULL);
                    push_STRING(s,l);
                    break;
                }
                case '+': {
                    long Y = pop_LONG(s);
                    long X = pop_LONG(s);
                    push_LONG(s, (X + Y));
                    break;
                }
                case '-': {
                    long Y = pop_LONG(s);
                    long X = pop_LONG(s);
                    push_LONG(s, (X - Y));
                    break;
                }
                case '*': {
                    long Y = pop_LONG(s);
                    long X = pop_LONG(s);
                    push_LONG(s, (X * Y));
                    break;
                }
                case '/': {
                    long Y = pop_LONG(s);
                    long X = pop_LONG(s);
                    push_LONG(s, (X / Y));
                    break;
                }
                case '(': {
                    long X = pop_LONG(s);
                    push_LONG(s, X-1);
                    break;
                }
                case ')': {
                    long X = pop_LONG(s);
                    push_LONG(s, X+1);
                    break;
                }
                case '%': {
                    long Y = pop_LONG(s);
                    long X = pop_LONG(s);
                    push_LONG(s, (X % Y));
                    break;
                }
                case '#': {
                    long Y = pop_LONG(s);
                    long X = pop_LONG(s);
                    push_LONG(s, (pow(X,Y)));
                    break;
                }
                case '&': {
                    long Y = pop_LONG(s);
                    long X = pop_LONG(s);
                    push_LONG(s,X&Y);
                    break;
                }
                case '|': {
                    long Y = pop_LONG(s);
                    long X = pop_LONG(s);
                    push_LONG(s,X|Y);
                    break;
                }
                case '^': {
                    long Y = pop_LONG(s);
                    long X = pop_LONG(s);
                    push_LONG(s,X^Y);
                    break;
                }
                case '~': {
                    long X = pop_LONG(s);
                    push_LONG(s,~X);
                    break;
                }
                case '_': {
                    long X = pop_LONG(s);
                    push_LONG(s,X);
                    push_LONG(s,X);
                    break;
                }
                case ';': {
                    pop_LONG(s);
                    break;
                }
                case '\\': {
                    long X = pop_LONG(s);
                    long Y = pop_LONG(s); 
                    push_LONG(s,X); push_LONG(s,Y);
                    break;
                }
                case '@': {
                    long X = pop_LONG(s);
                    long Y = pop_LONG(s);
                    long Z = pop_LONG(s);
                    push_LONG(s,Y); push_LONG(s,X); push_LONG(s,Z);
                    break;
                }
                case '$': {
                    long X = pop_LONG(s);
                    int v[1024];
                    int j = 0;
                    int i;
                    if (X == 0) {
                        long Y = pop_LONG(s);
                        push_LONG(s,Y);
                        push_LONG(s,Y);
                    } 
                    else {
                        for (i = 0; i < X; i++) {
                            v[i] = pop_LONG(s);
                        }
                        long Z = pop_LONG(s);
                        push_LONG(s,Z);
                        while (v[j] != '\0') {
                            push_LONG(s, v[j]);
                            j++;
                        }
                        push_LONG(s,Z);
                    }
                    break;
                }
                default: 
                    break;
            }
        
    }
    print_stack(s);

}
