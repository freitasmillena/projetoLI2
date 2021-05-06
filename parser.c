/**
* @file parser.h
*
* Module : Guião1 + Guião2 + Guião 3
* Description : Parser -> Trabalho de LI2 2020/2021
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
 * \brief A função index_finish devolve o índice do elemento logo a seguir do fim do array ou da string
 * 
 * @param line Recebe a linha por referência
 * @return retorna o índice
 */
int index_finish(char* line) {
    char *result;
    result = line;
    int count = 0;
    int r = 0;
    //Para Arrays
    if(*line == '[') {
        //percorrer linha e count++ para cada [ e count-- para cada ]. Ao chegar em count = 0, este é o array.
        count++;
        result++;

        while(count != 0) {
                    if(*result == '[') {count++; result++;}
                    else if (*result == ']') {count--; result++;}
                    else {result++; }
        }
        r = result - line; ///< result guarda o endereço do elemento após o fim do array e line guarda o endereço do primeiro elemento da linha. Ao diminuir, obtemos o índice do elemento após o fim do array
    }
    //Para Strings
    else if(*result == '"') {
       result++;

       while(*result != '"') {
           result++;

       }
       r = result - line + 1; ///< result guarda o endereço do último " da string e line guarda o endereço do primeiro elemento da linha. Ao diminuir e somar 1, obtemos o índice do elemento após o fim do string

    }

    return r;
}

/**
 * \brief A função get_token é responsável por separar o token a ser utilizado e também guardar o resto da linha que será utilizado posteriormente.
 * 
 * @param line Recebe a linha por referência
 * @param rest Onde será guardado o resto da linha após o token 
 * @return retorna o token
 */
char *get_token(char *line, char **rest) {

    char *delims = " \t\n";
    char *token = (char *)malloc(sizeof(char)*strlen(line));
    char *t;
    t = token;
    int i;

    if (*line == '\0') return NULL;

    else if (*line == '[' || *line == '"') {
        i = index_finish(line);

        strncpy(token, line, sizeof(char)*(i));
        strncpy(*rest, line + i+1, sizeof(char) * (strlen(line) - i + 1));

        *(t+i) = '\0';
    }

    else token = strtok_r(line, delims, rest);

    return token;

}

/**
 * \brief A função eval é responsável por tratar da linha ao chamar outra função get_token para a separação dos tokens e, assim, efetuar as operações matemáticas, lógicas, de conversão, entre outras.
 * Caso a stack recebida seja nula, cria uma.
 * 
 * @param line Recebe a linha por referência
 * @param init_stack Apontador para a stack
 * @return retorna a stack após as operações 
 */
Stack *eval(char *line, Stack* init_stack) {
    
    if(init_stack == NULL) {
        init_stack = malloc(sizeof(Stack));
        init_stack = create_stack();
    }
    
    
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

    char *rest = (char *)malloc(sizeof(char)*strlen(line));
    char *token;
    
    if(*line == '"') handle_string(line, init_stack, &rest);
    else {
        for(token = get_token(line,&rest); token != NULL ; token = get_token(rest, &rest)) {

            int r = handle_push(token,init_stack); 
            if (r) ;
            
            else {
            int x = idtype(init_stack);

            handle_math(token, x, init_stack);
            handle_binary(token, init_stack);
            handle_conversion(token, init_stack);
            handle_logic(token,init_stack);
            handle_stack(token, init_stack);
            handle_variable(token, init_stack, p);
            }
        }
    }
    
    return init_stack;
}

/**
 * \brief A função parse é responsável por chamar a função eval e passar um apontador para a stack caso não estejamos a trabalhar com arrays e strings.
 * Caso estejamos a trabalhar com arrays e strings, passa NULL para que seja criada uma nova estrutura para lidar com estes tipos.
 * @param line A linha inserida é passada por referência
 * @param s Apontador para a stack
 * 
 */
void parser(char *line, Stack* s) {
    if (*line == '[') eval(line, NULL);
    else eval(line,s);
}