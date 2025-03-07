/**MIT License
*
*Copyright (c) 2024 Santiago López Pereyra
*
*santiagolopezpereyra@gmail.com
*
*Permission is hereby granted, free of charge, to any person obtaining a copy
*of this software and associated documentation files (the "Software"), to deal
*in the Software without restriction, including without limitation the rights
*to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*copies of the Software, and to permit persons to whom the Software is
*furnished to do so, subject to the following conditions:
*
*The above copyright notice and this permission notice shall be included in all
*copies or substantial portions of the Software.
*
*The software is provided "as is", without warranty of any kind, express or
*implied, including but not limited to the warranties of merchantability,
*Fitness for a particular purpose and noninfringement. In no event shall the
*authors or copyright holders be liable for any claim, damages or other
*liability, whether in an action of contract, tort or otherwise, arising from,
*out of or in connection with the software or the use or other dealings in the
*software.
 */

#include "graphStruct.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  u32 label;
  u32 value;
} HeapNode;

typedef struct {
  HeapNode *array;
  u32 capacity;
  u32 size;
} Heap;

Heap *createHeap(u32 capacity);
void swap(HeapNode *a, HeapNode *b);
void heapify(Heap *heap, u32 i);
void insert(Heap *heap, u32 label, u32 value);
HeapNode extractMin(Heap *heap);
void printHeap(Heap *heap);
void dumpHeap(Heap *heap);
