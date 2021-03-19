#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"



void parse(char *line) {
    char *delims = " \t\n";

    for(char *token = strtok(line,delims); token != NULL; token = strtok(NULL,delims)) {
        char *sobra;
        long vi = strtol(token, &sobra, 10);

        if(strlen(sobra) == 0) {
            PUSH(vi);
            
        }

        else {
            if(strcmp(token, "+") == 0) {
                long Y = POP();
                long X = POP();
                PUSH(X + Y);
            }

        }
            

    }

}


