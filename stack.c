/**
 * @file stack.c 
 * 
 * Module : Guião1 (1a semana)
 * Description : Stack -> (Guião1) - Trabalho de LI2 2020/2021
 * 
 * Neste ficheiro stack.h tem-se como objetivo a implementação da stack. Stack é uma estrutura de dados linear que segue uma ordem particular para a qual as operações são realizadas e caracteriza um empilhamento de dados. A ordem a ser utilizada é **Last In First Out**.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

//Conversão de tipos

//Macro para conversão de tipos
#define DATA_CONVERSION(function,input_type,output_type)    \
DATA function(input_type val)                               \
{                                                           \
  DATA v;                                                   \
  v.type = output_type;                                     \
  v.x.output_type = val;                                    \
  return v;                                                 \
}

DATA_CONVERSION(charToDouble,char, DOUBLE)
DATA_CONVERSION(charToLong,char, LONG)
DATA_CONVERSION(longToDouble,long, DOUBLE)
DATA_CONVERSION(longToChar,long, CHAR)
DATA_CONVERSION(doubleToLong,double, LONG)

//no caso de double -> char, acredito que o ideal seja double -> long, long -> char 


int has_type(DATA n, int mask) {
    return (n.type & mask) != 0;
}

/**
 * \brief Função que cria uma stack vazia
 * 
 * @returns s , Stack criada
 */
Stack* create_stack() {
    Stack* s = (Stack*)malloc(sizeof(Stack)); ///< Aloca espaço para a stack 
    s->sp = -1; ///< inicializa stack pointer em -1, ou seja, stack está vazia
    s->capacity = 100; ///< Capacidade inicial da stack
    s->elements = (DATA *)malloc(s->capacity * sizeof(DATA)); ///< Aloca espaço para o array que contém os elementos da stack de acordo com a capacity e preenche 0 aos elementos
    
    return s;
} 
/**
 * \brief Função que retorna o topo da stack
 * 
 * @param s Stack
 * 
 * @returns s->elements[s->sp] , Elemento no qual o stack pointer está a apontar
 */
DATA top(Stack* s) {
    return s->elements[s->sp];
}


/**
 * \brief Função que verifica se a stack está vazia
 * 
 * @param s Stack
 * 
 * @returns s->sp == -1 , Se a stack estiver vazia retorna 1, caso contrário retorna 0
 */
int empty_stack(Stack* s) {
    
    return (s->sp == -1); 
}

/**
 * \brief Função que verifica se a stack está cheia
 * 
 * @param s Stack
 * 
 * @returns s->sp == s->capacity - 1 , capacity - 1 é o último elemento do array, caso este esteja preenchido, a stack está cheia
 */
int full_stack(Stack* s) {

    return (s->sp == s->capacity - 1); 

}

/**
 * \brief Função que adiciona um elemento no topo da stack
 * 
 * @param s e n , Stack e elemento que será adicionado à stack, respetivamente
 */
void push(Stack* s, DATA n) {
     
    if (full_stack(s)) {
        
        s->capacity *= 2; ///< Duplica a capacidade da stack
        s->elements = realloc(s->elements,s->capacity * sizeof(DATA)); ///< Realoca o espaço na memória do array que contém os elementos da stack para esta nova capacity
        
    }
    s->elements[++s->sp] = n; ///< Adiciona o elemento à stack e atualiza o stack pointer para a posição deste elemento

    
}


/**
 * \brief Funçao que remove o elemento do topo da stack
 * 
 * @param s Stack
 * 
 * @returns s->elements[s->sp--] , Stack sem o elemento do topo e com o stack pointer atualizado para o elemento que estava na célula de memória anterior ao que foi removido
 */
DATA pop(Stack* s) {
      

        s->capacity -= sizeof(long); ///< Retira o tamanho de um long da capacity
        s->elements = realloc(s->elements, s->capacity * sizeof(DATA)); ///< Realoca o espaço na memória do array que contém os elementos da stack para esta nova capacity
                
        return s->elements[s->sp--];
    
}

/**
 * \brief Função que imprime a stack
 * 
 * @param s Stack
 */
void print_stack(Stack *s) {
    
    for (int i = 0; i <= s->sp; i++) {
        DATA n = s->elements[i];
        TYPE type = n.type;
        switch(type) {
            case LONG:
                printf(" ""%ld", n.x.LONG); break;
            case DOUBLE:
                printf(" ""%g", n.x.DOUBLE); break;
            case CHAR:
                printf(" ""%c", n.x.CHAR); break;
            case STRING:
                printf(" ""%s", n.x.STRING); break;
        }
    }
    
}

//Macros para push e pop

#define STACK_OPERATION(_type, _name)         \
    void push_##_name(Stack *s, _type val) {  \
        DATA n;                               \
        n.type = _name;                       \
        n.x._name = val;                      \
        push(s,n);                            \
    }                                         \
    _type pop_##_name(Stack *s) {             \
        DATA n = pop(s);                      \
        assert(n.type == _name);              \
        return n.x._name;                     \
    }                                         \

STACK_OPERATION(long, LONG)
STACK_OPERATION(double, DOUBLE)
STACK_OPERATION(char, CHAR)
STACK_OPERATION(char *, STRING)

