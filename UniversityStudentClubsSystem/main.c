#include "club.c"

int main()
{
	int count;
	int choice;
	int first;
	int second;

	printf("Enter number of students: ");
	if (scanf("%d", &count) != 1 || count < 1)
	{
		printf("Invalid number of students.\n");
		return 1;
	}

	makeSet(count);

	do
	{
		printf("\n1. Merge clubs\n");
		printf("2. Check same network\n");
		printf("3. Display club size\n");
		printf("4. Display total networks\n");
		printf("5. Exit\n");
		printf("Enter choice: ");

		if (scanf("%d", &choice) != 1)
			break;

		switch (choice)
		{
		case 1:
			printf("Enter two student IDs: ");
			scanf("%d %d", &first, &second);
			if (!validStudent(first) || !validStudent(second))
				printf("Invalid student ID. IDs must be from 1 to %d.\n", N);
			else
				MERGE(first, second);
			break;

		case 2:
			printf("Enter two student IDs: ");
			scanf("%d %d", &first, &second);
			if (!validStudent(first) || !validStudent(second))
				printf("Invalid student ID. IDs must be from 1 to %d.\n", N);
			else
				SAME_NETWORK(first, second);
			break;

		case 3:
			printf("Enter student ID: ");
			scanf("%d", &first);
			if (!validStudent(first))
				printf("Invalid student ID. IDs must be from 1 to %d.\n", N);
			else
				CLUB_SIZE(first);
			break;

		case 4:
			TOTAL_NETWORKS();
			break;

		case 5:
			break;

		default:
			printf("Invalid choice.\n");
		}
	} while (choice != 5);

	free(parent);
	free(size);
	return 0;
}