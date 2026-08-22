#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main()
{
    printf("Enter a number N to be the size of the stack: ");
    int n;
    scanf("%d", &n);
    int stack[n];

    printf("1: Game start?\n"
            "2: Comleted game?\n"
            "3. Last Move?\n"
            "4. Move\n"
            "5. Go Back\n"
            "6. See Moves\n");
               int x;
    for (int i = 0; i < 10; i++){

        printf("Select a number from 1 to 6:");
        scanf("%d", &x);
        operation(x);
    }
    return 0;
}
