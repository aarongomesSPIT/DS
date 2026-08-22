#include <stdio.h>
#include <stdlib.h>
#include "supermarket.h"

void menu()
{
    printf("1. Add book\n"
    "2. Search book\n"
    "3. Generate Bill\n"
    "4. Update Stock\n"
    "5. Display All books\n"
    "6. Exit\n");
}


// ---------------------------------------------------------
// Main Function
// ---------------------------------------------------------
int main()
{
    printf("Welcome to the Supermarket Management System!\n");

    int choice = 0;
    while (choice != 6)
    {
        menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            ADD_book();
            break;
        case 2:
            SEARCH_book();
            break;
        case 4:
            UPDATE_STOCK();
            break;
        case 5:
            DISPLAY_ALL_bookS();
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
