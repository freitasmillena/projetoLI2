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
#include "op.h"

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

void parse(char *line, Stack* s) {
    char *delims = " \t\n";
    

    for(char *token = strtok(line,delims); token != NULL; token = strtok(NULL,delims)) {
        char *sobra;
        char *sobrad;
        char resto[50];

        if(line[0] == 'l') {
        
            int i,j;
            for (i = 2, j = 0; line[i] != '\0'; i++,j++) {
                resto[j] = line[i];
            }
        }
        
        long vi = strtol(token, &sobra, 10);
        double vd = strtod(token, &sobrad);
        
        if(strlen(sobra) == 0) push_LONG(s, vi);
        else if(strlen(sobrad) == 0) push_DOUBLE(s,vd);
        
        
        int x = idtype(s); 

        
        
        switch (*token) {

            case 'l': {
                char l[10240]; 
                assert(fgets(l, 10240, stdin) != NULL);
                assert(l[strlen(l) - 1] == '\n');
                parse(l,s);
                parse(resto,s);
                break;
            }
            case 'c': char_conversion(s); break;
            case 'f': double_conversion(s); break;
            case 'i': long_conversion(s); break;
            case 's': string_conversion(s); break;
            case '+': CASE_OP(ADD); break;
            case '-': CASE_OP(SUB); break;
            case '*': CASE_OP(MULT); break;
            case '/': CASE_OP(DIV); break;
            case '(': CASE_SOLO(--); break;
            case ')': CASE_SOLO(++); break;
            case '%': CASE_BIN(MOD); break;
            case '#': CASE_OP(pow); break;
            case '&': CASE_BIN(AND); break;
            case '|': CASE_BIN(OR); break;
            case '^': CASE_BIN(XOR); break;
            case '~': {long X = pop_LONG(s); push_LONG(s, ~X); break;}
            case '_': push(s,top(s)); break;
            case ';': pop(s); break;
            case '\\': SWAP(s); break;
            case '@': ROTATE(s); break;
            case '$': {long offset = pop_LONG(s); push(s, s->elements[s->sp - offset]); break;}
    
        }
    }
    
    
}

