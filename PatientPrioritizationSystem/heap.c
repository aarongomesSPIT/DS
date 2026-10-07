#include <stdio.h>

// Helper swap function
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify Up for Max Heap
void heapifyUp(int A[], int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (A[i] > A[parent]) {
            swap(&A[i], &A[parent]);
            i = parent;
        } else {
            break;
        }
    }
}

// Heapify Down for Max Heap
void heapifyDown(int A[], int i, int size) {
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (left < size && A[left] > A[largest])
            largest = left;
        if (right < size && A[right] > A[largest])
            largest = right;

        if (largest != i) {
            swap(&A[i], &A[largest]);
            i = largest;
        } else {
            break;
        }
    }
}

// Max Heap Insertion
void insertMaxHeap(int A[], int *size, int x) {
    A[*size] = x;
    (*size)++;
    heapifyUp(A, *size - 1);
}

// Min Heap Insertion
void insertMinHeap(int A[], int *size, int x) {
    A[*size] = x;
    (*size)++;
    int i = *size - 1;

    while (i > 0 && A[(i - 1) / 2] > A[i]) {
        swap(&A[i], &A[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Max Heap Deletion
int deleteMaxHeap(int A[], int *size) {
    if (*size <= 0) {
        printf("Heap Underflow\n");
        return -1;
    }

    int max = A[0];
    A[0] = A[*size - 1];
    (*size)--;

    if (*size > 0) {
        heapifyDown(A, 0, *size);
    }

    return max;
}

// Extract-Min (Min Heap Deletion)
int extractMin(int A[], int *size) {
    if (*size == 0) {
        printf("Heap Underflow\n");
        return -1;
    }

    int min = A[0];
    A[0] = A[*size - 1];
    (*size)--;

    int i = 0;
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < *size && A[left] < A[smallest])
            smallest = left;
        if (right < *size && A[right] < A[smallest])
            smallest = right;

        if (smallest != i) {
            swap(&A[i], &A[smallest]);
            i = smallest;
        } else {
            break;
        }
    }

    return min;
}