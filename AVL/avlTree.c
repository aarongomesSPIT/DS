// C Program to Implement AVL Tree
// AVL Tree is a self-balancing Binary Search Tree
#include <stdio.h>                   // Provides printf() and scanf()
#include <stdlib.h>                  // Provides malloc() and free()
#include "avlTree.h"

// Function to get the height of a node
int getHeight(struct Node *node)
{
    // If the node is NULL, its height is 0
    if (node == NULL)
        return 0;
    // Return the height stored in the node
    return node->height;
}

// Function to find the maximum of two numbers
int max(int a, int b)
{
    // If a is greater than b, return a
    // Otherwise, return b
    return (a > b) ? a : b;
}

// Function to create a new AVL Tree node
struct Node *createNode(Flight key)
{
    // Allocate memory dynamically for a new node
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    // Store the given key in the node
    node->key = key;
    // Initially, left child is NULL
    node->left = NULL;
    // Initially, right child is NULL
    node->right = NULL;
    // A new node is a leaf node
    // Therefore, its height is 1
    node->height = 1;
    // Return the address of the newly created node
    return node;
}

// Function to calculate the Balance Factor
int getBalanceFactor(struct Node *node)
{
    // If the node is NULL, balance factor is 0
    if (node == NULL)
        return 0;
    // Balance Factor = Height of Left Subtree - Height of Right Subtree
    return getHeight(node->left) -
           getHeight(node->right);
}

// ======================================================
// RIGHT ROTATION
// Used for LL Imbalance
// ======================================================
struct Node *rightRotate(struct Node *y)
{
    // Store the left child of y in x
    struct Node *x = y->left;
    // Store the right subtree of x temporarily
    struct Node *T2 = x->right;
    // Make y the right child of x
    x->right = y;
    // Make T2 the left child of y
    y->left = T2;
    // Update the height of y
    // Height = 1 + maximum height of its children
    y->height =
        1 + max(getHeight(y->left),
                getHeight(y->right));
    // Update the height of x
    // Height = 1 + maximum height of its children
    x->height =
        1 + max(getHeight(x->left),
                getHeight(x->right));
    // Return x because x is now the new root
    return x;
}

// ======================================================
// LEFT ROTATION
// Used for RR Imbalance
// ======================================================
struct Node *leftRotate(struct Node *x)
{
    // Store the right child of x in y
    struct Node *y = x->right;
    // Store the left subtree of y temporarily
    struct Node *T2 = y->left;
    // Make x the left child of y
    y->left = x;
    // Make T2 the right child of x
    x->right = T2;
    // Update the height of x
    // Height = 1 + maximum height of its children
    x->height =
        1 + max(getHeight(x->left),
                getHeight(x->right));
    // Update the height of y
    // Height = 1 + maximum height of its children
    y->height =
        1 + max(getHeight(y->left),
                getHeight(y->right));
    // Return y because y is now the new root
    return y;
}

// ======================================================
// INSERTION IN AVL TREE
// ======================================================
struct Node *insertNode(struct Node *node, Flight key)
{
    // --------------------------------------------------
    // STEP 1: Perform normal BST insertion
    // --------------------------------------------------
    // If the current position is NULL,
    // create a new node
    if (node == NULL)
        return createNode(key);
    // If key is smaller than current node's key,
    // insert into the left subtree
    if (key.BookingID < node->key.BookingID)
    {
        node->left = insertNode(node->left, key);
    }
    // If key is greater than current node's key,
    // insert into the right subtree
    else if (key.BookingID > node->key.BookingID)
    {
        node->right = insertNode(node->right, key);
    }
    // If key already exists,
    // do not insert duplicate value
    else
    {
        return node;
    }
    // --------------------------------------------------
    // STEP 2: Update the height of current node
    // --------------------------------------------------
    // Height =
    // 1 + maximum height of left and right subtree
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    // --------------------------------------------------
    // STEP 3: Calculate Balance Factor
    // --------------------------------------------------
    // Calculate the balance factor of current node
    int balance = getBalanceFactor(node);
    // --------------------------------------------------
    // STEP 4: Check for four rotation cases
    // --------------------------------------------------
    // ==================================================
    // CASE 1: LEFT LEFT (LL)
    // ==================================================
    // Balance factor greater than 1 means
    // the node is left-heavy
    //
    // key smaller than left child's key means
    // insertion happened in left subtree of left child
    if (balance > 1 && key.BookingID < node->left->key.BookingID)
    {
        // Perform Right Rotation
        return rightRotate(node);
    }
    // ==================================================
    // CASE 2: RIGHT RIGHT (RR)
    // ==================================================
    // Balance factor less than -1 means
    // the node is right-heavy
    //
    // key greater than right child's key means
    // insertion happened in right subtree of right child
    if (balance < -1 && key.BookingID > node->right->key.BookingID)
    {
        // Perform Left Rotation
        return leftRotate(node);
    }
    // ==================================================
    // CASE 3: LEFT RIGHT (LR)
    // ==================================================
    // Node is left-heavy
    // but insertion happened in right subtree
    // of the left child
    if (balance > 1 && key.BookingID > node->left->key.BookingID)
    {
        // First perform Left Rotation
        // on the left child
        node->left = leftRotate(node->left);
        // Then perform Right Rotation
        // on the current node
        return rightRotate(node);
    }
    // ==================================================
    // CASE 4: RIGHT LEFT (RL)
    // ==================================================
    // Node is right-heavy
    // but insertion happened in left subtree
    // of the right child
    if (balance < -1 && key.BookingID < node->right->key.BookingID)
    {
        // First perform Right Rotation
        // on the right child
        node->right = rightRotate(node->right);
        // Then perform Left Rotation
        // on the current node
        return leftRotate(node);
    }
    // If no rotation is required,
    // return the current node
    return node;
}

// ======================================================
// SEARCH OPERATION
// ======================================================
struct Node *searchNode(struct Node *root, int target)
{
    // If tree is empty OR target is found,
    // return the current node
    if (root == NULL || root->key.BookingID == target)
    {
        return root;
    }
    // If target is greater than current node,
    // search in the right subtree
    if (target > root->key.BookingID)
    {
        return searchNode(root->right, target);
    }
    // If target is smaller than current node,
    // search in the left subtree
    return searchNode(root->left, target);
}

// ======================================================
// FIND MINIMUM VALUE
// ======================================================
struct Node *findMin(struct Node *root)
{
    // If tree is empty, return NULL
    if (root == NULL)
        return NULL;
    // Keep moving to the left
    // until the leftmost node is found
    while (root->left != NULL)
    {
        // Move to the left child
        root = root->left;
    }
    // Return the leftmost node
    return root;
}

// ======================================================
// FIND MAXIMUM VALUE
// ======================================================
struct Node *findMax(struct Node *root)
{
    // If tree is empty, return NULL
    if (root == NULL)
        return NULL;
    // Keep moving to the right
    // until the rightmost node is found
    while (root->right != NULL)
    {
        // Move to the right child
        root = root->right;
    }
    // Return the rightmost node
    return root;
}

// ======================================================
// DELETE NODE FROM AVL TREE
// ======================================================
struct Node *deleteNode(struct Node *root, int key)
{
    // If tree is empty, return NULL
    if (root == NULL)
        return root;
    // --------------------------------------------------
    // STEP 1: Search for the node to be deleted
    // --------------------------------------------------
    // If key is greater than current node,
    // search in the right subtree
    if (key > root->key.BookingID)
    {
        root->right =
            deleteNode(root->right, key);
    }
    // If key is smaller than current node,
    // search in the left subtree
    else if (key < root->key.BookingID)
    {
        root->left =
            deleteNode(root->left, key);
    }
    // If key is equal to current node,
    // node has been found
    else
    {
        // ==================================================
        // CASE 1: NODE HAS NO CHILDREN
        // ==================================================
        if (root->left == NULL &&
            root->right == NULL)
        {
            // Free the memory occupied by the node
            free(root);
            // Return NULL because node is deleted
            return NULL;
        }
        // ==================================================
        // CASE 2: NODE HAS ONLY RIGHT CHILD
        // ==================================================
        else if (root->left == NULL)
        {
            // Store the right child temporarily
            struct Node *temp = root->right;
            // Delete the current node
            free(root);
            // Return the right child
            return temp;
        }
        // ==================================================
        // CASE 3: NODE HAS ONLY LEFT CHILD
        // ==================================================
        else if (root->right == NULL)
        {
            // Store the left child temporarily
            struct Node *temp = root->left;
            // Delete the current node
            free(root);
            // Return the left child
            return temp;
        }
        // ==================================================
        // CASE 4: NODE HAS TWO CHILDREN
        // ==================================================
        else
        {
            // Find the smallest node in the
            // right subtree
            //
            // This node is called Inorder Successor
            struct Node *temp =
                findMin(root->right);
            // Copy the Inorder Successor's value
            // into the node to be deleted
            root->key = temp->key;
            // Delete the duplicate Inorder Successor
            root->right =
                deleteNode(root->right,
                           temp->key.BookingID);
        }
    }
    // --------------------------------------------------
    // STEP 2: Update height after deletion
    // --------------------------------------------------
    root->height =
        1 + max(getHeight(root->left),
                getHeight(root->right));
    // --------------------------------------------------
    // STEP 3: Calculate Balance Factor
    // --------------------------------------------------
    int balance =
        getBalanceFactor(root);
    // --------------------------------------------------
    // STEP 4: Rebalance the AVL Tree
    // --------------------------------------------------
    // ==================================================
    // LL CASE AFTER DELETION
    // ==================================================
    if (balance > 1 &&
        getBalanceFactor(root->left) >= 0)
    {
        // Perform Right Rotation
        return rightRotate(root);
    }
    // ==================================================
    // LR CASE AFTER DELETION
    // ==================================================
    if (balance > 1 &&
        getBalanceFactor(root->left) < 0)
    {
        // First perform Left Rotation
        // on the left child
        root->left =
            leftRotate(root->left);
        // Then perform Right Rotation
        return rightRotate(root);
    }
    // ==================================================
    // RR CASE AFTER DELETION
    // ==================================================
    if (balance < -1 &&
        getBalanceFactor(root->right) <= 0)
    {
        // Perform Left Rotation
        return leftRotate(root);
    }
    // ==================================================
    // RL CASE AFTER DELETION
    // ==================================================
    if (balance < -1 &&
        getBalanceFactor(root->right) > 0)
    {
        // First perform Right Rotation
        // on the right child
        root->right =
            rightRotate(root->right);
        // Then perform Left Rotation
        return leftRotate(root);
    }
    // Return the balanced root
    return root;
}

// ======================================================
// INORDER TRAVERSAL
// Left -> Root -> Right
// ======================================================
void inOrder(struct Node *root)
{
    // Check whether current node exists
    if (root != NULL)
    {
        // Visit left subtree
        inOrder(root->left);
        // Visit root node
        PrintFlight(root->key);
        // Visit right subtree
        inOrder(root->right);
    }
}

// ======================================================
// PREORDER TRAVERSAL
// Root -> Left -> Right
// ======================================================
void preOrder(struct Node *root)
{
    // Check whether current node exists
    if (root != NULL)
    {
        // Visit root node first
        PrintFlight(root->key);
        // Visit left subtree
        preOrder(root->left);
        // Visit right subtree
        preOrder(root->right);
    }
}

// ======================================================
// POSTORDER TRAVERSAL
// Left -> Right -> Root
// ======================================================
void postOrder(struct Node *root)
{
    // Check whether current node exists
    if (root != NULL)
    {
        // Visit left subtree
        postOrder(root->left);
        // Visit right subtree
        postOrder(root->right);
        // Visit root node
        PrintFlight(root->key);
    }
}

// ======================================================
// DISPLAY HEIGHT AND BALANCE FACTOR
// ======================================================
void displayDetails(struct Node *root)
{
    // Check whether current node exists
    if (root != NULL)
    {
        // First visit left subtree
        displayDetails(root->left);
        // Display current node information
        PrintFlight(root->key);
        printf("Node: %d | Height: %d | Balance Factor: %d\n",
               root->key.BookingID,
               root->height,
               getBalanceFactor(root));
        // Visit right subtree
        displayDetails(root->right);
    }
}
