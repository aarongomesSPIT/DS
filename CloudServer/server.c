#include "fibonacciHeap.c"

#define MAX_SERVERS 100000
FibNode *nodeById[MAX_SERVERS];

static FibHeap *activeCluster;

static int validServerId(int serverId)
{
    return serverId >= 0 && serverId < MAX_SERVERS;
}

int lookupServerById(int serverId) {
    if (!validServerId(serverId))
        return -1;
    FibNode *node = nodeById[serverId];
    return node == NULL ? -1 : 0;
}

FibHeap *CREATE_REGION(void)
{
    return makeHeap();
}

int ADD_SERVER(FibHeap *cluster, int serverId, long long load)
{
    if (cluster == NULL || !validServerId(serverId) || nodeById[serverId] != NULL)
        return 0;

    FibNode *node = makeNode(serverId, load);
    if (node == NULL)
        return 0;
    addToRootList(cluster, node);
    cluster->n++;
    nodeById[serverId] = node;
    return 1;
}

FibNode *ALLOCATE_REQUEST(FibHeap *cluster)
{
    FibNode *node = fibExtractMin(cluster);
    if (node != NULL && validServerId(node->serverId))
        nodeById[node->serverId] = NULL;
    return node;
}

int UPDATE_LOAD(int serverId, long long newLoad)
{
    if (lookupServerById(serverId) != 0)
        return 0;
    return fibDecreaseKey(activeCluster, nodeById[serverId], newLoad);
}

FibHeap *MERGE_REGIONS(FibHeap *cluster1, FibHeap *cluster2)
{
    FibHeap *merged = fibUnion(cluster1, cluster2);
    if (merged != NULL)
        activeCluster = merged;
    return merged;
}

FibNode *LEAST_LOADED_SERVER(FibHeap *cluster)
{
    return fibMinimum(cluster);
}

int DECOMMISSION_SERVER(int serverId)
{
    FibNode *node;
    if (lookupServerById(serverId) != 0)
        return 0;
    node = nodeById[serverId];
    if (!fibDecreaseKey(activeCluster, node, LLONG_MIN))
        return 0;
    node = ALLOCATE_REQUEST(activeCluster);
    if (node == NULL)
        return 0;
    free(node);
    return 1;
}

void DESTROY_SERVER_HEAP(FibHeap *cluster)
{
    FibNode *node;
    if (cluster == NULL)
        return;
    while ((node = fibExtractMin(cluster)) != NULL)
        free(node);
    free(cluster);
}

void setActiveCluster(FibHeap *cluster)
{
    activeCluster = cluster;
}