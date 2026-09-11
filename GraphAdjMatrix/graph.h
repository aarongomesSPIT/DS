#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#define V 20
#define MAXQ 100

// Global variables
int graph[V][V];
int visited[V];
int n;

// Queue for BFS
int queue[MAXQ];
int front = -1;
int rear = -1;

int enqueue(int element);
int dequeue();
int isEmpty();
void initializeGraph();

#endif // GRAPH_H_INCLUDED
