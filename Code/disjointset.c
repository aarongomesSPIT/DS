#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* =========================================================
DISJOINT SET DATA STRUCTURE
========================================================= */
int *parent;
int *size;
int N;
int totalCommunities;
int largestCommunity;

/* =========================================================
INITIALIZE / MAKE-SET
========================================================= */
void makeSet(int n)
{
    int i;
    parent = (int *)malloc((n + 1) * sizeof(int));
    size = (int *)malloc((n + 1) * sizeof(int));
    for (i = 1; i <= n; i++)
    {
        parent[i] = i;
        size[i] = 1;
    }
    totalCommunities = n;
    largestCommunity = 1;
}
/* =========================================================
BASIC FIND
Without Path Compression
========================================================= */
int findBasic(int x)
{
    while (parent[x] != x)
    {
        x = parent[x];
    }
    return x;
}
/* =========================================================
BASIC UNION
========================================================= */
void unionBasic(int a, int b)
{
    int rootA = findBasic(a);
    int rootB = findBasic(b);
    if (rootA != rootB)
    {
        parent[rootB] = rootA;
    }
}
/* =========================================================
OPTIMIZED FIND
With Path Compression
========================================================= */
int findOptimized(int x)
{
    if (parent[x] != x)
    {
        parent[x] = findOptimized(parent[x]);
    }
    return parent[x];
}
/* =========================================================
UNION BY SIZE + PATH COMPRESSION
========================================================= */
void unionBySize(int a, int b)
{
    int rootA = findOptimized(a);
    int rootB = findOptimized(b);
    if (rootA == rootB)
    {
        return;
    }
    if (size[rootA] < size[rootB])
    {
        parent[rootA] = rootB;
        size[rootB] = size[rootB] + size[rootA];
        if (size[rootB] > largestCommunity)
            largestCommunity = size[rootB];
    }
    else
    {
        parent[rootB] = rootA;
        size[rootA] = size[rootA] + size[rootB];
        if (size[rootA] > largestCommunity)
            largestCommunity = size[rootA];
    }
    totalCommunities--;
}
