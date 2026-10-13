#include "fibonacciHeap.c"

ADD_SERVER(S,load)
ALLOCATE_REQUEST()
UPDATE_LOAD(S,newLoad)
MERGE_REGIONS(C1,C2)
LEAST_LOADED_SERVER()
DECOMMISSION_SERVER(S)



#define MAX_SERVERS 100000
FibNode *nodeById[MAX_SERVERS];
/* After successful insertion: */

int lookupServerById(int serverId) {
    if (serverId < 0 || serverId >= MAX_SERVERS) {
        return -1; /* Invalid ID */
    }
    FibNode *node = nodeById[serverId];
    if (node == NULL) {
        return -1; /* Server not found */
    }
    return 0; /* Success */
}
/* Before decrease or decommission: */
if (serverId < 0 || serverId >= MAX_SERVERS ||
nodeById[serverId] == NULL) {
printf("Invalid or inactive server ID\\n");
} else {
/* pass nodeById[serverId] to decrease-key */
}
/* Set nodeById[serverId] = NULL after permanent removal. */