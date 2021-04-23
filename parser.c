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

//Função para trocar os últimos dois elementos da stack
void SWAP(Stack* s) {
    DATA x,y;
    x = s->elements[s->sp]; ///< Elemento do topo da stack
    y = s->elements[s->sp - 1]; ///< Elemento anterior 
    s->elements[s->sp] = y; ///< y passa a estar no topo da stack
    s->elements[s->sp - 1] = x; ///< x passa estar na posição antiga de y
}

//Função para trocar os três últimos elementos da stack
void ROTATE(Stack* s) {
    DATA x,y,z;
    x = s->elements[s->sp]; ///< x é o elemento do topo da stack
    y = s->elements[s->sp - 1]; ///< y é o elemento abaixo de x
    z = s->elements[s->sp - 2]; ///< z é o elemento abaixo de y
    s->elements[s->sp] = z; ///< O topo da stack agora possui o elemento z
    s->elements[s->sp - 1] = x; ///< O endereço onde havia o y guardado passa a guardar o elemento x
    s->elements[s->sp - 2] = y; ///< O endereço onde havia o z guardado passa a guardar o elemento y

}

/**
* \brief Definição das operações
*/

#define ADD(x,y) x + y
#define SUB(x,y) x - y
#define MULT(x,y) x * y
#define DIV(x,y) x / y
#define DEC(x) x--
#define INC(x) x++
#define MOD(x,y) x % y
#define AND(x,y) x & y
#define OR(x,y) x | y
#define XOR(x,y) x ^ y
#define NOT(x) ~x
#define EQUAL(x,y) x == y
#define GREATER(x,y) x < y
#define LESS(x,y) x > y
#define EGREATER(x,y) x > y
#define ELESS(x,y) x < y
#define EIF(x,y) y != 0
#define EOR(x,y) y == 0


/**
* Desenvolvemos diferentes macros para os diferentes casos, tendo em consideração o sei tipo de dados.
*/


#define LOGIC_BIN(op)                       \
    {                                       \
    if (x==1) {                             \
        long X = pop_LONG(s);               \
        int y = idtype(s);                  \
        if (y == 1) {                       \
            long Y = pop_LONG(s);           \
            if (op(X,Y)) push_LONG(s,1);    \
            else push_LONG(s,0);            \
        }                                   \
        else if (y == 2) {                  \
           double Y = pop_DOUBLE(s);        \
           if (op(X,Y)) push_LONG(s,1);     \
           else push_LONG(s,0);             \
        }                                   \
        else if (y == 3) {                  \
            long_conversion(s);             \
            long Y = pop_LONG(s);           \
            if (op(X,Y)) push_LONG(s,1);    \
            else push_LONG(s,0);            \
        }                                   \
    }                                       \
    else if (x == 2) {                      \
        double X = pop_DOUBLE(s);           \
        int y = idtype(s);                  \
        if (y == 1) {                       \
            long Y = pop_LONG(s);           \
            if (op(X,Y)) push_LONG(s,1);    \
            else push_LONG(s,0);            \
        }                                   \
        else if (y == 2) {                  \
           double Y = pop_DOUBLE(s);        \
           if (op(X,Y)) push_LONG(s,1);     \
           else push_LONG(s,0);             \
        }                                   \
        else if (y == 3) {                  \
            long_conversion(s);             \
            long Y = pop_LONG(s);           \
            if (op(X,Y)) push_LONG(s,1);    \
            else push_LONG(s,0);            \
        }                                   \
    }                                       \
    else {                                  \
        long_conversion(s);                 \
        long X = pop_LONG(s);               \
        int y = idtype(s);                  \
        if (y == 1) {                       \
            long Y = pop_LONG(s);           \
            if (op(X,Y)) push_LONG(s,1);    \
            else push_LONG(s,0);            \
        }                                   \
        else if (y == 2) {                  \
           double Y = pop_DOUBLE(s);        \
           if (op(X,Y)) push_LONG(s,1);     \
           else push_LONG(s,0);             \
        }                                   \
        else if (y == 3) {                  \
            long_conversion(s);             \
            long Y = pop_LONG(s);           \
            if (op(X,Y)) push_LONG(s,1);    \
            else push_LONG(s,0);            \
        }                                   \
    }                                       \
    }                                       \
    
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


#define CASE_BIN(op)                                        \
                                                            \
    if (x == 1) {                                           \
                                                            \
                                                            \
            int y = idtype(s);                              \
            if (y == 1) {                                   \
                long X = pop_LONG(s);                       \
                long Y = pop_LONG(s);                       \
                push_LONG(s, op(Y,X));                      \
            }                                               \
    }                                                       \
                                                          


#define CASE_SOLO(op)                  \
                                       \
    if (x == 1) {                      \
                                       \
            long X = pop_LONG(s);      \
            push_LONG(s, op X);        \
                                       \
    }                                  \
    else if (x == 2) {                 \
            double X = pop_DOUBLE(s);  \
            push_DOUBLE(s,op X);       \
                                       \
    }                                  \
    else if (x == 3) {                 \
        char X = pop_CHAR(s);          \
        push_CHAR(s,op X);             \
    }                                  \





#define CASE_OP(op)                                         \
                                                            \
    if (x == 1)    {                                        \
            long X = pop_LONG(s);                           \
            int y = idtype(s);                              \
            if (y == 1) {                                   \
                                                            \
                long Y = pop_LONG(s);                       \
                push_LONG(s, op(Y,X));                      \
            }                                               \
            else if (y == 2) {                              \
                push_LONG(s,X);                             \
                double_conversion(s);                       \
                double Z = pop_DOUBLE(s);                   \
                double Y = pop_DOUBLE(s);                   \
                                                            \
                push_DOUBLE(s, op(Y,Z));                    \
            }                                               \
                                                            \
    }                                                       \
        else {                                              \
            double X = pop_DOUBLE(s);                       \
            int y = idtype(s);                              \
            if (y == 1) {                                   \
                double_conversion(s);                       \
                double Y = pop_DOUBLE(s);                   \
                push_DOUBLE(s, op(Y,X));                    \
            }                                               \
            else if (y == 2) {                              \
                double Y = pop_DOUBLE(s);                   \
                push_DOUBLE(s, op(Y,X));                    \
            }                                               \
                                                            \
        }                                                   \
                                                           

void var_top (Stack* s, char c, DATA *v) {
    v[c-65] = top(s); ///< o elemento que ocupa a posição c-65 tomará o valor do topo da stack. Por exemplo, para A, o código ASCII é 65 e portanto v[0] = topo da stack
    
}


void logic_e(char* c, Stack* s) {
    char x = c[1];

    switch(x) {
        case '&': LOGIC_BIN_E_IF(EIF); break; 
        case '|': LOGIC_BIN_E_OR(EOR); break; 
        case '>': LOGIC_BIN_E(EGREATER); break;
        case '<': LOGIC_BIN_E(ELESS); break;
    }
}



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
                    case '=': LOGIC_BIN(EQUAL); break;
                    case '>': LOGIC_BIN(GREATER); break;
                    case '<': LOGIC_BIN(LESS); break;
                    case '?': {long X = pop_LONG(s); long Y = pop_LONG(s); long Z = pop_LONG(s); if (Z != 0) push_LONG(s, Y); else push_LONG(s, X); break;}
                    case '!': {long X = pop_LONG(s); if (X == 0) push_LONG(s, 1); else push_LONG(s, 0); break;}
                    case 'e': logic_e(token, s); break;
                }
            }  
        }   
}

