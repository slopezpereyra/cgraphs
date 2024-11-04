#include <stdio.h>
#include <stdlib.h>
#include "graphStruct.h"


typedef struct {
    u32 label;
    u32 value;
} HeapNode;

typedef struct {
    HeapNode* array;
    u32 capacity;
    u32 size;
} Heap;


Heap* createHeap(u32 capacity);
void swap(HeapNode *a, HeapNode* b);
void heapify(Heap* heap, u32 i);
void insert(Heap* heap, u32 label, u32 value);
HeapNode extractMin(Heap* heap);
void printHeap(Heap* heap);
