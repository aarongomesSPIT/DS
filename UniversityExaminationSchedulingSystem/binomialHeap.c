#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

/*
===========================================================
MIN BINOMIAL HEAP - GENERAL IMPLEMENTATION
===========================================================
This code provides the core data structure operations.
Students should use these functions to build their own
application according to the given problem statement.
IMPORTANT:
Smaller key value = Higher priority
Supported operations:
1. Create Node
2. Link Trees
3. Merge Root Lists
4. Union / Merge Heaps
5. Insert
6. Find Minimum
7. Extract Minimum
8. Decrease Key
9. Delete
10. Search
11. Display
12. Measure Merge Time
The application-specific transaction/menu logic is NOT
implemented here.
===========================================================
*/

/*=========================================================
1. NODE STRUCTURE
=========================================================*/
/*
A typical Binomial Heap node contains:
● Examination ID
● Course Code
● Department
● Examination Date
Binomial Heap data:
● Priority/Key
● Degree of the node
● Parent pointer
● Child pointer
● Sibling pointer
*/

typedef struct BinomialNode
{
    /* Application-specific information */
    int ExaminationID;
    int CourseCode;
    char Department[50];
    char ExaminationDate[11];
    /* Priority / Heap Key */
    int key;
    /* Binomial Tree information */
    int degree;
    struct BinomialNode *parent;
    struct BinomialNode *child;
    struct BinomialNode *sibling;
} BinomialNode;


/*=========================================================
2. BINOMIAL HEAP STRUCTURE
=========================================================*/
typedef struct
{
    BinomialNode *head;
} BinomialHeap;

/*=========================================================
3. CREATE / INITIALIZE EMPTY HEAP
=========================================================*/
void initializeHeap(BinomialHeap *H)
{
    H->head = NULL;
}

/*=========================================================
4. CREATE A NEW NODE
=========================================================*/
BinomialNode *createNode(
    int ExaminationID,
    int CourseCode,
    const char *Department,
    const char *ExaminationDate,
    int key)
{
    BinomialNode *newNode;
    newNode = (BinomialNode *)malloc(sizeof(BinomialNode));
    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->ExaminationID = ExaminationID;
    newNode->CourseCode = CourseCode;
    strcpy(newNode->Department, Department);
    strcpy(newNode->ExaminationDate, ExaminationDate);
    /* Priority / Key */
    newNode->key = key;
    /*
    A newly created node is a Binomial Tree B0.
    Therefore:
    degree = 0
    parent = NULL
    child = NULL
    sibling = NULL
    */
    newNode->degree = 0;
    newNode->parent = NULL;
    newNode->child = NULL;
    newNode->sibling = NULL;
    return newNode;
}

/*=========================================================
5. LINK TWO BINOMIAL TREES
=========================================================*/
/*
LINK operation:
Given two Binomial Trees of the SAME degree:
Bk + Bk
The root having the smaller key becomes the parent.
Result:
B(k+1)
Example:
5 8
| + |
children children
Since 5 < 8:
5
/
8
The root 8 becomes a child of root 5.
IMPORTANT:
Both trees MUST have the same degree.
*/
void binomialLink(
    BinomialNode *y,
    BinomialNode *z)
{
    /*
    We want z to become child of y.
    Therefore y must have the smaller key.
    */
    z->parent = y;
    /*
    Insert z at the beginning of y's child list.
    */
    z->sibling = y->child;
    y->child = z;
    /*
    Since one complete Binomial Tree has been
    attached as a child, degree increases by 1.
    */
    y->degree++;
}

/*=========================================================
6. MERGE TWO ROOT LISTS
=========================================================*/
/*
This operation ONLY merges the root lists.
It does NOT consolidate trees having equal degrees.
Example:
H1:
B0 -> B2 -> B4
H2:
B0 -> B1 -> B3
After MERGE:
B0 -> B0 -> B1 -> B2 -> B3 -> B4
The UNION operation will subsequently perform
the required LINK operations.
*/
BinomialNode *mergeRootLists(
    BinomialNode *h1,
    BinomialNode *h2)
{
    BinomialNode *head = NULL;
    BinomialNode *tail = NULL;
    /* If one list is empty */
    if (h1 == NULL)
        return h2;
    if (h2 == NULL)
        return h1;
    /*
    Select the first root according to degree.
    */
    if (h1->degree <= h2->degree)
    {
        head = h1;
        h1 = h1->sibling;
    }
    else
    {
        head = h2;
        h2 = h2->sibling;
    }
    tail = head;
    /*
    Merge the remaining root lists in increasing
    order of degree.
    */
    while (h1 != NULL && h2 != NULL)
    {
        if (h1->degree <= h2->degree)
        {
            tail->sibling = h1;
            h1 = h1->sibling;
        }
        else
        {
            tail->sibling = h2;
            h2 = h2->sibling;
        }
        tail = tail->sibling;
    }
    /* Attach remaining roots */
    if (h1 != NULL)
        tail->sibling = h1;
    else
        tail->sibling = h2;
    return head;
}

/*=========================================================
7. UNION / MERGE TWO BINOMIAL HEAPS
=========================================================*/
/*
UNION performs two major steps:
Step 1:
Merge the two root lists according to degree.
Step 2:
Consolidate the heap by linking trees having
equal degree.
The final heap contains at most one tree of each degree.
IMPORTANT:
This operation modifies the two input heaps.
After union, H1 and H2 should normally be treated as
empty/source heaps because their nodes have been moved
into the resulting heap.
*/
BinomialHeap unionHeap(
    BinomialHeap *H1,
    BinomialHeap *H2)
{
    BinomialHeap result;
    BinomialNode *prevX;
    BinomialNode *x;
    BinomialNode *nextX;
    initializeHeap(&result);
    /*-----------------------------------------------------
    STEP 1: Merge the root lists
    -----------------------------------------------------*/
    result.head =
        mergeRootLists(H1->head, H2->head);
    /* If both heaps were empty */
    if (result.head == NULL)
    {
        H1->head = NULL;
        H2->head = NULL;
        return result;
    }
    /*-----------------------------------------------------
    STEP 2: Consolidate equal-degree trees
    -----------------------------------------------------*/
    prevX = NULL;
    x = result.head;
    nextX = x->sibling;
    while (nextX != NULL)
    {
        /*
        CASE 1:
        Degrees are different.
        Move forward.
        */
        if (x->degree != nextX->degree)
        {
            prevX = x;
            x = nextX;
        }
        /*
        CASE 2:
        Three consecutive trees have the same degree.
        Do NOT link x and nextX immediately.
        Example:
        B2 -> B2 -> B2
        We first process the later pair according
        to the standard consolidation procedure.
        */
        else if (
            nextX->sibling != NULL &&
            nextX->sibling->degree == x->degree)
        {
            prevX = x;
            x = nextX;
        }
        /*
        CASE 3:
        x and nextX have equal degree and must be linked.
        The smaller key becomes the parent.
        */
        else if (x->key <= nextX->key)
        {
            /*
            x becomes parent of nextX.
            */
            x->sibling = nextX->sibling;
            binomialLink(x, nextX);
        }
        /*
        CASE 4:
        nextX has the smaller key.
        Therefore nextX becomes parent of x.
        */
        else
        {
            if (prevX == NULL)
            {
                result.head = nextX;
            }
            else
            {
                prevX->sibling = nextX;
            }
            binomialLink(nextX, x);
            x = nextX;
        }
        nextX = x->sibling;
    }
    /*
    The original root lists are now consumed.
    */
    H1->head = NULL;
    H2->head = NULL;
    return result;
}


/*=========================================================
8. INSERT A NODE
=========================================================*/
/*
Insertion strategy:
1. Create a temporary heap H'
containing only the new node.
2. Perform UNION(H, H').
3. Result becomes the updated heap.
A single node is a B0 Binomial Tree.
*/
void insertNode(
    BinomialHeap *H,
    BinomialNode *newNode)
{
    BinomialHeap temp;
    initializeHeap(&temp);
    /*
    New node forms B0.
    */
    newNode->degree = 0;
    newNode->parent = NULL;
    newNode->child = NULL;
    newNode->sibling = NULL;
    temp.head = newNode;
    /*
    Merge temporary heap with existing heap.
    */
    *H = unionHeap(H, &temp);
}


/*=========================================================
9. FIND MINIMUM
=========================================================*/
/*
The minimum element must be present among the roots.
Why?
Because every Binomial Tree satisfies the Min Heap
property.
Therefore we only need to examine the root list.
Time Complexity:
O(log n)
*/
BinomialNode *findMinimum(BinomialHeap *H)
{
    BinomialNode *current;
    BinomialNode *minimum;
    if (H->head == NULL)
        return NULL;
    minimum = H->head;
    current = H->head->sibling;
    while (current != NULL)
    {
        if (current->key < minimum->key)
        {
            minimum = current;
        }
        current = current->sibling;
    }
    return minimum;
}


/*=========================================================
10. REVERSE A LINKED LIST
=========================================================*/
/*
Used during EXTRACT-MIN.
The children of the minimum root form a set of
Binomial Trees.
Their parent pointers must be removed.
The child list is reversed so that the resulting
root list is ordered by increasing degree.
*/
BinomialNode *reverseChildren(
    BinomialNode *child)
{
    BinomialNode *prev = NULL;
    BinomialNode *current = child;
    BinomialNode *next;
    while (current != NULL)
    {
        next = current->sibling;
        current->sibling = prev;
        current->parent = NULL;
        prev = current;
        current = next;
    }
    return prev;
}


/*=========================================================
11. EXTRACT MINIMUM
=========================================================*/
/*
EXTRACT-MIN:
1. Find minimum root.
2. Remove minimum root from root list.
3. Take its children.
4. Reverse the child list.
5. Make children a separate Binomial Heap.
6. UNION it with the remaining heap.
7. Return the removed minimum node.
The caller can use the returned node to process the
transaction/application record.
*/
BinomialNode *extractMin(BinomialHeap *H)
{
    BinomialNode *minimum;
    BinomialNode *current;
    BinomialNode *prev;
    BinomialNode *minPrev;
    BinomialHeap childHeap;
    BinomialNode *children;
    if (H->head == NULL)
    {
        return NULL;
    }
    /*-----------------------------------------------------
    STEP 1: Find minimum root and its predecessor
    -----------------------------------------------------*/
    minimum = H->head;
    current = H->head;
    prev = NULL;
    minPrev = NULL;
    while (current != NULL)
    {
        if (current->key < minimum->key)
        {
            minimum = current;
            minPrev = prev;
        }
        prev = current;
        current = current->sibling;
    }
    /*-----------------------------------------------------
    STEP 2: Remove minimum root from root list
    -----------------------------------------------------*/
    if (minPrev == NULL)
    {
        /*
        Minimum is the first root.
        */
        H->head = minimum->sibling;
    }
    else
    {
        /*
        Skip the minimum root.
        */
        minPrev->sibling = minimum->sibling;
    }
    /*-----------------------------------------------------
    STEP 3: Remove minimum's children
    -----------------------------------------------------*/
    children = minimum->child;
    /*
    Minimum is no longer part of the heap.
    */
    minimum->child = NULL;
    minimum->parent = NULL;
    minimum->sibling = NULL;
    /*-----------------------------------------------------
    STEP 4: Reverse child list
    -----------------------------------------------------*/
    children = reverseChildren(children);
    /*-----------------------------------------------------
    STEP 5: Create heap containing children
    -----------------------------------------------------*/
    initializeHeap(&childHeap);
    childHeap.head = children;
    /*-----------------------------------------------------
    STEP 6: Merge remaining heap and child heap
    -----------------------------------------------------*/
    *H = unionHeap(H, &childHeap);
    return minimum;
}


/*=========================================================
12. SWAP APPLICATION DATA
=========================================================*/
/*
During Decrease-Key, we can exchange the complete
application payload.
This is especially useful for the banking application.
The tree structure does NOT change.
Only the data stored in the nodes is exchanged.
This ensures that:
Transaction ID
Customer ID
Transaction Type
Amount
Priority
remain together.
*/
void swapTransactionData(
    BinomialNode *a,
    BinomialNode *b)
{
    int tempInt;
    char tempType[30];
    /* Swap Transaction ID */
    tempInt = a->ExaminationID;
    a->ExaminationID = b->ExaminationID;
    b->ExaminationID = tempInt;
    /* Swap Customer ID */
    tempInt = a->CourseCode;
    a->CourseCode = b->CourseCode;
    b->CourseCode = tempInt;
    /* Swap Department */
    strcpy(tempType, a->Department);
    strcpy(a->Department, b->Department);
    strcpy(b->Department, tempType);
    /* Swap Examination Date */
    strcpy(tempType, a->ExaminationDate);
    strcpy(a->ExaminationDate, b->ExaminationDate);
    strcpy(b->ExaminationDate, tempType);
    /* Swap Priority / Key */
    tempInt = a->key;
    a->key = b->key;
    b->key = tempInt;
}


/*=========================================================
13. DECREASE KEY
=========================================================*/
/*
DECREASE-KEY:
Reduce the key of a node.
Example:
Parent = 10
Node = 20
Decrease node:
20 -> 5
Since:
5 < 10
the node violates the Min Heap property.
Therefore it is moved upward.
The operation continues until:
1. Node reaches the root
OR
2. Parent key <= node key
IMPORTANT:
The tree structure itself is NOT changed.
*/
int decreaseKey(
    BinomialHeap *H,
    BinomialNode *x,
    int newKey)
{
    BinomialNode *parent;
    if (x == NULL)
    {
        printf("Invalid node.\n");
        return 0;
    }
    /*
    New key must be smaller than current key.
    */
    if (newKey >= x->key)
    {
        printf("New key must be smaller than current key.\n");
        return 0;
    }
    /*
    Change the key.
    To keep application data together, we first store
    the new key in x.
    */
    x->key = newKey;
    parent = x->parent;
    /*
    Move upward while heap-order property is violated.
    */
    while (parent != NULL &&
           x->key < parent->key)
    {
        /*
        Swap the complete transaction/application data.
        The parent/child pointers themselves are NOT
        changed.
        */
        swapTransactionData(x, parent);
        /*
        Continue from the parent's position.
        */
        x = parent;
        parent = x->parent;
    }
    return 1;
}


/*=========================================================
14. DELETE NODE
=========================================================*/
/*
Standard Binomial Heap deletion:
DELETE(x)
= DECREASE-KEY(x, -infinity)
followed by
EXTRACT-MIN()
Since C does not have mathematical -infinity for int,
INT_MIN is used as the smallest possible integer.
Assumption:
Valid priority values should be greater than INT_MIN.
*/
BinomialNode *deleteNode(
    BinomialHeap *H,
    BinomialNode *x)
{
    BinomialNode *deletedNode;
    if (x == NULL)
    {
        printf("Invalid node.\n");
        return NULL;
    }
    /*
    Force x to become the minimum-priority node.
    */
    x->key = INT_MIN;
    /*
    Move the minimum upward.
    We cannot call normal decreaseKey() with INT_MIN
    if x already has INT_MIN, so the bubbling is done
    directly here.
    */
    while (x->parent != NULL)
    {
        swapTransactionData(x, x->parent);
        x = x->parent;
    }
    /*
    x is now a root with the minimum key.
    Extract-Min removes it.
    */
    deletedNode = extractMin(H);
    return deletedNode;
}


/*=========================================================
15. SEARCH BY TRANSACTION ID
=========================================================*/
/*
The Binomial Heap is organized according to priority,
not Transaction ID.
Therefore searching by Transaction ID is generally
a traversal operation.
This function recursively searches all nodes.
*/
BinomialNode *searchTransaction(
    BinomialNode *root,
    int ExaminationID)
{
    BinomialNode *found;
    if (root == NULL)
        return NULL;
    /* Check current node */
    if (root->ExaminationID == ExaminationID)
        return root;
    /* Search children */
    found = searchTransaction(
        root->child,
        ExaminationID);
    if (found != NULL)
        return found;
    /* Search siblings */
    return searchTransaction(
        root->sibling,
        ExaminationID);
}


/*
Search the complete heap.
*/
BinomialNode *searchHeap(
    BinomialHeap *H,
    int ExaminationID)
{
    BinomialNode *current;
    BinomialNode *found;
    current = H->head;
    while (current != NULL)
    {
        found = searchTransaction(
            current,
            ExaminationID);
        if (found != NULL)
            return found;
        current = current->sibling;
    }
    return NULL;
}


/*=========================================================
16. DISPLAY ONE BINOMIAL TREE
=========================================================*/
void displayTree(
    BinomialNode *root,
    int level)
{
    int i;
    if (root == NULL)
        return;
    /* Indentation represents tree level */
    for (i = 0; i < level; i++)
    {
        printf(" ");
    }
    printf(
        "Exam ID=%d | Course Code=%d | Department=%s | Date=%s | Key=%d | Degree=%d\n",
        root->ExaminationID,
        root->CourseCode,
        root->Department,
        root->ExaminationDate,
        root->key,
        root->degree);
    /*
    Display children.
    */
    displayTree(root->child, level + 1);
    /*
    Display siblings at same level.
    */
    displayTree(root->sibling, level);
}


/*=========================================================
17. DISPLAY COMPLETE BINOMIAL HEAP
=========================================================*/
void displayHeap(BinomialHeap *H)
{
    BinomialNode *current;
    if (H->head == NULL)
    {
        printf("\nHeap is empty.\n");
        return;
    }
    printf("\n========== BINOMIAL HEAP ==========\n");
    current = H->head;
    /*
    Root list contains one root for every
    Binomial Tree in the heap.
    */
    while (current != NULL)
    {
        printf(
            "\nBinomial Tree B%d\n",
            current->degree);
        printf(
            "Root: Exam ID=%d | Key=%d\n",
            current->ExaminationID,
            current->key);
        displayTree(current->child, 1);
        current = current->sibling;
    }
    printf("\n===================================\n");
}


/*=========================================================
18. DISPLAY ROOT LIST
=========================================================*/
void displayRootList(BinomialHeap *H)
{
    BinomialNode *current;
    printf("\nRoot List:\n");
    current = H->head;
    while (current != NULL)
    {
        printf(
            "[Exam ID=%d Key=%d Degree=%d]",
            current->ExaminationID,
            current->key,
            current->degree);
        if (current->sibling != NULL)
            printf(" -> ");
        current = current->sibling;
    }
    printf(" -> NULL\n");
}


/*=========================================================
19. FREE ONE TREE
=========================================================*/
void freeTree(BinomialNode *root)
{
    BinomialNode *child;
    BinomialNode *next;
    if (root == NULL)
        return;
    child = root->child;
    while (child != NULL)
    {
        next = child->sibling;
        freeTree(child);
        child = next;
    }
    free(root);
}


/*=========================================================
20. FREE COMPLETE HEAP
=========================================================*/
void freeHeap(BinomialHeap *H)
{
    BinomialNode *current;
    BinomialNode *next;
    current = H->head;
    while (current != NULL)
    {
        next = current->sibling;
        freeTree(current);
        current = next;
    }
    H->head = NULL;
}


/*=========================================================
21. OPTIONAL: MEASURE UNION TIME
=========================================================*/
/*
This is only a GENERAL timing utility.
Students can adapt the idea for the required experiment.
The banking application logic is intentionally NOT included.
*/
double measureMergeTime(
    BinomialHeap *H1,
    BinomialHeap *H2)
{
    clock_t start;
    clock_t end;
    double timeTaken;
    BinomialHeap result;
    start = clock();
    /*
    Perform the actual Binomial Heap UNION.
    */
    result = unionHeap(H1, H2);
    end = clock();
    timeTaken =
        ((double)(end - start)) / CLOCKS_PER_SEC;
    /*
    Free the resulting heap after measurement.
    */
    freeHeap(&result);
    return timeTaken;
}


/*=========================================================
END OF GENERAL BINOMIAL HEAP IMPLEMENTATION
=========================================================*/