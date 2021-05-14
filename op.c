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
#include <string.h>
#include <assert.h>
#include <stdlib.h>

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

/**
 * \brief Função responsável por lidar com operações de conversão
 * @param token Apontador para o array token
 * @param s Apontador para a Stack
 */                                                                    
void handle_conversion(char *token, Stack* s) {
    
    switch(*token) {
        case 'l': {
            char l[10240]; ///< char l
            assert(fgets(l, 10240, stdin) != NULL); ///< confirmar que não é null
            push_STRING(s,l); ///< efetua operação de push para a string recebida
            break;
        }
        case 'c': char_conversion(s); break; ///< comando para converter para char
        case 'f': double_conversion(s); break; ///< comando para converter para double
        case 'i': long_conversion(s); break; ///< comando para converter para long
        case 's': string_conversion(s); break; ///< comando para converter para string
    }
    
}

/**
 * \brief Função responsável por lidar com operações matemáticas: +, -, *, /, (, ), % e #
 * @param token Apontador para o array token
 * @param x indica o tipo do elemento (long, double, char, string)
 * @param s Apontador para a Stack
 */    
void handle_math(char *token, int x, Stack* s) {
    
    switch(*token) {
        case '+': add_operation(x,s); break; ///< comando para operação de soma 
        case '-': sub_operation(x,s); break; ///< comando para operação de subtração
        case '*': mult_operation(x,s); break; ///< comando para operação de multiplicação
        case '/': div_operation(x,s); break; ///< comando para operação de divisão
        case '(': dec_operation(x,s);break; ///< comando para operação de decrementação
        case ')': inc_operation(x,s); break; ///< comando para operação de incrementação
        case '%': mod_operation(s); break; ///< comando para operação de resto da divisão ou módulo
        case '#': pow_operation(x,s); break; ///< comando para operação de potência
    }
}

/**
 * \brief Função responsável por lidar com operações binárias: &, |, ^ e ~.
 * @param token Apontador para o array token
 * @param s Apontador para a Stack
 */    
void handle_binary(char *token,Stack* s) {

    switch (*token)
    {
        case '&': and_operation(s); break; ///< comando para operação binária & (and)
        case '|': or_operation(s); break; ///< comando para operação binária | (or)
        case '^': xor_operation(s); break; ///< comando para operação binária ^ (xor)
        case '~': {long X = pop_LONG(s); push_LONG(s, ~X); break;} ///< comando para operação binária ~ (not)
        case ',': size_range(s); break;
    }
}

/**
 * \brief Função responsável por lidar com operações de lógica: =, <, >, ?, !, e.
 * @param token Apontador para o array token
 * @param s Apontador para a Stack
 */    
void handle_logic(char *token, Stack* s) {

    switch (*token)
    {
        case '=': equal_logic(s); break; ///< comando para operação lógica = (Igual) 
        case '>': greater_logic(s); break; ///< comando para operação lógica > (Maior) 
        case '<': less_logic(s); break; ///< comando para operação lógica < (Menor)
        case '?': if_then_else(s); break; ///< comando para operação lógica ? (if then else)
        case '!': logic_not(s); break; ///< comando para operação lógica ! (Não)
        case 'e': logic_e(token,s); break; ///< comando para operação lógica e<Operação>
    }
}

/**
 * \brief Função responsável por lidar com operações de manipulação da stack
 * @param token Apontador para o array token
 * @param s Apontador para a Stack
 */    
void handle_stack(char *token, Stack* s) {

    switch (*token)
    {
        case '_': push(s,top(s)); break; 
        case ';': pop(s); break; ///< comando para operação na stack (pop)
        case '\\': SWAP(s); break; ///< comando para operação na stack (Trocar os dois elementos no topo da stack)
        case '@': ROTATE(s); break; ///< comando para operação na stack (Rodar os três elementos no topo da stack)
        case '$': {long offset = pop_LONG(s); push(s, s->elements[s->sp - offset]); break;} ///< comando para operação na stack (Copiar n-ésimo elemento para o topo da stack)
    }
}

/**
 * \brief Função responsável por lidar com operações com variáveis: Letra, :<Letra>
 * @param token Apontador para o array token
 * @param s Apontador para a Stack
 * @param p array DATA por referência. Este array possui todas as letras com seus respetivos valores por omissão
 */    
void handle_variable(char *token, Stack* s, DATA *p) {
    long t = token[0];

    if(token[0] == ':') var_top(s, token[1], p); ///< caso seja comando :<Letra>               
       
    else if (t>=65 && t<=90) push(s, *(p+t-65)); ///< caso seja a variável <Letra>
}

/**
 * \brief Função responsável por lidar com push de longs e doubles
 * @param token Apontador para o array token
 * @param s Apontador para a Stack
 * @return Se r = 1, fez o push de long ou double, caso contrário não fez.
 */
int handle_push(char *token, Stack* s) {
    int r;
    char *sobra;
    char *sobrad;
    long vi = strtol(token, &sobra, 10);
    double vd = strtod(token, &sobrad);

    if(strlen(sobra) == 0) {push_LONG(s, vi); r = 1;}  
    else if(strlen(sobrad) == 0) {push_DOUBLE(s,vd); r = 1;}
    else r = 0;

    return r;
}


/**
 * \brief Função responsável por devolver interior de strings (futuramente também de arrays)
 * @param token Apontador para o array token
 * @param seps Separador, no caso de strings " e no caso de arrays [
 * @return result onde será guardado sem os separadores
 */
char *get_delimited(char *token, char *seps) {
    char *result = (char *)malloc(sizeof(char)*strlen(token));

    if(*seps == '"' || *seps == '[' ) strncpy(result, token +1, sizeof(char)*(strlen(token)-2));
    
    return result;
}


char *get_token(char *line, char **rest); 

/**
 * \brief Função responsável por concatenar strings com strings ou strings com chars
 *
 * @param s Apontador pra Stack
 */
void string_cat(Stack* s) {
    int x = idtype(s);
    char *c = malloc(100);
    
    switch(x) {
        case '3': {
            char X = pop_CHAR(s);
            int y = idtype(s);
            if (y == 4) {
                char *Y = pop_STRING(s);
                strcpy(c,Y);
                /**c = X;
                c++;
                *c = '\0';*/
                strcat(c,&X);
                //c--;
                push_STRING(s,c);
                //strcpy(t,)
                
            }
            break;

        }
        case '4': {
            char *X = pop_STRING(s);
            int y = idtype(s);
            if (y == 3) {
                char Y = pop_CHAR(s);
                strcpy(c,&Y);
                /**c = Y;
                c++;
                *c = '\0';*/
                strcat(c,X);
                //c--;
                push_STRING(s,c);
            }
            else {
                char *Y = pop_STRING(s);
                strcpy(c,Y);
                strcat(c,X);
                push_STRING(s,c);
            }
            break;
        }
    }


    
}

/**
 * \brief Função responsável por concatenar string n vezes
 * @param source String a ser concatenada
 * @param n Quantidade de vezes a concatenar 
 * @return result Onde será guardado a string após a operação
 */
char *concat_n_times(char *source, int n) {
    size_t length;
    char *result;
    int index;
    length = strlen(source);
    result = malloc(length * n + 1);
    if (!result) return NULL;
    for(index = 0; index < n; index++) {
        memcpy(result + index * length, source, length);
    }
    result[length * n] = '\0';
    return result;

}

/**
 * \brief Função responsável por devolver o índice no qual a substring ocorre na string 
 * @param string String principal
 * @param sub Substring
 * @return índice
 */
int index_sub(char *string, char *sub) {
    char *result = (char *)malloc(sizeof(char)*strlen(string));
    result = strstr(string,sub);
    return (result - string);
}

/**
 * \brief Função responsável por lidar com o operador , para strings
 * @param s Apontador para a Stack
 */
void size_range(Stack *s) {
    int x = idtype(s);
    if (x == 1) {
        long X = pop_LONG(s);
        char range[100];
        
        for(int i = 0; i < X ; ++i) {
            range[i] = i + '0'; 
        }
    
        push_STRING(s, range);
    }
    else {
        char *X = pop_STRING(s);
        push_LONG(s, strlen(X));
    }
}

/**
 * \brief Função responsável por lidar com o operador = para strings
 * @param s Apontador para a Stack
 */
void equal(Stack* s) {
    int x = idtype(s);
    if(x == 1) {
        long Y = pop_LONG(s);
        char *X = pop_STRING(s);
        
        push_CHAR(s, X[Y]);

    }
    else {
        char *X = pop_STRING(s);
        char *Y = pop_STRING(s);
        if(strcmp(X,Y) == 0) push_LONG(s,1);
        else push_LONG(s,0);
    }
}


/**
 * \brief Função responsável por lidar com o operador < para strings
 * @param s Apontador para a Stack
 */
void X_inicio(Stack* s) {
    int x = idtype(s);
    if(x == 4) {
        char *X = pop_STRING(s);
        char *Y = pop_STRING(s);
        if(strcmp(Y,X) < 0) push_LONG(s,1);
        else push_LONG(s,0);
    }
    else {
        long X = pop_LONG(s);
        char *string = pop_STRING(s);
        char *result = (char *)malloc(sizeof(char)*strlen(string));

        result = strndup(string,sizeof(char)*X);

        push_STRING(s, result);
    }

}

/**
 * \brief Função responsável por lidar com o operador > para strings
 * @param s Apontador para a Stack
 */
void X_fim(Stack* s) {
    int x = idtype(s);
    if(x == 4) {
        char *X = pop_STRING(s);
        char *Y = pop_STRING(s);
        if(strcmp(Y,X) > 0) push_LONG(s,1);
        else push_LONG(s,0);
    }
    else {
        long X = pop_LONG(s);
        char *string = pop_STRING(s);
        int length = strlen(string);
        char *result = (char *)malloc(sizeof(char)*length);
        
        int start = length - X;
        result = strndup(string + start, X);

       
        push_STRING(s, result);
    }

}

/**
 * \brief Função responsável por lidar com o operador ( para strings
 * @param s Apontador para a Stack
 */
void remove_first(Stack* s) {
    char *X = pop_STRING(s);
    char *Y = strndup(X, 1);;
    char *result = (char *)malloc(sizeof(char)*strlen(X));
    result = strdup(X+1);
    push_STRING(s,result);
    push_STRING(s,Y);
}

/**
 * \brief Função responsável por lidar com o operador ) para strings
 * @param s Apontador para a Stack
 */
void remove_last(Stack* s) {
    char *X = pop_STRING(s);
    int length = strlen(X);
    int last = length - 1;
    char *Y = strndup(X+last, 1);
    char *result = (char *)malloc(sizeof(char)*strlen(X));
    result = strndup(X, last);
    push_STRING(s,result);
    push_STRING(s,Y);
}

/**
 * \brief Função responsável por lidar com o operador e< para strings
 * @param s Apontador para a Stack
 */
void eless_string(Stack* s) {
    char *X = pop_STRING(s);
    char *Y = pop_STRING(s);
    if (strcmp(X,Y) < 0) push_STRING(s, X);
    else push_STRING(s, Y);
}

/**
 * \brief Função responsável por lidar com o operador e> para strings
 * @param s Apontador para a Stack
 */
void egreater_string(Stack* s) {
    char *X = pop_STRING(s);
    char *Y = pop_STRING(s);
    if (strcmp(X,Y) > 0) push_STRING(s, X);
    else push_STRING(s, Y);
}


/**
 * \brief Função responsável por identificar o operador junto do 'e' e proceder com sua operação
 * @param s Apontador para a Stack
 */
void elogic_string(char *token, Stack* s) {
    switch(*token) {
        case '<': eless_string(s); break;
        case '>': egreater_string(s);break;
    }
}

/**
 * \brief Função responsável por lidar com parser de strings
 * @param token Apontador para o array token
 * @param s Apontador para a Stack
 * @param rest Onde será guardado o resto da linha após o token 
 */
void handle_string(char *line, Stack* s, char **rest, DATA *p) {
    char *token;
    char seps[] = {'"', '\0'};
    for(token = get_token(line,rest); token != NULL ; token = get_token(*rest, rest)) {
       
       handle_variable(token, s, p);
       int r = handle_push(token,s); 
       if (r) continue; 
       string_op(token,s, seps);
       handle_stack(token,s);
       handle_conversion(token,s);


    }
} 

/**
 * \brief Função responsável por lidar com operações com strings
 * @param token Apontador para o array token
 * @param s Apontador para a Stack
 * 
 */
void string_op(char *token, Stack* s, char *seps) {
    switch (*token)
    {
    case '+': {
        /*string_conversion(s);
        char *X = pop_STRING(s);
        string_conversion(s);
        char *Y = pop_STRING(s);
        char *c = malloc(100);
        strcpy(c,Y);
        strcat(c,X);
        push_STRING(s, c);*/
        string_cat(s);
        break;
    }
    case '*': {
        long X = pop_LONG(s);
        char *Y = pop_STRING(s);
        push_STRING(s, concat_n_times(Y, X));
        break;

    }
    case '#': {
        char *X = pop_STRING(s);
        char *Y = pop_STRING(s);
        push_LONG(s, index_sub(Y, X));
        break;

    }
    case '=': equal(s); break;
    case ',': size_range(s); break;
    case '<': X_inicio(s); break;
    case '>': X_fim(s); break;
    case '(': remove_first(s); break;
    case ')': remove_last(s); break;
    case 'e': elogic_string(&token[1], s); break;

    case '"': push_STRING(s, get_delimited(token,seps)); break;
    default: break;
        
    
    }
}                                                                 
