#ifndef BINARYSEARCHTREE_H_INCLUDED
#define BINARYSEARCHTREE_H_INCLUDED

typedef struct {
    int id;               // The key used for BST ordering
    char title[50];
    char author[50];
    int pubYr;
    char category[50];
} Book;

struct Node
{
    Book key; // Stores the value of the node
    struct Node *left; // Pointer to the left child
    struct Node *right; // Pointer to the right child
};

struct Node *newNodeCreate(Book book);
struct Node *searchNode(struct Node *root, int target);
struct Node *insertNode(struct Node *node, Book value);
void postOrder(struct Node *root);
void inOrder(struct Node *root);
void preOrder(struct Node *root);
struct Node *findMin(struct Node *root);
struct Node *findMax(struct Node *root);

struct Node *deleteNode(struct Node *root, int x);


#endif // BINARYSEARCHTREE_H_INCLUDED
