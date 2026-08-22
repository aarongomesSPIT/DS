#include <stdio.h> // Provides printf()
#include <stdlib.h> // Provides malloc() and free()
#include "binarySearchTree.h"
#include "library.h"
// Define a structure for a Binary Search Tree node


// Function to create a new node with a given value
struct Node *newNodeCreate(Book value)
{
    // Allocate memory dynamically for a new node
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    // Store the given value in the node
    temp->key = value;
    // Initially, the new node has no children
    temp->left = NULL;
    temp->right = NULL;
    // Return the address of the newly created node
    return temp;
}

// Function to search for a node with a specific key
struct Node *searchNode(struct Node *root, int target)
{
    // If tree is empty OR target is found at current node,
    // return the current node
    if (root == NULL || root->key.id == target)
        return root;
    // If target is greater than current node's key,
    // search in the right subtree
    if (root->key.id < target)
        return searchNode(root->right, target);
    // If target is smaller than current node's key,
    // search in the left subtree
    return searchNode(root->left, target);
}

// Function to insert a node with a specific value
struct Node *insertNode(struct Node *node, Book value)
{
    // If current position is NULL,
    // create a new node here
    if (node == NULL)
        return newNodeCreate(value);
    // If value is smaller than current node,
    // insert into the left subtree
    if (value.id < node->key.id)
        node->left = insertNode(node->left, value);
    // If value is greater than current node,
    // insert into the right subtree
    else if (value.id > node->key.id)
        node->right = insertNode(node->right, value);
    // Return the root of the tree/subtree
    return node;
}


// Function to perform Postorder Traversal
// Postorder = Left -> Right -> Root
void postOrder(struct Node *root)
{
    // Check whether the current node exists
    if (root != NULL)
    {
        // Visit the left subtree
        postOrder(root->left);
        // Visit the right subtree
        postOrder(root->right);
        // Visit the root node
        PrintBook(root->key);
    }
}

// Function to perform Inorder Traversal
// Inorder = Left -> Root -> Right
void inOrder(struct Node *root)
{
    // Check whether the current node exists
    if (root != NULL)
    {
        // Visit the left subtree
        inOrder(root->left);
        // Visit the root node
        PrintBook(root->key);
        // Visit the right subtree
        inOrder(root->right);
    }
}


// Function to perform Preorder Traversal
// Preorder = Root -> Left -> Right
void preOrder(struct Node *root)
{
    // Check whether the current node exists
    if (root != NULL)
    {
        // Visit the root node first
        PrintBook(root->key);
        // Visit the left subtree
        preOrder(root->left);
        // Visit the right subtree
        preOrder(root->right);
    }
}

// Function to find the minimum value node
struct Node *findMin(struct Node *root)
{
    // If tree is empty, return NULL
    if (root == NULL)
        return NULL;
    // If left child exists,
    // continue searching in the left subtree
    else if (root->left != NULL)
        return findMin(root->left);
    // If there is no left child,
    // current node contains the minimum value
    return root;
}

// Function to find the maximum value node
struct Node *findMax(struct Node *root){
    // If tree is empty, return NULL
    if (root == NULL)
        return NULL;
    // If right child exists,
    // continue searching in the right subtree
    else if (root->right != NULL)
        return findMax(root->right);
    // If there is no right child,
    // current node contains the maximum value
    return root;
}

// Function to delete a node from the BST
struct Node *deleteNode(struct Node *root, int x)
{
    // If tree is empty or node is not found
    if (root == NULL)
        return NULL;
    // If value to be deleted is greater than
    // current node's key,
    // search in the right subtree
    if (x > root->key.id)
        root->right = deleteNode(root->right, x);
    // If value to be deleted is smaller than
    // current node's key,
    // search in the left subtree
    else if (x < root->key.id)
        root->left = deleteNode(root->left, x);
    // If x == root->key,
    // the node to be deleted has been found
    else
    {
        // CASE 1: Node has no children
        // It is a leaf node
        if (root->left == NULL && root->right == NULL)
        {
            // Free the memory occupied by the node
            free(root);
            // Return NULL because the node is deleted
            return NULL;
        }
        // CASE 2: Node has only one child
        else if (root->left == NULL || root->right == NULL)
        {
            // Temporary pointer to store the child
            struct Node *temp;
            // If left child does not exist,
            // use the right child
            if (root->left == NULL) temp = root->right;

            // Otherwise, use the left child
            else temp = root->left;
            // Delete the current node
            free(root);
            // Return the child to take its place
            return temp;
        }
        // CASE 3: Node has two children
        else
        {
            // Find the smallest node in the right subtree
            // This is called the Inorder Successor
            struct Node *temp = findMin(root->right);
            // Copy the Inorder Successor's value
            // into the current node
            root->key = temp->key;
            // Delete the duplicate Inorder Successor
            // from the right subtree
            root->right = deleteNode(root->right, temp->key.id);
        }
    }
    // Return the root after deletion
    return root;
}
