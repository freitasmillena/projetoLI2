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

#define ADD(x,y) x + y /** Macro para operação de soma */
#define SUB(x,y) x - y /** Macro para operação de subtração */
#define MULT(x,y) x * y /** Macro para operação de multiplicação */
#define DIV(x,y) x / y /** Macro para operação de divisão */
#define MOD(x,y) x % y /** Macro para operação de resto da divisão */
#define AND(x,y) x & y /** Macro para operação binária and */
#define OR(x,y) x | y /** Macro para operação binária or */
#define XOR(x,y) x ^ y /** Macro para operação binária xor */
#define EQUAL(x,y) x == y /** Macro para operação lógica igual */
#define GREATER(x,y) x < y /** Macro para operação lógica maior */
#define LESS(x,y) x > y /** Macro para operação lógica menor */
#define EGREATER(x,y) x > y /** Macro para operação lógica e> */
#define ELESS(x,y) x < y /** Macro para operação lógica e< */
#define EIF(x,y) y != 0 /** Macro para operação lógica e& */
#define EOR(x,y) y == 0 /** Macro para operação lógica e| */

/**
 * \brief Declaração da macro responsável pelas operações binárias como and, or, xor e mod
 *
 * Esta macro vai receber : 
 * @param function Nome da função que será usada
 * @param op operação a efetuar
 *
 * Para operações como and, or, xor e mod apenas trabalhamos com variaveís do tipo long.
 *
 */
#define CASE_BIN_PROTO(function, op)                               \
    void function(Stack* s);                                       \

CASE_BIN_PROTO(and_operation,  AND)
CASE_BIN_PROTO(or_operation, OR)
CASE_BIN_PROTO(xor_operation, XOR)
CASE_BIN_PROTO(mod_operation, MOD)

/**
 * \brief Declaração da macro responsável pelas operações com apenas um elemento como incrementar e decrementar
 * @param function Nome da função que será usada
 * @param op operação a efetuar
 *
 * Para operações com apenas uma variavel pode ser long ou double.
 */
#define CASE_SOLO_PROTO(function, op)   \
    void function(int x, Stack* s);     \

CASE_SOLO_PROTO(dec_operation, --)
CASE_SOLO_PROTO(inc_operation, ++)


/**
 * \brief Declaração da macro responsável pelas operações que recebem dois elementos como soma, subtração, divisão, multiplicação e potência.
 * Para operações como +, -, *, / e ^ trabalhamos com variaveís do tipo long e double.
 * Para esta macro tivemos de ter em conta o caso em que as duas variaveis não fazerem parte do mesmo tipo de variavel.
 *
 * @param function Nome da função que será usada
 * @param op operação a efetuar
 *
 */
#define CASE_OP_PROTO(function, op)     \
    void function(int x, Stack* s);     \

CASE_OP_PROTO(add_operation, ADD)
CASE_OP_PROTO(sub_operation, SUB)
CASE_OP_PROTO(mult_operation, MULT)
CASE_OP_PROTO(div_operation, DIV)
CASE_OP_PROTO(pow_operation, pow)

/**
 * \brief Declaração da função para trocar os últimos dois elementos da stack
 * 
 * @param s Recebe apontador para a Stack
 */
void SWAP(Stack* s);

/**
 * \brief Declaração da função para trocar os três últimos elementos da stack
 * 
 * @param s Recebe apontador para a Stack
 */
void ROTATE(Stack* s);


/**
 * \brief Declaração da macro responsável pelas operações lógicas como =, <, >
 * Para operações =, < e > trabalhamos com variaveís do tipo long e double.
 * Para esta macro, assim com a macro CASE_OP, tivemos de ter em conta o caso em que as duas variaveis não pertencem ao mesmo tipo.
 *
 * @param function Nome da função que será usada
 * @param op operação a efetuar
 */
#define LOGIC_BIN_PROTO(function, op)       \
    void function(Stack* s);                \

LOGIC_BIN_PROTO(equal_logic, EQUAL)
LOGIC_BIN_PROTO(greater_logic, GREATER)
LOGIC_BIN_PROTO(less_logic, LESS)

void var_top (Stack* s, char c, DATA *v);
void logic_not(Stack* s);
void if_then_else(Stack* s);

/**
 * \brief Declaração da macro responsável pelas operações lógicas e(Operação)
 * @param function Nome final de cada função
 * @param op Operação a ser utilizada
 * @param v Inteiro para controlo do push. Caso seja 2 significa que é uma operação e< ou e> portanto o push é de elementos da stack. Caso seja 0 é um e&.
 */
#define LOGIC_BIN_E_PROTO(function, op, v)\
    void function(Stack* s);              \

LOGIC_BIN_E_PROTO(greater_elogic, EGREATER, 2)
LOGIC_BIN_E_PROTO(less_elogic, LESS, 2)
LOGIC_BIN_E_PROTO(and_elogic, EIF, 0)


void logic_e_null(Stack* s);
void eor_logic(Stack* s);
void logic_e(char* c, Stack* s);