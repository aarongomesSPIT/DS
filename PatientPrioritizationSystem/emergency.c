#include <stdio.h>
#include <string.h>
#include "heap.c"

#define MAX_PATIENTS 100

typedef struct {
    int id;
    char name[50];
    int severity;
} Patient;

static Patient patientMap[MAX_PATIENTS];
static int mapCount = 0;

static void registerPatientDetails(Patient p) {
    patientMap[mapCount++] = p;
}

static char* getPatientName(int severity) {
    for (int i = 0; i < mapCount; i++) {
        if (patientMap[i].severity == severity)
            return patientMap[i].name;
    }
    return "Unknown";
}

static int getPatientId(int severity) {
    for (int i = 0; i < mapCount; i++) {
        if (patientMap[i].severity == severity)
            return patientMap[i].id;
    }
    return -1;
}

void registerPatient(int heap[], int *heapSize) {
    if (*heapSize >= MAX_PATIENTS) {
        printf("\n[!] Emergency Room capacity full!\n");
        return;
    }

    Patient p;
    printf("\nEnter Patient ID: ");
    scanf("%d", &p.id);
    getchar();

    printf("Enter Patient Name: ");
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = 0;

    do {
        printf("Enter Severity Score (1-100): ");
        scanf("%d", &p.severity);
        if (p.severity < 1 || p.severity > 100) {
            printf("Invalid severity score! Must be between 1 and 100.\n");
        }
    } while (p.severity < 1 || p.severity > 100);

    registerPatientDetails(p);
    insertMaxHeap(heap, heapSize, p.severity);
    printf("\n[+] Patient ID %d registered and queued successfully.\n", p.id);
}

void treatHighestPriority(int heap[], int *heapSize) {
    int maxSeverity = deleteMaxHeap(heap, heapSize);
    if (maxSeverity != -1) {
        printf("\n[***] TREATING PATIENT [***]\n");
        printf("Patient ID    : %d\n", getPatientId(maxSeverity));
        printf("Patient Name  : %s\n", getPatientName(maxSeverity));
        printf("Severity Score: %d\n", maxSeverity);
    }
}

void displayHighestPriority(int heap[], int heapSize) {
    if (heapSize == 0) {
        printf("\n[!] No patients currently waiting.\n");
        return;
    }
    int topSeverity = heap[0];
    printf("\n--- NEXT PATIENT TO BE TREATED ---\n");
    printf("Patient ID    : %d\n", getPatientId(topSeverity));
    printf("Patient Name  : %s\n", getPatientName(topSeverity));
    printf("Severity Score: %d\n", topSeverity);
}

void displayQueue(int heap[], int heapSize) {
    if (heapSize == 0) {
        printf("\n[!] Queue is empty. No waiting patients.\n");
        return;
    }
    printf("\n=======================================================\n");
    printf("             CURRENT ER WAITING QUEUE                  \n");
    printf("=======================================================\n");
    printf("%-10s | %-25s | %-15s\n", "ID", "Name", "Severity Score");
    printf("-------------------------------------------------------\n");
    for (int i = 0; i < heapSize; i++) {
        int sev = heap[i];
        printf("%-10d | %-25s | %-15d\n", getPatientId(sev), getPatientName(sev), sev);
    }
    printf("=======================================================\n");
}