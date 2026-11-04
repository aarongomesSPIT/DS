#define MAX 100
int queue[MAX];
// Variables to store index of front and rear element
int front = -1;
int rear = -1;


int isEmpty()
{
    if(front == -1) return 1;
    return 0;
}

int isFull(){
    if(rear == MAX - 1) return 1;
    return 0;
}


void enqueue(int value)
{
    if(isFull())
    {
        printf("Queue Overflow\n");
        return;
    }
    if(isEmpty())
    {
        front = 0;
    }
    rear++;
    queue[rear] = value;
    printf("Element inserted successfully.\n");
}

int dequeue(){
    int value;
    if(isEmpty())
    {
        printf("Queue Underflow\n");
        return -1;
    }
    value = queue[front];
    if(front == rear)
    {
        front = -1;
        rear = -1;
    }
    else front++;
    return value;
}

int peek()
{
    if(isEmpty())
    {
        printf("Queue is Empty\n");
        return -1;
    }
    return queue[front];
}

void display()
{
    if(isEmpty())
    {
        printf("Queue is Empty\n");
        return;
    }
    printf("Queue Elements: ");

    for(int i = front; i <= rear; i++)
    {
        printf("%d ", queue[i]);
    }
    printf("\n");
}
