#include <stdio.h>
#include <stdlib.h>
#include "binarySearchTree.h"
#include "library.h"

void menu()
{
    printf("----Smart Library Book Locator----\n");
    printf("1. Add a book.\n");
    printf("2. Search book by ID.\n");
    printf("3. Delete a book by ID.\n");
    printf("4. Display books in Ascending order of Book ID.\n");
    printf("5. Display the smallest Book ID.\n");
    printf("6. Display the largest Book ID.\n");
    printf("7. Find the immediately smaller Book ID for a given Book ID.\n");
    printf("8. Find the immediately larger Book ID for a given Book ID.\n");
    printf("9. Display the BST hierarchy using Preorder Traversal.\n");
    printf("10. Display the BST hierarchy using Postorder Traversal.\n");
    printf("11. Exit the program.\n");
    printf("Enter your choice: ");
}

// Main Function
int main()
{
    int choice = 0;

    while(choice != 11)
    {
        menu();
        scanf("%d", &choice);
        int id;
        switch(choice)
        {
            case 1:
                ADD_BOOK();
                break;
            case 2:
                {
                    printf("Enter the Book ID to search: ");
                    scanf("%d", &id);
                    SEARCH_BOOK(id);
                }
                break;
            case 3:
                {
                    printf("Enter the Book ID to delete: ");
                    scanf("%d", &id);
                    DELETE_BOOK(id);
                }
                break;
            case 4:
                DISPLAY_INORDER();
                break;
            case 5:
                FIND_MIN();
                break;
            case 6:
                FIND_MAX();
                break;
            case 7:
                printf("Enter the Book ID to find predecessor: ");
                scanf("%d", &id);
                FIND_PREDECESSOR(id);
                break;
            case 8:
                printf("Enter the Book ID to find successor: ");
                scanf("%d", &id);
                FIND_SUCCESSOR(id);
                break;
            case 9:
                DISPLAY_PREORDER();
                break;
            case 10:
                DISPLAY_POSTORDER();
                break;
            case 11:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    
    }

// End the program successfully
return 0;
}
