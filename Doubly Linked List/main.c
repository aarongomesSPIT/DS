#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "journey.h"
#include "doublyLinkedList.h"

void menu();

int is_int(const char *str);
int main()
{
    int choice = 0;
    int position;
    char query[50];
    while (choice != 10)
    {
        menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            ADD_DESTINATION();
            break;
        case 2:
            {
                int DestinationID;
                char DestinationName[50];
                printf("Enter Destination ID to remove: ");
                scanf("%d", &DestinationID);
                printf("Enter Destination Name to remove: ");
                scanf(" %[^\n]%*c", DestinationName);
                REMOVE_DESTINATION(DestinationID, DestinationName);
            }
            break;
        case 3:
            {
                int DestinationID;
                char DestinationName[50];
                printf("Enter Destination ID to search: ");
                scanf("%d", &DestinationID);
                printf("Enter Destination Name to search: ");
                scanf(" %[^\n]%*c", DestinationName);
                SEARCH_DESTINATION(DestinationID, DestinationName);
            }
            break;
        case 4:
            {
                int DestinationID;
                char DestinationName[50];
                printf("Enter Destination ID to update: ");
                scanf("%d", &DestinationID);
                printf("Enter Destination Name to update: ");
                scanf(" %[^\n]%*c", DestinationName);
                UPDATE_DESTINATION(DestinationID, DestinationName);
            }
            break;
        case 5:
            DISPLAY_FORWARD();
            break;
        case 6:
            DISPLAY_REVERSE();
            break;
        case 7:
            printf("Enter the DestiationID or DestinationName of current postition: ");
            scanf("%49s", query);
            if (is_int(query))
            {
                position = searchPosition(atoi(query), "");
                NEXT_DESTINATION(position);
            }
            else
            {
                position = searchPosition(0, query);
                NEXT_DESTINATION(position);
            }
            break;
        case 8:
            printf("Enter the DestiationID or DestinationName of current postition: ");
            scanf("%49s", query);
            if (is_int(query))
            {
                position = searchPosition(atoi(query), "");
                PREVIOUS_DESTINATION(position);
            }
            else
            {
                position = searchPosition(0, query);
                PREVIOUS_DESTINATION(position);
            }
            break;
        case 9:
            {
                int totalBudget = TOTAL_TRIP_BUDGET();
                printf("Total Trip Budget: %d\n", totalBudget);
            }
            break;
        case 10:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

void menu()
{
    printf("------Smart Travel Itinerary Planner-----!\n");
    printf("1. Add Destination\n");
    printf("2. Remove Destination\n");
    printf("3. Search Destination\n");
    printf("4. Update Destination\n");
    printf("5. Display Destinations Forward\n");
    printf("6. Display Destinations Reverse\n");
    printf("7. Next Destination\n");
    printf("8. Previous Destination\n");
    printf("9. Total Trip Budget\n");
    printf("10. Exit\n");
}


int is_int(const char *str) {
    if (str == NULL || *str == '\0') {
        return 0;
    }

    // Loop through every character
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit((unsigned char)str[i])) {
            return 0; // Found a non-digit character
        }
    }
    return 1;
}
