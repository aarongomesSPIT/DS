#include <stdio.h>
#include <stdlib.h>
#include "delivery.c"

void printMenu() {
    printf("\n--- Delivery Network Menu ---\n");
    printf("1. Create network\n");
    printf("2. Add routes\n");
    printf("3. Display network\n");
    printf("4. DFS traversal\n");
    printf("5. BFS traversal\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice = 0;

    printf("Delivery Network Management System\n");
    printf("===================================\n");

    while (choice != 6) {
        printMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number from 1 to 6.\n");
            while (getchar() != '\n') {
            }
            continue;
        }

        switch (choice) {
        case 1:
            CreateNetwork();
            break;
        case 2:
            AddTransportRoutes();
            break;
        case 3:
            DisplayNetwork();
            break;
        case 4:
            TraverseNetworkDFS();
            break;
        case 5:
            TraverseNetworkBFS();
            break;
        case 6:
            printf("Exiting the application.\n");
            break;
        default:
            printf("Invalid choice. Please select a value from 1 to 6.\n");
            break;
        }
    }

    return 0;
}
