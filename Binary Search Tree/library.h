#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED
#include "binarySearchTree.h"

void PrintBook(Book book);

void ADD_BOOK();
void SEARCH_BOOK(int id);
void DELETE_BOOK(int id);
void DISPLAY_INORDER();
void FIND_MIN();
void FIND_MAX();
void FIND_PREDECESSOR(int id);
void FIND_SUCCESSOR(int id);
void DISPLAY_PREORDER();
void DISPLAY_POSTORDER();

#endif // LIBRARY_H_INCLUDED
