#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef enum
{
    NODE_INCREMENT,
    NODE_DECREMENT,
    NODE_MOVE_LEFT,
    NODE_MOVE_RIGHT,
    NODE_LOOP_L,
    NODE_LOOP_R,
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

ASTNode *createNode(NodeType type);
void freeAST(ASTNode *root);

ASTNode *parseTokens(NodeType *tokens, size_t length);

void printNodes(ASTNode *root, int indent);

void parseNodes(ASTNode * root);

#endif // AST_H
