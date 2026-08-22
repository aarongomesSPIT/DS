#include "doublyLinkedList.h"
#include "journey.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>

void getDetails(tempDetails *details)
{
    printf("Destination ID: ");
    scanf("%d", &details->DestinationID);
    printf("Destination Name: ");
    scanf(" %[^\n]%*c", details->DestinationName);
    printf("City: ");
    scanf(" %[^\n]%*c", details->City);
    printf("Quantity: ");
    scanf("%d", &details->Quantity);
    printf("Planned Date (YYYY-MM-DD): ");
    scanf(" %[^\n]%*c", details->PlannedDate);
    printf("Number of Days: ");
    scanf("%d", &details->NoOfDays);
    printf("Estimated Budget: ");
    scanf("%d", &details->EstimatedBudget);
    printf("Mode of Transport: ");
    scanf(" %[^\n]%*c", details->ModeOfTransport);
}

void ADD_DESTINATION()
{
    tempDetails details;
    getDetails(&details); // Get destination details from user input
    insertAtEnd(&head, details.DestinationID, details.DestinationName, details.City, details.Quantity, details.PlannedDate, details.NoOfDays, details.EstimatedBudget, details.ModeOfTransport);
}

void REMOVE_DESTINATION(int DestinationID, char DestinationName[])
{
    int position = getPosition(head, DestinationID, DestinationName);
    if (position == -1)
    {
        printf("Destination not found!\n");
        return;
    }
    else
    {
        deleteAtPosition(&head, position);
        printf("Destination removed successfully!\n");
    }
}

void SEARCH_DESTINATION(int DestinationID, char DestinationName[])
{
    struct Node *result = searchNode(head, DestinationID, DestinationName);
    if (result != NULL)
    {
        printf("Destination found!\n");
        printf("Destination ID: %d\n", result->DestinationID);
        printf("Destination Name: %s\n", result->DestinationName);
        printf("City: %s\n", result->City);
        printf("Quantity: %d\n", result->Quantity);
        printf("Planned Date: %s\n", result->PlannedDate);
        printf("Number of Days: %d\n", result->NoOfDays);
        printf("Estimated Budget: %d\n", result->EstimatedBudget);
        printf("Mode of Transport: %s\n", result->ModeOfTransport);
    }
    else
    {
        printf("Destination not found!\n");
    }
}
void UPDATE_DESTINATION(int DestinationID, char DestinationName[])
{
    tempDetails details;
    getDetails(&details); // Get updated destination details from user input
    struct Node *result = searchNode(head, DestinationID, DestinationName);
    if (result != NULL)
    {
        result->DestinationID = details.DestinationID;
        strncpy(result->DestinationName, details.DestinationName, sizeof(result->DestinationName) - 1);
        result->DestinationName[sizeof(result->DestinationName) - 1] = '\0';
        strncpy(result->City, details.City, sizeof(result->City) - 1);
        result->City[sizeof(result->City) - 1] = '\0';
        result->Quantity = details.Quantity;
        strncpy(result->PlannedDate, details.PlannedDate, sizeof(result->PlannedDate) - 1);
        result->PlannedDate[sizeof(result->PlannedDate) - 1] = '\0';
        result->NoOfDays = details.NoOfDays;
        result->EstimatedBudget = details.EstimatedBudget;
        strncpy(result->ModeOfTransport, details.ModeOfTransport, sizeof(result->ModeOfTransport) - 1);
        result->ModeOfTransport[sizeof(result->ModeOfTransport) - 1] = '\0';
        printf("Destination updated successfully!\n");
    }
}


void DISPLAY_FORWARD()
{
    int position = 1;
    struct Node *temp = head;
    while (temp != NULL)
    {
        struct Node *details = getNodeAtPosition(head, position);
        printf("Position %d:\n", position);
        printf("Destination ID: %d\n", details->DestinationID);
        printf("Destination Name: %s\n", details->DestinationName);
        printf("City: %s\n", details->City);
        printf("Quantity: %d\n", details->Quantity);
        printf("Planned Date: %s\n", details->PlannedDate);
        printf("Number of Days: %d\n", details->NoOfDays);
        printf("Estimated Budget: %d\n", details->EstimatedBudget);
        printf("Mode of Transport: %s\n", details->ModeOfTransport);
        printf("\n");
        temp = temp->next;
        position++;
    }
}
void DISPLAY_REVERSE()
{
    int position = countNodes(head);
    struct Node *temp = head;
    // Traverse to the last node
    while (temp != NULL && temp->next != NULL)
    {
        temp = temp->next;
    }
    // Traverse backwards and display details
    while (temp != NULL)
    {
        printf("Position %d:\n", position);
        printf("Destination ID: %d\n", temp->DestinationID);
        printf("Destination Name: %s\n", temp->DestinationName);
        printf("City: %s\n", temp->City);
        printf("Quantity: %d\n", temp->Quantity);
        printf("Planned Date: %s\n", temp->PlannedDate);
        printf("Number of Days: %d\n", temp->NoOfDays);
        printf("Estimated Budget: %d\n", temp->EstimatedBudget);
        printf("Mode of Transport: %s\n", temp->ModeOfTransport);
        printf("\n");
        temp = temp->prev;
        position--;
    }
}
void NEXT_DESTINATION(int position)
{
    struct Node *temp = getNodeAtPosition(head, position + 1);
    if (temp != NULL)
    {
        printf("Destination ID: %d\n", temp->DestinationID);
        printf("Destination Name: %s\n", temp->DestinationName);
        printf("City: %s\n", temp->City);
        printf("Quantity: %d\n", temp->Quantity);
        printf("Planned Date: %s\n", temp->PlannedDate);
        printf("Number of Days: %d\n", temp->NoOfDays);
        printf("Estimated Budget: %d\n", temp->EstimatedBudget);
        printf("Mode of Transport: %s\n", temp->ModeOfTransport);
    }
    else
    {
        printf("Destination not found!\n");
    }
}
void PREVIOUS_DESTINATION(int position)
{
    struct Node *temp = getNodeAtPosition(head, position - 1);
    if (temp != NULL)
    {
        printf("Destination ID: %d\n", temp->DestinationID);
        printf("Destination Name: %s\n", temp->DestinationName);
        printf("City: %s\n", temp->City);
        printf("Quantity: %d\n", temp->Quantity);
        printf("Planned Date: %s\n", temp->PlannedDate);
        printf("Number of Days: %d\n", temp->NoOfDays);
        printf("Estimated Budget: %d\n", temp->EstimatedBudget);
        printf("Mode of Transport: %s\n", temp->ModeOfTransport);
    }
    else
    {
        printf("Destination not found!\n");
    }
}

int TOTAL_TRIP_BUDGET()
{
    int totalBudget = 0;
    struct Node *temp = head;
    while (temp != NULL)
    {
        totalBudget += temp->EstimatedBudget; // Convert EstimatedBudget to integer and add to total
        temp = temp->next;
    }
    return totalBudget;

}


int searchPosition(int DestinationID, char DestinationName[])
{
    int position = getPosition(head, DestinationID, DestinationName);

    return position;
}
