#include <stdio.h>
#include <stdlib.h>
#include "disjointset.c"

/* =========================================================
CHECK VALID USER
========================================================= */
int validUser(int user)
{
    if (user >= 1 && user <= N)
        return 1;
    return 0;
}
/* =========================================================
FRIEND(A,B)
========================================================= */
void friendUsers(int A, int B)
{
    int rootA, rootB;
    if (!validUser(A) || !validUser(B))
    {
        printf("Invalid User ID.\n");
        return;
    }
    rootA = findOptimized(A);
    rootB = findOptimized(B);
    if (rootA == rootB)
    {
        printf("Users are already in the same community.\n");
        return;
    }
    unionBySize(A, B);
    printf("Friendship established successfully.\n");
}
/* =========================================================
CONNECTED(A,B)
========================================================= */
void connected(int A, int B)
{
    if (!validUser(A) || !validUser(B))
    {
        printf("Invalid User ID.\n");
        return;
    }
    if (findOptimized(A) == findOptimized(B))
    {
        printf("Users belong to the same community.\n");
    }
    else
    {
        printf("Users belong to different communities.\n");
    }
}
/* =========================================================
COMMUNITY-SIZE(A)
========================================================= */
void communitySize(int A)
{
    int root;
    if (!validUser(A))
    {
        printf("Invalid User ID.\n");
        return;
    }
    root = findOptimized(A);
    printf("Community Size = %d\n", size[root]);
}
/* =========================================================
TOTAL-COMMUNITIES()
========================================================= */
void totalCommunitiesCount()
{
    printf("Total Communities = %d\n", totalCommunities);
}
/* =========================================================
LARGEST-COMMUNITY()
========================================================= */
void largestCommunitySize()
{
    printf("Largest Community = %d\n", largestCommunity);
}
/* =========================================================
RANDOM USER
========================================================= */
int randomUser()
{
    return rand() % N + 1;
}
/* =========================================================
GENERATE RANDOM FRIENDSHIP
========================================================= */
void randomFriendship()
{
    int A, B;
    A = randomUser();
    B = randomUser();
    while (A == B)
    {
        B = randomUser();
    }
    unionBySize(A, B);
}
/* =========================================================
PERFORMANCE TEST
At least 100000 friendship operations
========================================================= */
void performanceTest()
{
    int operations = 100000;
    int i;
    int A, B;
    clock_t start, end;
    double basicTime, optimizedTime;
    printf("\n============================================\n");
    printf(" PERFORMANCE COMPARISON\n");
    printf("============================================\n");
    printf("Number of Users = %d\n", N);
    printf("Friendship Operations = %d\n", operations);
    /* -----------------------------------------------------
    BASIC IMPLEMENTATION
    ----------------------------------------------------- */
    makeSet(N);
    start = clock();
    for (i = 0; i < operations; i++)
    {
        A = randomUser();
        B = randomUser();
        while (A == B)
        {
            B = randomUser();
        }
        unionBasic(A, B);
    }
    end = clock();
    basicTime =
        ((double)(end - start)) / CLOCKS_PER_SEC;
    free(parent);
    free(size);
    /* -----------------------------------------------------
    OPTIMIZED IMPLEMENTATION
    ----------------------------------------------------- */
    makeSet(N);
    start = clock();
    for (i = 0; i < operations; i++)
    {
        A = randomUser();
        B = randomUser();
        while (A == B)
        {
            B = randomUser();
        }
        unionBySize(A, B);
    }
    end = clock();
    optimizedTime =
        ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nBasic Union-Find Time = %.6f seconds\n",
           basicTime);
    printf("Optimized Union-Find Time = %.6f seconds\n",
           optimizedTime);
    printf("\nOptimization uses:\n");
    printf("1. Union by Size\n");
    printf("2. Path Compression\n");
    free(parent);
    free(size);
}