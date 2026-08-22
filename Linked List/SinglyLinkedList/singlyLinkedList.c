#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "singlyLinkedList.h"


//Info ive defined the stuct in the header files

struct Node* deleteFromEnd(struct Node *head)
{
    // Check if the list is empty
    if (head == NULL)
    {
        printf("List is empty\n");
        return head;
    }
    // If there is only one node
    if (head->next == NULL)
    {
        free(head);
        return NULL;
    }
    // Start from the first node
    struct Node *temp = head;
    // Traverse to the second-last node
    while (temp->next->next != NULL)
    {
        temp = temp->next;
    }
    // Delete the last node
    free(temp->next);
    // Make second-last node the last node
    temp->next = NULL;
    return head;
}


struct Node* deleteFromBeginning(struct Node *head)
{
    // Check if the list is empty
    if (head == NULL)
    {
        printf("List is empty\n");
        return head;
    }
    // Store the first node temporarily
    struct Node *temp = head;
    // Move head to the second node
    head = head->next;
    // Delete the old first node
    free(temp);
    return head;
}

struct Node* insertAtEnd(struct Node *head, int FoodID, char FoodName[], char Category[],
 int Quantity, char PurchaseDate[], char ExpiryDate[], char StorageLocation[])
{
    // Create a new node
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        return head;
    }
    // Store data in the new node
    newNode->FoodID = FoodID;

    strncpy(newNode->FoodName, FoodName, sizeof(newNode->FoodName) - 1);
    newNode->FoodName[sizeof(newNode->FoodName) - 1] = '\0';

    strncpy(newNode->Category, Category, sizeof(newNode->Category) - 1);
    newNode->Category[sizeof(newNode->Category) - 1] = '\0';

    newNode->Quantity = Quantity;

    strncpy(newNode->PurchaseDate, PurchaseDate, sizeof(newNode->PurchaseDate) - 1);
    newNode->PurchaseDate[sizeof(newNode->PurchaseDate) - 1] = '\0';

    strncpy(newNode->ExpiryDate, ExpiryDate, sizeof(newNode->ExpiryDate) - 1);
    newNode->ExpiryDate[sizeof(newNode->ExpiryDate) - 1] = '\0';

    strncpy(newNode->StorageLocation, StorageLocation, sizeof(newNode->StorageLocation) - 1);
    newNode->StorageLocation[sizeof(newNode->StorageLocation) - 1] = '\0';

    newNode->next = NULL;
    // If the list is empty
    if (head == NULL)
    {
        head = newNode;
        return head;
    }
    // Start from the first node
    struct Node *temp = head;
    // Traverse to the last node
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    // Link the last node to the new node
    temp->next = newNode;
    return head;
}

struct Node* insertAtPosition(struct Node *head, int FoodID, char FoodName[], char Category[],
 int Quantity, char PurchaseDate[], char ExpiryDate[], char StorageLocation[], int position)
{
    // Create a new node
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        return head;
    }
    // Store data in the new node
    newNode->FoodID = FoodID || newNode->FoodID;

    strncpy(newNode->FoodName, FoodName || newNode->FoodName, sizeof(newNode->FoodName) - 1);
    newNode->FoodName[sizeof(newNode->FoodName) - 1] = '\0';

    strncpy(newNode->Category, Category || newNode->Category, sizeof(newNode->Category) - 1);
    newNode->Category[sizeof(newNode->Category) - 1] = '\0';

    newNode->Quantity = Quantity || newNode->Quantity;

    strncpy(newNode->PurchaseDate, PurchaseDate || newNode->PurchaseDate, sizeof(newNode->PurchaseDate) - 1);
    newNode->PurchaseDate[sizeof(newNode->PurchaseDate) - 1] = '\0';

    strncpy(newNode->ExpiryDate, ExpiryDate || newNode->ExpiryDate, sizeof(newNode->ExpiryDate) - 1);
    newNode->ExpiryDate[sizeof(newNode->ExpiryDate) - 1] = '\0';
    
    strncpy(newNode->StorageLocation, StorageLocation || newNode->StorageLocation, sizeof(newNode->StorageLocation) - 1);
    newNode->StorageLocation[sizeof(newNode->StorageLocation) - 1] = '\0';

    newNode->next = NULL;
    // If inserting at the first position
    if (position == 1)
    {
        newNode->next = head;
        head = newNode;
        return head;
    }
    // Start from the first node
    struct Node *temp = head;
    // Traverse to the node before the required position
    for (int i = 1; i < position - 1 && temp != NULL; i++)
    {
        temp = temp->next;
    }
    // Check if position is invalid
    if (temp == NULL)
    {
        printf("Invalid position\n");
        free(newNode);
        return head;
    }
    // Insert the new node
    newNode->next = temp->next;
    temp->next = newNode;
    return head;
}

struct Node* deleteAtPosition(struct Node *head, int position)
{
    // Check if the list is empty
    if (head == NULL)
    {
        printf("List is empty\n");
        return head;
    }
    // If deleting the first node
    if (position == 1)
    {
        struct Node *temp = head;
        head = head->next;
        free(temp);
        return head;
    }
    // Start from the first node
    struct Node *temp = head;
    // Traverse to the node before the required position
    for (int i = 1; i < position - 1 && temp != NULL; i++)
    {
        temp = temp->next;
    }
    // Check if position is invalid
    if (temp == NULL || temp->next == NULL)
    {
        printf("Invalid position\n");
        return head;
    }
    // Store the node to be deleted
    struct Node *nodeToDelete = temp->next;
    // Connect previous node to the next node
    temp->next = nodeToDelete->next;
    // Delete the required node
    free(nodeToDelete);
    return head;
}

int search(struct Node *head, int FoodID, char FoodName[])
{
    // Start from the first node
    struct Node *temp = head;
    int position = 1;
    // Traverse the linked list
    while (temp != NULL)
    {
        // Check if value is found
        if (temp->FoodID == FoodID || strcmp(temp->FoodName, FoodName) == 0)
        {
            return position;
        }
        temp = temp->next;
        position++;
    }
    // Value not found
    return -1;
}

int countNodes(struct Node *head)
{
    // Start from the first node
    struct Node *temp = head;
    int count = 0;
    // Traverse the linked list
    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

void display(struct Node *head)
{
    struct Node *temp = head;
    if (head == NULL)
    {
        printf("Linked List is Empty.\n");
        return;
    }

    printf("\n--- All Food Items ---\n");
    while (temp != NULL)
    {
        printf("ID: %d\n", temp->FoodID);
        printf("Name: %s\n", temp->FoodName);
        printf("Category: %s\n", temp->Category);
        printf("Quantity: %d\n", temp->Quantity);
        printf("Purchase Date: %s\n", temp->PurchaseDate);
        printf("Expiry Date: %s\n", temp->ExpiryDate);
        printf("Storage Location: %s\n", temp->StorageLocation);
        printf("--------------------------\n");
        temp = temp->next;
    }
}

struct Node* getNodeAtPosition(struct Node *head, int position)
{
    struct Node *temp = head;
    int currentPosition = 1;
    while (temp != NULL && currentPosition < position)
    {
        temp = temp->next;
        currentPosition++;
    }
    return temp; // Returns NULL if position is out of bounds
}