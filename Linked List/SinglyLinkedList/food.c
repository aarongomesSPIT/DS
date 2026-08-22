#include "singlyLinkedList.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>


struct Node *head = NULL;

void ADD_FOOD(int FoodID, char FoodName[], char Category[],
 int Quantity, char PurchaseDate[], char ExpiryDate[], char StorageLocation[])
{
    head = insertAtEnd(head, FoodID, FoodName, Category, Quantity, PurchaseDate, ExpiryDate, StorageLocation);
}
void REMOVE_FOOD(int FoodID, char FoodName[]){

    int position = search(head, FoodID, FoodName);
    if (position != -1) {
        head = deleteAtPosition(head, position);
    } else {
        printf("Food item not found.\n");
    }
}
void SEARCH_FOOD(int FoodID, char FoodName[]){
    int position = search(head, FoodID, FoodName);
    if (position != -1)
    {
            struct Node *node = getNodeAtPosition(head, position);
            if (node != NULL) {
                printf("Food item found:\n");
                printf("ID: %d\n", node->FoodID);
                printf("Name: %s\n", node->FoodName);
                printf("Category: %s\n", node->Category);
                printf("Quantity: %d\n", node->Quantity);
                printf("Purchase Date: %s\n", node->PurchaseDate);
                printf("Expiry Date: %s\n", node->ExpiryDate);
                printf("Storage Location: %s\n", node->StorageLocation);
            } else {
                printf("Food item not found.\n");
            }
    }
    else
    {
        printf("Food item not found.\n");
    }
}
void UPDATE_QUANTITY(int FoodID, char FoodName[], int newQuantity)
{
    int position = search(head, FoodID, FoodName);
    if (position != -1)
    {
        struct Node *node = getNodeAtPosition(head, position);
        if (node != NULL) {
            node->Quantity = newQuantity;
            printf("Quantity updated successfully.\n");
        } else {
            printf("Food item not found.\n");
        }
    }
    else
    {
        printf("Food item not found.\n");
    }
}
void DISPLAY_ALL(){
    display(head);
}

void DISPLAY_EXPIRED() {
    if (head == NULL) {
        printf("The inventory is empty.\n");
        return;
    }

    char currentDate[11];
    printf("Enter current date (YYYY-MM-DD): ");
    scanf("%10s", currentDate);

    struct Node *temp = head;
    int found = 0;

    printf("\n--- Expired Food Items ---\n");
    while (temp != NULL) {
        // If ExpiryDate is strictly less than currentDate, it has expired
        if (strcmp(temp->ExpiryDate, currentDate) < 0) {
            printf("ID: %d | Name: %s | Expiry: %s | Location: %s\n",
                   temp->FoodID, temp->FoodName, temp->ExpiryDate, temp->StorageLocation);
            found = 1;
        }
        temp = temp->next;
    }

    if (!found) {
        printf("No expired food items found.\n");
    }
}

void DISPLAY_EXPIRING_SOON() {
    if (head == NULL) {
        printf("The inventory is empty.\n");
        return;
    }

    char currentDate[11];
    char targetYearMonth[8]; // To match "YYYY-MM"

    printf("Enter current date (YYYY-MM-DD): ");
    scanf("%10s", currentDate);

    // Extract the Year and Month (first 7 characters: "YYYY-MM")
    // to easily group items expiring in the same month/year period.
    strncpy(targetYearMonth, currentDate, 7);
    targetYearMonth[7] = '\0';

    struct Node *temp = head;
    int found = 0;

    printf("\n--- Food Items Expiring Soon (Same Month/Period) ---\n");
    while (temp != NULL) {
        // Condition 1: Expiry date is greater than or equal to today (not expired)
        // Condition 2: Expiry date matches the current year and month
        if (strcmp(temp->ExpiryDate, currentDate) >= 0 &&
            strncmp(temp->ExpiryDate, targetYearMonth, 7) == 0) {

            printf("ID: %d | Name: %s | Expiry: %s | Location: %s\n",
                   temp->FoodID, temp->FoodName, temp->ExpiryDate, temp->StorageLocation);
            found = 1;
        }
        temp = temp->next;
    }

    if (!found) {
        printf("No food items expiring soon for this period.\n");
    }
}

void CATEGORY_COUNT()
{
    printf("Number of categories: %d\n", countNodes(head));
}

void EARLIEST_EXPIRY() {
    if (head == NULL) {
        printf("The inventory is empty.\n");
        return;
    }

    struct Node *temp = head;
    struct Node *earliestNode = NULL;

    while (temp != NULL) {
        // Find the first valid node to initialize the comparison
        if (earliestNode == NULL) {
            earliestNode = temp;
        } else {
            // Compare expiry dates: if temp's expiry date is lexicographically
            // smaller than the current earliest, it means it's an earlier date.
            if (strcmp(temp->ExpiryDate, earliestNode->ExpiryDate) < 0) {
                earliestNode = temp;
            }
        }
        temp = temp->next;
    }

    if (earliestNode != NULL) {
        printf("--- Food Item with Earliest Expiry ---\n");
        printf("ID: %d | Name: %s | Expiry: %s | Location: %s\n",
               earliestNode->FoodID, earliestNode->FoodName,
               earliestNode->ExpiryDate, earliestNode->StorageLocation);
    }
}
