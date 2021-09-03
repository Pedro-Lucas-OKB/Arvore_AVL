#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "deletion.h"

// Função que remove um nó da AVL
Node *deleteNode(Node **pointer, int key, int *result, Node **root) {
    int L = 1; // Esquerda
    int R = 2; // Direita
    if((*pointer) == NULL) { // Se o pt é nulo, pode ser que a cahve não se encontra na AVL ou que
        *result = false;  // a AVL está vazia.
        return NULL;
    }else {
        if(key < (*pointer) -> key) { // Se a chave é menor que a chave do pt atual, então faz busca a esquerda
            (*pointer) -> left = deleteNode(&((*pointer) -> left), key, result, root);
            balanceAdjustment(pointer, L, result);
        }else if(key > (*pointer) -> key) { // Se a chave é maior que a chave do pt atual, então faz busca a direita
            (*pointer) -> right = deleteNode(&((*pointer) -> right), key, result, root);
            balanceAdjustment(pointer, R, result);
        }else { // Senão, a chave é igual e foi encontrada
            Node *aux = (*pointer); // Ponteiro auxiliar 
            if(leftNodeOnly((*pointer))) { // Caso onde so tem nó a esquerda
                if((*pointer) == (*root)) { // Tratamento para a raiz
                    (*pointer) = (*pointer) -> left;
                    (*root) = (*pointer);
                }else {
                    (*pointer) = (*pointer) -> left;
                }
                (*result) = true;
                free(aux);
            }else if(rightNodeOnly((*pointer))) { // Caso onde so tem nó a direita
                if((*pointer) == (*root)) { // Tratamento para a raiz
                    (*pointer) = (*pointer) -> right;
                    (*root) = (*pointer);
                }else {
                    (*pointer) = (*pointer) -> right;
                }
                (*result) = true;
                free(aux);
            }else if(leftRightNodes((*pointer))) { // Caso onde tem nó a esquerda e a direita
                Node *successorNode = (*pointer) -> right;
                if(successorNode -> left == NULL) {
                    successorNode -> left = (*pointer) -> left;
                    successorNode -> balance = (*pointer) -> balance;
                    (*pointer) = successorNode;
                    (*result) = true;
                }else {
                    Node *parent;
                    // Pegando o nó mais a esquerda da subarvore direita de pt
                    while(successorNode -> left != NULL) {
                        parent = successorNode;
                        successorNode = successorNode -> left;
                    }
                    swap(pointer, &(parent -> left)); // Trocando a chave
                    (*pointer) -> right = deleteNode(&((*pointer) -> right), key, result, root); // chamando a nova remoção 
                }
                balanceAdjustment(pointer, R, result);
            }else { // Caso onde o nó é uma folha
                if((*pointer) == (*root)) { // Tratamento para a raiz
                    (*root) = NULL;
                }
                free((*pointer));
                (*result) = true;
                return NULL;
            }
        }
    }
    return (*pointer);
}

/*
    Ajusta o balanço do nó da AVL quando ele fica desbalanceado à esquerda.
    Procedimento utilizado no remover.
*/
void heavyLeftFixDelete(Node **pointer, int *result) {
    Node *auxPointerU = (*pointer) -> left;
    if(auxPointerU -> balance <= 0) { // Right rotation | Rotação simples
        // Trocando ponteiros
        (*pointer) -> left = auxPointerU -> right;
        auxPointerU -> right = (*pointer);
        (*pointer) = auxPointerU;
        
        // Atualizando balanço
        if((*pointer) -> balance == -1) {
            (*pointer) -> balance = 0;
            (*pointer) -> right -> balance = 0;
            *result = true;
        }else if((*pointer) ->  balance == 0) {
            (*pointer) -> balance = 1;
            (*pointer) -> right -> balance = -1;
            *result = false;
        }
    }else { // left-right rotation | Rotação dupla
        // Trocando ponteiros
        Node *auxPointerV = auxPointerU -> right;
        auxPointerU -> right = auxPointerV -> left;
        auxPointerV -> left = auxPointerU;
        (*pointer) -> left = auxPointerV -> right;
        auxPointerV -> right = (*pointer);
        
        // Atualizando balanço
        switch(auxPointerV -> balance) {
            case -1:
                (*pointer) -> balance = 1;
                auxPointerU -> balance = 0;
                break;
            case 0:
                (*pointer) -> balance = 0;
                auxPointerU -> balance = 0;
                break;
            case 1:
                (*pointer) -> balance = 0;
                auxPointerU -> balance = -1;
                break;
            default:
                exit(1);
        }
        (*pointer) = auxPointerV;
        (*pointer) -> balance = 0;
        *result = true;
    }
}

/*
    Ajusta o balanço do nó da AVL quando ele fica desbalanceado à direita.
    Procedimento utilizado no remover.
*/
void heavyRightFixDelete(Node **pointer, int *result) {
    Node *auxPointerU = (*pointer) -> right;
    if(auxPointerU -> balance >= 0) { // Left rotation | Rotação simples
        // Trocando ponteiros
        (*pointer) -> right = auxPointerU -> left;
        auxPointerU -> left = (*pointer);
        (*pointer) = auxPointerU;

        // Atualizando balanço
        if((*pointer) -> balance == 1) {
            (*pointer) -> balance = 0;
            (*pointer) -> left -> balance = 0;
            *result = true;
        }else{
            (*pointer) -> balance = -1;
            (*pointer) -> left -> balance = 1;
            *result = false;
        }
    }else { // Right-left rotation | Rotação dupla
        // Trocando ponteiros
        Node *auxPointerV = auxPointerU -> left;
        auxPointerU -> left = auxPointerV -> right;
        auxPointerV -> right = auxPointerU;
        (*pointer) -> right = auxPointerV -> left;
        auxPointerV -> left = (*pointer);
        
        // Atualizando balanço 
        switch(auxPointerV -> balance) {
            case -1:
                (*pointer) -> balance = 0;
                auxPointerU -> balance = 1;
                break;
            case 0:
                (*pointer) -> balance = 0;
                auxPointerU -> balance = 0;
                break;
            case 1:
                (*pointer) -> balance = -1;
                auxPointerU -> balance = 0;
                break;
            default:
                exit(1);
        }
        (*pointer) = auxPointerV;
        (*pointer) -> balance = 0;
        *result = true;
    }
}

/*  Troca o valor da chave entre dois nós da AVL.
    Utilizado na remoção de um nó.
*/
void swap(Node **p1, Node **p2) {
    int aux = (*p1) -> key;
    (*p1) -> key = (*p2) -> key;
    (*p2) -> key = aux;
}

// Função que indica se um nó da é folha ou não
int isLeaf(Node *pointer) {
    if((pointer -> left == NULL) && (pointer -> right == NULL)) {
        return 1;
    }else return 0;
}

// Função que indica se um nó da arvore possui somente "filho" a esquerda
int leftNodeOnly(Node *pointer) {
    if((pointer -> left != NULL) && (pointer -> right == NULL)) {
        return 1;
    }else return 0;
}

// Função que indica se um nó da arvore possui somente "filho" a direita
int rightNodeOnly(Node *pointer) {
    if((pointer -> left == NULL) && (pointer -> right != NULL)) {
        return 1;
    }else return 0;
}

// Função que indica se um nó da arvore possui dois "filhos"
int leftRightNodes(Node *pointer) {
    if((pointer -> left != NULL) && (pointer -> right != NULL)) {
        return 1;
    }else return 0;
}

/*
    Ajusta o balanço da AVL. É usada na remoção.
*/
void balanceAdjustment(Node **pointer, int rotation, int *result) {
    int R = 2; // Direita
    if((*result) == true) {
        if(rotation == R) {
            switch ((*pointer) -> balance) {
            case 1:
                (*pointer) -> balance = 0;
                break;
            case 0:
                (*pointer) -> balance = -1;
                *result = false;
                break;
            case -1: // Caso onde ocorre o desbalanceamento
                heavyLeftFixDelete(pointer, result);
                break;
            default:
                exit(1);
            }
        }else {
            switch ((*pointer) -> balance) {
            case -1:
                (*pointer) -> balance = 0;
                break;
            case 0:
                (*pointer) -> balance = 1;
                *result = false;
                break;
            case 1: // Caso onde ocorre o desbalanceamento
                heavyRightFixDelete(pointer, result);
                break;
            default:
                exit(1);
            }
        }
    }
}