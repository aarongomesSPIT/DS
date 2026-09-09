#include <stdio.h>
#include "queue.h"
#define V 20
#define MAXQ 100

// Global variables
int graph[V][V];
int visited[V];
int n;
// Queue for BFS
int queue[V];
int front = -1;
int rear = -1;
// Function to enqueue an element

// Function to dequeue an element

// Function to check whether queue is empty

// Function to initialize adjacency matrix
void initializeGraph()
{
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            graph[i][j] = 1;
            graph[j][i] = 1;
        }
    }
}
// Function to add an undirected edge
void addEdge(int graph[V][V], int i, int j) {

    // Since the graph is undirected
    graph[i][j] = 1;
    graph[j][i] = 1;
}

// Function to display adjacency matrix
void displayMatrix(int graph[V][V]) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++)
            printf("%d ", graph[i][j]); // Display matrix element
        printf("\n");
    }
}

// DFS function
void dfsRec(int graph[V][V], int visited[V], int s, int res[V], int *idx) {
    visited[s] = 1;
    res[(*idx)++] = s;

    // Recursively visit all adjacent vertices
    // that are not visited yet
    for (int i = 0; i < V; i++) {
        if (graph[s][i] && visited[i] == 0)
            dfsRec(graph, visited, i, res, idx);
    }
}

void dfs(int graph[V][V], int res[V]) {
    int visited[V] = {0};
    int idx = 0;
    dfsRec(graph, visited, 0, res, &idx);
}

// BFS function
void bfs(int graph[V][V], int res[V], int *resSize) {
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
































// Main function
int main()
{
// Declare required variables
    int edges;
    int source, destination;
    int start;
    int choice;
// Input number of vertices
    statement;
// Initialize graph
    function_call;
// Input number of edges
    statement;
// Read edges
    for (initialization; condition; increment)
    {
// Input source and destination
        statement;
// Validate vertices
        if (condition)
        {
// Add edge
            function_call;
        }
        else
        {
// Display invalid input message
            statement;
        }
    }
// Menu loop
    do
    {
// Display menu
        statement;
// Accept user's choice
        statement;
// Menu selection
        switch (variable)
        {
        case 1:
// Display adjacency matrix
            function_call;
            break;
        case 2:
// Accept starting vertex
            statement;
// Validate starting vertex
            if (condition)
            {
// Reset visited array
                for (initialization; condition; increment)
                {
                    statement;
                }
// Perform DFS
                function_call;
            }
            else
            {
// Invalid vertex
                statement;
            }
            break;
        case 3:
// Accept starting vertex
            statement;
// Validate starting vertex
            if (condition)
            {
// Perform BFS
                function_call;
            }
            else
            {
// Invalid vertex
                statement;
            }
            break;
        case 4:
// Exit message
            statement;
            break;
        default:
// Invalid menu choice
            statement;
        }
    }
    while (condition);
    return 0;
}
