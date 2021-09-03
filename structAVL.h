#include<stdlib.h>

#ifndef AVL_H
#define AVL_H

// Estrutura dos nós
typedef struct node{
    int key; // chave
    int balance; // balanco do no
    int height; // altura
    struct node *left;
    struct node *right;
} Node;

Node **roots; // Vetor de ponteiros para armazenar as AVLs

#endif