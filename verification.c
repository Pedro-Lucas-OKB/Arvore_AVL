#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "verification.h"


// Recebe uma arvore e calcula a altura de cada nó da mesma
int calculateHeight(Node *p) {
    if(p == NULL) return 0;
    int h1, h2;

    if(p -> left != NULL) {
        h1 = calculateHeight(p -> left);
    }else h1  = 0;

    if(p -> right != NULL) {
        h2 = calculateHeight(p -> right);
    }else h2  = 0;

    p -> height = (max(h1, h2) + 1); // Soma "+1" por causa do no atual da recursão
    return p -> height;
}

// Retorna o maior entre dois valores (inteiros)
int max(int a, int b) {
    if(a > b) {
        return a;
    }else return b;
}

/*
    Verifica se uma arvore é AVL, atraves das propriedades de balanço de cada nó.
    *result entra com valor 1.
    Caso (*result) saia como:
    1: Então é AVL
    0: NÃO é AVL
*/
void verifyAVL(Node *p, int *result) {
    if(p == NULL) return;
    int balance = (calculateHeight(p -> right) - calculateHeight(p -> left));
    if(balance > 1 || balance < -1) {
        *result = 0;
    }
    verifyAVL(p -> left, result);
    verifyAVL(p -> right, result);
}

// Conta a quantidade de nós de uma arvore
int countNodes(Node *p) {
    int count;
    if(p == NULL) {
        return 0;
    }else {
        count = countNodes(p -> left);
        count += countNodes(p -> right);
        count++; // por causa do no atual
    }
    return count;
}

// Atualiza a altura de uma arvore
void updateHeight(Node *tree) {
    if(tree == NULL) return;
    tree -> height = calculateHeight(tree);
}