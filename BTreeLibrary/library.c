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

void pushBook(int isbn, const char *title, const char *author, int stock) {
    Book newBook = populateBook(isbn, title, author, stock);
    if (no_of_books == 0)
    {
        root = createNode(1);
    }
    if (search(root, newBook) == NULL)
    {
        insert(&root, newBook);
        no_of_books++;
    }
    else
    {
        printf("Book with ISBN %d already exists. Skipping.\n", isbn);
    }
}

void ADD_BOOK()
{
    printf("Enter the Book ISBN: ");
    int isbn;
    scanf("%d", &isbn);
    printf("Enter the Book Title: ");
    char title[50];
    scanf(" %[^\n]", title);
    printf("Enter the Book Author: ");
    char author[50];
    scanf(" %[^\n]", author);
    printf("Enter the stock quantity: ");
    int stock;
    scanf("%d", &stock);

    pushBook(isbn, title, author, stock);
}

void readCSV(const char *filename)
{
    FILE *fp;
    char line[500];

    int isbn, stock;
    char title[200];
    char author[200];
    int no_of_books = 0;

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    // Skip header
    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp))
    {
        if (sscanf(line, "%d,%199[^,],%199[^,],%d",
                   &isbn, title, author, &stock) == 4)
        {
            pushBook(isbn, title, author, stock);
            no_of_books++;
        }
    }
    printf("Finished reading CSV file. Total books added: %d\n", no_of_books);
    fclose(fp);
}

void SEARCH_BOOK()
{
    printf("Enter the Book ISBN to search: ");
    int isbn;
    scanf("%d", &isbn);
    Book key;
    key.isbn = isbn;
    BTreeNode *resultNode = NULL;
    int index = -1;
    if (findKey(root, key, &resultNode, &index))
    {
        printf("Book with ISBN %d found.\n", isbn);
        printBook(resultNode->keys[index]);
    }
    else
    {
        printf("Book with ISBN %d not found.\n", isbn);
    }
}

void BORROW_BOOK()
{
    printf("Enter the book ISBN to borrow: ");
    int isbn;
    scanf("%d", &isbn);
    Book key;
    key.isbn = isbn;
    BTreeNode *resultNode = NULL;
    int index = -1;
    if (findKey(root, key, &resultNode, &index))
    {
        printf("Book with ISBN %d found.\n", isbn);
        if (resultNode->keys[index].stock > 0)
        {
            resultNode->keys[index].stock--;
            printf("Book borrowed successfully. Remaining stock: %d\n", resultNode->keys[index].stock);
        }
        else
        {
            printf("Book is out of stock.\n");
        }
        printBook(resultNode->keys[index]);
    }
    else
    {
        printf("Book with ISBN %d not found.\n", isbn);
    }
}

void RETURN_BOOK()
{
    printf("Enter the book ISBN to return: ");
    int isbn;
    scanf("%d", &isbn);
    Book key;
    key.isbn = isbn;
    BTreeNode *resultNode = NULL;
    int index = -1;
    if (findKey(root, key, &resultNode, &index))
    {
        printf("Book with ISBN %d found.\n", isbn);
        resultNode->keys[index].stock++;
        printBook(resultNode->keys[index]);
    }
    else
    {
        printf("Book with ISBN %d not found.\n", isbn);
    }
}


void DISPLAY_ALL_BOOKS()
{
    printf("Displaying all Books in the Library...\n");

    traverse(root);
}
