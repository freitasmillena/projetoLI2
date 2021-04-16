

void SWAP(Stack* s) {
    DATA x,y;
    x = s->elements[s->sp];
    y = s->elements[s->sp - 1];
    s->elements[s->sp] = y;
    s->elements[s->sp - 1] = x;
}

void ROTATE(Stack* s) {
    DATA x,y,z;
    x = s->elements[s->sp];
    y = s->elements[s->sp - 1];
    z = s->elements[s->sp - 2];
    s->elements[s->sp] = z;
    s->elements[s->sp - 1] = x;
    s->elements[s->sp - 2] = y;

}

#define ADD(x,y) x + y
#define SUB(x,y) x - y
#define MULT(x,y) x * y
#define DIV(x,y) x / y
#define DEC(x) x--
#define INC(x) x++
#define MOD(x,y) x % y
#define AND(x,y) x & y
#define OR(x,y) x | y
#define XOR(x,y) x ^ y
#define NOT(x) ~x



#define CASE_BIN(op)                                        \
                                                            \
    if (x == 1) {                                           \
                                                            \
                                                            \
            int y = idtype(s);                              \
            if (y == 1) {                                   \
                long X = pop_LONG(s);                       \
                long Y = pop_LONG(s);                       \
                push_LONG(s, op(Y,X));                      \
            }                                               \
    }                                                       \
                                                          


#define CASE_SOLO(op)                  \
                                       \
    if (x == 1) {                      \
                                       \
            long X = pop_LONG(s);      \
            push_LONG(s, op X);        \
                                       \
    }                                  \
    else if (x == 2) {                 \
            double X = pop_DOUBLE(s);  \
            push_DOUBLE(s,op X);       \
                                       \
    }                                  \
                                      



#define CASE_OP(op)                                         \
                                                            \
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
                                                           



