/**
 * @file op.c 
 * 
 * Module : Guião1 + Guião 2 
 * Description : Op -> (Guião1 e Guião2) - Trabalho de LI2 2020/2021
 * 
 * Neste ficheiro op.c tem-se como objetivo a implementação de operações matemáticas. Operações como: soma, subtração, multiplicação, divisão, entre outras.
 */
#include <stdio.h>
#include "stack.h"
#include "op.h"

/**
* Desenvolvemos diferentes macros para os diferentes casos, tendo em consideração o sei tipo de dados.
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


#define CASE_SOLO(function, op)            \
    void function(int x, Stack* s){        \
        if (x == 1) {                      \
                                           \
                long X = pop_LONG(s);      \
                push_LONG(s, op(X));       \
                                           \
        }                                  \
        else if (x == 2) {                 \
                double X = pop_DOUBLE(s);  \
                push_DOUBLE(s,op(X));      \
                                           \
        }                                  \
        else if (x == 3) {                 \
            char X = pop_CHAR(s);          \
            push_CHAR(s,op(X));            \
        }                                  \
    }                                      \

CASE_SOLO(dec_operation, --)
CASE_SOLO(inc_operation, ++)



#define CASE_OP(function, op)                                   \
    void function(int x, Stack* s) {                            \
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
    }                                                           \
                                                           
CASE_OP(add_operation, ADD)
CASE_OP(sub_operation, SUB)
CASE_OP(mult_operation, MULT)
CASE_OP(div_operation, DIV)
CASE_OP(pow_operation, pow)

/**
 * \brief Função para trocar os últimos dois elementos da stack
 * 
 * @param s Stack
 */
void SWAP(Stack* s) {
    DATA x,y;
    x = s->elements[s->sp]; ///< Elemento do topo da stack
    y = s->elements[s->sp - 1]; ///< Elemento anterior 
    s->elements[s->sp] = y; ///< y passa a estar no topo da stack
    s->elements[s->sp - 1] = x; ///< x passa estar na posição antiga de y
}

/**
 * \brief Função para trocar os três últimos elementos da stack
 * 
 * @param s Stack
 */
void ROTATE(Stack* s) {
    DATA x,y,z;
    x = s->elements[s->sp]; ///< x é o elemento do topo da stack
    y = s->elements[s->sp - 1]; ///< y é o elemento abaixo de x
    z = s->elements[s->sp - 2]; ///< z é o elemento abaixo de y
    s->elements[s->sp] = z; ///< O topo da stack agora possui o elemento z
    s->elements[s->sp - 1] = x; ///< O endereço onde havia o y guardado passa a guardar o elemento x
    s->elements[s->sp - 2] = y; ///< O endereço onde havia o z guardado passa a guardar o elemento y

}

void var_top (Stack* s, char c, DATA *v) {
    v[c-65] = top(s); ///< o elemento que ocupa a posição c-65 tomará o valor do topo da stack. Por exemplo, para A, o código ASCII é 65 e portanto v[0] = topo da stack
    
}


#define LOGIC_BIN(function, op)             \
    void function(int x, Stack* s) {        \
    if (x==2) {                             \
        double X = pop_DOUBLE(s);           \
        int y = idtype(s);                  \
        if (y == 2) {                       \
            double Y = pop_DOUBLE(s);       \
            if (op(X,Y)) push_LONG(s,1);    \
            else push_LONG(s,0);            \
        }                                   \
        else  {                             \
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
        if (y == 2) {                       \
            double Y = pop_DOUBLE(s);       \
            if (op(X,Y)) push_LONG(s,1);    \
            else push_LONG(s,0);            \
        }                                   \
        else  {                             \
            long_conversion(s);             \
            long Y = pop_LONG(s);           \
            if (op(X,Y)) push_LONG(s,1);    \
            else push_LONG(s,0);            \
        }                                   \
    }                                       \
    }                                       \

LOGIC_BIN(equal_elogic, EQUAL)
LOGIC_BIN(greater_elogic, GREATER)
LOGIC_BIN(less_elogic, LESS)

