#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "navigation.h"

void printMenu(); 


 
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
        startCustomMap();
        printf("You have selected the Custom Map.\n");
    } else {
        printf("Invalid choice. Exiting the program.\n");
        return 1;
    }
    int choice = 0;
    while (choice != 5)
    {
        printMenu();
        printf("Enter your choice (1-5): ");
        scanf("%d", &choice);
    }
    return 0;
}

void printMenu()
{
    printf("\n--- Menu ---\n");
    printf("1. Display Adjacency Matrix\n");
    printf("2. Perform Depth-First Search (DFS)\n");
    printf("3. Perform Breadth-First Search (BFS)\n");
    printf("4. Find Shortest Path\n");
    printf("5. Exit\n");
}


● Source and destination locations for each road
● Starting location for BFS traversal
● Starting location for DFS traversa

