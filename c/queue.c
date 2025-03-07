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






/**
 * @file queue.c
 * @brief Implementation of a linked list-based queue.
 *
 * This file contains functions to manage a queue data structure using a linked
 * list. The queue allows enqueue, dequeue, and other utility operations.
 */

#include "queue.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Creates a new linked list node with the specified key.
 *
 * @param k The key to be stored in the new node.
 * @return A pointer to the newly created node.
 * @note Exits the program if memory allocation fails.
 */
struct QNode *newNode(u32 k) {
  struct QNode *temp = (struct QNode *)malloc(sizeof(struct QNode));
  if (temp == NULL) {
    printf("Error: malloc failed\n");
    exit(1);
  }
  temp->key = k;
  temp->next = NULL;
  return temp;
}

/**
 * @brief Creates an empty queue.
 *
 * @return A pointer to the newly created queue.
 * @note Exits the program if memory allocation fails.
 */
struct Queue *createQueue() {
  struct Queue *q = (struct Queue *)malloc(sizeof(struct Queue));
  if (q == NULL) {
    printf("Error: malloc failed\n");
    exit(1);
  }
  q->front = q->rear = NULL;
  q->count = 0;
  return q;
}

/**
 * @brief Adds a key to the end of the queue.
 *
 * @param q A pointer to the queue.
 * @param k The key to be added to the queue.
 */
void enQueue(struct Queue *q, u32 k) {
  struct QNode *temp = newNode(k);
  (q->count)++;

  if (q->rear == NULL) {
    q->front = q->rear = temp;
    return;
  }

  q->rear->next = temp;
  q->rear = temp;
}

/**
 * @brief Removes the key from the front of the queue.
 *
 * @param q A pointer to the queue.
 * @note Does nothing if the queue is empty.
 */
void deQueue(struct Queue *q) {
  if (q->front == NULL)
    return;

  (q->count)--;
  struct QNode *temp = q->front;
  q->front = q->front->next;

  if (q->front == NULL)
    q->rear = NULL;

  free(temp);
}

/**
 * @brief Removes and returns the key from the front of the queue.
 *
 * @param q A pointer to the queue.
 * @return The key at the front of the queue.
 * @note Assumes the queue is not empty.
 */
u32 pop(struct Queue *q) {
  u32 front = q->front->key;
  deQueue(q);
  return front;
}

/**
 * @brief Checks if the queue is empty.
 *
 * @param q A pointer to the queue.
 * @return true if the queue is empty, false otherwise.
 */
bool isEmpty(struct Queue *q) { return (q->front == NULL); }

/**
 * @brief Empties the queue and frees associated memory.
 *
 * @param q A pointer to the queue.
 */
void dumpQueue(struct Queue *q) {
  while (q->front != NULL) {
    deQueue(q);
  }
  free(q);
}

/**
 * @brief Compares two queues by their element count in ascending order.
 *
 * @param a Pointer to the first queue.
 * @param b Pointer to the second queue.
 * @return Negative if a has fewer elements than b, positive if a has more
 * elements than b, and zero if they are equal.
 */
int compareQueue(const void *a, const void *b) {
  struct Queue **queueA = (struct Queue **)a;
  struct Queue **queueB = (struct Queue **)b;

  return ((*queueA)->count - (*queueB)->count);
}

/**
 * @brief Compares two queues by their element count in descending order.
 *
 * @param a Pointer to the first queue.
 * @param b Pointer to the second queue.
 * @return Positive if a has fewer elements than b, negative if a has more
 * elements than b, and zero if they are equal.
 */
int compareQueueDescending(const void *a, const void *b) {
  struct Queue **queueA = (struct Queue **)a;
  struct Queue **queueB = (struct Queue **)b;

  return ((*queueB)->count - (*queueA)->count);
}
