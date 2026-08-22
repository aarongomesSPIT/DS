#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "FlightReservationSystem.h"
#include "avlTree.h"

// Initially, the AVL is empty
struct Node *root = NULL;

// Function to populate and return a Book struct
Flight populateFlight(int BookingID, const char *name, int FlightNo, const char *Destination)
{
    Flight f;
    f.BookingID = BookingID;

    strncpy(f.Name, name, sizeof(f.Name) - 1);
    f.Name[sizeof(f.Name) - 1] = '\0';

    f.FlightNumber = FlightNo;

    strncpy(f.Destination, Destination, sizeof(f.Destination) - 1);
    f.Destination[sizeof(f.Destination) - 1] = '\0';
    return f;
}

void PrintFlight(Flight f)
{
    printf("Flight Details:\n");
    printf("\t ID: %d\n", f.BookingID);
    printf("\t Name: %s\n", f.Name);
    printf("\t Number: %d\n", f.FlightNumber);
    printf("\t Destination: %s\n", f.Destination);
}

void INSERT_BOOKING()
{
    printf("Enter the Booking ID: ");
    int id;
    scanf("%d", &id);

    if (searchFlight(id) != NULL)
    {
        printf("Booking ID: %d already exists in the AVL.\n", id);
        return;
    }
    printf("Enter the Passanger Name: ");
    char name[50];
    scanf("%s", name);
    int no;
    printf("Enter the Flight Number: ");
    scanf("%d", &no);
    char destination[50];
    printf("Enter the Destination: ");
    scanf("%s", destination);

    Flight f = populateFlight(id, name, no, destination);
    root = insertNode(root, f);
    printf("Flight added successfully\n");

}

void SEARCH_BOOKING(int id)
{
    struct Node *node = searchNode(root, id);
    if (node == NULL)
    {
        printf("Flight ID: %d not found in the AVL.\n", id);
        return;
    }
    PrintFlight(node->key);

}

Flight *searchFlight(int id)
{
    struct Node *node = searchNode(root, id);
    if (node == NULL)
    {
        return NULL;
    }
    return &(node->key);
}

void CANCEL_BOOKING(int id)
{
    root = deleteNode(root, id);
}

void DISPLAY_INORDER()
{
    inOrder(root);
}

void DISPLAY_PREORDER()
{
    preOrder(root);
}

void DISPLAY_POSTORDER()
{
    postOrder(root);
}

void FIND_MIN()
{
    root = findMin(root);
    PrintFlight(root->key);
}
