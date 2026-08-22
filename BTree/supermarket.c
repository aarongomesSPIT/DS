#include <stdio.h>
#include <stdlib.h>
#include "supermarket.h"

int no_of_products = 0;
BTreeNode* root;

void printProduct(Product prd)
{
    printf("Product Barcode: %d, Quantity: %d\n", prd.bcode, prd.quantity);
}

void ADD_PRODUCT()
{
    printf("Enter the Product Barcode: ");
    int bcode;
    scanf("%d", &bcode);
    printf("Enter the stock quantity: ");
    int quantity;
    scanf("%d", &quantity);

    if (quantity < 0)
    {
        printf("Quantity cannot be negative.\n");
        return;
    }

    if (no_of_products == 0)
    {
        root = createNode(1);
    }

    Product key = {bcode, 0};
    if (search(root, key) != NULL)
    {
        printf("Product with barcode %d already exists.\n", bcode);
        return;
    }

    Product newProduct;
    newProduct.bcode = bcode;
    newProduct.quantity = quantity;
    insert(&root, newProduct);
    no_of_products++;

}

void SEARCH_PRODUCT()
{
    printf("Enter the Product Barcode to search: ");
    int bcode;
    scanf("%d", &bcode);
    Product key;
    key.bcode = bcode;
    key.quantity = 0; // Not used in search
    BTreeNode* result = search(root, key);
    if (result != NULL)
    {
        printf("Product with barcode %d found.\n", bcode);
        printProduct(result->keys[0]);
    }
    else
    {
        printf("Product with barcode %d not found.\n", bcode);
    }
}

void UPDATE_STOCK()
{
    printf("Enter the Product Barcode to update: ");
    int bcode;
    scanf("%d", &bcode);
    printf("Enter the new stock quantity: ");
    int quantity;
    scanf("%d", &quantity);

    Product oldKey;
    oldKey.bcode = bcode;
    oldKey.quantity = 0;

    Product newKey;
    newKey.bcode = bcode;
    newKey.quantity = quantity;

    update(root, oldKey, newKey);
}

void GENERATE_BILL()
{
    printf("Enter the Product Barcode to generate bill: ");
    int bcode;
    scanf("%d", &bcode);

    Product key;
    key.bcode = bcode;
    key.quantity = 0; // Not used in search
    BTreeNode* result = search(root, key);
    if (result != NULL)
    {
        printf("Generating bill for product with barcode %d.\n", bcode);
        printProduct(result->keys[0]);
    }
    else
    {
        printf("Product with barcode %d not found.\n", bcode);
    }
}

void DISPLAY_ALL_PRODUCTS()
{
    printf("Displaying all products in the supermarket...\n");

    traverse(root);
}