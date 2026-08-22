#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include <time.h>

void addTask();
void executeTask();
void operate();

int main()
{
    srand(time(NULL));  // seed with current time
    int n;
    printf("Enter a number(N) of Tasks to be run: ");
    scanf("%d", &n);

    for(int i = 0; i < (int) n/2; i++){
        operate();
    }
    return 0;
}


void operate(){
    // Randomly add or execute a task
    if (rand() % 2) addTask();
    else executeTask();
}
void addTask()
{
    int r = rand();
    printf("Inserting %d into the queue.\n", r);
    enqueue(r);
}

void executeTask()
{
    printf("Executing a task hence dequeued a element.\n");
    dequeue();
}
