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

/* TODO: addToRootList(H, x)

If H->min == NULL, x becomes the only root and H->min.

Otherwise splice x into the root list and update H->min if needed.

*/

void fibInsert(FibHeap *H, int serverId, long long load)
{
    FibNode *x = makeNode(serverId, load);

    if (x == NULL)
    { /* TODO: report allocation failure */
        return;
    }

    /* TODO: addToRootList(H, x); */
    H->n++;
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
    /* TODO A: promote each child of z into the root list:
    detach child; set child->parent = NULL;
    add child to roots; clear child->mark.
    */
    /* TODO B: remove z from the root list. */
    /* TODO C: if roots remain, call consolidate(H). */
    /* TODO D: otherwise set H->min = NULL. */
    H->n--;
    /* TODO E: detach z safely and return it. */
    return z;
}

void consolidate(FibHeap *H)
{
    /* TODO:
    1.

    Initialize a temporary degree table A[] to NULL.

    2.

    Visit each root x.

    3.

    While A[x->degree] contains a root y:

    -

    keep the smaller-key root as parent

    -

    link the other root under it

    -

    increment parent degree; clear child mark

    -

    continue with the new degree

    4.

    Rebuild the root list from A[].

    5.

    Recompute H->min.

    */
}

void cut(FibHeap *H, FibNode *x, FibNode *y)
{

    /* TODO:

    remove x from y's child list;
    update y->child if it points to x;
    decrement y->degree;

    add x to H's root list;

    set x->parent = NULL and x->mark = 0.

    */
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

    if (y != NULL && x->key < y->key)
    {
        cut(H, x, y);

        cascadingCut(H, y);
    }

    /* TODO: update H->min if x is now the smallest. */
    return 1;
}

FibHeap *fibUnion(FibHeap *H1, FibHeap *H2)
{
    if (H1 == NULL)
        return H2;
    if (H2 == NULL)
        return H1;
    /* TODO: create result heap H.
    - concatenate root lists in O(1)
    - set H->min to the smaller non-NULL minimum
    - set H->n = H1->n + H2->n
    - return H
    Decide whether H1 and H2 are consumed by this operation.
    */
    return NULL; /* replace after implementing */
}
