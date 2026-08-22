#include "library.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Initially, the BST is empty
struct Node *root = NULL;

// Function to populate and return a Book struct
Book populateBook(int id, const char *title, const char *author, int pubYr, const char *category) {
    Book b;
    b.id = id;

    strncpy(b.title, title, sizeof(b.title) - 1);
    b.title[sizeof(b.title) - 1] = '\0';

    strncpy(b.author, author, sizeof(b.author) - 1);
    b.author[sizeof(b.author) - 1] = '\0';

    b.pubYr = pubYr;

    strncpy(b.category, category, sizeof(b.category) - 1);
    b.category[sizeof(b.category) - 1] = '\0';
    return b;
}

void PrintBook(Book book)
{
    printf("Book Details:\n");
    printf("\t ID: %d\n", book.id);
    printf("\t Title: %s\n", book.title);
    printf("\t Author: %s\n", book.author);
    printf("\t Publication Year: %d\n", book.pubYr);
    printf("\t Category: %s\n", book.category);
}

void ADD_BOOK()
{
    printf("Enter the Book ID: ");
    int id;
    scanf("%d", &id);
    printf("Enter the Book title: ");
    char title[50];
    scanf("%s", title);
    char author[50];
    printf("Enter the Book Author: ");
    scanf("%s", author);
    int pubYr;
    printf("Enter the publication year: ");
    scanf("%d", &pubYr);
    char category[50];
    printf("Enter the Book Category: ");
    scanf("%s", category);

    Book b = populateBook(id, title, author, pubYr, category);
    root = insertNode(root, b);
    printf("Book added successfully\n");
}

void SEARCH_BOOK(int id)
{
    struct Node *node = searchNode(root, id);

    if (node == NULL)
    {
        printf("Book ID: %d not found in the BST.\n", id);
        return;
    }
    PrintBook(node->key);
}

void DELETE_BOOK(int id)
{
    root = deleteNode(root, id);
}

void DISPLAY_INORDER()
{
    inOrder(root);
}

void FIND_MIN()
{
    struct Node *node = findMin(root);
    if (node == NULL)
    {
        printf("Tree is empty. No minimum book.\n");
        return;
    }
    PrintBook(node->key);
}

void FIND_MAX()
{
    struct Node *node = findMax(root);
    if (node == NULL)
    {
        printf("Tree is empty. No maximum book.\n");
        return;
    }
    PrintBook(node->key);
}

void FIND_PREDECESSOR(int id)
{
    for (struct Node *current = root; current != NULL;)
    {
        if (id < current->key.id)
        {
            current = current->left;
        }
        else if (id > current->key.id)
        {
            current = current->right;
        }
        else
        {
            struct Node *predecessor = findMax(current->left);
            if (predecessor != NULL)
            {
                PrintBook(predecessor->key);
            }
            else
            {
                printf("No predecessor found for Book ID: %d\n", id);
            }
            return;
        }
    }
    printf("Book ID: %d not found in the BST.\n", id);
}

void FIND_SUCCESSOR(int id)
{
    for (struct Node *current = root; current != NULL;)
    {
        if (id < current->key.id)
        {
            current = current->left;
        }
        else if (id > current->key.id)
        {
            current = current->right;
        }
        else
        {
            struct Node *successor = findMin(current->right);
            if (successor != NULL)
            {
                PrintBook(successor->key);
            }
            else
            {
                printf("No successor found for Book ID: %d\n", id);
            }
            return;
        }
    }
    printf("Book ID: %d not found in the BST.\n", id);
}

void DISPLAY_PREORDER()
{
    preOrder(root);
}

void DISPLAY_POSTORDER()
{
    postOrder(root);
}
