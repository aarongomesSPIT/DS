#include "doublyLinkedList.h"
#include "journey.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node *head = NULL;
struct Node *newNode, *temp;
void createList(int n) {


    int DestinationID;
    char DestinationName[50];
    char City[50];
    int Quantity;
    char PlannedDate[50]; // Warning the date should be in the format "YYYY-MM-DD"
    int NoOfDays;
    int EstimatedBudget;
    char ModeOfTransport[50];
    for (int i = 1; i <= n; i++)
    {
        // Allocate memory for new node
        newNode = (struct Node *)malloc(sizeof(struct Node));
        printf("Enter data for node %d: ", i);

        printf("Destination ID: ");
        scanf("%d", &DestinationID);
        printf("Destination Name: ");
        scanf(" %[^\n]%*c", DestinationName);
        printf("City: ");
        scanf(" %[^\n]%*c", City);
        printf("Quantity: ");
        scanf("%d", &Quantity);
        printf("Planned Date (YYYY-MM-DD): ");
        scanf(" %[^\n]%*c", PlannedDate);
        printf("Number of Days: ");
        scanf("%d", &NoOfDays);
        printf("Estimated Budget: ");
        scanf("%d", &EstimatedBudget);
        printf("Mode of Transport: ");
        scanf(" %[^\n]%*c", ModeOfTransport);

        newNode->DestinationID = DestinationID;

        strncpy(newNode->DestinationName, DestinationName, sizeof(newNode->DestinationName) - 1);
        newNode->DestinationName[sizeof(newNode->DestinationName) - 1] = '\0';

        strncpy(newNode->City, City, sizeof(newNode->City) - 1);
        newNode->City[sizeof(newNode->City) - 1] = '\0';

        newNode->Quantity = Quantity;

        strncpy(newNode->PlannedDate, PlannedDate, sizeof(newNode->PlannedDate) - 1);
        newNode->PlannedDate[sizeof(newNode->PlannedDate) - 1] = '\0';

        newNode->NoOfDays = NoOfDays;

        newNode->EstimatedBudget = EstimatedBudget;

        strncpy(newNode->ModeOfTransport, ModeOfTransport, sizeof(newNode->ModeOfTransport) - 1);
        newNode->ModeOfTransport[sizeof(newNode->ModeOfTransport) - 1] = '\0';


        newNode->prev = NULL;
        newNode->next = NULL;
        // If list is empty
        if (head == NULL)
        {
            head = newNode;
            temp = newNode;
        }
        else
        {
            // Connect new node with last node
            temp->next = newNode;
            newNode->prev = temp;
            // Move temp to new last node
            temp = newNode;
        }
    }
}

void displayList() {
    struct Node *temp = head;
    printf("\nDoubly Linked List: ");
    while (temp != NULL)
    {
        printf("%d", temp->DestinationID);
        if (temp->next != NULL)
        printf(" <-> ");
        temp = temp->next;
    }
    printf("\n");
}

void traverseReverse(struct Node *head) {
    // Check if list is empty
    if (head == NULL)
    {
        printf("List is empty!\n");
        return;
    }
    struct Node *temp = head;
    // Move to the last node
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    // Traverse backwards using prev
    while (temp != NULL)
    {
        printf("%d ", temp->DestinationID);
        temp = temp->prev;
    }
}

void insertAtBeginning(struct Node **head, int DestinationID,
    char DestinationName[], char City[], int Quantity, char PlannedDate[], int NoOfDays, int EstimatedBudget,
    char ModeOfTransport[])
{
    // Create a new node
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->DestinationID = DestinationID;

    strncpy(newNode->DestinationName, DestinationName, sizeof(newNode->DestinationName) - 1);
    newNode->DestinationName[sizeof(newNode->DestinationName) - 1] = '\0';

    strncpy(newNode->City, City, sizeof(newNode->City) - 1);
    newNode->City[sizeof(newNode->City) - 1] = '\0';

    newNode->Quantity = Quantity;

    strncpy(newNode->PlannedDate, PlannedDate, sizeof(newNode->PlannedDate) - 1);
    newNode->PlannedDate[sizeof(newNode->PlannedDate) - 1] = '\0';

    newNode->NoOfDays = NoOfDays;

    newNode->EstimatedBudget = EstimatedBudget;

    strncpy(newNode->ModeOfTransport, ModeOfTransport, sizeof(newNode->ModeOfTransport) - 1);
    newNode->ModeOfTransport[sizeof(newNode->ModeOfTransport) - 1] = '\0';

    newNode->prev = NULL;
    newNode->next = *head;
    // If list is not empty
    if (*head != NULL)
    {
        (*head)->prev = newNode;
    }
    // Make new node the head
    *head = newNode;
}

void insertAtEnd(struct Node **head, int DestinationID,
    char DestinationName[], char City[], int Quantity, char PlannedDate[], int NoOfDays, int EstimatedBudget,
    char ModeOfTransport[])
{
    // Create a new node
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->DestinationID = DestinationID;

    strncpy(newNode->DestinationName, DestinationName, sizeof(newNode->DestinationName) - 1);
    newNode->DestinationName[sizeof(newNode->DestinationName) - 1] = '\0';

    strncpy(newNode->City, City, sizeof(newNode->City) - 1);
    newNode->City[sizeof(newNode->City) - 1] = '\0';

    newNode->Quantity = Quantity;

    strncpy(newNode->PlannedDate, PlannedDate, sizeof(newNode->PlannedDate) - 1);
    newNode->PlannedDate[sizeof(newNode->PlannedDate) - 1] = '\0';

    newNode->NoOfDays = NoOfDays;

    newNode->EstimatedBudget = EstimatedBudget;

    strncpy(newNode->ModeOfTransport, ModeOfTransport, sizeof(newNode->ModeOfTransport) - 1);
    newNode->ModeOfTransport[sizeof(newNode->ModeOfTransport) - 1] = '\0';


    newNode->next = NULL;
    // If list is empty
    if (*head == NULL)
    {
        newNode->prev = NULL;
        *head = newNode;
        return;
    }
    // Traverse to the last node
    struct Node *temp = *head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    // Connect new node with last node
    temp->next = newNode;
    newNode->prev = temp;
}


void insertAtPosition(struct Node **head, int DestinationID,
    char DestinationName[], char City[], int Quantity, char PlannedDate[], int NoOfDays, int EstimatedBudget,
    char ModeOfTransport[], int position)
{
    // Insert at beginning if position is 1
    if (position == 1)
    {
        insertAtBeginning(head, DestinationID,
            DestinationName, City, Quantity, PlannedDate, NoOfDays, EstimatedBudget,
            ModeOfTransport);
        return;
    }
    // Traverse to position - 1
    struct Node *temp = *head;
    for (int i = 1; i < position - 1 && temp != NULL; i++)
    {
        temp = temp->next;
    }
    // Check for invalid position
    if (temp == NULL)
    {
        printf("Invalid position!\n");
        return;
    }
    // Create a new node
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->DestinationID = DestinationID;

    strncpy(newNode->DestinationName, DestinationName, sizeof(newNode->DestinationName) - 1);
    newNode->DestinationName[sizeof(newNode->DestinationName) - 1] = '\0';

    strncpy(newNode->City, City, sizeof(newNode->City) - 1);
    newNode->City[sizeof(newNode->City) - 1] = '\0';

    newNode->Quantity = Quantity;

    strncpy(newNode->PlannedDate, PlannedDate, sizeof(newNode->PlannedDate) - 1);
    newNode->PlannedDate[sizeof(newNode->PlannedDate) - 1] = '\0';

    newNode->NoOfDays = NoOfDays;

    newNode->EstimatedBudget = EstimatedBudget;

    strncpy(newNode->ModeOfTransport, ModeOfTransport, sizeof(newNode->ModeOfTransport) - 1);
    newNode->ModeOfTransport[sizeof(newNode->ModeOfTransport) - 1] = '\0';

    // Set links of new node
    newNode->next = temp->next;
    newNode->prev = temp;
    // Update previous pointer of next node
    if (temp->next != NULL)
    {
        temp->next->prev = newNode;
    }
    // Update next pointer of previous node
    temp->next = newNode;
}


void deleteAtBeginning(struct Node **head)
{
    // Check if list is empty
    if (*head == NULL)
    {
        printf("List is empty!\n");
        return;
    }
    // Store the first node
    struct Node *temp = *head;
    // Move head to the next node
    *head = (*head)->next;
    // If list is not empty after deletion
    if (*head != NULL)
    {
        (*head)->prev = NULL;
    }
    // Delete the old first node
    free(temp);
}

void deleteAtEnd(struct Node **head)
{
    // Check if list is empty
    if (*head == NULL)
    {
        printf("List is empty!\n");
        return;
    }
    // Store head in temp
    struct Node *temp = *head;
    // If there is only one node
    if (temp->next == NULL)
    {
        *head = NULL;
        free(temp);
        return;
    }
    // Traverse to the last node
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    // Make previous node the last node
    temp->prev->next = NULL;
    // Delete the last node
    free(temp);
}

void deleteAtPosition(struct Node **head, int position)
{
    // Check if list is empty
    if (*head == NULL)
    {
        printf("List is empty!\n");
        return;
    }
    // Delete first node if position is 1
    if (position == 1)
    {
        deleteAtBeginning(head);
        return;
    }
    struct Node *temp = *head;
    // Traverse to the node to be deleted
    for (int i = 1; i < position && temp != NULL; i++)
    {
        temp = temp->next;
    }
    // Check for invalid position
    if (temp == NULL)
    {
        printf("Invalid position!\n");
        return;
    }
    // Connect previous node to next node
    temp->prev->next = temp->next;
    // Connect next node to previous node
    if (temp->next != NULL)
    {
        temp->next->prev = temp->prev;
    }
    // Delete the node
    free(temp);
}

int countNodes(struct Node *head)
{
    int count = 0;
    struct Node *temp = head;
    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

struct Node *searchNode(struct Node *head, int DestinationID, char DestinationName[])
{
    struct Node *temp = head;
    while (temp != NULL)
    {
        if (temp->DestinationID == DestinationID || strcmp(temp->DestinationName, DestinationName) == 0)
        {
            return temp; // Node found
        }
        temp = temp->next;
    }
    return NULL; // Node not found
}

int getPosition(struct Node *head, int DestinationID, char DestinationName[])
{
    struct Node *temp = head;
    int position = 1;
    while (temp != NULL)
    {
        if (temp->DestinationID == DestinationID || strcmp(temp->DestinationName, DestinationName) == 0)
        {
            return position; // Node found
        }
        temp = temp->next;
        position++;
    }
    return -1; // Node not found
}

struct Node *getNodeAtPosition(struct Node *head, int position)
{
    struct Node *temp = head;
    int currentPosition = 1;
    while (temp != NULL)
    {
        if (currentPosition == position)
        {
            return temp; // Node found
        }
        temp = temp->next;
        currentPosition++;
    }


    return NULL; // Node not found
}
