/**
 * @file stack.c 
 * 
 * Module : Guião1 + Guião 2 + Guião 3
 * Description : Stack -> (Guião1 e Guião2 e Guião 3) - Trabalho de LI2 2020/2021
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
* @returns r , Inteiro que corresponde ao tipo do elemento
*/
int idtype(Stack* s) {
    int r = 0;  ///< r inicializado em 0
    DATA elem = s->elements[s->sp]; ///< elemento no topo da stack guardado em DATA
    TYPE type = elem.type; ///< tipo do elemento
    switch(type) {  
        case LONG: r = 1; break; ///< caso seja long, r = 1
        case DOUBLE: r = 2; break; ///< caso seja double, r = 2
        case CHAR: r = 3; break;   ///< caso seja char, r = 3
        case STRING: r = 4; break; ///< caso seja string, r = 4
    }
    return r; ///< retorna o inteiro correspondente ao tipo do elemento
}


//Conversão de tipos

/**
 * \brief Macro para criar funções que efetue conversões entre os diversos tipos disponíveis na stack: double, long, char e string
 * @param function Nome da função
 * @param input_type tipo do input
 * @param output_type tipo do output
 */
#define DATA_CONVERSION(function,input_type,output_type)                                             \
DATA function(input_type val) /** Macro chama função para o input type */                            \
{                                                                                                    \
  DATA v;   /** Uma struct DATA v */                                                                 \
  v.type = output_type; /** type é o tipo do output desejado */                                      \
  v.x.output_type = val; /** guarda o valor em v.x.output_type*/                                     \
  return v;  /** retorna o valor após a conversão */                                                 \
}                                                                                                    \

DATA_CONVERSION(charToDouble,char, DOUBLE) 
DATA_CONVERSION(charToLong,char, LONG)     
DATA_CONVERSION(longToDouble,long, DOUBLE) 
DATA_CONVERSION(longToChar,long, CHAR)     
DATA_CONVERSION(doubleToLong,double, LONG) 


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
    
    return s; ///< retorna a stack criada
} 


/**
 * \brief Função que retorna o topo da stack
 * 
 * @param s Stack
 * 
 * @returns s->elements[s->sp] , Elemento no qual o stack pointer está a apontar
 */
DATA top(Stack* s) {
    return s->elements[s->sp]; ///< retorna o elemento do topo da stack, ou seja, aquele no qual o sp está a apontar
}


/**
 * \brief Função que verifica se a stack está vazia
 * 
 * @param s Stack
 * 
 * @returns s->sp == -1 , Se a stack estiver vazia retorna 1, caso contrário retorna 0
 */
int empty_stack(Stack* s) {
    
    return (s->sp == -1); ///< é empty se sp for igual ao seu valor inicializado que é -1
}

/**
 * \brief Função que verifica se a stack está cheia
 * 
 * @param s Stack
 * 
 * @returns s->sp == s->capacity - 1 , capacity - 1 é o último elemento do array, caso este esteja preenchido, a stack está cheia
 */
int full_stack(Stack* s) {

    return (s->sp == s->capacity - 1); ///< a stack encontra-se cheia de o sp estiver a apontar para a capacidade - 1, pois o sp é inicializado igual a -1

}

/**
 * \brief Função que adiciona um elemento no topo da stack
 * 
 * @param s e n , Stack e elemento que será adicionado à stack, respetivamente
 */
void push(Stack* s, DATA n) {
     
    if (full_stack(s)) { ///< caso a stack esteja cheia
        
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
      
    return s->elements[s->sp--]; ///< retorna o elemento que estava no topo da stack e decrementa o sp
  
}

/**
 * \brief Função que imprime a stack
 * 
 * @param s Apontador para a Stack
 */
void print_stack(Stack *s) {
    
    for (int i = 0; i <= s->sp; i++) {  ///< ciclo for até que i seja menor ou igual ao sp
        DATA n = s->elements[i]; ///< guarda o elemento em DATA n
        TYPE type = n.type; ///< tipo do elemento
        switch(type) {
            case LONG: ///< caso seja long
                printf("%ld", n.x.LONG); break; ///< imprime ao usar %ld
            case DOUBLE: ///< caso seja double
                printf("%g", n.x.DOUBLE); break; ///< imprime ao usar %g
            case CHAR: ///< caso seja char
                printf("%c", n.x.CHAR); break; ///< imprime ao usar %c
            case STRING: ///< caso seja string
                printf("%s", n.x.STRING); break; ///< imprime ao usar %s
        }
    }
    
}


/**
 * \brief Macro para efetuar operações de acordo com disponíveis dos elementos na stack: double, long, char e string
 * 
 * Esta macro vai receber:
 * @param _type tipo do elemento
 * @param _name nome correspondente ao tipo: LONG, DOUBLE, CHAR, STRING
 */
#define STACK_OPERATION(_type, _name)                                                                            \
    void push_##_name(Stack *s, _type val) {    /** Macro gera a função push para cada tipo */                   \
        DATA n; /** Struct DATA n */                                                                             \
        n.type = _name;  /** tipo = _name recebido (LONG,DOUBLE, CHAR, STRING) */                                \
        n.x._name = val; /** valor guardado na union dentro da struct no campo correspondente ao seu tipo */     \
        push(s,n);  /** efetua operação push para o elemento */                                                  \
    }                                                                                                            \
    _type pop_##_name(Stack *s) {/** Macro gera a função push para cada tipo */                                  \
        DATA n = pop(s); /** Struct DATA n guarda o valor retirado do topo da stack */                           \
        assert(n.type == _name); /** confirmar que o tipo corresponde corretamente */                            \
        return n.x._name; /** retorna o elemento */                                                              \
    }                                                                                                            \

STACK_OPERATION(long, LONG) 
STACK_OPERATION(double, DOUBLE) 
STACK_OPERATION(char, CHAR) 
STACK_OPERATION(char *, STRING) 

//Conversão de tipos

/**
 * \brief Função para conversão de um elemento para o tipo char
 * @param s Apontador para a stack
 */
void char_conversion (Stack* s) {
    int x = idtype(s); ///< x guarda o inteiro correspondente ao tipo do elemento do topo da stack
    switch (x) {
        case (1): { ///< caso seja long
            long y = pop_LONG(s); ///< efetua operação pop e guarda em long y
            push(s, longToChar(y)); ///< efetua operação push do char após a conversão de long para char
            break;
        }
        case (2): { ///< caso seja double
            long y  = (long) pop_DOUBLE(s); ///< efetua operação pop e guarda em long y, neste caso temos que guardar de double pra long para depois converter para char
            push(s, longToChar(y)); ///< efetua operação push do char após a conversão de long para char
            break;
        }
        case (3): ; break; ///< caso seja char, não efetua operação

    }
}

/**
 * \brief Função para conversão de um elemento para o tipo long
 * @param s Apontador para a stack
 */
void long_conversion (Stack* s) {
    int x = idtype(s); ///< x guarda o inteiro correspondente ao tipo do elemento do topo da stack
    switch (x) {
        case (1): ; break; ///< caso seja long, não efetua operação
        case (2): { ///< caso seja double
            double y = pop_DOUBLE(s); ///< efetua operação pop e guarda em double y
            push(s, doubleToLong(y)); ///< efetua operação push do double após a conversão de long para double
            break;
        }
        case (3): { ///< caso seja char
            char c = pop_CHAR(s); ///< efetua operação pop e guarda em char c
            push(s,charToLong(c)); ///< efetua operação push do char após a conversão de long para char
            break;
        }
        case (4): { ///< caso seja string 
            char *ptr; ///< apontador ptr para string
            long r = strtol(pop_STRING(s),&ptr, 10); ///< converte string para long
            push_LONG(s,r); ///< efetua operação push do long após a conversão
            break;
        }

    }
}

/**
 * \brief Função para conversão de um elemento para o tipo double
 * @param s Apontador para a stack
 */
void double_conversion(Stack* s) {
    int x = idtype(s); ///< x guarda o inteiro correspondente ao tipo do elemento do topo da stack
    switch (x) {
        case (1): { ///< caso seja long 
            long y = pop_LONG(s); ///< efetua operação pop e guarda em long y
            push(s,longToDouble(y)); ///< efetua operação push do double após a conversão de long para double
            break;
        }
        case (2): ; break; ///< caso seja double, não efetua operação
        case (3): { ///< caso seja char 
            char c = pop_CHAR(s); ///< efetua operação pop e guarda em char c
            push(s,charToDouble(c)); ///< efetua operação push do double após a conversão de char para double
            break;
        }
        case (4): { ///< caso seja string 
            char *ptr; ///< apontador ptr para string
            double r = strtod(pop_STRING(s),&ptr); ///< converte string para double
            push_DOUBLE(s,r); ///< efetua operação push do double após a conversão
            break;
        }

    }
}

/**
 * \brief Função para conversão de um elemento para o tipo string
 * @param s Apontador para a stack
 */
void string_conversion(Stack* s) {
    int x = idtype(s); ///< x guarda o inteiro correspondente ao tipo do elemento do topo da stack
    char str[40]; ///< array de char str
    switch (x) {
        case (1): { ///< caso seja long 
            sprintf(str, "%ld", pop_LONG(s)); ///< converte de long para string
            push_STRING(s,str); ///< efetua operação push da string
            break;
        }
        case (2): { ///< caso seja double 
            sprintf(str, "%g", pop_DOUBLE(s)); ///< converte de double para string
            push_STRING(s,str); ///< efetua operação push da string
            break;
        }
        case (3): { ///< caso seja char 
            sprintf(str, "%c", pop_CHAR(s)); ///< converte de char para string
            push_STRING(s,str); ///< efetua operação push da string
            break;
        }
        case (4): ;break; ///< caso seja string, não efetua operação 
    }
}


