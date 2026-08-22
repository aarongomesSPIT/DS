#include <stdio.h>
#include <stdlib.h>
#include "FlightReservationSystem.h"


void menu()
{
    printf("----Flight Reservation System----\n");
    printf("1. Add a Flight.\n");
    printf("2. Search Flight by ID.\n");
    printf("3. Cancel a Flight by ID.\n");
    printf("4. Display Flights in IN ORDER order of Booking ID.\n");
    printf("5. Display Flights in PRE ORDER order of Booking ID.\n");
    printf("6. Display Flights in Post ORDER order of Booking ID.\n");
    printf("7. Display the smallest Booking ID.\n");
    printf("8. Exit the program.\n");
    printf("Enter your choice: ");
}


// Main Function
int main()
{
    int choice = 0;


    while(choice != 8)
    {
        menu();
        scanf("%d", &choice);
        int id;
        switch(choice)
        {
        case 1:
            INSERT_BOOKING();
            break;
        case 2:
        {
            printf("Enter the Book ID to search: ");
            scanf("%d", &id);
            SEARCH_BOOKING(id);
        }
        break;
        case 3:
        {
            printf("Enter the Book ID to delete: ");
            scanf("%d", &id);
            CANCEL_BOOKING(id);
        }
        break;
        case 4:
            DISPLAY_INORDER();
            break;
        case 5:
            DISPLAY_PREORDER();
            break;
        case 6:
            DISPLAY_POSTORDER();
            break;
        case 7:
            FIND_MIN();
            break;
        case 8:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }

    }


// End the program successfully
    return 0;
}
