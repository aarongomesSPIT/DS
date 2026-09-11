#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#define V 20
#define MAXQ 100



int enqueue(int element);
int dequeue();
int isEmpty();
void initializeGraph(int vertices);
int getVertexCount();
int isValidVertex(int vertex);
int addEdge(int i, int j);
void displayMatrix();
void dfsRec(int visited[V], int s, int res[V], int *idx);
void dfs(int start, int res[V], int *resSize);
void bfs(int start, int res[V], int *resSize);


#endif // GRAPH_H_INCLUDED
