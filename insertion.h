#include "structAVL.h"

/* FUNÇÕES */
// Adicionar 

void insertNode(int key, Node **pointer, int *result);
Node *initializeNode(int key);
void heavyLeftFixInsert(Node **pointer, int *result);
void heavyRightFixInsert(Node **pointer, int *result);