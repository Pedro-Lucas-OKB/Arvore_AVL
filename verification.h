#include "structAVL.h"

/* FUNÇÕES */
// Verificação

void verifyAVL(Node *p, int *result);
int calculateHeight(Node *p);
int countNodes(Node *p);
void updateHeight(Node *tree);
int max(int a, int b);