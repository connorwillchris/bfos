#ifndef LIB_H
#define LIB_H

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

typedef struct {
    char * buffer;
    size_t bufferSize;
} AST_Node;

int compileFile(char * string, int fileSize);

#endif // LIB_H
