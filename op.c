/**
 * @file op.c 
 * 
 * Module : Guião1 + Guião 2 
 * Description : Op -> (Guião1 e Guião2) - Trabalho de LI2 2020/2021
 * 
 * Neste ficheiro op.c tem-se como objetivo a implementação de operações matemáticas. Operações como: soma, subtração, multiplicação, divisão, entre outras.
 *
 */

#include <stdio.h>
#include "stack.h"
#include "op.h"

/**
* Desenvolvemos diferentes macros para os diferentes casos, tendo em consideração o seu tipo de dados.
*/

/**
 * \brief Macro responsável pelas operações binárias como and, or, xor e mod
 *
 * Esta macro vai receber : 
 * @param function Nome da função que será usada
 * @param op operação a efetuar
 *
 * Para operações como and, or, xor e mod apenas trabalhamos com variaveís do tipo long.
 *
 */
#define CASE_BIN(function, op)        \
    void function(Stack* s) {         \
        long X = pop_LONG(s);         \
        long Y = pop_LONG(s);         \
        push_LONG(s, op(Y,X));        \
    }                                 \

CASE_BIN(and_operation,  AND)
CASE_BIN(or_operation, OR)
CASE_BIN(xor_operation, XOR)
CASE_BIN(mod_operation, MOD)                                                   

/**
 * \brief Macro responsável pelas operações com apenas um elemento como incrementar e decrementar
 * @param function Nome da função que será usada
 * @param op operação a efetuar
 *
 * Para operações com apenas uma variavel pode ser long ou double.
 */
#define CASE_SOLO(function, op)            \
    void function(int x, Stack* s){        \
        if (x == 1) {                      \
                                           \
                long X = pop_LONG(s);      \
                push_LONG(s, op(X));       \
                                           \
        }                                  \
        else if (x == 2) {                 \
                double X = pop_DOUBLE(s);  \
                push_DOUBLE(s,op(X));      \
                                           \
        }                                  \
        else if (x == 3) {                 \
            char X = pop_CHAR(s);          \
            push_CHAR(s,op(X));            \
        }                                  \
    }                                      \

CASE_SOLO(dec_operation, --)   
CASE_SOLO(inc_operation, ++)  


/**
 * \brief Macro responsável pelas operações que recebem dois elementos como soma, subtração, divisão, multiplicação e potência.
 * Para operações como +, -, *, / e ^ trabalhamos com variaveís do tipo long e double.
 * Para esta macro tivemos de ter em conta o caso em que as duas variaveis não fazerem parte do mesmo tipo de variavel.
 *
 * @param function Nome da função que será usada
 * @param op operação a efetuar
 * 
*/
#define CASE_OP(function, op)                                   \
    void function(int x, Stack* s) {                            \
        if (x == 1)    {                                        \
                long X = pop_LONG(s);                           \
                int y = idtype(s);                              \
                if (y == 1) {                                   \
                                                                \
                    long Y = pop_LONG(s);                       \
                    push_LONG(s, op(Y,X));                      \
                }                                               \
                else if (y == 2) {                              \
                    push_LONG(s,X);                             \
                    double_conversion(s);                       \
                    double Z = pop_DOUBLE(s);                   \
                    double Y = pop_DOUBLE(s);                   \
                                                                \
                    push_DOUBLE(s, op(Y,Z));                    \
                }                                               \
                                                                \
        }                                                       \
            else {                                              \
                double X = pop_DOUBLE(s);                       \
                int y = idtype(s);                              \
                if (y == 1) {                                   \
                    double_conversion(s);                       \
                    double Y = pop_DOUBLE(s);                   \
                    push_DOUBLE(s, op(Y,X));                    \
                }                                               \
                else if (y == 2) {                              \
                    double Y = pop_DOUBLE(s);                   \
                    push_DOUBLE(s, op(Y,X));                    \
                }                                               \
                                                                \
            }                                                   \
    }                                                           \
                                                           
CASE_OP(add_operation, ADD)      
CASE_OP(sub_operation, SUB)      
CASE_OP(mult_operation, MULT)    
CASE_OP(div_operation, DIV)      
CASE_OP(pow_operation, pow)  

/**
 * \brief Função para trocar os últimos dois elementos da stack
 * 
 * @param s Recebe apontador para a Stack
 */
void SWAP(Stack* s) {
    DATA x,y;
    x = s->elements[s->sp];        ///< Elemento do topo da stack
    y = s->elements[s->sp - 1];    ///< Elemento anterior 
    s->elements[s->sp] = y;        ///< y passa a estar no topo da stack
    s->elements[s->sp - 1] = x;    ///< x passa estar na posição antiga de y
}

/**
 * \brief Função para trocar os três últimos elementos da stack
 * 
 * @param s Recebe apontador para a Stack
 */
void ROTATE(Stack* s) {
    DATA x,y,z;
    x = s->elements[s->sp];         ///< x é o elemento do topo da stack
    y = s->elements[s->sp - 1];     ///< y é o elemento abaixo de x
    z = s->elements[s->sp - 2];     ///< z é o elemento abaixo de y
    s->elements[s->sp] = z;         ///< O topo da stack agora possui o elemento z
    s->elements[s->sp - 1] = x;     ///< O endereço onde havia o y guardado passa a guardar o elemento x
    s->elements[s->sp - 2] = y;     ///< O endereço onde havia o z guardado passa a guardar o elemento y

}

/**
 * \brief Função que atribui valor a uma letra
 * 
 * @param s apontador para a Stack
 * @param c char recebido
 * @param v apontador para uma struct DATA
 */
void var_top (Stack* s, char c, DATA *v) {
    v[c-65] = top(s); ///< o elemento que ocupa a posição c-65 tomará o valor do topo da stack. Por exemplo, para A, o código ASCII é 65 e portanto v[0] = topo da stack
    
}

/**
 * \brief Macro responsável pelas operações lógicas como =, <, >
 * Para operações =, < e > trabalhamos com variaveís do tipo long e double.
 * Para esta macro, assim com a macro CASE_OP, tivemos de ter em conta o caso em que as duas variaveis não pertencem ao mesmo tipo.
 *
 * @param function Nome da função que será usada
 * @param op operação a efetuar
 */
#define LOGIC_BIN(function, op)             \
    void function(Stack* s) {               \
        double_conversion(s);               \
        double X = pop_DOUBLE(s);           \
        double_conversion(s);               \
        double Y = pop_DOUBLE(s);           \
        if (op(X,Y)) push_LONG(s,1);        \
        else push_LONG(s,0);                \
    }                                       \

LOGIC_BIN(equal_logic, EQUAL)
LOGIC_BIN(greater_logic, GREATER)
LOGIC_BIN(less_logic, LESS)

/**
 * \brief Função responsável pela operação lógica "!"
 * @param s Apontador para a Stack
 */
void logic_not(Stack* s) {
    double_conversion(s);
    double X = pop_DOUBLE(s);
    if (X == 0) push_LONG(s,1);
    else push_LONG(s,0);
}

/**
 * \brief Função responsável pela operação lógica "?"
 * @param s Apontador para a Stack
 */
void if_then_else(Stack* s) {
    DATA x,y,z;
    x = pop(s);
    y = pop(s);
    z = pop(s);
    if (z.x.LONG != 0) push(s,y);
    else push(s,x);
}

/**
 * \brief Macro responsável pelas operações lógicas e(Operação)
 * @param function Nome final de cada função
 * @param op Operação a ser utilizada
 * @param v Inteiro para controlo do push. Caso seja 2 significa que é uma operação e< ou e> portanto o push é de elementos da stack. Caso seja 0 é um e&.
 */
#define LOGIC_BIN_E(function, op, v)                                               \
    void function(Stack* s) {                                                      \
        int x = idtype(s);                                                         \
        double_conversion(s);                                                      \
        double X = pop_DOUBLE(s);                                                  \
        int y = idtype(s);                                                         \
        double_conversion(s);                                                      \
        double Y = pop_DOUBLE(s);                                                  \
        if (op(X,Y)) {                                                             \
            switch(x) {                                                            \
                case (1): push_DOUBLE(s, X); long_conversion(s); break;            \
                case (2): push_DOUBLE(s,X); break;                                 \
                case (3): push_DOUBLE(s,X); char_conversion(s); break;             \
            }                                                                      \
        }                                                                          \
        else {                                                                     \
            if (v == 2) {                                                          \
                switch(y) {                                                        \
                    case (1): push_DOUBLE(s,Y); long_conversion(s); break;         \
                    case (2): push_DOUBLE(s,Y); break;                             \
                    case (3): push_DOUBLE(s,Y); char_conversion(s); break;         \
                }                                                                  \
            }                                                                      \
            else push_LONG(s,v);                                                   \
        }                                                                          \
    }                                                                              \

LOGIC_BIN_E(greater_elogic, EGREATER, 2)
LOGIC_BIN_E(less_elogic, ELESS, 2)
LOGIC_BIN_E(and_elogic, EIF, 0)


/**
 * \brief Função responsável pela operação de lógica quando há apenas e. Caso tenha 1 x e, faz push de 1, caso tenha 0 x e faz push de x.
 * @param s Apontador para a Stack
 */
void logic_e_null(Stack* s) {
    long X = pop_LONG(s);
    long Y = pop_LONG(s);

    if (Y == 0) push_LONG(s,X);
    else push_LONG(s,Y);
}

/**
 * \brief Função responsável pela operação de lógica e| : Se algum valor for diferente de 0, retorna o maior entre eles
 * @param s Apontador para a Stack
 */
void eor_logic(Stack* s) {                                                          
        int x = idtype(s);                                                         
        double_conversion(s);                                                      
        double X = pop_DOUBLE(s);                                                  
        int y = idtype(s);                                                         
        double_conversion(s);                                                      
        double Y = pop_DOUBLE(s);                                                  
                                                      
        if (X != 0 || Y != 0) {   ///< apenas um precisa ser diferente de 0
            if (X > Y) {          ///< caso X > Y, adiciona à stack o X                                
                switch(x) {       ///< Verificar tipo de X para adicionar à stack corretamente                   
                    case (1): push_DOUBLE(s,X); long_conversion(s); break;            
                    case (2): push_DOUBLE(s,X); break;                                 
                    case (3): push_DOUBLE(s,X); char_conversion(s); break;             
                }                                                                      
            }
            else {  ///< caso X < Y, adiciona à stack o X 
                switch(y) {    ///< Verificar tipo de Y para adicionar à stack corretamente                                                     
                    case (1): push_DOUBLE(s,Y); long_conversion(s); break;            
                    case (2): push_DOUBLE(s,Y); break;                                 
                    case (3): push_DOUBLE(s,Y); char_conversion(s); break;             
                }  
            }       
        }
        else push_LONG(s,1);
} 



/**
 * \brief Função responsável por detetar as operações lógicas e aplicar suas respetivas funções
 * @param c Apontador para o array token
 * @param s Apontador para a Stack
 */
void logic_e(char* c, Stack* s) {
    char x = c[1];

    switch(x) {
        case '&': and_elogic(s); break; 
        case '|': eor_logic(s); break; 
        case '>': greater_elogic(s); break;
        case '<': less_elogic(s); break;
        default:  logic_e_null(s); break;
    }
}

                                                                    
