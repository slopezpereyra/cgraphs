/**
 * @file api.c
 * @brief Min heap for {x, y} nodes. Designed for quick access to edges
 * ordered by weight in some weight graph algorithms (e.g. Prim's algorithm).
 * Achieved by storing in the node's label the index of the edge in the graph
 * and in its value its weight.
 */

#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Creates a heap of given capacity.
 *
 *
 * @return A pointer to the allocated heap.
 */
Heap *createHeap(u32 capacity) {
  Heap *heap = (Heap *)malloc(sizeof(Heap));
  heap->array = (HeapNode *)malloc(capacity * sizeof(HeapNode));
  heap->capacity = capacity;
  heap->size = 0;
  return heap;
}

/**
 * @brief Frees the memory allocated for the heap and its array.
 *
 * @param heap Pointer to the heap to be freed.
 */
void dumpHeap(Heap *heap) {
  free(heap->array);
  free(heap);
}

/**
 * @brief Swaps two nodes in the heap.
 *
 * @param a Pointer to the first heap node.
 * @param b Pointer to the second heap node.
 */
void swap(HeapNode *a, HeapNode *b) {
  HeapNode temp = *a;
  *a = *b;
  *b = temp;
}

/**
 * @brief Ensures the min-heap property for the heap starting from a specified
 * index.
 *
 * This function assumes that the subtrees rooted at the left and right children
 * of the given index `i` are min-heaps, but the element at `i` may violate the
 * min-heap property. It performs the necessary swaps to maintain the heap
 * structure.
 *
 * @param heap Pointer to the heap structure.
 * @param i Index of the element that may violate the min-heap property.
 */
void heapify(Heap *heap, u32 i) {
  u32 smallest = i;
  u32 left = 2 * i + 1;
  u32 right = 2 * i + 2;

  if (left < heap->size &&
      heap->array[left].value < heap->array[smallest].value)
    smallest = left;

  if (right < heap->size &&
      heap->array[right].value < heap->array[smallest].value)
    smallest = right;

  if (smallest != i) {
    swap(&heap->array[i], &heap->array[smallest]);
    heapify(heap, smallest);
  }
}

/**
 * @brief Inserts a new node with a specified label and value into the heap.
 *
 * The function inserts a new node at the end of the heap and then adjusts the
 * heap to maintain the min-heap property.
 *
 * @param heap Pointer to the heap structure.
 * @param label Label of the new node.
 * @param value Value of the new node.
 *
 * @note If the heap capacity is full, the function will print an error message
 * and terminate the program.
 */
void insert(Heap *heap, u32 label, u32 value) {
  if (heap->size >= heap->capacity) {
    printf("Cannot add element to heap: capacity is full\n");
    exit(1);
  }

  u32 i = heap->size++;
  heap->array[i].label = label;
  heap->array[i].value = value;

  while (i != 0 && heap->array[(i - 1) / 2].value > heap->array[i].value) {
    swap(&heap->array[i], &heap->array[(i - 1) / 2]);
    i = (i - 1) / 2;
  }
}

/**
 * @brief Extracts the minimum element from the heap.
 *
 * Removes and returns the root element of the heap (minimum value in a
 * min-heap). After removal, the heap is adjusted to maintain the min-heap
 * property.
 *
 * @param heap Pointer to the heap structure.
 * @return The minimum node in the heap, or a node with label 0 and value -1 if
 * the heap is empty.
 *
 * @note If the heap is empty, the function will print a warning message.
 */
HeapNode extractMin(Heap *heap) {
  if (heap->size == 0) {
    printf("Heap is empty. Cannot extract minimum element.\n");
    return (HeapNode){0, -1};
  }

  HeapNode minNode = heap->array[0];
  heap->array[0] = heap->array[heap->size - 1];
  heap->size--;
  heapify(heap, 0);
  return minNode;
}

/**
 * @brief Prints all elements in the heap.
 *
 * Outputs each element's label and value to the console in a readable format.
 *
 * @param heap Pointer to the heap structure.
 */
void printHeap(Heap *heap) {
  printf("Heap elements:\n");
  for (u32 i = 0; i < heap->size; i++) {
    printf("Label: %d, Value: %d\n", heap->array[i].label,
           heap->array[i].value);
  }
  printf("\n");
}
