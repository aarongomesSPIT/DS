#include <stdio.h>
#include "graph.h"

// Function to enqueue an element
int enqueue(int element)
{
    if (rear == MAXQ - 1)
    {
        printf("Queue overflow\n");
        return -1;
    }
    else
    {
        if (front == -1)
            front = 0;
        rear++;
        queue[rear] = element;
        return 0;
    }
}
// Function to dequeue an element
int dequeue()
{
    if (front == -1)
    {
        printf("Queue underflow\n");
        return -1;
    }
    else
    {
        int element = queue[front];
        if (front == rear)
        {
            front = -1;
            rear = -1;
        }
        else
        {
            front++;
        }
        return element;
    }
}
// Function to check whether queue is empty
int isEmpty()
{
    if (front == -1)
        return 1;
    else
        return 0;
}
// Function to initialize adjacency matrix
void initializeGraph()
{
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            graph[i][j] = 0;
            graph[j][i] = 0;
        }
    }
}
// Function to add an undirected edge
void addEdge(int i, int j) {

    // Since the graph is undirected
    graph[i][j] = 1;
    graph[j][i] = 1;
}

// Function to display adjacency matrix
void displayMatrix() {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++)
            printf("%d ", graph[i][j]); // Display matrix element
        printf("\n");
    }
}

// DFS function
void dfsRec(int visited[V], int s, int res[V], int *idx) {
    visited[s] = 1;
    res[(*idx)++] = s;

    // Recursively visit all adjacent vertices
    // that are not visited yet
    for (int i = 0; i < V; i++) {
        if (graph[s][i] && visited[i] == 0)
            dfsRec(visited, i, res, idx);
    }
}

void dfs(int res[V]) {
    int visited[V] = {0};
    int idx = 0;
    dfsRec(visited, 0, res, &idx);
}

// BFS function
void bfs(int res[V], int *resSize) {
    int visited[V] = {0};
    int q[MAXQ];
    int front = 0, rear = 0;
    int src = 0;
    visited[src] = 1;
    q[rear++] = src;

    while (front < rear) {
        int curr = q[front++];
        res[(*resSize)++] = curr;

        // visit all the unvisited
        // neighbours of current node
        for (int x = 0; x < V; x++) {
            if (graph[curr][x] && !visited[x]) {
                visited[x] = 1;
                q[rear++] = x;
            }
        }
    }
}