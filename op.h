/**
 * @file op.h 
 * 
 * Module : Guião1 + Guião2
 * Description : Op -> (Guião1 e Guião2) - Trabalho de LI2 2020/2021
 * 
 * Neste ficheiro op.h tem-se como objetivo a implementação das operações matemáticas. 
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * \brief Macro que contém o nome das operações matemáticas e o que é suposto cada uma fazer
 * @param x primeiro elemento retirado da stack para efetuar a operação
 * @param y segundo elemento retirado da stack para efetuar a operação
 */
#define ADD(x,y) x + y
#define SUB(x,y) x - y
#define MULT(x,y) x * y
#define DIV(x,y) x / y
#define MOD(x,y) x % y
#define AND(x,y) x & y
#define OR(x,y) x | y
#define XOR(x,y) x ^ y
#define EQUAL(x,y) x == y
#define GREATER(x,y) x < y
#define LESS(x,y) x > y
#define EGREATER(x,y) x > y
#define ELESS(x,y) x < y
#define EIF(x,y) y != 0
#define EOR(x,y) y == 0

#define CASE_BIN_PROTO(function, op)                               \
    void function(Stack* s);                                       \

CASE_BIN_PROTO(and_operation,  AND)
CASE_BIN_PROTO(or_operation, OR)
CASE_BIN_PROTO(xor_operation, XOR)
CASE_BIN_PROTO(mod_operation, MOD)

#define CASE_SOLO_PROTO(function, op)   \
    void function(int x, Stack* s);     \

CASE_SOLO_PROTO(dec_operation, --)
CASE_SOLO_PROTO(inc_operation, ++)

#define CASE_OP_PROTO(function, op)     \
    void function(int x, Stack* s);     \

CASE_OP_PROTO(add_operation, ADD)
CASE_OP_PROTO(sub_operation, SUB)
CASE_OP_PROTO(mult_operation, MULT)
CASE_OP_PROTO(div_operation, DIV)
CASE_OP_PROTO(pow_operation, pow)

void SWAP(Stack* s);
void ROTATE(Stack* s);

#define LOGIC_BIN_PROTO(function, op)       \
    void function(Stack* s);                \

LOGIC_BIN_PROTO(equal_logic, EQUAL)
LOGIC_BIN_PROTO(greater_logic, GREATER)
LOGIC_BIN_PROTO(less_logic, LESS)

void var_top (Stack* s, char c, DATA *v);
void logic_not(Stack* s);
void if_then_else(Stack* s);

#define LOGIC_BIN_E_PROTO(function, op, v)\
    void function(Stack* s);              \

LOGIC_BIN_E_PROTO(greater_elogic, EGREATER, 2)
LOGIC_BIN_E_PROTO(less_elogic, LESS, 2)
LOGIC_BIN_E_PROTO(and_elogic, EIF, 0)

void logic_e_null(Stack* s);
void eor_logic(Stack* s);
void logic_e(char* c, Stack* s);