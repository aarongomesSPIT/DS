#ifndef GRAPHADJLIST_H_INCLUDED
#define GRAPHADJLIST_H_INCLUDED

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

Graph* createGraph(int vertices);
Node* createNode(int vertex);
void addEdge(Graph *graph, int src, int dest);
void displayGraph(Graph *graph);
void DFS(Graph *graph, int vertex, int visited[]);
void BFS(Graph *graph, int startVertex);

#endif // GRAPHADJLIST_H_INCLUDED
