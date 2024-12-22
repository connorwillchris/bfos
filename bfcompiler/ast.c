#include "ast.h"

size_t findMatchingLoopEnd(NodeType * tokens, int currentIndex, size_t length) {
    while (tokens[currentIndex] != ']') {
        currentIndex++;
        /*if (currentIndex >= length) {
            fprintf(stderr, "Error: Unclosed bracket ']'!\n");
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

        if (tokens[i] == '[') {
            size_t loopEnd = findMatchingLoopEnd(tokens, i, length);
            node->data.loopBody = parseTokens(&tokens[i + 1], loopEnd - i - 1);
            i = loopEnd;
        }
    }

    return root;
}

ASTNode* createNode(char type) {
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
    for (int i = 0; i < indent; i++) {
        printf("    ");
    }

    while (root) {
        for (int i = 0; i < indent; i++) {
            printf("    ");
        }

        switch (root->type) {
            case '+': printf("+\n"); break;
            case '-': printf("-\n"); break;
            case '<': printf("<\n"); break;
            case '>': printf(">\n"); break;
            case '.': printf(".\n"); break;
            case ',': printf(",\n"); break;
            case '[':
            case ']':
                printf("[\n");
                printNodes(root->data.loopBody, indent + 1);
                for (int i = 0; i < indent; i++) {
                    printf("    ");
                }
                printf("]\n");
                break;
            
            default: break;
        }
        
        root = root->next;
    }
}
