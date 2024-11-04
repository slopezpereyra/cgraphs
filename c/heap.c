#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

Heap* createHeap(u32 capacity) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->array = (HeapNode*)malloc(capacity * sizeof(HeapNode));
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

// Function to swap two nodes in the heap
void swap(HeapNode *a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Heap* heap, u32 i) {
    u32 smallest = i;
    u32 left = 2 * i + 1;
    u32 right = 2 * i + 2;

    // Check if the left child has a smaller value than the root
    if (left < heap->size && heap->array[left].value < heap->array[smallest].value)
        smallest = left;

    // Check if the right child has a smaller value than the smallest so far
    if (right < heap->size && heap->array[right].value < heap->array[smallest].value)
        smallest = right;

    // If the smallest is not the root, swap the root with the smallest
    if (smallest != i) {
        swap(&heap->array[i], &heap->array[smallest]);
        heapify(heap, smallest);
    }
}

void insert(Heap* heap, u32 label, u32 value) {
    // Insert the new element at the end
    if (heap->size >= heap->capacity) {
        printf("Cannot add element to heap: capacity is full\n");
        exit(1);
    }
    
    // Insert the new node at the end
    u32 i = heap->size++;
    heap->array[i].label = label;
    heap->array[i].value = value;

    // Fix the min heap property by moving the node up if needed
    while (i != 0 && heap->array[(i - 1) / 2].value > heap->array[i].value) {
        swap(&heap->array[i], &heap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Function to extract the minimum element from the heap (for min heap)
HeapNode extractMin(Heap* heap) {
    if (heap->size == 0) {
        printf("Heap is empty. Cannot extract minimum element.\n");
        return (HeapNode){0, -1};
    }

    // Store the root element
    HeapNode minNode = heap->array[0];
    // Replace the root with the last element
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    // Heapify the root
    heapify(heap, 0);
    return minNode;
}

void printHeap(Heap* heap) {
    printf("Heap elements:\n");
    for (u32 i = 0; i < heap->size; i++) {
        printf("Label: %d, Value: %d\n", heap->array[i].label, heap->array[i].value);
    }
    printf("\n");
}
