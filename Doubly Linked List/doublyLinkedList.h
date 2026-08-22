#ifndef DOUBLYLINKEDLIST_H_INCLUDED
#define DOUBLYLINKEDLIST_H_INCLUDED

// Define structure of a node
struct Node
{
    int DestinationID;
    char DestinationName[50];
    char City[50];
    int Quantity;
    char PlannedDate[50]; // Warning the date should be in the format "YYYY-MM-DD"
    int NoOfDays;
    int EstimatedBudget;
    char ModeOfTransport[50];
    struct Node *prev;
    struct Node *next;
};

extern struct Node *head;

void traverseReverse(struct Node *head);

void insertAtBeginning(struct Node **head, int DestinationID,
    char DestinationName[], char City[], int Quantity, char PlannedDate[], int NoOfDays, int EstimatedBudget,
    char ModeOfTransport[]);

void insertAtEnd(struct Node **head, int DestinationID,
    char DestinationName[], char City[], int Quantity, char PlannedDate[], int NoOfDays, int EstimatedBudget,
    char ModeOfTransport[]);

void insertAtPosition(struct Node **head, int DestinationID,
    char DestinationName[], char City[], int Quantity, char PlannedDate[], int NoOfDays, int EstimatedBudget,
    char ModeOfTransport[], int position);


void deleteAtBeginning(struct Node **head);
void deleteAtEnd(struct Node **head);
void deleteAtPosition(struct Node**head, int position);

// Function to search for a node by DestinationID and DestinationName
struct Node *searchNode(struct Node *head, int DestinationID, char DestinationName[]);
// Function to get the position of a node by DestinationID and DestinationName
int getPosition(struct Node *head, int DestinationID, char DestinationName[]);
int countNodes(struct Node *head);
struct Node *getNodeAtPosition(struct Node *head, int position);

#endif // DOUBLYLINKEDLIST_H_INCLUDED
