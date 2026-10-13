#include "server.c"

int main(void)
{
	int serverCount;
	printf("Number of servers: ");
	if (scanf("%d", &serverCount) != 1 || serverCount < 0 || serverCount > MAX_SERVERS) {
		printf("Invalid server count.\n");
		return 1;
	}

	activeCluster = CREATE_REGION();
	if (activeCluster == NULL)
		return 1;

	for (int i = 0; i < serverCount; i++) {
		long long load;
		printf("Load for server %d: ", i);
		if (scanf("%lld", &load) != 1 || !ADD_SERVER(activeCluster, i, load)) {
			printf("Unable to add server %d.\n", i);
			DESTROY_SERVER_HEAP(activeCluster);
			return 1;
		}
	}

	for (;;) {
		int choice;
		printf("\n1. Add server\n2. Allocate request\n3. Update load\n"
			   "4. Merge regions\n5. Least-loaded server\n6. Decommission server\n"
			   "7. Exit\nChoice: ");
		if (scanf("%d", &choice) != 1)
			break;

		if (choice == 1) {
			int id;
			long long load;
			printf("Server ID and load: ");
			scanf("%d %lld", &id, &load);
			printf(ADD_SERVER(activeCluster, id, load) ? "Server added.\n" : "Invalid or active server ID.\n");
		} else if (choice == 2) {
			FibNode *node = ALLOCATE_REQUEST(activeCluster);
			if (node == NULL)
				printf("No active servers.\n");
			else {
				printf("Allocated server %d (load %lld).\n", node->serverId, node->key);
				free(node);
			}
		} else if (choice == 3) {
			int id;
			long long load;
			printf("Server ID and new lower load: ");
			scanf("%d %lld", &id, &load);
			printf(UPDATE_LOAD(id, load) ? "Load updated.\n" : "Invalid server or load.\n");
		} else if (choice == 4) {
			FibHeap *other = CREATE_REGION();
			int id;
			long long load;
			printf("Other region server ID and load (use -1 to finish):\n");
			while (scanf("%d", &id) == 1 && id != -1) {
				scanf("%lld", &load);
				if (!ADD_SERVER(other, id, load))
					printf("Unable to add server %d.\n", id);
			}
			activeCluster = MERGE_REGIONS(activeCluster, other);
			printf("Regions merged.\n");
		} else if (choice == 5) {
			FibNode *node = LEAST_LOADED_SERVER(activeCluster);
			if (node == NULL)
				printf("No active servers.\n");
			else
				printf("Least-loaded server: %d (load %lld).\n", node->serverId, node->key);
		} else if (choice == 6) {
			int id;
			printf("Server ID: ");
			scanf("%d", &id);
			printf(DECOMMISSION_SERVER(id) ? "Server decommissioned.\n" : "Invalid server ID.\n");
		} else if (choice == 7) {
			break;
		} else {
			printf("Invalid choice.\n");
		}
	}

	DESTROY_SERVER_HEAP(activeCluster);
	return 0;
}