/**
 * @file stack.h 
 * 
 * Module : Guião1 (1a semana)
 * Description : Stack -> (Guião1) - Trabalho de LI2 2020/2021
 * 
 * Neste ficheiro stack.h tem-se como objetivo a implementação da stack. Stack é uma estrutura de dados linear que segue uma ordem particular para a qual as operações são realizadas e caracteriza um empilhamento de dados. A ordem a ser utilizada é **Last In First Out**.
 * 
 */
#include <stdio.h>
#include <stdlib.h>

typedef enum {LONG = 1, DOUBLE = 2, CHAR = 4, STRING = 8, POINTER } TYPE;

#define INTEGER (LONG | CHAR)
#define NUMBER  (INTEGER | DOUBLE)

typedef struct {
  TYPE type;
  union {
  long LONG;
  double DOUBLE;
  char CHAR;
  char *STRING;
  void *ptr;
  } x;
} DATA;


/**
 * \brief Representação da stack através de uma estrutura
 */
typedef struct {
    int sp; ///< Stack pointer -> Aponta para o elemento no topo da Stack
    DATA *elements; ///< Array para conter os elementos da Stack
    int capacity; ///< Capacidade total atual da Stack

}Stack;

int has_type(DATA n, int mask);
Stack* create_stack();
DATA top(Stack* s);
void push(Stack *s, DATA n);
DATA pop(Stack *s);
int empty_stack(Stack* s);
int full_stack(Stack* s);
void print_stack(Stack *s);


//Macros 

#define DATA_CONVERSION_PROTO(function,input_type,output_type) \
    DATA function(input_type val);  

DATA_CONVERSION_PROTO(charToDouble,char, DOUBLE)
DATA_CONVERSION_PROTO(charToLong,char, LONG)
DATA_CONVERSION_PROTO(longToDouble,long, DOUBLE)
DATA_CONVERSION_PROTO(longToChar,long, CHAR)
DATA_CONVERSION_PROTO(doubleToLong,double, LONG)                 



#define STACK_OPERATION_PROTO(_type, _name)   \
    void push_##_name(Stack *s, _type val);   \
    _type pop_##_name(Stack *s);

STACK_OPERATION_PROTO(long,LONG)
STACK_OPERATION_PROTO(double,DOUBLE)
STACK_OPERATION_PROTO(char,CHAR)
STACK_OPERATION_PROTO(char *, STRING)

/**
* \brief Indicar o tipo de dados que está na stack.
*/

  int id_Type(Stack *s) {
    int r;
    if(has_type(top(s), LONG)) r = 1;
    if(has_type(top(s), DOUBLE)) r = 2;
    if(has_type(top(s), CHAR)) r = 4;
    if(has_type(top(s), STRING)) r = 8;
    return r;
}
