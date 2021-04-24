/**
* @file parser.h
*
* Module : Guião1 + Guião2 (1a semana e 2a semana)
* Description : Parser -> (Guião1) - Trabalho de LI2 2020/2021
*
* No primeiro guião, temos como objetivo criar um programa que fosse capaz de ler
* um input (ex.: " 17 11 - ( 18 9 / ") e devolver um output (ex.: 52).
* Do Guião2, adicionamos mais operações e contruímos o código de forma a ser possivel utilizar diferentes tipos de dados.
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "stack.h"
#include "op.h"

/*
void logic_e(char* c, Stack* s) {
    char x = c[1];

    switch(x) {
        case '&': LOGIC_BIN_E_IF(EIF); break; 
        case '|': LOGIC_BIN_E_OR(EOR); break; 
        case '>': LOGIC_BIN_E(EGREATER); break;
        case '<': LOGIC_BIN_E(ELESS); break;
    }
}
*/

/*

#define LOGIC_BIN_E(op)             \
    {                               \
    DATA X = pop(s);                \
    DATA Y = pop(s);                \
                                    \
    long y = Y.x.LONG;              \
    long x = X.x.LONG;              \
                                    \
    if (op(x,y)) push_LONG(s,x);    \
    else push_LONG(s,y);            \
    }                               \
#define LOGIC_BIN_E_IF(op)          \
    {                               \
    DATA X = pop(s);                \
    DATA Y = pop(s);                \
                                    \
    long y = Y.x.LONG;              \
    long x = X.x.LONG;              \
                                    \
    if (op(x,y)) push_LONG(s,x);    \
    else push_LONG(s,0);            \
    }                               \
#define LOGIC_BIN_E_OR(op)          \
    {                               \
    DATA X = pop(s);                \
    DATA Y = pop(s);                \
                                    \
    long y = Y.x.LONG;              \
    long x = X.x.LONG;              \
                                    \
    if (op(x,y)) push_LONG(s,x);    \
    else push_LONG(s,1);            \
    }                               \

*/


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
    
    //Array no qual cada elemento é uma struct. Possui todas as variáveis e as que possuem valor por omissão já encontram-se inicializadas
    DATA abc[26] = { 
                { .type = LONG, .x.LONG = 10 },
                { .type = LONG, .x.LONG = 11 },
                { .type = LONG, .x.LONG = 12 },
                { .type = LONG, .x.LONG = 13 },
                { .type = LONG, .x.LONG = 14 },
                { .type = LONG, .x.LONG = 15 },
                { .type = CHAR, .x.CHAR = 'G' },
                { .type = CHAR, .x.CHAR = 'H' },
                { .type = CHAR, .x.CHAR = 'I' },
                { .type = CHAR, .x.CHAR = 'J' },
                { .type = CHAR, .x.CHAR = 'K' },
                { .type = CHAR, .x.CHAR = 'L' },
                { .type = CHAR, .x.CHAR = 'M' },
                { .type = CHAR, .x.CHAR = '\n' },
                { .type = CHAR, .x.CHAR = 'O' },
                { .type = CHAR, .x.CHAR = 'P' },
                { .type = CHAR, .x.CHAR = 'Q' },
                { .type = CHAR, .x.CHAR = 'R' },
                { .type = CHAR, .x.CHAR = ' ' },
                { .type = CHAR, .x.CHAR = 'T' },
                { .type = CHAR, .x.CHAR = 'U' },
                { .type = CHAR, .x.CHAR = 'V' },
                { .type = CHAR, .x.CHAR = 'W' },
                { .type = LONG, .x.LONG = 0 },
                { .type = LONG, .x.LONG = 1 },
                { .type = LONG, .x.LONG = 2 }
            };
    DATA *p = abc;

    for(char *token = strtok(line,delims); token != NULL; token = strtok(NULL,delims)) {
        char *sobra;
        char *sobrad;
        
        
        long vi = strtol(token, &sobra, 10);
        double vd = strtod(token, &sobrad);
        long t = token[0];

        if(strlen(sobra) == 0) push_LONG(s, vi); ///< caso seja long
        
        else if(strlen(sobrad) == 0) push_DOUBLE(s,vd); ///< caso seja double
        
        else if(token[0] == ':') var_top(s, token[1], p); ///< caso seja comando :<Letra>               
        
        else if (t>=65 && t<=90) push(s, abc[t-65]); ///< caso seja a variável <Letra>
                
        else {
                int x = idtype(s); 
                               
                switch (*token) {

                    case 'l': {
                        char l[10240]; 
                        assert(fgets(l, 10240, stdin) != NULL);
                        push_STRING(s,l);
                        break;
                    }
                    case 'c': char_conversion(s); break;
                    case 'f': double_conversion(s); break;
                    case 'i': long_conversion(s); break;
                    case 's': string_conversion(s); break;
                    case '+': add_operation(x,s); break;
                    case '-': sub_operation(x,s); break;
                    case '*': mult_operation(x,s); break;
                    case '/': div_operation(x,s); break;
                    case '(': dec_operation(x,s);break;
                    case ')': inc_operation(x,s); break;
                    case '%': mod_operation(x,s); break;
                    case '#': pow_operation(x,s); break;
                    case '&': and_operation(x,s); break;
                    case '|': or_operation(x,s); break;
                    case '^': xor_operation(x,s); break;
                    case '~': {long X = pop_LONG(s); push_LONG(s, ~X); break;}
                    case '_': push(s,top(s)); break;
                    case ';': pop(s); break;
                    case '\\': SWAP(s); break;
                    case '@': ROTATE(s); break;
                    case '$': {long offset = pop_LONG(s); push(s, s->elements[s->sp - offset]); break;}
                    case '=': equal_elogic(x,s); break;
                    case '>': greater_elogic(x,s); break;
                    case '<': less_elogic(x,s); break;
                    case '?': {long X = pop_LONG(s); long Y = pop_LONG(s); long Z = pop_LONG(s); if (Z != 0) push_LONG(s, Y); else push_LONG(s, X); break;}
                    case '!': {long X = pop_LONG(s); if (X == 0) push_LONG(s, 1); else push_LONG(s, 0); break;}
                    //case 'e': logic_e(token, s); break;
                }
            }  
        }   
}

