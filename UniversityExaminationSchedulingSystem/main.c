#include "exam.c"

int idExists(BinomialHeap *a, BinomialHeap *b, BinomialHeap *central,
             int merged, int id)
{
    if (searchHeap(merged ? central : a, id) != NULL) return 1;
    if (!merged && searchHeap(b, id) != NULL) return 1;
    return 0;
}

BinomialHeap *findHeap(BinomialHeap *a, BinomialHeap *b,
                       BinomialHeap *central, int merged, int id)
{
    if (merged) return searchHeap(central, id) ? central : NULL;
    if (searchHeap(a, id) != NULL) return a;
    if (searchHeap(b, id) != NULL) return b;
    return NULL;
}

BinomialHeap *chooseQueue(BinomialHeap *a, BinomialHeap *b,
                          BinomialHeap *central, int merged)
{
    int choice;
    if (merged) return central;

    printf("Select queue (1 or 2): ");
    if (scanf("%d", &choice) != 1) return NULL;
    if (choice == 1) return a;
    if (choice == 2) return b;
    printf("Invalid queue.\n");
    return NULL;
}

int main(void)
{
    BinomialHeap dept1, dept2, central;
    int merged = 0, choice, id, courseCode, priority, newPriority, size, i;
    int sizes[3];
    char department[50], date[11];
    BinomialHeap *queue, *foundHeap;
    BinomialNode *exam;

    initializeHeap(&dept1);
    initializeHeap(&dept2);
    initializeHeap(&central);

    do {
        printf("\n=== University Examination Scheduling ===\n");
        printf("1. Insert examination\n");
        printf("2. Display all examinations\n");
        printf("3. Merge departmental heaps\n");
        printf("4. Extract minimum priority\n");
        printf("5. Decrease priority\n");
        printf("6. Delete examination\n");
        printf("7. Measure merge time\n");
        printf("8. Show complexity\n");
        printf("0. Exit\n");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting.\n");
            break;
        }

        switch (choice) {
        case 1:
            queue = chooseQueue(&dept1, &dept2, &central, merged);
            if (queue == NULL) break;
            printf("Examination ID: "); scanf("%d", &id);
            if (idExists(&dept1, &dept2, &central, merged, id)) {
                printf("Examination ID already exists.\n");
                break;
            }
            printf("Course code (number): "); scanf("%d", &courseCode);
            printf("Department (one word): "); scanf("%49s", department);
            printf("Examination date (DD-MM-YYYY): "); scanf("%10s", date);
            printf("Priority (smaller means higher priority): "); scanf("%d", &priority);
            if (INSERT_EXAM(queue, id, courseCode, department, date, priority))
                printf("Examination inserted.\n");
            else
                printf("Could not insert examination.\n");
            break;

        case 2:
            DISPLAY_ALL(&dept1, &dept2, &central, merged);
            break;

        case 3:
            if (merged) {
                printf("The heaps have already been merged.\n");
            } else {
                central = MERGE_HEAPS(&dept1, &dept2);
                merged = 1;
                printf("Both departmental queues merged into the centralized queue.\n");
            }
            break;

        case 4:
            queue = chooseQueue(&dept1, &dept2, &central, merged);
            if (queue == NULL) break;
            exam = EXTRACT_MIN(queue);
            if (exam == NULL) {
                printf("Heap is empty.\n");
            } else {
                printf("Scheduled examination: ID=%d, Course=%d, Department=%s, Date=%s, Priority=%d\n",
                       exam->ExaminationID, exam->CourseCode, exam->Department,
                       exam->ExaminationDate, exam->key);
                free(exam);
            }
            break;

        case 5:
            printf("Examination ID: "); scanf("%d", &id);
            foundHeap = findHeap(&dept1, &dept2, &central, merged, id);
            if (foundHeap == NULL) {
                printf("Examination ID not found.\n");
                break;
            }
            printf("New priority: "); scanf("%d", &newPriority);
            if (DECREASE_KEY(foundHeap, id, newPriority))
                printf("Priority decreased.\n");
            else
                printf("New priority must be smaller than the current priority.\n");
            break;

        case 6:
            printf("Examination ID to delete: "); scanf("%d", &id);
            foundHeap = findHeap(&dept1, &dept2, &central, merged, id);
            if (foundHeap == NULL) {
                printf("Examination ID not found.\n");
            } else {
                exam = DELETE_EXAM(foundHeap, id);
                if (exam != NULL) {
                    printf("Deleted examination ID %d.\n", exam->ExaminationID);
                    free(exam);
                } else {
                    printf("Could not delete examination.\n");
                }
            }
            break;

        case 7:
            printf("Enter three heap sizes (nodes in each heap): ");
            if (scanf("%d %d %d", &sizes[0], &sizes[1], &sizes[2]) != 3) {
                printf("Invalid input.\n");
                break;
            }
            for (i = 0; i < 3; i++) {
                size = sizes[i];
                if (size < 1 || size > 100000) {
                    printf("Size %d is invalid; enter a value from 1 to 100000.\n", size);
                } else {
                    printf("Merge two heaps of %d nodes each: %.8f seconds\n",
                           size, MEASURE_MERGE_TIME(size));
                }
            }
            break;

        case 8:
            printf("Merge: O(log n) | Insert: O(log n) | Find minimum: O(log n)\n");
            printf("Extract minimum: O(log n) | Search by ID: O(n)\n");
            printf("Decrease key/Delete including search: O(n) | Space: O(n)\n");
            break;

        case 0:
            printf("Exiting.\n");
            break;

        default:
            printf("Invalid menu choice.\n");
        }
    } while (choice != 0);

    freeHeap(&dept1);
    freeHeap(&dept2);
    freeHeap(&central);
    return 0;
}