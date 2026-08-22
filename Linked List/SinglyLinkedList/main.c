#include <stdio.h>
#include <stdlib.h>
#include "food.h"
#include "singlyLinkedList.h"
int main()
{

    printf("------Food Menu APP--------\n");
    printf("1. Add Food\n");
    printf("2. Remove Food\n");
    printf("3. Search Food\n");
    printf("4. Update Quantity\n");
    printf("5. Display All Food\n");
    printf("6. Display Expired Food\n");
    printf("7. Display Expiring Soon Food\n");
    printf("8. Count Categories\n");
    printf("9. Earliest Expiry\n");
    printf("10. Exit\n");

    int choice = 0;
    while (1)
    {
        printf("Enter your choice: ");
            scanf("%d", &choice);

        if (choice < 1 || choice > 10)
        {
            printf("Invalid choice.\n");
            continue;
        }
        switch (choice)
        {
            int foodID;
            char foodName[50];
            char category[50];
            int quantity;
            char purchaseDate[11];
            char expiryDate[11];
            char storageLocation[50];
        case 1:
            printf("Adding Food...\n");
            printf("Enter FoodID: ");
            scanf("%d", &foodID);
            printf("Enter Food Name: ");
            scanf("%s", foodName);
            printf("Enter Category: ");
            scanf("%s", category);
            printf("Enter Quantity: ");
            scanf("%d", &quantity);
            printf("Enter Purchase Date (YYYY-MM-DD): ");
            scanf("%s", purchaseDate);
            printf("Enter Expiry Date (YYYY-MM-DD): ");
            scanf("%s", expiryDate);
            printf("Enter Storage Location: ");
            scanf("%s", storageLocation);
            ADD_FOOD(foodID, foodName, category, quantity, purchaseDate, expiryDate, storageLocation);
            break;
        case 2:
            printf("Removing Food...\n");
            printf("Enter FoodID or Food Name to remove: ");
            scanf("%d", &foodID);
            printf("Enter Food Name: ");
            scanf("%s", foodName);
            REMOVE_FOOD(foodID, foodName);
            break;
        case 3:
            printf("Searching Food...\n");
            printf("Enter FoodID or Food Name to search: ");
            scanf("%d", &foodID);
            printf("Enter Food Name: ");
            scanf("%s", foodName);
            SEARCH_FOOD(foodID, foodName);
            break;
        case 4:
            printf("Updating Quantity...\n");
            printf("Enter FoodID or Food Name to update quantity: ");
            scanf("%d", &foodID);
            printf("Enter Food Name: ");
            scanf("%s", foodName);
            printf("Enter new quantity: ");
            int newQuantity;
            scanf("%d", &newQuantity);
            UPDATE_QUANTITY(foodID, foodName, newQuantity);
            break;
        case 5:
            printf("Displaying All Food...\n");
            DISPLAY_ALL();
            break;
        case 6:
            printf("Displaying Expired Food...\n");
            DISPLAY_EXPIRED();
            break;
        case 7:
            printf("Displaying Expiring Soon Food...\n");
            DISPLAY_EXPIRING_SOON();
            break;
        case 8:
            printf("Counting Categories...\n");
            CATEGORY_COUNT();
            break;
        case 9:
            printf("Finding Earliest Expiry...\n");
            EARLIEST_EXPIRY();
            break;
        case 10:
            printf("Exiting...\n");
            exit(0);
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
    }
}

    return 0;
}
