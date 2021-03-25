#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stack.h"



void parse(char *line) {
    char *delims = " \t\n";
    Stack* s = create_stack();

    for(char *token = strtok(line,delims); token != NULL; token = strtok(NULL,delims)) {
        char *sobra;
        long vi = strtol(token, &sobra, 10);
        if(strlen(sobra) == 0) {
            
            push(s, vi);
            
        }
        int choice = 0;
        if (strcmp(token, "+") == 0) choice = 1;
        if (strcmp(token, "-") == 0) choice = 2;
        if (strcmp(token, "*") == 0) choice = 3;
        if (strcmp(token, "/") == 0) choice = 4;
        if (strcmp(token, "(") == 0) choice = 5;
        if (strcmp(token, ")") == 0) choice = 6;
        if (strcmp(token, "%") == 0) choice = 7;
        if (strcmp(token, "#") == 0) choice = 8;
        if (strcmp(token, "&") == 0) choice = 9;
        if (strcmp(token, "|") == 0) choice = 10;
        if (strcmp(token, "^") == 0) choice = 11;
        if (strcmp(token, "~") == 0) choice = 12;

        
        switch (choice) {
                case 1: {
                    long Y = pop(s);
                    long X = pop(s);
                    push(s, (X + Y));
                    break;
                }
                case 2: {
                    long Y = pop(s);
                    long X = pop(s);
                    push(s, (X - Y));
                    break;
                }
                case 3: {
                    long Y = pop(s);
                    long X = pop(s);
                    push(s, (X * Y));
                    break;
                }
                case 4: {
                    long Y = pop(s);
                    long X = pop(s);
                    push(s, (X / Y));
                    break;
                }
                case 5: {
                    long X = pop(s);
                    push(s, X-1);
                    break;
                }
                case 6: {
                    long X = pop(s);
                    push(s, X+1);
                    break;
                }
                case 7: {
                    long Y = pop(s);
                    long X = pop(s);
                    push(s, (X % Y));
                    break;
                }
                case 8: {
                    long Y = pop(s);
                    long X = pop(s);
                    push(s, (pow(X,Y)));
                    break;
                }
                case 9: {
                    long Y = pop(s);
                    long X = pop(s);
                    push(s,X&Y);
                    break;
                }
                case 10: {
                    long Y = pop(s);
                    long X = pop(s);
                    push(s,X|Y);
                    break;
                }
                case 11: {
                    long Y = pop(s);
                    long X = pop(s);
                    push(s,X^Y);
                    break;
                }
                case 12: {
                    long X = pop(s);
                    push(s,~X);
                    break;
                }
                default: 
                    break;
            }
        
    }
    
    print_stack(s);

    putchar('\n');
}


