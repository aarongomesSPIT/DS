#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

// ---------------------------------------------------------
// Create a New Node
// ---------------------------------------------------------

BTreeNode *createNode(int isLeaf)
{
    BTreeNode *node =
        (BTreeNode *)malloc(sizeof(BTreeNode));
    node->isLeaf = isLeaf;
    node->numKeys = 0;
    // Initialize child pointers
    for (int i = 0; i < MAX_CHILDREN; i++)
    {
        node->children[i] = NULL;
    }
    return node;
}

// ---------------------------------------------------------
// Search
//
// Returns the node containing the key.
// Returns NULL if the key is not present.
// ---------------------------------------------------------
BTreeNode *search(BTreeNode *root, Book key)
{
    if (root == NULL)
        return NULL;
    int i = 0;
    // Find the first key greater than or equal to key
    while (i < root->numKeys &&
           key.isbn > root->keys[i].isbn)
    {
        i++;
    }
    // Key found
    if (i < root->numKeys &&
        key.isbn == root->keys[i].isbn)
    {
        return root;
    }
    // Key not found and current node is a leaf
    if (root->isLeaf)
    {
        return NULL;
    }
    // Search in the appropriate child
    return search(root->children[i], key);
}

// ---------------------------------------------------------
// Display Search Result
// ---------------------------------------------------------
void searchKey(BTreeNode *root, Book key)
{
    BTreeNode *result = search(root, key);
    if (result != NULL)
    {
        printf("\nKey %d found in the B-Tree.\n", key.isbn);
    }
    else
    {
        printf("\nKey %d not found in the B-Tree.\n", key.isbn);
    }
}

// ---------------------------------------------------------
// Split a Full Child
//
// Example:
//
// Before splitting:
//
// [10 | 20 | 30 | 40]
//
// The middle key 20 is promoted.
//
// [20]
//    (tree split)
// [10] [30 | 40]
//
// ---------------------------------------------------------
void splitChild(BTreeNode *parent,
                int index,
                BTreeNode *child)
{
    BTreeNode *newChild =
        createNode(child->isLeaf);
    // Number of keys moved to the new child
    newChild->numKeys = MIN_KEYS;
    // Copy keys to the right child
    for (int i = 0; i < MIN_KEYS; i++)
    {
        newChild->keys[i] =
            child->keys[i + MIN_KEYS + 1];
    }
    // Copy children if the node is not a leaf
    if (!child->isLeaf)
    {
        for (int i = 0; i < MIN_KEYS + 1; i++)
        {
            newChild->children[i] =
                child->children[i + MIN_KEYS + 1];
        }
    }
    // Reduce the number of keys in left child
    child->numKeys = MIN_KEYS;
    // Shift parent's children
    for (int i = parent->numKeys;
         i >= index + 1;
         i--)
    {
        parent->children[i + 1] =
            parent->children[i];
    }
    // Attach new right child
    parent->children[index + 1] = newChild;
    // Shift parent's keys
    for (int i = parent->numKeys - 1;
         i >= index;
         i--)
    {
        parent->keys[i + 1] =
            parent->keys[i];
    }
    // Promote middle key to parent
    parent->keys[index] =
        child->keys[MIN_KEYS];
    parent->numKeys++;
}

// ---------------------------------------------------------
// Insert into a Non-Full Node
// ---------------------------------------------------------
void insertNonFull(BTreeNode *node, Book key)
{
    int i = node->numKeys - 1;
    // -----------------------------------------------------
    // Case 1: Node is a leaf
    // -----------------------------------------------------
    if (node->isLeaf)
    {
        // Shift larger keys to the right
        while (i >= 0 &&
               node->keys[i].isbn > key.isbn)
        {
            node->keys[i + 1].isbn =
                node->keys[i].isbn;
            i--;
        }
        // Insert key
        node->keys[i + 1] = key;
        node->numKeys++;
    }
    // -----------------------------------------------------
    // Case 2: Node is an internal node
    // -----------------------------------------------------
    else
    {
        // Find the correct child
        while (i >= 0 &&
               node->keys[i].isbn > key.isbn)
        {
            i--;
        }
        i++;
        // Split child if it is full
        if (node->children[i]->numKeys == MAX_KEYS)
        {
            splitChild(node,
                       i,
                       node->children[i]);
            // Decide which child to follow
            if (key.isbn > node->keys[i].isbn)
            {
                i++;
            }
        }
        // Continue insertion
        insertNonFull(node->children[i], key);
    }
}
// ---------------------------------------------------------
// Insert
//
// Handles insertion and root splitting.
// ---------------------------------------------------------
void insert(BTreeNode **root, Book key)
{
    BTreeNode *r = *root;
    // -----------------------------------------------------
    // If root is full, create a new root
    // -----------------------------------------------------
    if (r->numKeys == MAX_KEYS)
    {
        BTreeNode *newRoot =
            createNode(0);
        newRoot->children[0] = r;
        // Split old root
        splitChild(newRoot, 0, r);
        int i = 0;
        // Decide correct child
        if (newRoot->keys[0].isbn < key.isbn)
        {
            i++;
        }
        insertNonFull(newRoot->children[i], key);
        // Update root
        *root = newRoot;
    }
    // -----------------------------------------------------
    // Root is not full
    // -----------------------------------------------------
    else
    {
        insertNonFull(r, key);
    }
}
// ---------------------------------------------------------
// Find Node and Index of a Key
//
// Used by the update operation.
//
// Returns 1 if found.
// Returns 0 if not found.
//
// index stores the position of the key.
// ---------------------------------------------------------
int findKey(BTreeNode *root,
            Book key,
            BTreeNode **resultNode,
            int *index)
{
    if (root == NULL)
        return 0;
    int i = 0;
    // Find possible position of key
    while (i < root->numKeys &&
           key.isbn > root->keys[i].isbn)
    {
        i++;
    }
    // Key found
    if (i < root->numKeys &&
        key.isbn == root->keys[i].isbn)
    {
        *resultNode = root;
        *index = i;
        return 1;
    }
    // Cannot find key further
    if (root->isLeaf)
        return 0;
    // Search appropriate child
    return findKey(root->children[i],
                   key,
                   resultNode,
                   index);
}
// ---------------------------------------------------------
// Check Whether New Key is Valid for Update
//
// The new key must remain between the keys immediately
// before and after the old key in the same node.
//
// This prevents the B-Tree ordering from being broken.
//
// ---------------------------------------------------------
int isValidUpdate(BTreeNode *node,
                  int index,
                  Book newKey)
{
    // Check previous key
    if (index > 0 &&
        newKey.isbn <= node->keys[index - 1].isbn)
    {
        return 0;
    }
    // Check next key
    if (index < node->numKeys - 1 &&
        newKey.isbn >= node->keys[index + 1].isbn)
    {
        return 0;
    }
    return 1;
}
// ---------------------------------------------------------
// Update
//
// Changes an existing key to a new key.
//
// Example:
//
// [10 | 20 | 30]
//
// Update 20 -> 25
//
// Result:
//
// [10 | 25 | 30]
//
// The update is allowed only if the B-Tree ordering
// remains valid.
// ---------------------------------------------------------
void update(BTreeNode *root,
            Book oldKey,
            Book newKey)
{
    BTreeNode *node = NULL;
    int index = -1;
    // Find old key
    if (!findKey(root,
                 oldKey,
                 &node,
                 &index))
    {
        printf("\nKey %d not found.\n",
               oldKey.isbn);
        return;
    }

    // Stock-only update: keep the same ISBN and change only the stock amount.
    if (oldKey.isbn == newKey.isbn)
    {
        node->keys[index].stock = newKey.stock;
        printf("\nStock updated successfully.\n");
        return;
    }

    // Check if new key already exists
    if (search(root, newKey) != NULL)
    {
        printf("\nKey %d already exists.\n",
               newKey.isbn);
        return;
    }
    // Check whether update maintains ordering
    if (!isValidUpdate(node,
                       index,
                       newKey))
    {
        printf("\nUpdate cannot be performed.\n");
        printf("New key would violate B-Tree ordering.\n");
        return;
    }
    // Perform update
    node->keys[index] = newKey;
    printf("\nKey updated successfully.\n");
}

// ---------------------------------------------------------
// Traverse B-Tree
//
// In-order traversal displays keys in sorted order.
// ---------------------------------------------------------
void traverse(BTreeNode *root)
{
    if (root == NULL)
        return;
    int i;
    for (i = 0;
         i < root->numKeys;
         i++)
    {
        // Visit left child
        if (!root->isLeaf)
        {
            traverse(root->children[i]);
        }
        // Visit current key
        printBook(root->keys[i]);
    }
    // Visit last child
    if (!root->isLeaf)
    {
        traverse(root->children[i]);
    }
}
