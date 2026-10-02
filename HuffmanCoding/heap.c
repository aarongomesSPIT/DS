#include <stdio.h>

// Helper swap function
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Simplified Heapify Up (Works for Max Heap)
void heapifyUp(int A[], int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (A[i] > A[parent]) { // For Max Heap (use < for Min Heap)
            swap(&A[i], &A[parent]);
            i = parent;
        } else {
            break;
        }
    }
}

// Simplified Heapify Down (Works for Max Heap)
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

// Simplified Max Heap Insertion (using heapifyUp)
void insertMaxHeap(int A[], int *size, int x) {
    A[*size] = x; // Insert at end
    (*size)++;    // Increase size
    heapifyUp(A, *size - 1); // Adjust position
}

// Simplified Min Heap Insertion
void insertMinHeap(int A[], int *size, int x) {
    A[*size] = x;
    (*size)++;
    int i = *size - 1;

    while (i > 0 && A[(i - 1) / 2] > A[i]) {
        swap(&A[i], &A[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Simplified Max Heap Deletion (using heapifyDown)
int deleteMaxHeap(int A[], int *size) {
    if (*size <= 0) {
        printf("Heap Underflow\n");
        return -1;
    }

    int max = A[0];            // Store root
    A[0] = A[*size - 1];       // Replace with last element
    (*size)--;                 // Reduce size

    if (*size > 0) {
        heapifyDown(A, 0, *size); // Restore heap
    }

    return max;                // Return deleted max element
}

// Simplified Extract-Min (Min Heap Deletion using heapifyDown logic)
int extractMin(int A[], int *size) {
    if (*size == 0) {
        printf("Heap Underflow\n");
        return -1;
    }

    int min = A[0];            // Store root
    A[0] = A[*size - 1];       // Replace with last element
    (*size)--;                 // Reduce size

    // Restore Min Heap
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

    return min; // Return minimum element
}
