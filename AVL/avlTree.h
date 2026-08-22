#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED
#include "FlightReservationSystem.h" // For the Flight structure

typedef struct Node
{
	Flight key;
	struct Node *left;
	struct Node *right;
	int height;
} Node;

int getHeight(Node *node);
int max(int a, int b);
Node *createNode(Flight key);
int getBalanceFactor(Node *node);
Node *rightRotate(Node *y);
Node *leftRotate(Node *x);
Node *insertNode(Node *node, Flight key);
Node *searchNode(Node *root, int target);
Node *findMin(Node *root);
Node *findMax(Node *root);
Node *deleteNode(Node *root, int key);
void inOrder(Node *root);
void preOrder(Node *root);
void postOrder(Node *root);
void displayDetails(Node *root);


#endif // AVLTREE_H_INCLUDED
