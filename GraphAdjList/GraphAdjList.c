#include <stdio.h>
#include <stdlib.h>

// Node of Adjacency List
typedef struct Node {
    int vertex;
    struct Node *next;
} Node;

// Graph structure
typedef struct Graph {
    int vertices;
    struct Node **adjList;
} Graph;


// Create a new node
Node* createNode(int vertex) {
    Node *newNode =
        (Node*)malloc(sizeof(Node));

    newNode->vertex = vertex;
    newNode->next = NULL;

    return newNode;
}
// Create Graph
Graph* createGraph(int vertices) {
    Graph *graph =
        (Graph*)malloc(sizeof(Graph));

    graph->vertices = vertices;

    // Create an array of adjacency lists. Size of array will be equal to number of vertices
    graph->adjList =
        (Node**)malloc(vertices * sizeof(Node*));

    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
    }

    return graph;
}

// Add Edge - Undirected Graph
void addEdge(Graph *graph, int src, int dest) {

    // Add destination to source
    Node *newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    // Add source to destination
    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}
// Display Adjacency List
void displayGraph(Graph *graph) {

    printf("\nAdjacency List:\n");

    for (int i = 0; i < graph->vertices; i++) {

        struct Node *temp = graph->adjList[i];

        printf("%d -> ", i);

        while (temp != NULL) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }

        printf("NULL\n");
    }
}

// DFS
void DFS(Graph *graph, int vertex, int visited[]) {

    visited[vertex] = 1;

    printf("%d ", vertex);

    Node *temp = graph->adjList[vertex];

    while (temp != NULL) {

        int connectedVertex = temp->vertex;

        if (visited[connectedVertex] == 0) {
            DFS(graph, connectedVertex, visited);
        }

        temp = temp->next;
    }
}

// BFS
void BFS(Graph *graph, int startVertex) {

    int visited[graph->vertices];

    for (int i = 0; i < graph->vertices; i++) {
        visited[i] = 0;
    }

    int queue[graph->vertices];

    int front = 0;
    int rear = 0;

    visited[startVertex] = 1;

    queue[rear++] = startVertex;

    while (front < rear) {

        int vertex = queue[front++];

        printf("%d ", vertex);

        Node *temp = graph->adjList[vertex];

        while (temp != NULL) {

            int connectedVertex = temp->vertex;

            if (visited[connectedVertex] == 0) {

                visited[connectedVertex] = 1;

                queue[rear++] = connectedVertex;
            }

            temp = temp->next;
        }
    }
}
