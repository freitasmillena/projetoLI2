/**
 * @file stack.c 
 * 
 * Module : Guião1 + Guião 2 
 * Description : Stack -> (Guião1 e Guião2) - Trabalho de LI2 2020/2021
 * 
 * Neste ficheiro stack.c tem-se como objetivo a implementação da stack. Stack é uma estrutura de dados linear que segue uma ordem particular para a qual as operações são realizadas e caracteriza um empilhamento de dados. A ordem a ser utilizada é **Last In First Out**.
 * (Guião2) Atualizar o código para os diferentes tipos de dados.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"


//Identificação de tipos
/**
* \brief Função que indica o tipo do dado que está no topo da stack.
* @param s Apontador para a stack 
* @returns r , Tipo do elemento
*/
int idtype(Stack* s) {
    int r = 0;
    DATA elem = s->elements[s->sp];
    TYPE type = elem.type;
    switch(type) {
        case LONG: r = 1; break;
        case DOUBLE: r = 2; break;
        case CHAR: r = 3; break;
        case STRING: r = 4; break;
    }
    return r;
}


//Conversão de tipos

/**
 * \brief Macro para criar funções que efetue conversões entre os diversos tipos disponíveis na stack: double, long, char e string
 * @param function Nome da função
 * @param input_type tipo do input
 * @param output_type tipo do output
 */
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
        
        s->capacity += 100; ///< Duplica a capacidade da stack
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
      
    return s->elements[s->sp--];
  
}

/**
 * \brief Função que imprime a stack
 * 
 * @param s Apontador para a Stack
 */
void print_stack(Stack *s) {
    
    for (int i = 0; i <= s->sp; i++) {
        DATA n = s->elements[i];
        TYPE type = n.type;
        switch(type) {
            case LONG:
                printf("%ld", n.x.LONG); break;
            case DOUBLE:
                printf("%g", n.x.DOUBLE); break;
            case CHAR:
                printf("%c", n.x.CHAR); break;
            case STRING:
                printf("%s", n.x.STRING); break;
        }
    }
    
}


/**
 * \brief Macro para efetuar operações de acordo com disponíveis dos elementos na stack: double, long, char e string
 * 
 */
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

/**
 * \brief Função para conversão de um elemento para o tipo char
 * @param s Apontador para a stack
 */
void char_conversion (Stack* s) {
    int x = idtype(s);
    switch (x) {
        case (1): {
            long y = pop_LONG(s); 
            push(s, longToChar(y)); 
            break;
        }
        case (2): {
            long y  = (long) pop_DOUBLE(s);
            push(s, longToChar(y));
            break;
        }
        case (3): ; break;

    }
}

/**
 * \brief Função para conversão de um elemento para o tipo long
 * @param s Apontador para a stack
 */
void long_conversion (Stack* s) {
    int x = idtype(s);
    switch (x) {
        case (1): ; break;
        case (2): {
            double y = pop_DOUBLE(s); 
            push(s, doubleToLong(y)); 
            break;
        }
        case (3): {
            char c = pop_CHAR(s); 
            push(s,charToLong(c)); 
            break;
        }
        case (4): {
            char *ptr; 
            long r = strtol(pop_STRING(s),&ptr, 10); 
            push_LONG(s,r); 
            break;
        }

    }
}

/**
 * \brief Função para conversão de um elemento para o tipo double
 * @param s Apontador para a stack
 */
void double_conversion(Stack* s) {
    int x = idtype(s);
    switch (x) {
        case (1): {
            long y = pop_LONG(s); 
            push(s,longToDouble(y)); 
            break;
        }
        case (2): ; break;
        case (3): {
            char c = pop_CHAR(s); 
            push(s,charToDouble(c)); 
            break;
        }
        case (4): {
            char *ptr; 
            double r = strtod(pop_STRING(s),&ptr); 
            push_DOUBLE(s,r); 
            break;
        }

    }
}

/**
 * \brief Função para conversão de um elemento para o tipo string
 * @param s Apontador para a stack
 */
void string_conversion(Stack* s) {
    int x = idtype(s);
    char str[40];
    switch (x) {
        case (1): {
            sprintf(str, "%ld", pop_LONG(s)); 
            push_STRING(s,str);
            break;
        }
        case (2): {
            sprintf(str, "%g", pop_DOUBLE(s)); 
            push_STRING(s,str); 
            break;
        }
        case (3): {
            sprintf(str, "%c", pop_CHAR(s)); 
            push_STRING(s,str); 
            break;
        }
        case (4): ;break;
    }
}


