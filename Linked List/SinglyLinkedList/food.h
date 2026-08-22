#ifndef FOOD_H_INCLUDED
#define FOOD_H_INCLUDED

void ADD_FOOD(int FoodID, char FoodName[], char Category[],
 int Quantity, char PurchaseDate[], char ExpiryDate[], char StorageLocation[]);
void REMOVE_FOOD(int FoodID, char FoodName[]);
void SEARCH_FOOD(int FoodID, char FoodName[]);
void UPDATE_QUANTITY(int FoodID, char FoodName[], int NewQuantity);
void DISPLAY_ALL();
void DISPLAY_EXPIRED();
void DISPLAY_EXPIRING_SOON();
void CATEGORY_COUNT();
void EARLIEST_EXPIRY();

#endif // FOOD_H_INCLUDED
