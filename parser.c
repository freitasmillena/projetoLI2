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
    
    
    DATA abc[26] = { /** //Array no qual cada elemento é uma struct. Possui todas as variáveis e as que possuem valor por omissão já encontram-se inicializadas */
                { .type = LONG, .x.LONG = 10 },   /** Inicializa A com o valor por omissão de 10 */
                { .type = LONG, .x.LONG = 11 },   /** Inicializa B com o valor por omissão de 11 */
                { .type = LONG, .x.LONG = 12 },   /** Inicializa C com o valor por omissão de 12 */
                { .type = LONG, .x.LONG = 13 },   /** Inicializa D com o valor por omissão de 13 */
                { .type = LONG, .x.LONG = 14 },   /** Inicializa E com o valor por omissão de 14 */
                { .type = LONG, .x.LONG = 15 },   /** Inicializa F com o valor por omissão de 15 */
                { .type = CHAR, .x.CHAR = 'G' },  /** Char 'G' */
                { .type = CHAR, .x.CHAR = 'H' },  /** Char 'H' */
                { .type = CHAR, .x.CHAR = 'I' },  /** Char 'I' */
                { .type = CHAR, .x.CHAR = 'J' },  /** Char 'J' */
                { .type = CHAR, .x.CHAR = 'K' },  /** Char 'K' */
                { .type = CHAR, .x.CHAR = 'L' },  /** Char 'L' */
                { .type = CHAR, .x.CHAR = 'M' },  /** Char 'M' */
                { .type = CHAR, .x.CHAR = '\n' }, /** Inicializa N com o valor por omissão '\n' */
                { .type = CHAR, .x.CHAR = 'O' },  /** Char 'O' */
                { .type = CHAR, .x.CHAR = 'P' },  /** Char 'P' */
                { .type = CHAR, .x.CHAR = 'Q' },  /** Char 'Q' */
                { .type = CHAR, .x.CHAR = 'R' },  /** Char 'R' */
                { .type = CHAR, .x.CHAR = ' ' },  /** Inicializa S com o valor por omissão ' ' */
                { .type = CHAR, .x.CHAR = 'T' },  /** Char 'T' */
                { .type = CHAR, .x.CHAR = 'U' },  /** Char 'U' */
                { .type = CHAR, .x.CHAR = 'V' },  /** Char 'V' */
                { .type = CHAR, .x.CHAR = 'W' },  /** Char 'W' */
                { .type = LONG, .x.LONG = 0 },    /** Inicializa X com o valor por omissão de 0 */
                { .type = LONG, .x.LONG = 1 },    /** Inicializa Y com o valor por omissão de 1 */
                { .type = LONG, .x.LONG = 2 }     /** Inicializa Z com o valor por omissão de 2 */
            };
    DATA *p = abc; ///< apontador para array de DATA abc 

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
                int x = idtype(s); ///< verifica o tipo do elemento no topo da stack
                               
                switch (*token) {

                    case 'l': {  ///< comando para ler linha
                        char l[10240]; ///< char l
                        assert(fgets(l, 10240, stdin) != NULL); ///< confirmar que não é null
                        push_STRING(s,l); ///< efetua operação de push para a string recebida
                        break;
                    }
                    case 'c': char_conversion(s); break; ///< comando para converter para char
                    case 'f': double_conversion(s); break; ///< comando para converter para double
                    case 'i': long_conversion(s); break; ///< comando para converter para long
                    case 's': string_conversion(s); break; ///< comando para converter para string
                    case '+': add_operation(x,s); break; ///< comando para operação de soma 
                    case '-': sub_operation(x,s); break; ///< comando para operação de subtração
                    case '*': mult_operation(x,s); break; ///< comando para operação de multiplicação
                    case '/': div_operation(x,s); break; ///< comando para operação de divisão
                    case '(': dec_operation(x,s);break; ///< comando para operação de decrementação
                    case ')': inc_operation(x,s); break; ///< comando para operação de incrementação
                    case '%': mod_operation(s); break; ///< comando para operação de resto da divisão ou módulo
                    case '#': pow_operation(x,s); break; ///< comando para operação de potência
                    case '&': and_operation(s); break; ///< comando para operação binária & (and)
                    case '|': or_operation(s); break; ///< comando para operação binária | (or)
                    case '^': xor_operation(s); break; ///< comando para operação binária ^ (xor)
                    case '~': {long X = pop_LONG(s); push_LONG(s, ~X); break;} ///< comando para operação binária ~ (not)
                    case '_': push(s,top(s)); break; ///< comando para operação na stack (Duplicar)
                    case ';': pop(s); break; ///< comando para operação na stack (pop)
                    case '\\': SWAP(s); break; ///< comando para operação na stack (Trocar os dois elementos no topo da stack)
                    case '@': ROTATE(s); break; ///< comando para operação na stack (Rodar os três elementos no topo da stack)
                    case '$': {long offset = pop_LONG(s); push(s, s->elements[s->sp - offset]); break;} ///< comando para operação na stack (Copiar n-ésimo elemento para o topo da stack)
                    case '=': equal_logic(s); break; ///< comando para operação lógica = (Igual) 
                    case '>': greater_logic(s); break; ///< comando para operação lógica > (Maior) 
                    case '<': less_logic(s); break; ///< comando para operação lógica < (Menor)
                    case '?': if_then_else(s); break; ///< comando para operação lógica ? (if then else)
                    case '!': logic_not(s); break; ///< comando para operação lógica ! (Não)
                    case 'e': logic_e(token,s); break; ///< comando para operação lógica e<Operação> 
                }
            }  
        }   
}

