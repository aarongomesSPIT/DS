#ifndef SINGLYLINKEDLIST_H_INCLUDED
#define SINGLYLINKEDLIST_H_INCLUDED


// Structure of a Node
struct Node
{
    int FoodID;
    char FoodName[50];
    char Category[50];
    int Quantity;
    char PurchaseDate[50];  // Warning the date should be in the format "YYYY-MM-DD"
    char ExpiryDate[50];    // Warning the date should be in the format "YYYY-MM-DD"
    char StorageLocation[50];
    struct Node *next;
};


struct Node* deleteFromEnd(struct Node *head);

struct Node* deleteFromBeginning(struct Node *head);

struct Node* insertAtEnd(struct Node *head, int FoodID, char FoodName[], char Category[],
 int Quantity, char PurchaseDate[], char ExpiryDate[], char StorageLocation[]);

struct Node* insertAtPosition(struct Node *head, int FoodID, char FoodName[], char Category[],
 int Quantity, char PurchaseDate[], char ExpiryDate[], char StorageLocation[], int position);

struct Node* deleteAtPosition(struct Node *head, int position);

int search(struct Node *head, int FoodID, char FoodName[]);

int countNodes(struct Node *head);

void display(struct Node *head);

struct Node* getNodeAtPosition(struct Node *head, int position);

#endif // SINGLYLINKEDLIST_H_INCLUDED
