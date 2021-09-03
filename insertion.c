#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "insertion.h"

// Insere um novo nó na arvore
void insertNode(int key, Node **pointer, int *result) {
    if((*pointer) == NULL) {
        (*pointer) = initializeNode(key);
        (*result) = true;
        return;
    }else{
        if(key == (*pointer) -> key) { // Quando a chave já se encontra na AVL, a inserção é anulada.
            (*result) = false;
            return;
        }else if(key < (*pointer) -> key) { // Caso a chave seja menor que pt.chave, chama recursão para pt.esq
            insertNode(key, &(*pointer) -> left, result);
            if((*result) == true) {
                switch ((*pointer) -> balance) {
                case 1:
                    (*pointer) -> balance = 0;
                    (*result) = false;
                    break;
                case 0:
                    (*pointer) -> balance = -1;
                    break;
                case -1: // Caso onde é causado desbalanceamento
                    heavyLeftFixInsert(pointer, result);
                    break;
                default:
                    exit(1); // Erro
                }
            }
        }else { // Caso a chave seja maior que pt.chave, chama recursivamente para o nó direito
            insertNode(key, &(*pointer) -> right, result);
            if((*result) == true) {
                switch ((*pointer) -> balance) {
                case -1:
                    (*pointer) -> balance = 0;
                    (*result) = false;
                    break;
                case 0:
                    (*pointer) -> balance = 1;
                    break;
                case 1: // Caso onde é causado desbalanceamento
                    heavyRightFixInsert(pointer, result);
                    break;
                default:
                    exit(1);
                }
            }
        }
    }
}

/*
    Ajusta o balanço do nó da AVL quando ele fica desbalanceado à esquerda.
    Procedimento utilizado no inserir.
*/
void heavyLeftFixInsert(Node **pointer, int *result) {
    Node *auxPointerU = (*pointer) -> left;
    if(auxPointerU -> balance == -1) { // Right rotation | Rotação simples
        // Trocando ponteiros
        (*pointer) -> left = auxPointerU -> right;
        auxPointerU -> right = (*pointer);
        (*pointer) = auxPointerU;

        // Atualizando balanço
        (*pointer) -> balance = (*pointer) -> right -> balance = 0;
    }else { // left-right rotation | Rotação dupla
        // Trocando ponteiros
        Node *auxPointerV = auxPointerU -> right;
        auxPointerU -> right = auxPointerV -> left;
        auxPointerV -> left = auxPointerU;
        (*pointer) -> left = auxPointerV -> right;
        auxPointerV -> right = (*pointer);
        
        // Atualizando balanço
        if(auxPointerV -> balance == 1) {
            auxPointerU -> balance = -1;
            (*pointer) -> balance = 0;
        }else if (auxPointerV -> balance == 0) { // Caso onde o V pode ter bal 0
            (*pointer) -> balance = 0;
            auxPointerU -> balance = 0;
        }else {
            auxPointerU -> balance = 0;
            (*pointer) -> balance = 1;
        }
        (*pointer) = auxPointerV;
    }
    (*pointer) -> balance = 0;
    *result = false;
}

/*
    Ajusta o balanço do nó da AVL quando ele fica desbalanceado à direita.
    Procedimento utilizado no inserir.
*/
void heavyRightFixInsert(Node **pointer, int *result) {
    Node *auxPointerU = (*pointer) -> right;
    if(auxPointerU -> balance == 1) { // Left rotation | Rotação simples
        // Trocando ponteiros
        (*pointer) -> right = auxPointerU -> left;
        auxPointerU -> left = (*pointer);
        (*pointer) = auxPointerU;

        // Atualizando balanço
        (*pointer) -> balance = (*pointer) -> left -> balance = 0;
    }else { // Right-left rotation | Rotação dupla
        // Trocando ponteiros
        Node *auxPointerV = auxPointerU -> left;
        auxPointerU -> left = auxPointerV -> right;
        auxPointerV -> right = auxPointerU;
        (*pointer) -> right = auxPointerV -> left;
        auxPointerV -> left = (*pointer);
        
        // Atualizando balanço
        if(auxPointerV -> balance == 1) {
            (*pointer) -> balance = -1;
            auxPointerU -> balance = 0;
        }else if (auxPointerV -> balance == 0) { // Caso onde o V pode ter bal 0
            (*pointer) -> balance = 0;
            auxPointerU -> balance = 0;
        }else {
            auxPointerU -> balance = 1;
            (*pointer) -> balance = 0;
        }
        (*pointer) = auxPointerV;
    }
    (*pointer) -> balance = 0;
    *result = false;
}

/*  Função que aloca espaço para um nó e ajusta os valores de seus campos, 
    e, por fim, retorna esse nó.
    Usada na inserção.
*/
Node *initializeNode(int key) {
    Node *node = (Node*)malloc(sizeof(Node));
    if(node == NULL) {
        printf("\n ******* AVISO: ERRO NA ALOCACAO DE MEMORIA *******\n");
        exit(1); // Fechando o programa em caso de erro
    }
    node -> left = node -> right = NULL;
    node -> key = key;
    node -> height = 1; // altura inicial
    node -> balance = 0; // Balanço inicial
    return node;
}