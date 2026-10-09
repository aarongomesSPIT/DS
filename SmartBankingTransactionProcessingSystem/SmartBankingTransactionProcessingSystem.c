#include "binomialHeap.c"

BinomialHeap branchA;
BinomialHeap branchB;
BinomialHeap centralHeap;

BinomialHeap *selectHeap(void)
{
    int choice;

    printf("\nSelect queue:\n");
    printf("1. Branch A\n");
    printf("2. Branch B\n");
    printf("3. Centralized queue\n");
    printf("Enter choice: ");

    if (scanf("%d", &choice) != 1)
        return NULL;

    if (choice == 1)
        return &branchA;
    if (choice == 2)
        return &branchB;
    if (choice == 3)
        return &centralHeap;

    printf("Invalid choice.\n");
    return NULL;
}

int transactionIDExists(int id)
{
    if (searchHeap(&branchA, id) != NULL)
        return 1;
    if (searchHeap(&branchB, id) != NULL)
        return 1;
    if (searchHeap(&centralHeap, id) != NULL)
        return 1;
    return 0;
}

void printTransaction(BinomialNode *node)
{
    if (node == NULL)
        return;

    printf("Transaction ID: %d\n", node->transactionID);
    printf("Customer ID: %d\n", node->customerID);
    printf("Type: %s\n", node->transactionType);
    printf("Amount: %.2f\n", node->amount);
    printf("Priority: %d\n", node->key);
}

void INSERT_TRANSACTION(void)
{
    BinomialHeap *heap;
    BinomialNode *node;
    int tid, cid, priority;
    double amount;
    char type[30];

    heap = selectHeap();
    if (heap == NULL)
        return;

    printf("Enter Transaction ID: ");
    if (scanf("%d", &tid) != 1)
        return;

    if (transactionIDExists(tid))
    {
        printf("Transaction ID already exists.\n");
        return;
    }

    printf("Enter Customer ID: ");
    if (scanf("%d", &cid) != 1)
        return;

    printf("Enter Transaction Type (one word): ");
    if (scanf("%29s", type) != 1)
        return;

    printf("Enter Amount: ");
    if (scanf("%lf", &amount) != 1)
        return;

    printf("Enter Priority (smaller value means higher priority): ");
    if (scanf("%d", &priority) != 1)
        return;

    node = createNode(tid, cid, type, amount, priority);
    insertNode(heap, node);
    printf("Transaction inserted.\n");
}

void DISPLAY_ALL(void)
{
    BinomialHeap *heap = selectHeap();

    if (heap != NULL)
        displayHeap(heap);
}

void MERGE_HEAPS(void)
{
    centralHeap = unionHeap(&centralHeap, &branchA);
    centralHeap = unionHeap(&centralHeap, &branchB);

    printf("Both branches were merged into the centralized queue.\n");
    displayHeap(&centralHeap);
}

void EXTRACT_MIN(void)
{
    BinomialHeap *heap;
    BinomialNode *node;

    heap = selectHeap();
    if (heap == NULL)
        return;

    node = extractMin(heap);
    if (node == NULL)
    {
        printf("The queue is empty.\n");
        return;
    }

    printf("\nProcessing transaction:\n");
    printTransaction(node);
    free(node);
}

void DECREASE_KEY(void)
{
    BinomialHeap *heap;
    BinomialNode *node;
    int tid, newKey;

    heap = selectHeap();
    if (heap == NULL)
        return;

    printf("Enter Transaction ID: ");
    if (scanf("%d", &tid) != 1)
        return;

    node = searchHeap(heap, tid);
    if (node == NULL)
    {
        printf("Transaction not found.\n");
        return;
    }

    printf("Enter the new priority: ");
    if (scanf("%d", &newKey) != 1)
        return;

    decreaseKey(heap, node, newKey);
}

void DELETE_TRANSACTION(void)
{
    BinomialHeap *heap;
    BinomialNode *node;
    BinomialNode *deleted;
    int tid;

    heap = selectHeap();
    if (heap == NULL)
        return;

    printf("Enter Transaction ID: ");
    if (scanf("%d", &tid) != 1)
        return;

    node = searchHeap(heap, tid);
    if (node == NULL)
    {
        printf("Transaction not found.\n");
        return;
    }

    deleted = deleteNode(heap, node);
    if (deleted != NULL)
    {
        printf("Transaction deleted:\n");
        printTransaction(deleted);
        free(deleted);
    }
}

void buildTestHeap(BinomialHeap *heap, int count, int firstID)
{
    int i;
    BinomialNode *node;

    initializeHeap(heap);

    for (i = 0; i < count; i++)
    {
        node = createNode(firstID + i, firstID + i, "TEST", i + 1,
                          (i * 17) % 10000);
        insertNode(heap, node);
    }
}

void MEASURE_MERGE_TIME(void)
{
    int maxSize, size;

    printf("Maximum test size per heap (at least 1000): ");
    if (scanf("%d", &maxSize) != 1 || maxSize < 1000)
    {
        printf("Enter a number of 1000 or more.\n");
        return;
    }

    printf("\nTransactions per heap\tMerge time (seconds)\n");

    for (size = 1000; size <= maxSize; size = size * 2)
    {
        BinomialHeap a, b;
        double seconds;

        buildTestHeap(&a, size, 1);
        buildTestHeap(&b, size, size + 1);
        seconds = measureMergeTime(&a, &b);

        printf("%d\t\t\t%.9f\n", size, seconds);

        if (size > maxSize / 2)
            break;
    }
}

void menu()
{
    int choice;

    initializeHeap(&branchA);
    initializeHeap(&branchB);
    initializeHeap(&centralHeap);

    do
    {
        printf("\n===== SMART BANKING SYSTEM =====\n");
        printf("1. Insert transaction\n");
        printf("2. Display transactions\n");
        printf("3. Merge branch heaps\n");
        printf("4. Extract minimum\n");
        printf("5. Decrease priority\n");
        printf("6. Delete transaction\n");
        printf("7. Measure merge time\n");
        printf("0. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1)
            break;

        switch (choice)
        {
            case 1: INSERT_TRANSACTION(); break;
            case 2: DISPLAY_ALL(); break;
            case 3: MERGE_HEAPS(); break;
            case 4: EXTRACT_MIN(); break;
            case 5: DECREASE_KEY(); break;
            case 6: DELETE_TRANSACTION(); break;
            case 7: MEASURE_MERGE_TIME(); break;
            case 0: printf("Goodbye.\n"); break;
            default: printf("Invalid menu choice.\n");
        }
    } while (choice != 0);

    freeHeap(&branchA);
    freeHeap(&branchB);
    freeHeap(&centralHeap);
}
