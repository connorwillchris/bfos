#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>


typedef enum {
    NODE_INCREMENT,
    NODE_DECREMENT,
    NODE_MOVE_LEFT,
    NODE_MOVE_RIGHT,
    NODE_LOOP,
    NODE_INPUT,
    NODE_OUTPUT
} NodeType;

typedef struct ASTNode {
    NodeType type;
    struct ASTNode *next;
    union {
        struct ASTNode *loopBody; // For loops
    } data;
} ASTNode;

ASTNode* createNode(char type);
void freeAST(ASTNode *root);

ASTNode * parseTokens(NodeType * tokens, size_t length);

void printNodes(ASTNode * root, int indent);

#endif // AST_H