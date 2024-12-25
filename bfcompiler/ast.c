#include "ast.h"

size_t findMatchingLoopEnd(NodeType * tokens, int currentIndex, size_t length) {
    while (tokens[currentIndex] != NODE_LOOP_R) {
        currentIndex++;
        /*if (currentIndex >= length) {
            /fprintf(stderr, "Error: Unclosed bracket ']'!\n");
            exit(1);
        }*/
    }

    return currentIndex;
}

ASTNode * parseTokens(NodeType * tokens, size_t length) {
    ASTNode *root = NULL;
    ASTNode **current = &root;

    for (size_t i = 0; i < length; i++) {
        ASTNode *node = createNode(tokens[i]);
        *current = node;
        current = &node->next;

        if (tokens[i] == NODE_LOOP_L) {
            size_t loopEnd = findMatchingLoopEnd(tokens, i, length);
            node->data.loopBody = parseTokens(&tokens[i + 1], loopEnd - i - 1);
            i = loopEnd;
        }
        
    }

    return root;
}

ASTNode* createNode(NodeType type) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = type;
    node->next = NULL;
    if (type == '[' || type == ']') {
        node->data.loopBody = NULL;
    }
    return node;
}

void freeAST(ASTNode *root) {
    while (root) {
        ASTNode *next = root->next;
        if (root->type == '[' || root->type == ']') {
            freeAST(root->data.loopBody);
        }
        free(root);
        root = next;
    }
}

void printNodes(ASTNode * root, int indent) {
    while (root) {
        for (int i = 0; i < indent; i++) {
            printf("  ");
        }

        switch (root->type) {
            case NODE_INCREMENT:
                printf("Increment\n");
                break;
            case NODE_DECREMENT:
                printf("Decrement\n");
                break;
            case NODE_MOVE_LEFT:
                printf("Move Left\n");
                break;
            case NODE_MOVE_RIGHT:
                printf("Move Right\n");
                break;
            case NODE_INPUT:
                printf("Input\n");
                break;
            case NODE_OUTPUT:
                printf("Output\n");
                break;
            case NODE_LOOP_L:
                for (int i = 0; i < indent; i++) {
                    printf("  ");
                }
                printf("[\n");
                printNodes(root->data.loopBody, indent + 1);
                break;
            
            case NODE_LOOP_R:
                for (int i = 0; i < indent; i++) {
                    printf("  ");
                }
                printf("]\n");
                printNodes(root->data.loopBody, indent);
                break;

            default:
                break;
        }

        root = root->next;
    }
}

void parseNodes(ASTNode * root) {
    while (root) {
        switch (root->type) {
            case NODE_INCREMENT:
                printf("\tlbu t0, 0(a0)\n\taddi t0, t0, 1\n\tsb t0, 0(a0)\n");
                break;
            case NODE_DECREMENT:
                printf("\tlbu t0, 0(a0)\n\taddi t0, t0, -1\n\tsb t0, 0(a0)\n");
                break;
            case NODE_MOVE_LEFT:
                printf("\taddi a0, a0, 1\n");
                break;
            case NODE_MOVE_RIGHT:
                printf("\taddi a0, a0, -1\n");
                break;
            case NODE_INPUT:
                printf("\tcall read\n");
                break;
            case NODE_OUTPUT:
                printf("\tcall write\n");
                break;
            case NODE_LOOP_L:
                printf("\tcall L%d\nL%d:\n", 1, 1);
                //parseNodes(root->data.loopBody);
                break;
            case NODE_LOOP_R:
                printf("\tret\n");
                break;

            default:
                break;
        }
        root = root->next;
    }
}