#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int vertex;
    struct Node *next;
} Node;

typedef struct Graph {
    int vertices;
    Node **adjList;
} Graph;

Node *createNode(int vertex) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

Graph *createGraph(int vertices) {
    if (vertices <= 0) {
        printf("Number of vertices must be greater than zero.\n");
        return NULL;
    }

    Graph *graph = (Graph *)malloc(sizeof(Graph));
    if (graph == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    graph->vertices = vertices;
    graph->adjList = (Node **)malloc(vertices * sizeof(Node *));
    if (graph->adjList == NULL) {
        printf("Memory allocation failed.\n");
        free(graph);
        exit(1);
    }

    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
    }

    return graph;
}

int isValidVertex(Graph *graph, int vertex) {
    return graph != NULL && vertex >= 0 && vertex < graph->vertices;
}

int hasEdge(Graph *graph, int src, int dest) {
    Node *temp = graph->adjList[src];
    while (temp != NULL) {
        if (temp->vertex == dest) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

void addEdge(Graph *graph, int src, int dest) {
    if (graph == NULL || !isValidVertex(graph, src) || !isValidVertex(graph, dest) || src == dest) {
        printf("Invalid edge.\n");
        return;
    }

    if (hasEdge(graph, src, dest)) {
        return;
    }

    Node *newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

void displayGraph(Graph *graph) {
    if (graph == NULL) {
        printf("Graph is not created yet.\n");
        return;
    }

    printf("\nAdjacency List:\n");
    for (int i = 0; i < graph->vertices; i++) {
        Node *temp = graph->adjList[i];
        printf("%d -> ", i);
        while (temp != NULL) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

void DFS(Graph *graph, int vertex, int visited[]) {
    if (graph == NULL || !isValidVertex(graph, vertex)) {
        return;
    }

    visited[vertex] = 1;
    printf("%d ", vertex);

    Node *temp = graph->adjList[vertex];
    while (temp != NULL) {
        int connectedVertex = temp->vertex;
        if (!visited[connectedVertex]) {
            DFS(graph, connectedVertex, visited);
        }
        temp = temp->next;
    }
}

void BFS(Graph *graph, int startVertex) {
    if (graph == NULL || !isValidVertex(graph, startVertex)) {
        printf("Invalid starting vertex.\n");
        return;
    }

    int *visited = (int *)calloc(graph->vertices, sizeof(int));
    int *queue = (int *)malloc(graph->vertices * sizeof(int));

    if (visited == NULL || queue == NULL) {
        printf("Memory allocation failed.\n");
        free(visited);
        free(queue);
        return;
    }

    int front = 0;
    int rear = 0;
    visited[startVertex] = 1;
    queue[rear++] = startVertex;

    printf("BFS traversal from vertex %d: ", startVertex);
    while (front < rear) {
        int vertex = queue[front++];
        printf("%d ", vertex);

        Node *temp = graph->adjList[vertex];
        while (temp != NULL) {
            int connectedVertex = temp->vertex;
            if (!visited[connectedVertex]) {
                visited[connectedVertex] = 1;
                queue[rear++] = connectedVertex;
            }
            temp = temp->next;
        }
    }
    printf("\n");

    free(visited);
    free(queue);
}
