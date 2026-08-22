#include <stdio.h>
#include <stdlib.h>
#include "library.h"

void menu()
{
    printf("1. Add book\n"
    "2. Search book\n"
    "3. Borrow Book\n"
    "4. Return Book\n"
    "5. Display All books\n"
    "6. Exit\n");
}


// ---------------------------------------------------------
// Main Function
// ---------------------------------------------------------
int main()
{
    printf("Welcome to the Library Management System!\n");
    readCSV("library_dataset.csv");
    int choice = 0;
    while (choice != 6)
    {
        menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            ADD_BOOK();
            break;
        case 2:
            SEARCH_BOOK();
            break;
        case 3:
            BORROW_BOOK();
            break;
        case 4:
            RETURN_BOOK();
            break;
        case 5:
            DISPLAY_ALL_BOOKS();
            break;
        case 6:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
