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
#include "stack.h"

/**
 * \brief Função que cria uma stack vazia
 * 
 * @returns s , Stack criada
 */
Stack* create_stack() {
    Stack* s = (Stack*)malloc(sizeof(Stack)); ///< Aloca espaço para a stack
    s->sp = -1; ///< inicializa stack pointer em -1, ou seja, stack está vazia
    s->capacity = 10240; ///< Capacidade inicial da stack
    s->elements = (long*)malloc(s->capacity * sizeof(long)); ///< Aloca espaço para o array que contém os elementos da stack de acordo com a capacity
    
    return s;
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
void push(Stack* s, long n) {
     
    if (full_stack(s)) {
        
        s->capacity *= 2; ///< Duplica a capacidade da stack
        s->elements = realloc(s->elements,s->capacity * sizeof(long)); ///< Realoca o espaço na memória do array que contém os elementos da stack para esta nova capacity
        
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
int pop(Stack* s) {
    
    if (empty_stack(s)) return 0; 

    else {

        s->capacity -= sizeof(long); ///< Retira o tamanho de um long da capacity
        s->elements = realloc(s->elements, s->capacity * sizeof(long)); ///< Realoca o espaço na memória do array que contém os elementos da stack para esta nova capacity
        


        
        return s->elements[s->sp--];
    }

}

/**
 * \brief Função que imprime a stack
 * 
 * @param s Stack
 */
void print_stack(Stack *s) {
    
    for (int i = 0; i <= s->sp; i++) {
        printf("%ld", s->elements[i]);
    }
}
