#ifndef FLIGHTRESERVATIONSYSTEM_H_INCLUDED
#define FLIGHTRESERVATIONSYSTEM_H_INCLUDED

typedef struct {
    int BookingID;
    char Name[50];
    int FlightNumber;
    char Destination[50];
} Flight;

Flight populateFlight(int BookingID, const char *name, int FlightNo, const char *Destination);
void PrintFlight(Flight f);

void INSERT_BOOKING();
void SEARCH_BOOKING(int id);
Flight *searchFlight(int id);
void CANCEL_BOOKING(int id);
void DISPLAY_INORDER();
void DISPLAY_PREORDER();
void DISPLAY_POSTORDER();
void FIND_MIN();

#endif // FLIGHTRESERVATIONSYSTEM_H_INCLUDED
