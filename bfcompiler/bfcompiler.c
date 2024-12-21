#include <stdio.h>
#include <stdlib.h>

#include "lib.h"

int main(int argc, char ** argv) {
	// if there are 2 or more arguments
	if (argc > 1) {
		// compile all the files...
		for (int i = 1; i < argc; i++) {
			int error = openFile(argv[i]);
			
			// check if the file COULD be compiled, otherwise
			// throw an error
			if (error) {
				return error;
			}
		}
	}
	// otherwise throw an error
	else {
		fprintf(stderr, "No file arguments given!\n");
		return 1;
	}
	
	// exit with error code of success
	return 0;
}

int openFile(char * pathname) {
	FILE * file = fopen(pathname, "rb");
	
	// check if the file could be opened
	if (file == NULL) {
		fprintf(stderr, "Could not open file '%s'!\n", pathname);
		return 2;
	}
	
	fseek(file, 0L, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);
	
	// create a zero terminated buffer
	char * buffer = (char *)malloc(fileSize + 1);
	// throw an error on unable to malloc file
	if (file == NULL) {
		fprintf(stderr, "Not enough memory to read '%s'\n", pathname);
		return 3;
	}
	
	size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
	// for the final error, make sure the read doesn't fail
	if (bytesRead < fileSize) {
		fprintf(stderr, "Could not read file '%s'\n", pathname);
		return 4;
	}
	
	// if all the errors above don't happen, we can successfully compile!
	int error = scanFile(buffer, fileSize);
	if (error)
		return error;

	// free the malloced file so we don't get a memory leak!
	free(buffer);
	fclose(file);
	
	// just so we don't get an error on accident!!
	return 0;
}

int scanFile(char * string, int fileSize) {
	// allocate 4096 bytes of space to start out. We can expand
	// as needed.
	int currentBufferSize = BUFFER_SIZE;

	// create a buffer index
	size_t bufferIndex = 0;
	
	// finally, malloc a list of tokens
	char * buffer = (char *)malloc(currentBufferSize);
	
	// loop through each char in the string, looking for
	// any of the valid chars.
	for (int i = 0; i < fileSize; i++) {
		switch(string[i]) {
			case '<':
			case '>':
			case '+':
			case '-':
			case '[':
			case ']':
			case '.':
			case ',':
				// if the buffer is full, realloc it to be
				// bigger
				if (bufferIndex >= currentBufferSize) {
					currentBufferSize += BUFFER_SIZE;
					buffer = (char *)realloc(
						buffer, currentBufferSize
					);
				}
				// add the char to the buffer
				buffer[bufferIndex++] = string[i];
				break;

			default:
				break;
		}
	}

	// now that we have a buffer, we can start compiling the
	// code
	createAST(buffer, bufferIndex);

	// get rid of buffer so we don't get a mem leak
	free(buffer);
	return 0;
}
