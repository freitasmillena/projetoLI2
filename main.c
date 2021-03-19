#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

int main() {
    char line[10240]; 

    assert(fgets(line, 10240, stdin) != NULL);
    assert(line[strlen(line) - 1] == '\n');

    parse(line);

    return 0;
}

