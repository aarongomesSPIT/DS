#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>


typedef struct FibNode
{
    int serverId;
    long long key;
    int degree;
    int mark;
    /* load; smaller means less loaded */
    /* 0 = unmarked, 1 = marked */
    struct FibNode *parent, *child;
    struct FibNode *left, *right;
} FibNode;


typedef struct
{
    FibNode *min;
    int n;
} FibHeap;

void consolidate(FibHeap *H);

FibHeap *makeHeap(void)
{
    FibHeap *H = malloc(sizeof(*H));
    if (H == NULL)
        return NULL;
    H->min = NULL;
    H->n = 0;
    return H;
}

FibNode *makeNode(int id, long long load)
{
    FibNode *x = malloc(sizeof(*x));
    if (x == NULL)
        return NULL;
    x->serverId = id;
    x->key = load;
    x->degree = 0;
    x->mark = 0;
    x->parent = NULL;
    x->child = NULL;
    x->left = x;
    x->right = x;
    return x;
}

static void insertAfter(FibNode *a, FibNode *x)
{
    x->right = a->right;

    x->left = a;

    a->right->left = x;
    a->right = x;
}

static void removeFromList(FibNode *x)
{
    x->left->right = x->right;

    x->right->left = x->left;
    x->left = x;

    x->right = x;
}

static int nodeLess(const FibNode *a, const FibNode *b)
{
    return a->key < b->key ||
           (a->key == b->key && a->serverId < b->serverId);
}

static void addToRootList(FibHeap *H, FibNode *x)
{
    x->parent = NULL;
    x->mark = 0;
    if (H->min == NULL) {
        x->left = x;
        x->right = x;
        H->min = x;
    } else {
        insertAfter(H->min, x);
        if (nodeLess(x, H->min))
            H->min = x;
    }
}

FibNode *fibInsert(FibHeap *H, int serverId, long long load)
{
    FibNode *x = makeNode(serverId, load);

    if (x == NULL)
    {
        return NULL;
    }

    addToRootList(H, x);
    H->n++;
    return x;
}

FibNode *fibMinimum(FibHeap *H)
{
    return (H == NULL) ? NULL : H->min;
}

FibNode *fibExtractMin(FibHeap *H)
{
    if (H == NULL || H->min == NULL)
        return NULL;
    FibNode *z = H->min;
    if (z->child != NULL) {
        FibNode *child = z->child;
        FibNode *current = child;
        do {
            FibNode *next = current->right;
            current->parent = NULL;
            current->mark = 0;
            removeFromList(current);
            addToRootList(H, current);
            current = next;
        } while (current != child);
        z->child = NULL;
        z->degree = 0;
    }

    if (z->right == z) {
        H->min = NULL;
    } else {
        H->min = z->right;
        removeFromList(z);
    }
    H->n--;
    if (H->min != NULL)
        consolidate(H);
    z->left = z;
    z->right = z;
    z->parent = NULL;
    return z;
}

void consolidate(FibHeap *H)
{
    enum { DEGREE_TABLE_SIZE = 64 };
    FibNode *table[DEGREE_TABLE_SIZE] = {0};
    FibNode **roots = NULL;
    int rootCount = 0;

    if (H->min != NULL) {
        FibNode *curr = H->min;
        do {
            rootCount++;
            curr = curr->right;
        } while (curr != H->min);

        roots = (FibNode **)malloc((size_t)rootCount * sizeof(*roots));
        if (roots == NULL)
            return;

        curr = H->min;
        for (int i = 0; i < rootCount; i++) {
            roots[i] = curr;
            curr = curr->right;
        }
    }

    for (int i = 0; i < rootCount; i++) {
        FibNode *x = roots[i];
        int degree = x->degree;
        while (table[degree] != NULL) {
            FibNode *y = table[degree];
            if (nodeLess(y, x)) {
                FibNode *temp = x;
                x = y;
                y = temp;
            }
            table[degree] = NULL;
            removeFromList(y);
            y->parent = x;
            y->mark = 0;
            if (x->child == NULL) {
                x->child = y;
            } else {
                insertAfter(x->child, y);
            }
            x->degree++;
            degree = x->degree;
        }
        table[degree] = x;
    }

    H->min = NULL;
    for (int i = 0; i < DEGREE_TABLE_SIZE; i++) {
        if (table[i] != NULL) {
            table[i]->left = table[i];
            table[i]->right = table[i];
            addToRootList(H, table[i]);
        }
    }
    free(roots);
}

void cut(FibHeap *H, FibNode *x, FibNode *y)
{
    if (x->right == x)
        y->child = NULL;
    else {
        if (y->child == x)
            y->child = x->right;
        removeFromList(x);
    }
    y->degree--;
    addToRootList(H, x);
}

void cascadingCut(FibHeap *H, FibNode *y)
{
    FibNode *z = y->parent;

    if (z == NULL)
        return;
    if (y->mark == 0)
    {

        y->mark = 1;

        /* first child loss */
    }
    else
    {

        cut(H, y, z);
        cascadingCut(H, z);
    }
}

int fibDecreaseKey(FibHeap *H, FibNode *x, long long newKey)
{
    if (H == NULL || x == NULL || newKey > x->key)
        return 0;
    x->key = newKey;

    FibNode *y = x->parent;

    if (y != NULL && nodeLess(x, y))
    {
        cut(H, x, y);

        cascadingCut(H, y);
    }

    if (H->min == NULL || nodeLess(x, H->min))
        H->min = x;
    return 1;
}

FibHeap *fibUnion(FibHeap *H1, FibHeap *H2)
{
    if (H1 == NULL)
        return H2;
    if (H2 == NULL)
        return H1;
    if (H1->min == NULL) {
        H2->n += H1->n;
        free(H1);
        return H2;
    }
    if (H2->min == NULL) {
        H1->n += H2->n;
        free(H2);
        return H1;
    }
    FibHeap *result = makeHeap();
    if (result == NULL)
        return NULL;
    result->min = nodeLess(H1->min, H2->min) ? H1->min : H2->min;
    FibNode *h1 = H1->min;
    FibNode *h2 = H2->min;
    FibNode *h1Right = h1->right;
    FibNode *h2Left = h2->left;
    h1->right = h2;
    h2->left = h1;
    h1Right->left = h2Left;
    h2Left->right = h1Right;
    result->n = H1->n + H2->n;
    free(H1);
    free(H2);
    return result;
}
