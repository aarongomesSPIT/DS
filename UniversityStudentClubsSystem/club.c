#include "disjointset.c"

int validStudent(int student)
{
	return student >= 1 && student <= N;
}

void MERGE(int first, int second)
{
	if (findOptimized(first) == findOptimized(second))
	{
		printf("Students are already in the same network.\n");
		return;
	}

	unionBySize(first, second);
	printf("Networks merged successfully.\n");
}

void SAME_NETWORK(int first, int second)
{
	if (findOptimized(first) == findOptimized(second))
		printf("Yes, they belong to the same network.\n");
	else
		printf("No, they belong to different networks.\n");
}

void CLUB_SIZE(int student)
{
	printf("Club network size: %d\n", size[findOptimized(student)]);
}

void TOTAL_NETWORKS(void)
{
	printf("Total club networks: %d\n", totalCommunities);
}