#ifndef BTREE_H_INCLUDED
#define BTREE_H_INCLUDED

#define MAX_KEYS 3
#define MIN_KEYS 1
#define MAX_CHILDREN (MAX_KEYS + 1)

typedef struct Product
{
    int bcode;
    int quantity;
} Product;

void printProduct(Product prd);

// ---------------------------------------------------------
// B-Tree Node
// ---------------------------------------------------------
typedef struct BTreeNode
{
    Product keys[MAX_KEYS];
    struct BTreeNode* children[MAX_CHILDREN];
    int numKeys;
    int isLeaf;
} BTreeNode;

BTreeNode *createNode(int isLeaf);
BTreeNode *search(BTreeNode *root, Product key);
void searchKey(BTreeNode *root, Product key);
void splitChild(BTreeNode *parent, int index, BTreeNode *child);
void insertNonFull(BTreeNode *node, Product key);
void insert(BTreeNode **root, Product key);
int findKey(BTreeNode *root, Product key, BTreeNode **resultNode, int *index);
int isValidUpdate(BTreeNode *node, int index, Product newKey);
void update(BTreeNode *root, Product oldKey, Product newKey);
void traverse(BTreeNode *root);

#endif // BTREE_H_INCLUDED
