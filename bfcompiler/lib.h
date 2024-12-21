#ifndef LIB_H
#define LIB_H

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

typedef enum {
	NONE,
	INSTRUCTION,
	LOOP_BEGIN,
	LOOP_END,
} NodeType;

int scanFile(char * string, int fileSize);

int openFile(char * pathname);

int createAST(char * buffer, int bufferSize);

#endif // LIB_H
