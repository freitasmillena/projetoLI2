/**
 * @file op.c 
 * 
 * Module : Guião1 + Guião 2 
 * Description : Op -> (Guião1 e Guião2) - Trabalho de LI2 2020/2021
 * 
 * Neste ficheiro op.c tem-se como objetivo a implementação de operações matemáticas. Operações como: soma, subtração, multiplicação, divisão, entre outras.
 *
 */

#include <stdio.h>
#include "stack.h"
#include "op.h"

/**
* Desenvolvemos diferentes macros para os diferentes casos, tendo em consideração o seu tipo de dados.
*/

/**
 * \brief Macro responsável pelas operações binárias como and, or, xor e mod
 *
 * Esta macro vai receber : 
 * @param function Nome da função que será usada
 * @param op operação a efetuar
 *
 * Para operações como and, or, xor e mod apenas trabalhamos com variaveís do tipo long.
 *
 */
#define CASE_BIN(function, op)                                  \
    void function(int x, Stack* s) {                            \
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
    }                                                           \

CASE_BIN(and_operation,  AND)
CASE_BIN(or_operation, OR)
CASE_BIN(xor_operation, XOR)
CASE_BIN(mod_operation, MOD)                                                   

/**
 * \brief Macro responsável pelas operações com apenas um elemento como incrementar e decrementar
 * @param function Nome da função que será usada
 * @param op operação a efetuar
 *
 * Para operações com apenas uma variavel pode ser long ou double.
 */
#define CASE_SOLO(function, op)            \
    void function(int x, Stack* s){        \  
        if (x == 1) {                      \  ///< Incrementação ou Decremetação no caso de X ser long
                                           \
                long X = pop_LONG(s);      \
                push_LONG(s, op(X));       \
                                           \
        }                                  \
        else if (x == 2) {                 \  ///< Incrementação ou Decremetação no caso de X ser double
                double X = pop_DOUBLE(s);  \
                push_DOUBLE(s,op(X));      \
                                           \
        }                                  \
        else if (x == 3) {                 \  ///< Incrementação ou Decremetação no caso de X ser char
            char X = pop_CHAR(s);          \
            push_CHAR(s,op(X));            \
        }                                  \
    }                                      \

CASE_SOLO(dec_operation, --)  ///< Decrementação 
CASE_SOLO(inc_operation, ++)  ///< Incrementação


/**
 * \brief Macro responsável pelas operações que recebem dois elementos como soma, subtração, divisão, multiplicação e potência.
 * Para operações como +, -, *, / e ^ trabalhamos com variaveís do tipo long e double.
 * Para esta macro tivemos de ter em conta o caso em que as duas variaveis não fazerem parte do mesmo tipo de variavel.
 *
 * @param function Nome da função que será usada
 * @param op operação a efetuar
 *
 */
#define CASE_OP(function, op)                                   \
    void function(int x, Stack* s) {                            \
        if (x == 1)    {                                        \
                long X = pop_LONG(s);                           \     ///< Operação no caso de X ser long
                int y = idtype(s);                              \     ///< vamos identificar o tipo de y (pois este pode ser long ou double) 
                if (y == 1) {                                   \     ///< X e Y são LONG
                                                                \
                    long Y = pop_LONG(s);                       \
                    push_LONG(s, op(Y,X));                      \
                }                                               \
                else if (y == 2) {                              \    ///< X é LONG e Y é DOUBLE
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
                double X = pop_DOUBLE(s);                       \    ///< Operação no caso de X ser double
                int y = idtype(s);                              \    ///< vamos identificar o tipo de y 
                if (y == 1) {                                   \    ///< X é DOUBLE e Y é LONG
                    double_conversion(s);                       \
                    double Y = pop_DOUBLE(s);                   \
                    push_DOUBLE(s, op(Y,X));                    \
                }                                               \
                else if (y == 2) {                              \    ///< X e Y é DOUBLE 
                    double Y = pop_DOUBLE(s);                   \
                    push_DOUBLE(s, op(Y,X));                    \
                }                                               \
                                                                \
            }                                                   \
    }                                                           \
                                                           
CASE_OP(add_operation, ADD)      ///< Soma
CASE_OP(sub_operation, SUB)      ///< Subtração
CASE_OP(mult_operation, MULT)    ///< Multiplicação
CASE_OP(div_operation, DIV)      ///< Divisão
CASE_OP(pow_operation, pow)      ///< Potência

/**
 * \brief Função para trocar os últimos dois elementos da stack
 * 
 * @param s Recebe apontador para a Stack
 */
void SWAP(Stack* s) {
    DATA x,y;
    x = s->elements[s->sp];        ///< Elemento do topo da stack
    y = s->elements[s->sp - 1];    ///< Elemento anterior 
    s->elements[s->sp] = y;        ///< y passa a estar no topo da stack
    s->elements[s->sp - 1] = x;    ///< x passa estar na posição antiga de y
}

/**
 * \brief Função para trocar os três últimos elementos da stack
 * 
 * @param s Recebe apontador para a Stack
 */
void ROTATE(Stack* s) {
    DATA x,y,z;
    x = s->elements[s->sp];         ///< x é o elemento do topo da stack
    y = s->elements[s->sp - 1];     ///< y é o elemento abaixo de x
    z = s->elements[s->sp - 2];     ///< z é o elemento abaixo de y
    s->elements[s->sp] = z;         ///< O topo da stack agora possui o elemento z
    s->elements[s->sp - 1] = x;     ///< O endereço onde havia o y guardado passa a guardar o elemento x
    s->elements[s->sp - 2] = y;     ///< O endereço onde havia o z guardado passa a guardar o elemento y

}

/**
 * \brief Função que atribui valor a uma letra
 * 
 * @param s apontador para a Stack
 * @param c char recebido
 * @param v apontador para uma struct DATA
 */
void var_top (Stack* s, char c, DATA *v) {
    v[c-65] = top(s); ///< o elemento que ocupa a posição c-65 tomará o valor do topo da stack. Por exemplo, para A, o código ASCII é 65 e portanto v[0] = topo da stack
    
}

/**
 * \brief Macro responsável pelas operações lógicas como =, <, >
 * Para operações =, < e > trabalhamos com variaveís do tipo long e double.
 * Para esta macro, assim com a macro CASE_OP, tivemos de ter em conta o caso em que as duas variaveis não pertencem ao mesmo tipo.
 *
 * @param function Nome da função que será usada
 * @param op operação a efetuar
 */
#define LOGIC_BIN(function, op)             \
    void function(int x, Stack* s) {        \
    if (x==2) {                             \
        double X = pop_DOUBLE(s);           \    ///< Para X como DOUBLE
        int y = idtype(s);                  \
        if (y == 2) {                       \
            double Y = pop_DOUBLE(s);       \    ///< caso de Y ser DOUBLE
            if (op(X,Y)) push_LONG(s,1);    \
            else push_LONG(s,0);            \
        }                                   \
        else  {                             \
            long_conversion(s);             \
            long Y = pop_LONG(s);           \    ///< caso de Y ser LONG
            if (op(X,Y)) push_LONG(s,1);    \
            else push_LONG(s,0);            \
        }                                   \
    }                                       \
    else {                                  \
        long_conversion(s);                 \
        long X = pop_LONG(s);               \    ///< Para X como LONG
        int y = idtype(s);                  \
        if (y == 2) {                       \
            double Y = pop_DOUBLE(s);       \    ///< caso de Y ser DOUBLE
            if (op(X,Y)) push_LONG(s,1);    \
            else push_LONG(s,0);            \
        }                                   \
        else  {                             \
            long_conversion(s);             \    ///< caso de Y ser LONG
            long Y = pop_LONG(s);           \
            if (op(X,Y)) push_LONG(s,1);    \
            else push_LONG(s,0);            \
        }                                   \
    }                                       \
    }                                       \

LOGIC_BIN(equal_elogic, EQUAL)             ///< Operação de igualar
LOGIC_BIN(greater_elogic, GREATER)         ///< Operação de maior que
LOGIC_BIN(less_elogic, LESS)               ///< Operação de menor que

/** Conclusão/ Discussão:
*
* A utilização de macros permite-nos, para cada caso, ter um cuidado em particular com os diferentes tipos de dados e operações.
* Tivemos em atenção o facto de nas operações com 2 variaveis o facto de ambas poderem não ser do mesmo tipo.
* Desta forma, podemos organizar o código de uma maneira mais legivel e prática.
*
*/
