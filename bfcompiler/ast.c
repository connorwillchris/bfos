#include "lib.h"

int compileFile(char * string, int fileSize) {
	// allocate 4096 bytes of space to start out. We can expand as needed.
	int currentBufferSize = 4096;
	
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
				// if the buffer is full, realloc it to be biffer
				if (bufferIndex >= currentBufferSize) {
					currentBufferSize += BUFFER_SIZE;
					buffer = (char *)realloc(buffer, currentBufferSize);
				}

				// add the char to the buffer
				buffer[bufferIndex++] = string[i];
				break;
			default:
				//continue;
				break;
		}
	}

	// now that we have a buffer, we can start compiling the code


	// get rid of buffer so we don't get a mem leak
	free(buffer);
	return 0;
}
