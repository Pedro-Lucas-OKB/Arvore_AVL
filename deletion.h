#include"structAVL.h"

/* FUNÇÕES */
// Remover

Node *deleteNode(Node **pointer, int key, int *result, Node**root);
void heavyRightFixDelete(Node **pointer, int *result);
void heavyLeftFixDelete(Node **pointer, int *result);
void balanceAdjustment(Node **pointer, int rotation, int *result);
int isLeaf(Node *pointer);
int leftRightNodes(Node *pointer);
int rightNodeOnly(Node *pointer);
int leftNodeOnly(Node *pointer);
void swap(Node **p1, Node **p2);