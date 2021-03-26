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

/**
 * \brief Representação da stack através de uma estrutura
 */
typedef struct {
    int sp; ///< Stack pointer -> Aponta para o elemento no topo da Stack
    long *elements; ///< Array para conter os elementos da Stack
    int capacity; ///< Capacidade total atual da Stack

}Stack;

void push(Stack *s, long n);
int pop(Stack *s);
int empty_stack(Stack* s);
int full_stack(Stack* s);
void print_stack(Stack *s);
