#include "fibonacciHeap.c"

#define MAX_FLIGHTS 100000
FibNode *nodeById[MAX_FLIGHTS];

FibHeap *activeSector;

int validFlightId(int flightId)
{
    return flightId >= 0 && flightId < MAX_FLIGHTS;
}

FibHeap *CREATE_SECTOR(void)
{
    return makeHeap();
}

int SCHEDULE_FLIGHT(FibHeap *sector, int flightId, long long priority)
{
    if (sector == NULL || !validFlightId(flightId) || nodeById[flightId] != NULL)
        return 0;

    FibNode *node = makeNode(flightId, priority);
    if (node == NULL)
        return 0;
    addToRootList(sector, node);
    sector->n++;
    nodeById[flightId] = node;
    return 1;
}

FibNode *NEXT_TO_LAND(FibHeap *sector)
{
    FibNode *node = fibExtractMin(sector);
    if (node != NULL && validFlightId(node->serverId))
        nodeById[node->serverId] = NULL;
    return node;
}

int REPRIORITIZE(int flightId, long long newPriority)
{
    if (!validFlightId(flightId) || nodeById[flightId] == NULL)
        return 0;
    return fibDecreaseKey(activeSector, nodeById[flightId], newPriority);
}

FibHeap *MERGE_TOWER(FibHeap *sector1, FibHeap *sector2)
{
    FibHeap *merged = fibUnion(sector1, sector2);
    if (merged != NULL)
        activeSector = merged;
    return merged;
}

FibNode *CURRENT_PRIORITY_FLIGHT(FibHeap *sector)
{
    return fibMinimum(sector);
}

int CANCEL_FLIGHT(int flightId)
{
    if (!validFlightId(flightId) || nodeById[flightId] == NULL)
        return 0;
    if (!fibDecreaseKey(activeSector, nodeById[flightId], LLONG_MIN))
        return 0;
    FibNode *node = NEXT_TO_LAND(activeSector);
    if (node == NULL)
        return 0;
    free(node);
    return 1;
}

void DESTROY_SECTOR(FibHeap *sector)
{
    FibNode *node;
    if (sector == NULL)
        return;
    while ((node = fibExtractMin(sector)) != NULL)
        free(node);
    free(sector);
}