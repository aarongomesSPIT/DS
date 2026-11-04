
#include <stdlib.h>
#define MAX 100

// Declare a stack
int stack[MAX];

//The top element
int top = -1;

int pop()
{
    int item;
    if(isEmpty())
    {
        printf("Stack Underflow\n");
        return -1;
    }
    item = stack[top];
    top--;
    return item;
}


int isEmpty()
{
    if(top == -1) return 1;
    return 0;
}

int isFull(){
    if(top == MAX-1) return 1;
    return 0;
}

void push(int item)
{
    if(isFull())
    {
        printf("Stack Overflow\n");
        return;
    }
    top++;
    stack[top] = item;
}

int peek()
{
    if(isEmpty())
    {
        printf("Stack Empty\n");
        return -1;
    }
    return stack[top];
}

void display()
{
    int i;
    if(isEmpty())
    {
        printf("Stack Empty\n");
        return;
    }
    for(i = top; i >= 0; i--)
    {
        printf("%d ", stack[i]);
    }
    printf("\n");
}

void operation(int opt)
{
    printf("Rand no: %d\n", opt);
    switch (opt){

        case 1:
             printf("Stack is Empty?: ");
             printf("%d\n", isEmpty());
             break;
        case 2:
            printf("Stack is Full?: ");
            printf("%d\n", isFull());
            break;
        case 3:
            printf("The top of stack is: %d\n",peek());
            break;
        case 4:
            printf("PUSH AND DISPLAY:");
            push(rand() % 100);
            display();
            break;
        case 5:
            printf("POP:");
            pop();
            display();
            break;
        case 6:
            printf("DISPLAY:");
            display();
        default:
            printf("The defasilt\n");
        }
}
