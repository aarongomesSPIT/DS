#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GraphAdjList.c"

Graph *graph = NULL;

int CreateNetwork() {
    int vertices;
    printf("Enter the number of delivery centers in the network: ");
    if (scanf("%d", &vertices) != 1 || vertices <= 0) {
        printf("Invalid number of delivery centers.\n");
        return 0;
    }

    graph = createGraph(vertices);
    if (graph == NULL) {
        return 0;
    }

    return 1;
}

void AddTransportRoutes() {
    if (graph == NULL) {
        printf("Create the network first.\n");
        return;
    }

    int edges;
    printf("Enter the number of transport routes to add: ");
    if (scanf("%d", &edges) != 1 || edges < 0) {
        printf("Invalid number of routes.\n");
        return;
    }

    for (int i = 0; i < edges; i++) {
        int src, dest;
        printf("Enter the source and destination delivery centers for route %d: ", i + 1);
        if (scanf("%d %d", &src, &dest) != 2) {
            printf("Invalid route input.\n");
            return;
        }
        addEdge(graph, src, dest);
    }
}

void DisplayNetwork() {
    printf("Delivery Network Adjacency List:\n");
    displayGraph(graph);
}

void TraverseNetworkDFS() {
    if (graph == NULL) {
        printf("Create the network first.\n");
        return;
    }

    int startVertex;
    printf("Enter the starting delivery center for DFS traversal: ");
    if (scanf("%d", &startVertex) != 1 || !isValidVertex(graph, startVertex)) {
        printf("Invalid starting vertex.\n");
        return;
    }

    int *visited = (int *)calloc(graph->vertices, sizeof(int));
    if (visited == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("DFS Traversal starting from delivery center %d: ", startVertex);
    DFS(graph, startVertex, visited);
    printf("\n");

    free(visited);
}

void TraverseNetworkBFS() {
    if (graph == NULL) {
        printf("Create the network first.\n");
        return;
    }

    int startVertex;
    printf("Enter the starting delivery center for BFS traversal: ");
    if (scanf("%d", &startVertex) != 1 || !isValidVertex(graph, startVertex)) {
        printf("Invalid starting vertex.\n");
        return;
    }

    BFS(graph, startVertex);
}