#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "deletion.h"
#include "walk.h"

/*
    Percurso na ABB: Em Ordem
*/
void inOrder(Node *node) {
    if (node -> left != NULL) {
        inOrder (node -> left);
    }
    
    printf("|%d| ", node -> key);
    
    if (node -> right != NULL) {
        inOrder (node -> right);
    }
}

/*
    Percurso na ABB: Pré-Ordem
*/
void preOrder(Node *node) {
    printf("|%d -> balanco: %d | altura: %d", node -> key, node -> balance, node -> height);
    if(leftRightNodes(node)) {
        printf(" -> ESQUERDA: %d | DIREITA: %d ", 
        node-> left -> key, node -> right -> key);
    }
    printf("\n");

    if (node -> left != NULL) {
        preOrder(node -> left);
    }
    
    if (node -> right != NULL) {
        preOrder(node -> right);
    }
}

/*
    Percurso na ABB: Pós-Ordem
*/
void postOrder(Node *node) {
    if (node -> left != NULL) {
        postOrder(node -> left);
    }
    
    if (node -> right != NULL) {
        postOrder(node -> right);
    }

    printf("|%d| ", node -> key);
}