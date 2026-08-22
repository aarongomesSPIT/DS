#include <stdio.h>
#include <stdlib.h>
#include "library.h"

int no_of_books = 0;
BTreeNode* root;

void printBook(Book book)
{
   printf("Book Details:\n");
   printf("\t ISBN: %d\n", book.isbn);
   printf("\t Title: %s\n", book.title);
   printf("\t Author: %s\n", book.author);
   printf("\t Stock: %d\n", book.stock);
}


Book populateBook(int isbn, const char *title, const char *author, int stock) {
   Book b;
   b.isbn = isbn;

   strncpy(b.title, title, sizeof(b.title) - 1);
   b.title[sizeof(b.title) - 1] = '\0';

   strncpy(b.author, author, sizeof(b.author) - 1);
   b.author[sizeof(b.author) - 1] = '\0';

   b.stock = stock;
   return b;
}

void ADD_BOOK()
{
    printf("Enter the Book ISBN: ");
    int isbn;
    scanf("%d", &isbn);
    printf("Enter the stock quantity: ");
    int quantity;
    scanf("%d", &quantity);

    if (quantity < 0)
    {
        printf("Quantity cannot be negative.\n");
        return;
    }

    if (no_of_books == 0)
    {
        root = createNode(1);
    }

    Book newbook = populateBook(isbn, title, author, stock);
    if (search(root, key) != NULL)
    {
        printf("Book with ISBN %d already exists.\n", isbn);
        return;
    }

    insert(&root, newbook);
    no_of_books++;

}

void SEARCH_BOOK()
{
    printf("Enter the Book ISBN to search: ");
    int isbn;
    scanf("%d", &isbn);
    Book key;
    key.isbn = isbn;
    key.quantity = 0; // Not used in search
    BTreeNode* result = search(root, key);
    if (result != NULL)
    {
        printf("Book with ISBN %d found.\n", isbn);
        printBook(result->keys[0]);
    }
    else
    {
        printf("Book with ISBN %d not found.\n", isbn);
    }
}

void UPDATE_STOCK()
{
    printf("Enter the book ISBN to update: ");
    int isbn;
    scanf("%d", &isbn);
    printf("Enter the new stock quantity: ");
    int quantity;
    scanf("%d", &quantity);

    Book oldKey;
    oldKey.isbn = isbn;
    oldKey.stock = 0;

    Book newKey;
    newKey.isbn = isbn;
    newKey.stock = quantity;

    update(root, oldKey, newKey);
}



void DISPLAY_ALL_BOOKS()
{
    printf("Displaying all Books in the Library...\n");

    traverse(root);
}
