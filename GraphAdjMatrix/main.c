#include <stdio.h>
#include <stdlib.h>
#include "navigation.h"

void printMenu();
void printTraversal(const char *name, int start, int result[], int resultSize);

int main()
{
    printf("---- Smart Campus Navigation System ----!\n");
    int mapType;
    printf("Select the type of map:\n");
    printf("1. Campus Map\n");
    printf("2. Custom Map\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &mapType);
    if (mapType == 1) {
        startCampusMap();
        printf("You have selected the Campus Map.\n");
    } 
    else if (mapType == 2) {
        if (!startCustomMap())
            return 1;
        printf("You have selected the Custom Map.\n");
    } else {
        printf("Invalid choice. Exiting the program.\n");
        return 1;
    }
    int choice = 0;
    while (choice != 4)
    {
        printMenu();
        printf("Enter your choice (1-4): ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number from 1 to 4.\n");
            while (getchar() != '\n')
                ;
            continue;
        }

        int start;
        int result[V];
        int resultSize = 0;

        switch (choice)
        {
        case 1:
            displayMatrix();
            break;
        case 2:
        case 3:
            printf("Enter starting vertex (0-%d): ", getVertexCount() - 1);
            if (scanf("%d", &start) != 1)
            {
                printf("Invalid vertex input.\n");
                while (getchar() != '\n')
                    ;
                break;
            }
            if (!isValidVertex(start))
            {
                printf("Invalid vertex number.\n");
                break;
            }
            if (choice == 2)
            {
                dfs(start, result, &resultSize);
                printTraversal("DFS", start, result, resultSize);
            }
            else
            {
                bfs(start, result, &resultSize);
                printTraversal("BFS", start, result, resultSize);
            }
            break;
        case 4:
            printf("Exiting the application.\n");
            break;
        default:
            printf("Invalid menu selection. Please choose a number from 1 to 4.\n");
        }
    }
    return 0;
}

void printMenu()
{
    printf("\n--- Menu ---\n");
    printf("1. Display Adjacency Matrix\n");
    printf("2. Perform Depth-First Search (DFS)\n");
    printf("3. Perform Breadth-First Search (BFS)\n");
    printf("4. Exit\n");
}

void printTraversal(const char *name, int start, int result[], int resultSize)
{
    printf("%s traversal from vertex %d: ", name, start);
    for (int i = 0; i < resultSize; i++)
        printf("%d%s", result[i], i == resultSize - 1 ? "\n" : " -> ");
}