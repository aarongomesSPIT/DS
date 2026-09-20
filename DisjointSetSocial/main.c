#include <stdio.h>
#include <stdlib.h>
#include "social.c"


/* =========================================================
MENU
========================================================= */
void menu()
{
    int choice;
    int A, B;
    do
    {
        printf("\n============================================\n");
        printf(" SOCIAL NETWORK COMMUNITY DETECTION\n");
        printf("============================================\n");
        printf("1. FRIEND(A,B)\n");
        printf("2. CONNECTED(A,B)\n");
        printf("3. COMMUNITY-SIZE(A)\n");
        printf("4. TOTAL-COMMUNITIES()\n");
        printf("5. LARGEST-COMMUNITY()\n");
        printf("6. PERFORMANCE TEST\n");
        printf("7. EXIT\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter User A and User B: ");
            scanf("%d %d", &A, &B);
            friendUsers(A, B);
            break;
        case 2:
            printf("Enter User A and User B: ");
            scanf("%d %d", &A, &B);
            connected(A, B);
            break;
        case 3:
            printf("Enter User ID: ");
            scanf("%d", &A);
            communitySize(A);
            break;
        case 4:
            totalCommunitiesCount();
            break;
        case 5:
            largestCommunitySize();
            break;
        case 6:
            performanceTest();
            break;
        case 7:
            printf("Exiting program...\n");
            break;
        default:
            printf("Invalid choice.\n");
        }
    }
    while (choice != 7);
}

int main()
{
    int n;
    printf("Enter the number of users: ");
    scanf("%d", &n);
    N = n;
    makeSet(N);
    menu();
    free(parent);
    free(size);
    return 0;
}