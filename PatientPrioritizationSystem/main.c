#include <stdio.h>
#include <stdlib.h>

#include "emergency.c"

int main() {
    int choice;

    while (1) {
        printf("\n--- Emergency Room Prioritization ---\n");
        printf("1. Register New Patient\n");
        printf("2. Display All Waiting Patients\n");
        printf("3. Display Highest Priority Patient\n");
        printf("4. Treat Highest Priority Patient\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerPatient();
                break;
            case 2:
                displayQueue();
                break;
            case 3:
                displayHighestPriority();
                break;
            case 4:
                treatPatient();
                break;
            case 5:
                printf("Exiting system...\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
                break;
        }
    }

    return 0;
}