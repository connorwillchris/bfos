#ifndef LIB_H
#define LIB_H

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

int scanFile(char * string, int fileSize);
int openFile(char * pathname);

#endif // LIB_H
