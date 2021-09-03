#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "testing.h"
#include "insertion.h"
#include "deletion.h"
#include "verification.h"


// Procedimento que realiza as remocoes exigidas
void testDeletions() {
    int i;
    int count; // contador
    int resultHeight; // Variavel para o resultado de alteracao de altura
    for(i = 0; i < QTD_AVL; i++) {
        count = QTD_NODES; // contador
        resultHeight = 0; 
        // Enquanto nao ocorrerem as N remocoes, o laco continua
        while (count > (QTD_NODES - QTD_REMOVES)) {
            int key = rand() % RAND_LIMITER; // Em minha máquina, o RAND_MAX é 2^15 (32768)
            deleteNode(&(roots[i]), key, &resultHeight, &(roots[i]));
            count = countNodes(roots[i]);
        }
        // Atualizando a altura da arvore apos as remocoes
        updateHeight(roots[i]);
    }
}

// Verifica se as arvores são todas AVL
void verifyTrees(int fase) {
    int resultAVL;
    int countAVL = 0;
    int i;
    int qtd;
    // Muda dependendo da fase de teste
    if(fase == 2) {
        qtd = QTD_NODES;
    }else {
        qtd = (QTD_NODES - QTD_REMOVES);
    }
    // Laco que passa por cada arvore verificando se e AVL ou nao
    for(i = 0; i < QTD_AVL; i++) {
        resultAVL = 1; // Variavel e passada para a funcao como 1
        verifyAVL(roots[i], &resultAVL);
        int nodes = countNodes(roots[i]);
        
        if(resultAVL && (nodes == qtd) && nodes > 0) {
            countAVL++;
        }
    }
    printf("\nRESULTADO: %d arvores de um total de %d sao arvores AVL com %d nos cada\n",
    countAVL, QTD_AVL, qtd);
}

// Mostra as primeiras N arvores e suas infos
void showTrees() {
    int i;
    printf("\nPRIMEIRAS %d ARVORES\n", PRINT_LIMIT);
    for(i = 0; i < PRINT_LIMIT; i++) {
        if(roots[i] != NULL) {
            int nodes = countNodes(roots[i]); // contando os nos
            printf("Arvore %d | Quantidade de nos = %d | Altura = %d\n", i, nodes, (roots[i]) -> height);
        }else printf("Arvore %d | NULL\n", i);
    }
}

// Prepara as arvores a serem criadas
void testInsertions() {
    int resultHeight;
    int i;
    // alocando memória para as raizes
    roots = (Node**)malloc(sizeof(Node*) * QTD_AVL);
    // Inicializando cara raiz para apontar para NULL
    for (i = 0; i < QTD_AVL; i++) {
        roots[i] = NULL;
    }
    
    // Inserindo a quantidade definida de nós em cada árvore
    for(i = 0; i < QTD_AVL; i++) {
        int count = 0;
        resultHeight = 0;
        // Enquanto nao ocorrerem as N insercoes, o laco continua
        while (count < QTD_NODES) {
            int key = rand() % RAND_LIMITER; // Em minha máquina, o RAND_MAX é 2^15 (32768)
            insertNode(key, &(roots[i]), &resultHeight);
            count = countNodes(roots[i]);
        }
        // Atualizando a altura da arvore apos as inserções
        updateHeight(roots[i]);
    }
}