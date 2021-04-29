/**
 * @file stack.h 
 * 
 * Module : Guião1 + Guião2
 * Description : Stack -> (Guião1 e Guião2) - Trabalho de LI2 2020/2021
 * 
 * Neste ficheiro stack.h tem-se como objetivo a implementação da stack. Stack é uma estrutura de dados linear que segue uma ordem particular para a qual as operações são realizadas e caracteriza um empilhamento de dados. A ordem a ser utilizada é **Last In First Out**.
 * (Guião 2) Atualizar a stack de forma a trabalhar com os diferentes tipos de dados.
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Enum para tipos de dados possíveis
 */
typedef enum { /**Enum de tipo TYPE */
    LONG = 1, /**Dados tipo long */
    DOUBLE = 2, /**Dados tipo double */
    CHAR = 3, /**Dados tipo char */
    STRING = 4 /**Dados tipo string */
    } TYPE; /** Nome da enum */

/**
 * \brief Máscaras para integers 
 */
#define INTEGER (LONG | CHAR) /** integer é long ou char */

/**
 * \brief Máscaras para numbers 
 */
#define NUMBER  (INTEGER | DOUBLE) /** number é integer ou double */

/**
 * \brief Estrutura que guarda dados e seu respetivo tipo
 */
typedef struct { /** Estrutura do tipo DATA */
  TYPE type; /** Tipo de dados guardado pela struct */
  union { /**Union para guardar o dado no seu respetivo tipo */
  long LONG; /** Valor do tipo long */
  double DOUBLE; /** Valor do tipo double */
  char CHAR; /** Valor do tipo char */
  char *STRING; /** Valor do tipo string */
  } x; /** Union x */
} DATA; /** Struct DATA */


/**
 * \brief Representação da stack através de uma estrutura
 */
typedef struct { 
    int sp; ///< Stack pointer -> Aponta para o elemento no topo da Stack
    DATA *elements; ///< Array para conter os elementos da Stack
    int capacity; ///< Capacidade total atual da Stack

}Stack;

//Declarações de funções
int idtype(Stack* s);
Stack* create_stack();
DATA top(Stack* s);
void push(Stack *s, DATA n);
DATA pop(Stack *s);
int empty_stack(Stack* s);
int full_stack(Stack* s);
void print_stack(Stack *s);
void char_conversion (Stack* s);
void long_conversion (Stack* s);
void double_conversion (Stack* s);
void string_conversion (Stack* s);

//Macros para conversão de tipos de dados.

/**
 * \brief Declaração da Macro para criar funções que efetue conversões entre os diversos tipos disponíveis na stack: double, long, char e string
 * @param function Nome da função
 * @param input_type tipo do input
 * @param output_type tipo do output
 */
#define DATA_CONVERSION_PROTO(function,input_type,output_type)                 \
    DATA function(input_type val); /** Macro chama função para o input type */ \

DATA_CONVERSION_PROTO(charToDouble,char, DOUBLE) ///< Declaração da função gerada pela macro DATA_CONVERSION para converter de char para double
DATA_CONVERSION_PROTO(charToLong,char, LONG) ///< Declaração da função gerada pela macro DATA_CONVERSION para converter de char para long
DATA_CONVERSION_PROTO(longToDouble,long, DOUBLE) ///< Declaração da função gerada pela macro DATA_CONVERSION para converter de long para double
DATA_CONVERSION_PROTO(longToChar,long, CHAR) ///< Declaração da função gerada pela macro DATA_CONVERSION para converter de long para char
DATA_CONVERSION_PROTO(doubleToLong,double, LONG) ///< Declaração da função gerada pela macro DATA_CONVERSION para converter de double para long                 


/**
 * \brief Declaração da Macro para efetuar operações de acordo com disponíveis dos elementos na stack: double, long, char e string
 * 
 * Esta macro vai receber:
 * @param _type tipo do elemento
 * @param _name nome correspondente ao tipo: LONG, DOUBLE, CHAR, STRING
 */
#define STACK_OPERATION_PROTO(_type, _name)                                                 \
    void push_##_name(Stack *s, _type val); /** Macro gera a função push para cada tipo */  \
    _type pop_##_name(Stack *s); /** Macro gera a função push para cada tipo */             \

STACK_OPERATION_PROTO(long,LONG) ///< Declaração da função gerada pela macro STACK_OPERATION para efetuar push e pop de elemento com tipo long
STACK_OPERATION_PROTO(double,DOUBLE) ///< Declaração da função gerada pela macro STACK_OPERATION para efetuar push e pop de elemento com tipo double
STACK_OPERATION_PROTO(char,CHAR) ///< Declaração da função gerada pela macro STACK_OPERATION para efetuar push e pop de elemento com tipo char
STACK_OPERATION_PROTO(char *, STRING) ///< Declaração da função gerada pela macro STACK_OPERATION para efetuar push e pop de elemento com tipo string

