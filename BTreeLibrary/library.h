#ifndef SUPERMARKET_H_INCLUDED
#define SUPERMARKET_H_INCLUDED
#include <string.h>

#include "btree.h"

void readCSV(const char *filename);
void pushBook(int isbn, const char *title, const char *author, int stock);
void ADD_BOOK();
void SEARCH_BOOK();
void BORROW_BOOK();
void RETURN_BOOK();
void DISPLAY_ALL_BOOKS();

#endif // SUPERMARKET_H_INCLUDED
