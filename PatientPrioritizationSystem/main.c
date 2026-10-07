#include <stdio.h>
#include <stdlib.h>
#include "emergency.c"

int main() {
    int heap[MAX_PATIENTS];
    int heapSize = 0;
    int choice;

    while (1) {
        printf("\n=======================================================\n");
        printf("    EMERGENCY ROOM PATIENT PRIORITIZATION SYSTEM       \n");
        printf("=======================================================\n");
        printf("1. Register New Patient (Insert)\n");
        printf("2. Display All Waiting Patients\n");
        printf("3. Display Patient with Highest Priority\n");
        printf("4. Remove (Treat) Highest Priority Patient\n");
        printf("5. Exit\n");
        printf("-------------------------------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("\n[!] Invalid input. Exiting.\n");
            break;
        }

        switch (choice) {
            case 1:
                registerPatient(heap, &heapSize);
                break;
            case 2:
                displayQueue(heap, heapSize);
                break;
            case 3:
                displayHighestPriority(heap, heapSize);
                break;
            case 4:
                treatHighestPriority(heap, &heapSize);
                break;
            case 5:
                printf("\nExiting System.\n");
                exit(0);
            default:
                printf("\n[!] Invalid selection! Choose between 1 and 5.\n");
        }
    }

    return 0;
}