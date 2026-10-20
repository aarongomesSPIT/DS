#include "atc.c"

int main(void)
{
    int flightCount;
    printf("Number of flights: ");
    if (scanf("%d", &flightCount) != 1 || flightCount < 0 || flightCount > MAX_FLIGHTS) {
        printf("Invalid flight count.\n");
        return 1;
    }

    activeSector = CREATE_SECTOR();
    if (activeSector == NULL)
        return 1;

    for (int i = 0; i < flightCount; i++) {
        long long priority;
        printf("Priority for flight %d: ", i);
        if (scanf("%lld", &priority) != 1 || !SCHEDULE_FLIGHT(activeSector, i, priority)) {
            printf("Unable to add flight %d.\n", i);
            DESTROY_SECTOR(activeSector);
            return 1;
        }
    }

    int choice = 0;
    while (choice != 7) {
        printf("\n1. Schedule flight\n2. Next to land\n3. Reprioritize\n"
               "4. Merge tower\n5. Current priority flight\n6. Cancel flight\n"
               "7. Exit\nChoice: ");
        if (scanf("%d", &choice) != 1)
            break;

        switch (choice) {
        case 1: {
            int id;
            long long priority;
            printf("Flight ID and priority: ");
            scanf("%d %lld", &id, &priority);
            printf(SCHEDULE_FLIGHT(activeSector, id, priority)
                   ? "Flight scheduled.\n"
                   : "Invalid or already scheduled flight ID.\n");
            break;
        }
        case 2: {
            FibNode *node = NEXT_TO_LAND(activeSector);
            if (node == NULL)
                printf("No flights in queue.\n");
            else {
                printf("Flight %d cleared to land (priority %lld).\n", node->serverId, node->key);
                free(node);
            }
            break;
        }
        case 3: {
            int id;
            long long priority;
            printf("Flight ID and new lower priority: ");
            scanf("%d %lld", &id, &priority);
            printf(REPRIORITIZE(id, priority)
                   ? "Priority updated.\n"
                   : "Invalid flight or priority not lower.\n");
            break;
        }
        case 4: {
            FibHeap *other = CREATE_SECTOR();
            int id;
            long long priority;
            printf("Other sector flight ID and priority (use -1 to finish):\n");
            while (scanf("%d", &id) == 1 && id != -1) {
                scanf("%lld", &priority);
                if (!SCHEDULE_FLIGHT(other, id, priority))
                    printf("Unable to add flight %d.\n", id);
            }
            activeSector = MERGE_TOWER(activeSector, other);
            printf("Towers merged.\n");
            break;
        }
        case 5: {
            FibNode *node = CURRENT_PRIORITY_FLIGHT(activeSector);
            if (node == NULL)
                printf("No flights in queue.\n");
            else
                printf("Most urgent flight: %d (priority %lld).\n", node->serverId, node->key);
            break;
        }
        case 6: {
            int id;
            printf("Flight ID: ");
            scanf("%d", &id);
            printf(CANCEL_FLIGHT(id) ? "Flight cancelled.\n" : "Invalid flight ID.\n");
            break;
        }
        case 7:
            break;
        default:
            printf("Invalid choice.\n");
        }
    }

    DESTROY_SECTOR(activeSector);
    return 0;
}