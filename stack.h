#include <stdio.h>
#include <stdlib.h>

//representar stack através de uma estrutura

typedef struct {
    int sp; //stack pointer 
    long *elements; 
    int capacity;

}Stack;

void push(Stack *s, long n);
int pop(Stack *s);

//Cria uma stack vazia

Stack* create_stack() {
    Stack* s = (Stack*)malloc(sizeof(Stack)); //alocar espaço para a stack
    s->sp = -1; //inicializa stack pointer em -1, ou seja, stack está vazia
    s->capacity = 10240;
    s->elements = (long*)malloc(s->capacity * sizeof(long));
    
    return s;
} 

//Verifica se a stack está vazia
int empty_stack(Stack* s) {
    
    return (s->sp == -1); //se for verdadeiro 1, se for falso 0 
}

//Verifica se a stack está cheia
int full_stack(Stack* s) {

    return (s->sp == s->capacity - 1); //capacity - 1 é o último elemento do array, caso esteja preenchido, logo, a stack está cheia

}

//Adicionar elementos na stack

void push(Stack* s, long n) { //n é o elemento que será adicionado
     
    if (full_stack(s)) {
        
        s->capacity *= 2; //duplica a capacidade da stack
        s->elements = realloc(s->elements,s->capacity * sizeof(long)); //realloc desta nova capacidade
        
    }
    s->elements[++s->sp] = n;

    
}
