#ifndef JOURNEY_H_INCLUDED
#define JOURNEY_H_INCLUDED


// Temporary structure to hold destination details when updating or adding new destination
typedef struct Details
{
    int DestinationID;
    char DestinationName[50];
    char City[50];
    int Quantity;
    char PlannedDate[50]; // Warning the date should be in the format "YYYY-MM-DD"
    int NoOfDays;
    int EstimatedBudget;
    char ModeOfTransport[50];
} tempDetails;

void getDetails(tempDetails *details);

void ADD_DESTINATION();
void REMOVE_DESTINATION(int DestinationID, char DestinationName[]);
void SEARCH_DESTINATION(int DestinationID, char DestinationName[]);
void UPDATE_DESTINATION(int DestinationID, char DestinationName[]);

void DISPLAY_FORWARD();
void DISPLAY_REVERSE();
void NEXT_DESTINATION(int position);
void PREVIOUS_DESTINATION(int position);
int TOTAL_TRIP_BUDGET();

int searchPosition(int DestinationID, char DestinationName[]);

#endif // JOURNEY_H_INCLUDED
