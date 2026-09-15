#include <stdio.h>
#include <stdlib.h>
#include "GraphAdjList.c"
#include <string.h>

Graph *graph;

void CreateNetwork()
{
    printf("Enter the number of delivery centers in the network: ");
    int vertices;
    scanf("%d", &vertices);

    graph = createGraph(vertices);
}

void AddTransportRoutes()
{
    printf("Enter the number of transport routes to add: ");
    int edges;
    scanf("%d", &edges);

    for (int i = 0; i < edges; i++)
    {
        int src, dest;
        printf("Enter the source and destination delivery centers for route %d: ", i + 1);
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }
}

void DisplayNetwork()
{
    printf("Delivery Network Adjacency List:\n");
    displayGraph(graph);
}

void TraverseNetworkDFS()
{
    printf("Enter the starting delivery center for DFS traversal: ");
    int startVertex;
    scanf("%d", &startVertex);

    int visited[graph->vertices];
    memset(visited, 0, sizeof(visited));

    printf("DFS Traversal starting from delivery center %d: ", startVertex);
    DFS(graph, startVertex, visited);
    printf("\n");
}

void TraverseNetworkBFS()
{
    printf("Enter the starting delivery center for BFS traversal: ");
    int startVertex;
    scanf("%d", &startVertex);

    printf("BFS Traversal starting from delivery center %d: ", startVertex);
    BFS(graph, startVertex);
    printf("\n");
}