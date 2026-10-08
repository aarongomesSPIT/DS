#include <stdio.h>
#include "heap.c"

struct Patient {
    int id;
    char name[50];
    int severity;
};

struct Patient patients[100];
int totalRegistered = 0;

int heap[100];
int heapSize = 0;

void printPatientBySeverity(int severity) {
    for (int i = 0; i < totalRegistered; i++) {
        if (patients[i].severity == severity) {
            printf("ID: %d, Name: %s, Severity: %d\n", 
                   patients[i].id, patients[i].name, patients[i].severity);
            return;
        }
    }
    printf("Patient not found.\n");
}

void registerPatient() {
    int id, severity;
    char name[50];

    printf("Enter Patient ID: ");
    scanf("%d", &id);
    printf("Enter Patient Name: ");
    scanf("%s", name);
    printf("Enter Severity Score (1-100): ");
    scanf("%d", &severity);

    patients[totalRegistered].id = id;
    patients[totalRegistered].severity = severity;
    
    int i = 0;
    while (name[i] != '\0') {
        patients[totalRegistered].name[i] = name[i];
        i++;
    }
    patients[totalRegistered].name[i] = '\0';
    
    totalRegistered++;

    insertMaxHeap(heap, &heapSize, severity);
    printf("Patient registered successfully!\n");
}

void displayQueue() {
    if (heapSize == 0) {
        printf("Queue is empty.\n");
    } else {
        printf("\n--- Current Waiting Queue ---\n");
        for (int i = 0; i < heapSize; i++) {
            printPatientBySeverity(heap[i]);
        }
    }
}

void displayHighestPriority() {
    if (heapSize == 0) {
        printf("Queue is empty.\n");
    } else {
        printf("\n--- Highest Priority Patient ---\n");
        printPatientBySeverity(heap[0]);
    }
}

void treatPatient() {
    if (heapSize == 0) {
        printf("No patients to treat.\n");
    } else {
        int highestSeverity = deleteMaxHeap(heap, &heapSize);
        printf("\n--- Treating Patient ---\n");
        printPatientBySeverity(highestSeverity);
    }
}