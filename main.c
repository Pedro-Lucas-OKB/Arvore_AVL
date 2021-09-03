/*
 * Universidade Federal do Ceará 
 * Estruturas de Dados Avançadas (EDA) - 2021.1
 * Pedro Lucas da Costa Vidal 
 * Ciência da Computação
 * Árvore AVL - Implementação
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> // Apenas para representar valores booleanos
#include "testing.h"
#include "structAVL.h"

int main() {
    roots = NULL;
    srand(time(NULL));
    clock_t time;
    double totalTime;
    
    printf("\nTESTAGEM\n");
    // FASE 1
    printf("\nFASE 1: criando %d AVLs com %d nos cada.\n", QTD_AVL, QTD_NODES);
    printf("Por favor, aguarde. . .\n");
    time = clock();
    testInsertions();
    time = clock() - time;
    totalTime = (double) time/CLOCKS_PER_SEC; // Pegando o tempo em segundos
    printf("\nFASE 1 - TEMPO DE CRIACAO: %.10lf segundos\n", totalTime);
    showTrees();

    // FASE 2
    printf("\n:::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\nFASE 2: Verificando se as %d arvores sao AVL"
    " e se cada arvore possui %d nos.\n", QTD_AVL, QTD_NODES);
    printf("Por favor, aguarde. . .\n");
    time = clock(); // tempo inicial
    verifyTrees(2);
    time = clock() - time; // Pegando tempo de execucao
    totalTime = (double) time/CLOCKS_PER_SEC; // Pegando o tempo em segundos
    printf("FASE 2 - TEMPO DE EXECUCAO: %.10lf segundos\n", totalTime);
    
    // FASE 3 
    printf("\n:::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\nFASE 3: Remover %d nos de cada uma das %d arvores\n", QTD_REMOVES, QTD_AVL);
    printf("Por favor, aguarde. . .\n");
    time = clock();
    testDeletions();
    time = clock() - time;
    totalTime = (double) time/CLOCKS_PER_SEC; // Pegando o tempo em segundos
    printf("\nFASE 3 - TEMPO DE EXECUCAO DAS REMOCOES: %.10lf segundos\n", totalTime);
    showTrees();

    // FASE 4
    printf("\n:::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\nFASE 4: Verificar se, apos as remocoes, as arvores continuam sendo AVL"
    " e se cada uma possui %d nos.\n", (QTD_NODES - QTD_REMOVES));
    printf("Por favor, aguarde. . .\n");
    time = clock();
    verifyTrees(4);
    time = clock() - time;
    totalTime = (double) time/CLOCKS_PER_SEC; // Pegando o tempo em segundos
    printf("\nFASE 4 - TEMPO DE EXECUCAO: %.10lf segundos\n", totalTime);
    
    printf("\nFIM DO PROGRAMA! :D\n");
    return 0;
}
