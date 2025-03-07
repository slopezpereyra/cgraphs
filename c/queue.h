/** MIT License
 *
 * Copyright (c) 2024 Santiago López Pereyra
 *
 * santiagolopezpereyra@gmail.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * The software is provided "as is", without warranty of any kind, express or
 * implied, including but not limited to the warranties of merchantability,
 * fitness for a particular purpose, and noninfringement. In no event shall the
 * authors or copyright holders be liable for any claim, damages, or other
 * liability, whether in an action of contract, tort, or otherwise, arising from,
 * out of or in connection with the software or the use or other dealings in the
 * software.
 */






#include <stdbool.h>
#include <stdint.h>
typedef uint32_t u32;

// A linked list (LL) node to store a queue entry
struct QNode {
  u32 key;
  struct QNode *next;
};

// The queue, front stores the front node of LL and rear
// stores the last node of LL
struct Queue {
  u32 count;
  struct QNode *front, *rear;
};

// A utility function to create a new linked list node.
struct QNode *newNode(u32 k);

// A utility function to create an empty queue
struct Queue *createQueue();

// The function to add a key k to q
void enQueue(struct Queue *q, u32 k);

// Function to remove a key from given queue q
void deQueue(struct Queue *q);

u32 pop(struct Queue *q);

bool isEmpty(struct Queue *q);

void dumpQueue(struct Queue *q);

int compareQueue(const void *a, const void *b);
int compareQueueDescending(const void *a, const void *b);
