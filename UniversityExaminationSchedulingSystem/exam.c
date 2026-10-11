#include "binomialHeap.c"
#include <time.h>

BinomialHeap *findHeap(BinomialHeap *a, BinomialHeap *b,
                       BinomialHeap *central, int merged, int id)
{
    if (merged) return searchHeap(central, id) ? central : NULL;
    if (searchHeap(a, id) != NULL) return a;
    if (searchHeap(b, id) != NULL) return b;
    return NULL;
}

void displayMenu(void)
{
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

void printExam(const char *message, BinomialNode *exam)
{
    printf("%s: ID=%d, Course=%d, Department=%s, Date=%s, Priority=%d\n",
           message, exam->ExaminationID, exam->CourseCode,
           exam->Department, exam->ExaminationDate, exam->key);
}

int INSERT_EXAM(BinomialHeap *H, int id, int courseCode,
                const char *department, const char *date, int priority)
{
    if (searchHeap(H, id) != NULL) return 0;
    insertNode(H, createNode(id, courseCode, department, date, priority));
    return 1;
}

void DISPLAY_ALL(BinomialHeap *dept1, BinomialHeap *dept2,
                 BinomialHeap *central, int merged)
{
    if (merged) {
        printf("\n--- Centralized University Queue ---\n");
        displayHeap(central);
    } else {
        printf("\n--- Department Queue 1 ---\n");
        displayHeap(dept1);
        printf("\n--- Department Queue 2 ---\n");
        displayHeap(dept2);
    }
}

BinomialHeap MERGE_HEAPS(BinomialHeap *dept1, BinomialHeap *dept2)
{
    return unionHeap(dept1, dept2);
}

void swapExamData(BinomialNode *a, BinomialNode *b)
{
    int tempInt;
    char tempDepartment[50];
    char tempDate[11];

    tempInt = a->ExaminationID;
    a->ExaminationID = b->ExaminationID;
    b->ExaminationID = tempInt;

    tempInt = a->CourseCode;
    a->CourseCode = b->CourseCode;
    b->CourseCode = tempInt;

    strcpy(tempDepartment, a->Department);
    strcpy(a->Department, b->Department);
    strcpy(b->Department, tempDepartment);

    strcpy(tempDate, a->ExaminationDate);
    strcpy(a->ExaminationDate, b->ExaminationDate);
    strcpy(b->ExaminationDate, tempDate);

    tempInt = a->key;
    a->key = b->key;
    b->key = tempInt;
}

int DECREASE_KEY(BinomialHeap *H, int id, int newPriority)
{
    BinomialNode *node = searchHeap(H, id), *parent;

    if (node == NULL || newPriority >= node->key) return 0;

    node->key = newPriority;
    while (node->parent != NULL && node->key < node->parent->key) {
        parent = node->parent;
        swapExamData(node, parent);
        node = parent;
    }
    return 1;
}

BinomialNode *DELETE_EXAM(BinomialHeap *H, int id)
{
    BinomialNode *node = searchHeap(H, id);

    if (node == NULL) return NULL;

    node->key = INT_MIN;
    while (node->parent != NULL) {
        BinomialNode *parent = node->parent;
        swapExamData(node, parent);
        node = parent;
    }
    return extractMin(H);
}

double MEASURE_MERGE_TIME(int n)
{
    BinomialHeap a, b, result;
    clock_t start, end;
    int i;

    initializeHeap(&a);
    initializeHeap(&b);
    for (i = 0; i < n; i++) {
        insertNode(&a, createNode(i + 1, 100 + i, "DeptA", "01-01-2027", i % 1000));
        insertNode(&b, createNode(n + i + 1, 200 + i, "DeptB", "02-01-2027", (i + 17) % 1000));
    }

    start = clock();
    result = unionHeap(&a, &b);
    end = clock();

    freeHeap(&result);
    freeHeap(&a);
    freeHeap(&b);
    return (double)(end - start) / CLOCKS_PER_SEC;
}