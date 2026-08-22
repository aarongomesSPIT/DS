#ifndef BTREE_H_INCLUDED
#define BTREE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define MAX_KEYS 3
#define MIN_KEYS 1
#define MAX_CHILDREN (MAX_KEYS + 1)

typedef struct Book{
   int isbn;               // The key used for BST ordering
   char title[50];
   char author[50];
   int stock;
} Book;

void printBook(Book prd);

// ---------------------------------------------------------
// B-Tree Node
// ---------------------------------------------------------
typedef struct BTreeNode
{
    Book keys[MAX_KEYS];
    struct BTreeNode* children[MAX_CHILDREN];
    int numKeys;
    int isLeaf;
} BTreeNode;

BTreeNode *createNode(int isLeaf);
BTreeNode *search(BTreeNode *root, Book key);
void searchKey(BTreeNode *root, Book key);
void splitChild(BTreeNode *parent, int index, BTreeNode *child);
void insertNonFull(BTreeNode *node, Book key);
void insert(BTreeNode **root, Book key);
int findKey(BTreeNode *root, Book key, BTreeNode **resultNode, int *index);
int isValidUpdate(BTreeNode *node, int index, Book newKey);
void update(BTreeNode *root, Book oldKey, Book newKey);
void traverse(BTreeNode *root);

#endif // BTREE_H_INCLUDED
